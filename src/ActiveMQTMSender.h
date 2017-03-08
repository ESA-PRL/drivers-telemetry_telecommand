#ifndef ActiveMQTMSender_H
#define ActiveMQTMSender_H

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


class ActiveMQTMSender: public SimpleThread {

 public:
  
  Connection* connectionMonitor;
  
  Session* sessionMonitor;
   
  
  Destination* gncexoterDestinationMonitoring;
  MessageProducer* gncexoterProducerMonitoring;
  
  Destination* mastDestinationMonitoring;
  MessageProducer* mastProducerMonitoring;
  
  Destination* pancamDestinationMonitoring;
  MessageProducer* pancamProducerMonitoring;
  
  Destination* saDestinationMonitoring;
  MessageProducer* saProducerMonitoring;
 
  Destination* adeDestinationMonitoring;
  MessageProducer* adeProducerMonitoring;
 
  Destination* imageDestinationMonitoring;
  MessageProducer* imageProducerMonitoring;
 
  Destination* fileDestinationMonitoring;
  MessageProducer* fileProducerMonitoring;
 
  Destination* imageFLocDestinationMonitoring;
  MessageProducer* imageFLocProducerMonitoring;
 
  Destination* imageRLocDestinationMonitoring;
  MessageProducer* imageRLocProducerMonitoring;
 
  Destination* imagePanCamDestinationMonitoring;
  MessageProducer* imagePanCamProducerMonitoring;
 
  Destination* demDestinationMonitoring;
  MessageProducer* demProducerMonitoring;
 
  Destination* demFLocDestinationMonitoring;
  MessageProducer* demFLocProducerMonitoring;
  
  Destination* demRLocDestinationMonitoring;
  MessageProducer* demRLocProducerMonitoring;
  
  Destination* demPanCamDestinationMonitoring;
  MessageProducer* demPanCamProducerMonitoring;
 
  std::string brokerURI;
  int numMessages;
  bool useTopic;
  bool sessionTransacted;
  
  bool isConnected;
  string topicname;

public:
  ActiveMQTMSender(const std::string& brokerURI, 
		   int numMessages, 
		   bool useTopic = false, 
		   bool sessionTransacted = false,
		   string topic_str = "TM"):
    connectionMonitor(NULL),
    sessionMonitor(NULL), 
    numMessages(numMessages),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    topicname(topic_str),
    brokerURI(brokerURI) 
      {
	isConnected = false;
	createThread();
      }

    /*
      ActiveMQTMSender(const std::string& brokerURI, 
      int numMessages, 
      bool useTopic = false, 
      bool sessionTransacted = false,
      string topic_str = "TM");
    */
  int init();
  
  
  virtual ~ActiveMQTMSender();
  
  void close();
  
  void* thread ();

 private:
  
  void cleanup();
};
 
#endif
