#ifndef ActiveMQFilesClient_H
#define ActiveMQFilesClient_H

#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/commands/ActiveMQStreamMessage.h>
#include <activemq/commands/ActiveMQBlobMessage.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>

#include "simplethread.h" 

using namespace activemq::commands;
using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;


class ActiveMQFilesClient: public SimpleThread {
  
 public:
  
  Connection* connectionFilesTextMsg;
  Connection* connectionFiles;
  
  Session* sessionFilesTextMsg;
  Session* sessionFiles;
  
  Destination* destinationFilesTextMsg;
  Destination* destinationFiles;
  
  MessageProducer* producerFilesTextMsg;
  MessageProducer* producerFiles;
  
  int numMessages;
  bool useTopic;
  bool sessionTransacted;
 
  int simVersionId;
  char simJobId[80];
  char simUserName[80];
  char mqFilesTextMsgServerURL[240];
  char mqFilesServerURL[240];


  bool isConnected;
 
public:
    
  ActiveMQFilesClient(int numMessages, 
		      bool useTopic = false, 
		      bool sessionTransacted = false);
  
      int init();
      
 
      virtual ~ActiveMQFilesClient();

      int sendStartMsg(const char *msg_text) ;

      int sendMsg(const char *msg_text) ;

    void close();

    void* thread ();
private:
 
    void cleanup();
};
 
#endif
