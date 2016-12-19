
#include "ActiveMQTCReceiver.h"

ActiveMQTCReceiver::~ActiveMQTCReceiver() {
  cleanup();
}

void ActiveMQTCReceiver::close() {
  this->cleanup();
}
 
void* ActiveMQTCReceiver::thread() {
  
  while (true) {
    
    if (!isConnected) {

      std::cout << "ActiveMQTCReceiver:" << " connecting" <<  std::endl;
      try {
	
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
	
	// Create a Connection
	connection = connectionFactory->createConnection();
	connection->start();
	connection->setExceptionListener(this);
	
	// Create a Session
	if (this->sessionTransacted == true) {
	  session = connection->createSession(Session::SESSION_TRANSACTED);
	} else {
	  session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	
	// Create the destination (Topic or Queue)
	if (useTopic) {
	  destination = session->createTopic("TC");
	} else {
	  destination = session->createQueue("TC");
	}
	
	// Create a MessageConsumer from the Session to the Topic or Queue
	consumer = session->createConsumer(destination);
	
	consumer->setMessageListener(this);

	isConnected = true;
	std::cout << "ActiveMQTCReceiver:" << " connected" <<  std::endl;
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cout << "ActiveMQTCReceiver: exception detected" << std::endl;
	session = NULL;
	isConnected = false;
      }
    }
    else {
      sleep(3);
    }
  }
return NULL;
}

// Called from the consumer since this class is a registered MessageListener.
void ActiveMQTCReceiver::onMessage(const cms::Message* message) {
  
  static int count = 0;
  
  try {
    count++;
    const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
    string text = "";
    
    if (textMessage != NULL) {
      text = textMessage->getText();
      // handleTcMsg(m_procRoverCtrl->GetCanal(), (char *) text.c_str());
    } else {
      text = "NOT A TEXTMESSAGE!";
    }
    printf("Message #%d Received: %s\n", count, text.c_str());
    
  } catch (CMSException& e) {
    e.printStackTrace();
    isConnected = false;
    return; 
  }
  
  // Commit all messages.
  if (this->sessionTransacted) {
    session->commit();
  }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
 void ActiveMQTCReceiver::onException(const CMSException& ex AMQCPP_UNUSED) {
   isConnected = false;
 }



void ActiveMQTCReceiver::cleanup() {
  if (connection != NULL) {
    try {
      connection->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  // Destroy resources.
  try {
    delete destination;
    destination = NULL;
    delete consumer;
    consumer = NULL;
    delete session;
    session = NULL;
    delete connection;
    connection = NULL;
  } catch (CMSException& e) {
    e.printStackTrace();
  }
}
