
#include <stdio.h>

#include "ActiveMQAdmin.h"
// #include "ProcRoverCtrl.h"

#include "linuxOrcc.h"
// #include "canal.h"
#include "GeneralSupportLibrary.h"

// extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
// extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

ActiveMQAdmin::~ActiveMQAdmin() noexcept(true) {
  cleanup();
}

void ActiveMQAdmin::close() {
  this->cleanup();
}

int ActiveMQAdmin::initAdmin(char *mgmnt_url) {
  return OK;
}

int ActiveMQAdmin::sendSimAliveMsg() {
  if (sessionAdmin == NULL) {
    return ERROR;
  }
  try {
    std::auto_ptr<TextMessage> message(sessionAdmin->createTextMessage("ROVER.STATUS"));
    message->setStringProperty("STATUSMSG", "ROVERALIVE (1)");
    message->setStringProperty("ACTION", "ROVER.STATUS");
    message->setStringProperty("IPINFO", "localhost-test");
    message->setStringProperty("HOSTNAME", "localhost-test");
    
    if (producerInternalStatus != NULL) {
      producerInternalStatus->send(message.get());
    }
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cerr << "ActiveMQAdmin - exception detected" << std::endl;
    sessionAdmin = NULL;
    producerInternalStatus = NULL;
    isConnected = false;
  }
}

void* ActiveMQAdmin::thread() {
  
  while (true) {
    
    if (!isConnected) {

      std::cout << "ActiveMQAdmin:" << " connecting" <<  std::endl;
      try {
	
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
	
	// Create a Connection
	connectionAdmin = connectionFactory->createConnection();
	if (connectionAdmin == NULL) {
	  std::cerr << "ActiveMQAdmin - connectionAdmin is null" << std::endl;
	  return NULL;
	}
	connectionAdmin->start();
	
	// Create a Session
	if (this->sessionTransacted) {
	  sessionAdmin = connectionAdmin->createSession(Session::SESSION_TRANSACTED);
	}
	else {
	  sessionAdmin = connectionAdmin->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	
	if (sessionAdmin != NULL) {
	  // create the 'internal status' topic    
	  string internal_status_topic("ROVER.STATUS");
	
	  destinationInternalStatus = sessionAdmin->createTopic(internal_status_topic);
	  if (destinationInternalStatus != NULL) {
	    // Create a MessageProducer from the Session to the Topic or Queue
	    producerInternalStatus = sessionAdmin->createProducer(destinationInternalStatus);
	    if (producerInternalStatus != NULL) {
	      producerInternalStatus->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	      
	      std::cout << "ActiveMQAdmin:" << " connected" <<  std::endl;
	      isConnected = true;
	    }
	  }
	}
	if (!isConnected) {
	  std::cout << "ActiveMQAdmin:" << " error" <<  std::endl;
	  return NULL;
	}
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cout << "ActiveMQAdmin: exception detected" << std::endl;
	sessionAdmin = NULL;
	producerInternalStatus = NULL;
	isConnected = false;
	sleep(3);
      }
    }
    else {
      sendSimAliveMsg(); 
      sleep(2);
    }
  }
  return NULL;
}

void ActiveMQAdmin::cleanup() {
  
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
    if ( producerInternalStatus != NULL) {
      delete producerInternalStatus;
      producerInternalStatus = NULL;
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
 
