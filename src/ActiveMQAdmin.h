#ifndef ActiveMQAdmin_H
#define ActiveMQAdmin_H

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
#include <memory>
#include "utils.h"

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

//#include "ProcRoverCtrl.h"

#include "linuxOrcc.h"
//#include "canal.h"
#include "simplethread.h"

//extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

class ActiveMQAdmin : public SimpleThread {

 private:

  Connection* connectionAdmin;

  Session* sessionAdmin;
  
  Destination* destinationInternalStatus;

  MessageProducer* producerInternalStatus;
  
  std::string brokerURI;
  int numMessages;
  bool useTopic;
  bool sessionTransacted;
  

  bool isConnected;
  
 public:
  
  ActiveMQAdmin(const std::string& brokerURI, 
		int numMessages, 
		bool useTopic = false, 
		bool sessionTransacted = false) :
    connectionAdmin(NULL),
    sessionAdmin(NULL),
    destinationInternalStatus(NULL),
    producerInternalStatus(NULL),
    numMessages(numMessages),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    isConnected(false),
    brokerURI(brokerURI) 
      {
	createThread();
      };
    
    int initAdmin(char *mgmnt_url);
    
    
    virtual ~ActiveMQAdmin() noexcept(true);
    
    int sendMessage(string msg);
    
    int sendStartActivityMsg(const char *msg);
    
    int sendEndActivityMsg();
    
    int sendSimAliveMsg();
    
    void close();
    
    void* thread ();
  
 private:
    
    void cleanup();
};
 
#endif
