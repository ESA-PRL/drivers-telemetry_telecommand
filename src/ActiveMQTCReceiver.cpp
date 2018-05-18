
#include "comm.h"
#include "ActiveMQTCReceiver.h"


int handleTcMsg(ActiveMQTCReceiver *, char *msg);

ActiveMQTCReceiver::~ActiveMQTCReceiver() {
  cleanup();
}

void ActiveMQTCReceiver::close() {
  this->cleanup();
}
 
void ActiveMQTCReceiver::addCommandInfo(CommandInfo *cmd_info) {
  cmdList.push_back( cmd_info ); 
}
CommandInfo* ActiveMQTCReceiver::extractCommandInfo() {
  std::list<CommandInfo*>::iterator pr; 
  if (cmdList.size() == 0) {
    return NULL;
  }
  pr = cmdList.begin();
  cmdList.clear();
  return (*pr);
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
  std::string simEnvVar = "/home/marta";  // TODO make this a config param

  try {
	count++;
	const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);

	if (textMessage != NULL) {
       std::cerr << "TEXT Message debug" << std::endl;
	  if (textMessage->propertyExists("TCLINE")) {
        std::cerr << "TCLINE debug" << std::endl;
		string tc = textMessage->getStringProperty("TCLINE");
		if (tc.size() > 0) {
		  string text = "";
		  text.append(textMessage->getStringProperty("TCLINE"));
		  printf("ACTEXEC Message #%d Received: %s\n", count, text.c_str());
		  handleTcMsg(this, (char *) text.c_str());
		}
	  }
	  else if (textMessage->propertyExists("LOADACTPLAN")) {
        std::cerr << "LOADACTPLAN debug" << std::endl;
		string actplan = textMessage->getStringProperty("LOADACTPLAN");
		if (actplan.size() > 0) {
		  if (textMessage->propertyExists("NAME")) {
			string filename = textMessage->getStringProperty("NAME");
			if (filename.size() > 0) {
			  std::ofstream file;
			  file.open(simEnvVar + std::string("/Operations/inputs/") + filename);
			  file << actplan;
			  file << std::endl;
			  file.close();
              std::cerr << "LOADACTPLAN: " << filename << std::endl;

			}
		  }
		}
	  }
	  else if (textMessage->propertyExists("EXECACTPLAN")) {
       std::cerr << "EXECACTPLAN debug" << std::endl;
       string execplan = textMessage->getStringProperty("EXECACTPLAN");
       if (execplan.size() > 0) {
        // the handleTcMsg requires three items
        string execplantext = "1 d d d Activity_Plan 1 " + simEnvVar + "/Operations/inputs/" + execplan;
        printf("EXECACTPLAN Message #%d Received: %s\n", count, execplan.c_str());
        handleTcMsg(this, (char *) execplantext.c_str());
       }
      }
    }
else {
  const BytesMessage* bytesMessage = dynamic_cast<const BytesMessage*> (message);

  if (bytesMessage != NULL) {

  }
  else {
    // text = "NOT A TEXTMESSAGE OR BYTEMESSAGE!";
  }
}

} catch (CMSException& e) {
e.printStackTrace();
isConnected = false;
return;
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

int handleTcMsg(ActiveMQTCReceiver *tc_receiver, char *msg) {
  
  char ackid[80], 
    actionname[80], 
    actioncmd[80], 
    actionparam[280];
  int rcv_rc, send_rc, cmd_id;
  
  std::cerr << " - handleTcMsg: ->" << msg << "<--" << std::endl;
  
  // 
  // Count the number off tokens
  // 
  char tmp_msg[1024];
  strcpy(tmp_msg, msg);
  int total_tokens_nbr = 0;
  char *tmp_token_str = strtok(tmp_msg, " ");
  while(tmp_token_str != NULL) {
    total_tokens_nbr++;
    tmp_token_str = strtok(NULL, " ");
  }

  strcpy(actionparam, "\0");
  int tokens_nbr = 0;
  char *token_str = strtok(msg, " ");
  while(token_str != NULL) {
    tokens_nbr++;
    if (tokens_nbr == 1) {
      strcpy(ackid, token_str);
      strcat(actionparam, ackid);
      strcat(actionparam, " ");
    }
    else if (tokens_nbr == 5) {
      strcpy(actionname, token_str);
      strcpy(actioncmd, "START");
    }
    else if (tokens_nbr > 6 && tokens_nbr <= total_tokens_nbr) {
      strcat(actionparam, token_str);
      if (tokens_nbr < (total_tokens_nbr)) strcat(actionparam, " ");
    }
    token_str = strtok(NULL, " ");
  }
  
  std::cerr << "Name of the Action ->" << actionname << "<--" << std::endl
	    << "Action Cmd = ->" << actioncmd << "<--" << std::endl
	    << "Action Params = ->" << actionparam << "<--" << std::endl;
  
  if (!strcmp(actioncmd, "START")) {
    CommandInfo *cmd_info = new CommandInfo(actionname, actionparam);
    tc_receiver->addCommandInfo(cmd_info);
  }
  else
    {
      std::cout << "action " << actionname << " to be executed by Rock" << std::endl;
    }
return OK;

}
