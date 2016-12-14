
#include <stdio.h>
#include <unistd.h>

#include "ActiveMQMonitorClient.h"
#include "GeneralSupportLibrary.h"

//extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
//extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

ActiveMQMonitorClient::ActiveMQMonitorClient(int numMessages, 
					     bool useTopic, 
					     bool sessionTransacted,
					     string topic_str) :
  connectionMonitor(NULL),
  sessionMonitor(NULL),
  destinationMonitoring(NULL),
  producerMonitoring(NULL),
  numMessages(numMessages),
  useTopic(useTopic),
  sessionTransacted(sessionTransacted),
  isConnected(false),
  topicname(topic_str)
{

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

    createThread();
}
      

ActiveMQMonitorClient::~ActiveMQMonitorClient(){
  cleanup();
}

void ActiveMQMonitorClient::close() {
  this->cleanup();
}


int ActiveMQMonitorClient::sendMsg(const char *msg_text) {
  if (sessionMonitor == NULL) {
    return ERROR;
  }

  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionMonitor->createTextMessage(msg_text));
  message->setStringProperty("JOBID", sim_job_str);
  message->setStringProperty("STATUS", "SIMALIVE");
  try {
    if (producerMonitoring != NULL) {
      producerMonitoring->send( message.get()); // message.get()
    }
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cout << "ActiveMQMonitorClient - exception detected while sending message" << std::endl;
    isConnected = false;
  }
}

void* ActiveMQMonitorClient::thread() {
  
  while (true) {
    
    if (!isConnected) {
      
      try {
	string broker_uri("tcp://"+ string(mqMonitoringServerURL) +"?timeout=3000");
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
	
	// Create a Connection
	connectionMonitor = connectionFactory->createConnection();
	if (connectionMonitor == NULL) {
	  std::cerr << "ActiveMQMonitorClient - connection is null" << std::endl;
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
	  std::cerr << "ActiveMQMonitorClient - sessionMonitor is null" << std::endl;
	  return NULL;
	}
	
	string sim_version_id_str(simJobId);
	
	ostringstream convert;
	convert << simVersionId ;
	string sim_id_str = convert.str();
	// create the 'monitoring' topic
	// string monitoring_topic("SIMULATOR." + sim_id_str + ".MONITORING");
	string monitoring_topic(topicname);
	
	
	// std::to_string(simJobId) + "
	
	destinationMonitoring = sessionMonitor->createTopic(monitoring_topic);
	if (destinationMonitoring == NULL) {
	  std::cerr << "ActiveMQMonitorClient - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	
	
	// Create a MessageProducer from the Session to the Topic or Queue
	producerMonitoring = sessionMonitor->createProducer(destinationMonitoring);
	if (producerMonitoring == NULL) {
	  std::cerr << "ActiveMQMonitorClient - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	producerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cerr << "ActiveMQMonitorClient - exception detected" << std::endl;
	sessionMonitor = NULL;
	producerMonitoring = NULL;
	isConnected = false;
	
      }
    }
    else {
      sleep(3);
    }
  }
  return NULL;
}


void ActiveMQMonitorClient::cleanup() {
  
  if (connectionMonitor != NULL) {
    try {
      connectionMonitor->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
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
}
 
