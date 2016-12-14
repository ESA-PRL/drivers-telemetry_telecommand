
#include <stdio.h>
#include <unistd.h>

#include "ActiveMQFilesClient.h"
#include "GeneralSupportLibrary.h"

//extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
//extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

ActiveMQFilesClient::ActiveMQFilesClient(int numMessages, 
		      bool useTopic, 
		      bool sessionTransacted) :
  connectionFilesTextMsg(NULL),
  sessionFilesTextMsg(NULL),
  destinationFilesTextMsg(NULL),
  producerFilesTextMsg(NULL),
  numMessages(numMessages),
  useTopic(useTopic),
  sessionTransacted(sessionTransacted),
  isConnected(false)
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
				   mqFilesTextMsgServerURL) == ERROR) {
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
      

ActiveMQFilesClient::~ActiveMQFilesClient(){
  cleanup();
}

void ActiveMQFilesClient::close() {
  this->cleanup();
}

int ActiveMQFilesClient::sendStartMsg(const char *msg_text) {
  if (sessionFilesTextMsg == NULL) {
    return ERROR;
  }

  std::auto_ptr<TextMessage> message(sessionFilesTextMsg->createTextMessage(msg_text));
  message->setStringProperty("FILETYPE", "IMAGE");
  message->setStringProperty("STREAMQUEUENAME", "TLM.STREAM_1");
  try {
  if (producerFilesTextMsg != NULL) {
    producerFilesTextMsg->send( message.get()); 
  }
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cout << "ActiveMQFilesClient - exception detected while sending message" << std::endl;
    isConnected = false;
  }
}

int ActiveMQFilesClient::sendMsg(const char *msg_text) {
  if (sessionFilesTextMsg == NULL) {
    return ERROR;
  }

  ActiveMQStreamMessage streamMsg;
  
  std::vector<unsigned char> data;
  data.push_back( 2 );
  data.push_back( 4 );
  data.push_back( 8 );
  data.push_back( 16 );
  data.push_back( 32 );
  std::vector<unsigned char> readData( data.size() );

  streamMsg.writeBytes( data );
  streamMsg.reset();


  // std::auto_ptr<ActiveMQBlobMessage> blob_message(sessionFiles->createBlobMessage(msg_text));

  std::auto_ptr<TextMessage> message(sessionFilesTextMsg->createTextMessage(msg_text));
  message->setStringProperty("FILETYPE", "IMAGE");
  message->setStringProperty("STREAMQUEUENAME", "TLM.STREAM_1");
  try {
  if (producerFilesTextMsg != NULL) {
    // producerFilesTextMsg->send(&streamMsg); // message.get()
    producerFilesTextMsg->send( message.get()); // message.get()
  }
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cout << "ActiveMQFilesClient - exception detected while sending message" << std::endl;
    isConnected = false;
  }
}

void* ActiveMQFilesClient::thread() {
  
  while (true) {
    
    if (!isConnected) {
      
      try {
	string broker_uri("tcp://"+ string(mqFilesTextMsgServerURL) +"?timeout=3000");
	string broker_uri_file("tcp://192.168.1.50:8161?timeout=3000");

	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFileFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri_file));
	
	// Create a Connection
	connectionFilesTextMsg = connectionFactory->createConnection();
	if (connectionFilesTextMsg == NULL) {
	  std::cerr << "ActiveMQFilesClient - connection is null" << std::endl;
	  return NULL;
	}
	connectionFilesTextMsg->start();
	

	// Create a Connection
	connectionFiles = connectionFileFactory->createConnection();
	if (connectionFiles == NULL) {
	  std::cerr << "ActiveMQFilesClient - connection is null" << std::endl;
	  return NULL;
	}
	connectionFiles->start();
	
	// Create a Session
	if (this->sessionTransacted) {
	  sessionFilesTextMsg = connectionFilesTextMsg->createSession(Session::SESSION_TRANSACTED);
	} else {
	  sessionFilesTextMsg = connectionFilesTextMsg->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	if (sessionFilesTextMsg == NULL) {
	  std::cerr << "ActiveMQFilesClient - sessionFiles is null" << std::endl;
	  return NULL;
	}

	/*
	sessionFiles = connectionFiles->createSession(Session::AUTO_ACKNOWLEDGE);
	if (sessionFiles == NULL) {
	  std::cerr << "ActiveMQFilesClient - sessionFiles is null" << std::endl;
	  return NULL;
	}
	*/
	
	string sim_version_id_str(simJobId);
	
	ostringstream convert;
	convert << simVersionId ;
	string sim_id_str = convert.str();
	string monitoring_topic("TLM.FILESTREAMTOPIC");
	
	
	destinationFilesTextMsg = sessionFilesTextMsg->createTopic(monitoring_topic);
	if (destinationFilesTextMsg == NULL) {
	  std::cerr << "ActiveMQFilesClient - destinationFiles is null" << std::endl;
	  return NULL;
	}
	
	
	// Create a MessageProducer from the Session to the Topic or Queue
	producerFilesTextMsg = sessionFilesTextMsg->createProducer(destinationFilesTextMsg);
	if (producerFilesTextMsg == NULL) {
	  std::cerr << "ActiveMQFilesClient - producerFiles is null" << std::endl;
	  return NULL;
	}
	producerFilesTextMsg->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cerr << "ActiveMQFilesClient - exception detected" << std::endl;
	sessionFilesTextMsg = NULL;
	producerFilesTextMsg = NULL;
	isConnected = false;
	
      }
    }
    else {
      sleep(3);
    }

  } // while (true)

  return NULL;
}


void ActiveMQFilesClient::cleanup() {
  
  if (connectionFilesTextMsg != NULL) {
    try {
      connectionFilesTextMsg->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  // Destroy resources.
  try {
    if ( producerFilesTextMsg != NULL) {
      delete producerFilesTextMsg;
      producerFilesTextMsg = NULL;
    }
    if ( sessionFilesTextMsg != NULL) {
      delete sessionFilesTextMsg;
      sessionFilesTextMsg = NULL;
    }
    if ( connectionFilesTextMsg != NULL) {
      delete connectionFilesTextMsg;
      connectionFilesTextMsg = NULL;
    }
  } catch (CMSException& e) {
    e.printStackTrace();
  }
}
 
