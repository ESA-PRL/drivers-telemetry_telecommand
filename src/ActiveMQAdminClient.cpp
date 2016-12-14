
#include <stdio.h>
#include <thread> 
#include <unistd.h>

#include "GeneralSupportLibrary.h"
#include "ActiveMQAdminClient.h"

ActiveMQAdminClient::ActiveMQAdminClient(int numMessages, 
					 bool useTopic, 
					 bool sessionTransacted) :
  connectionAdmin(NULL),
  sessionAdmin(NULL),
  destinationInternalStatus(NULL),
  numMessages(numMessages),
  useTopic(useTopic),
  sessionTransacted(sessionTransacted),
  isConnected(false)
{	
    
    FILE* configFile;
    if ((configFile = fopen("./activeMQ.conf", "r")) == NULL) {
      std::cout << "activeMQ.conf config file not identified" 
		<< std::endl;
      return ;
    }
    
    if (GeneralSupport::ReadString(configFile, (char *)"SIMULATOR_USER_NAME", 
				   simUserName) == ERROR) {
      return ;
    }
    
    // set the management queue url
    if (GeneralSupport::ReadString(configFile, (char *)"MANAGEMENT_MQ_SERVER_URL", 
				   mqManagementServerURL) == ERROR) {
      return ;
    }

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

ActiveMQAdminClient::~ActiveMQAdminClient(){
  cleanup();
}

void ActiveMQAdminClient::close() {
  this->cleanup();
}

int ActiveMQAdminClient::sendSimAliveMsg() {
  if (sessionAdmin == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionAdmin->createTextMessage("ROVER.STATUS"));
  message->setStringProperty("STATUSMSG", "ROVERALIVE (1)");
  message->setStringProperty("ACTION", "ROVER.STATUS");
  message->setStringProperty("IPINFO", "localhost-test");
  message->setStringProperty("HOSTNAME", "localhost-test");

  try {
    if (producerInternalStatus != NULL) {
      producerInternalStatus->send(message.get());
    }
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cout << "ActiveMQAdminClient - exception detected while sending message" << std::endl;
    sessionAdmin = NULL;
    producerInternalStatus = NULL;
    isConnected = false;
  }
}

void* ActiveMQAdminClient::thread() {

  while (true) {
    
    if (!isConnected) {
    
      try {
	std::string broker_uri =
	  "failover:(tcp://" + string(mqManagementServerURL) +
	  ")?initialReconnectDelay=10" +
	  "&maxReconnectDelay=100" +
	  "&useExponentialBackOff=false" +
	  "&maxReconnectAttempts=1" +
	  "&startupMaxReconnectAttempts=1" +
	  "&timeout=100"; 
	
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
	
	// Create a Connection
	std::cout << "ActiveMQAdminClient - before createConnection" << std::endl;
	connectionAdmin = connectionFactory->createConnection();
	if (connectionAdmin == NULL) {
	  std::cout << "ActiveMQAdminClient - connectionAdmin is null" << std::endl;
	  return NULL;
	}
	connectionAdmin->start();
	
	// Create a Session
	if (sessionTransacted) {
	  sessionAdmin = connectionAdmin->createSession(Session::SESSION_TRANSACTED);
	} else {
	  sessionAdmin = connectionAdmin->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	
	if (sessionAdmin == NULL) {
	  std::cout << "ActiveMQAdminClient - sessionAdmin is null" << std::endl;
	  return NULL;
	}
	// create the 'internal status' topic    
	string internal_status_topic("ROVER.STATUS");
	
	destinationInternalStatus = sessionAdmin->createTopic(internal_status_topic);
	if (destinationInternalStatus == NULL) {
	  std::cout << "ActiveMQAdminClient - destinationInternalStatus is null" << std::endl;
	  return NULL;
	}
	
	// Create a MessageProducer from the Session to the Topic or Queue
	producerInternalStatus = sessionAdmin->createProducer(destinationInternalStatus);
	if (producerInternalStatus == NULL) {
	  std::cout << "ActiveMQAdminClient - producerInternalStatus is null" << std::endl;
	  return NULL;
	}
	producerInternalStatus->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	
	isConnected = true;
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cout << "ActiveMQAdminClient: connection failed - retrying to connect" << std::endl;
	sessionAdmin = NULL;
	producerInternalStatus = NULL;
	
	isConnected = false;
	
      }
    }
    else {
      sleep(3);
    }
  }
  return NULL;
}

void ActiveMQAdminClient::cleanup() {
  
  if (connectionAdmin != NULL) {
    try {
      connectionAdmin->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  // Destroy resources.
  try {
    if ( destinationInternalStatus != NULL) {
      delete destinationInternalStatus;
      destinationInternalStatus = NULL;
    }
    if ( sessionAdmin != NULL) {
      delete sessionAdmin;
      sessionAdmin = NULL;
    }
    if ( connectionAdmin != NULL) {
      delete connectionAdmin;
      connectionAdmin = NULL;
    }
  } catch (CMSException& e) {
    e.printStackTrace();
  }
}
 
