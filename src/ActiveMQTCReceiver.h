
#ifndef ActiveMQTCReceiver_H
#define ActiveMQTCReceiver_H

#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
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
#include <fstream>
#include <memory>
#include "utils.h"

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

#define ORC_LOGFILES_NBR 11
#define ORC_MAX_PATHNAME_SIZE 240

// #include "ProcRoverCtrl.h"

#include "linuxOrcc.h"
#include "simplethread.h"
// #include "canal.h"

// extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
// extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

class ActiveMQTCReceiver : public ExceptionListener,
  public MessageListener,
  public SimpleThread {
  
 private:
  
  CountDownLatch latch;
  CountDownLatch doneLatch;
  Connection* connection;
  Session* session;
  Destination* destination;
  MessageConsumer* consumer;
  long waitMillis;
  bool useTopic;
  bool sessionTransacted;
  std::string brokerURI;
  bool isConnected;

  std::list <CommandInfo*> cmdList; 
  
  ActiveMQTCReceiver(const ActiveMQTCReceiver&);
  ActiveMQTCReceiver& operator=(const ActiveMQTCReceiver&);
  
 public:
  
  ActiveMQTCReceiver(const std::string& brokerURI, 
		     int numMessages, 
		     bool useTopic = false, 
		     bool sessionTransacted = false, int waitMillis = 30000) :
    latch(1),
    doneLatch(numMessages),
    connection(NULL),
    session(NULL),
    destination(NULL),
    consumer(NULL),
    waitMillis(waitMillis),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    brokerURI(brokerURI) 
      {
	isConnected = false;
	createThread();
      }
    
    virtual ~ActiveMQTCReceiver();
    
    void close();
    
    void waitUntilReady();
    
    void* thread ();
    
    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage(const cms::Message* message);
    
    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException(const CMSException& ex AMQCPP_UNUSED);
    
  void addCommandInfo(CommandInfo *);
  CommandInfo* extractCommandInfo(); 
 private:
    void cleanup();

};
#endif
