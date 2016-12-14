#ifndef ActiveMQMonitorClient_H
#define ActiveMQMonitorClient_H

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


class ActiveMQMonitorClient: public SimpleThread {

 public:
  
  Connection* connectionMonitor;
  
  Session* sessionMonitor;
  
  Destination* destinationMonitoring;
  
  MessageProducer* producerMonitoring;
  
  int numMessages;
  bool useTopic;
  bool sessionTransacted;
 
  int simVersionId;
  char simJobId[80];
  char simUserName[80];
  char mqMonitoringServerURL[240];
  
  
  bool isConnected;
  string topicname;

public:
    
  ActiveMQMonitorClient(int numMessages, 
			bool useTopic = false, 
			bool sessionTransacted = false,
			string topic_str = "TM");
  
  int init();
  
  
  virtual ~ActiveMQMonitorClient();
  
  int sendMsg(const char *msg_text) ;
  
  void close();
  
  void* thread ();
 private:
  
  void cleanup();
};
 
#endif
