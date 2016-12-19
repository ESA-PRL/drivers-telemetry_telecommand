
#include <stdio.h>
#include <unistd.h>

#include "ActiveMQTMSender.h"
#include "GeneralSupportLibrary.h"

//extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
//extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

ActiveMQTMSender::ActiveMQTMSender(int numMessages, 
					     bool useTopic, 
					     bool sessionTransacted,
					     string topic_str) :
  connectionMonitor(NULL),
  sessionMonitor(NULL), 
  numMessages(numMessages),
  useTopic(useTopic),
  sessionTransacted(sessionTransacted),
  isConnected(false),
  topicname(topic_str)
{

    strcpy(mqMonitoringServerURL, "192.168.200.236:9009");
/*
    FILE* configFile;
    char configFileName[1024];
    sprintf(configFileName, "./activeMQ.conf");
    if ((configFile = fopen(configFileName, "r")) == NULL) {
      std::cerr << configFileName << "activeMQ.conf file not identified" 
		<< std::endl;
      return ;
    }
    
    // set the user name
    if (GeneralSupport::ReadString(configFile, (char *)"SIMULATOR_USER_NAME", 
				   simUserName) == ERROR) {
      return ;
    }
    
    // set the monitor queue url
    if (GeneralSupport::ReadString(configFile, (char *)"MONITORING_MQ_SERVER_URL", 
				   mqMonitoringServerURL) == ERROR) {
      return ;
    }
    
    // get the job id
    if (GeneralSupport::ReadString(configFile, (char *)"SIMULATOR_JOB_ID", 
				   simJobId) == ERROR) {
      return ;
    }
    
    if (GeneralSupport::read_int(configFile, (char *)"SIMULATOR_ID", 
				 &simVersionId) == ERROR) {
      return ;
    }
*/
    createThread();
}
      

ActiveMQTMSender::~ActiveMQTMSender(){
  cleanup();
}

void ActiveMQTMSender::close() {
  this->cleanup();
}

void* ActiveMQTMSender::thread() {
  
  while (true) {
    
    if (!isConnected) {
      
      std::cout << "ActiveMQTMSender:" << " connecting" <<  std::endl;
      try {
	string broker_uri("tcp://"+ string(mqMonitoringServerURL) +"?timeout=3000");
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
	
	// Create a Connection
	connectionMonitor = connectionFactory->createConnection();
	if (connectionMonitor == NULL) {
	  std::cerr << "ActiveMQTMSender - connection is null" << std::endl;
	  return NULL;
	}
	connectionMonitor->start();
	
	// Create a Session
	if (this->sessionTransacted) {
	  sessionMonitor = connectionMonitor->createSession(Session::SESSION_TRANSACTED);
	} else {
	  sessionMonitor = connectionMonitor->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	
	if (sessionMonitor == NULL) {
	  std::cerr << "ActiveMQTMSender - sessionMonitor is null" << std::endl;
	  return NULL;
	}
	
 
	string gncexoter_str("GNC_STATE");
	string mast_str("MAST_STATE");
	string pancam_str("PANCAM_STATE");
	string sa_str("SA_STATE");

	gncexoterDestinationMonitoring = sessionMonitor->createTopic(gncexoter_str);
	if (gncexoterDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	gncexoterProducerMonitoring = sessionMonitor->createProducer(gncexoterDestinationMonitoring);
	if (gncexoterProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	gncexoterProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	mastDestinationMonitoring = sessionMonitor->createTopic(mast_str);
	if (mastDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	mastProducerMonitoring = sessionMonitor->createProducer(mastDestinationMonitoring);
	if (mastProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	mastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
  	
	pancamDestinationMonitoring = sessionMonitor->createTopic(pancam_str);
	if (pancamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pancamProducerMonitoring = sessionMonitor->createProducer(pancamDestinationMonitoring);
	if (pancamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pancamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	saDestinationMonitoring = sessionMonitor->createTopic(sa_str);
	if (saDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	saProducerMonitoring = sessionMonitor->createProducer(saDestinationMonitoring);
	if (saProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	saProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
 

	std::cout << "ActiveMQTMSender:" << " connected" <<  std::endl;
	isConnected = true;
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cerr << "ActiveMQTMSender - exception detected" << std::endl;
	sessionMonitor = NULL; 
	isConnected = false;
	
      }
    }
    else {
      sleep(3);
    }
  }
  return NULL;
}


void ActiveMQTMSender::cleanup() {
  
  if (connectionMonitor != NULL) {
    try {
      connectionMonitor->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  /*
  // Destroy resources.
  try {
    if ( producerMonitoring != NULL) {
      delete producerMonitoring;
      producerMonitoring = NULL;
    }
    if ( sessionMonitor != NULL) {
      delete sessionMonitor;
      sessionMonitor = NULL;
    }
    if ( connectionMonitor != NULL) {
      delete connectionMonitor;
      connectionMonitor = NULL;
    }
  } catch (CMSException& e) {
    e.printStackTrace();
  }
  */
}
 
