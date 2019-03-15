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

  Destination* adeDestinationMonitoring;
  MessageProducer* adeProducerMonitoring;
   
  Destination* saDestinationMonitoring;
  MessageProducer* saProducerMonitoring;
  
  Destination* dhsDestinationMonitoring;
  MessageProducer* dhsProducerMonitoring;
  
  Destination* ttcDestinationMonitoring;
  MessageProducer* ttcProducerMonitoring;

  Destination* gncDestinationMonitoring;
  MessageProducer* gncProducerMonitoring;

  Destination* mastDestinationMonitoring;
  MessageProducer* mastProducerMonitoring;

  Destination* locomDestinationMonitoring;
  MessageProducer* locomProducerMonitoring;

  Destination* fileDestinationMonitoring;
  MessageProducer* fileProducerMonitoring;

  /********* img **********/
  Destination* imgPancamLeftDestinationMonitoring;
  MessageProducer* imgPancamLeftProducerMonitoring;
  Destination* imgPancamRightDestinationMonitoring;
  MessageProducer* imgPancamRightProducerMonitoring;

  Destination* imgMastDestinationMonitoring;
  MessageProducer* imgMastProducerMonitoring;

  Destination* imgNavcamLeftDestinationMonitoring;
  MessageProducer* imgNavcamLeftProducerMonitoring;
  Destination* imgNavcamRightDestinationMonitoring;
  MessageProducer* imgNavcamRightProducerMonitoring;

  Destination* imgFrontDestinationMonitoring;
  MessageProducer* imgFrontProducerMonitoring;

  Destination* imgLidarDestinationMonitoring;
  MessageProducer* imgLidarProducerMonitoring;

  Destination* imgTofDestinationMonitoring;
  MessageProducer* imgTofProducerMonitoring;

  Destination* imgLoccamLeftDestinationMonitoring;
  MessageProducer* imgLoccamLeftProducerMonitoring;
  Destination* imgLoccamRightDestinationMonitoring;
  MessageProducer* imgLoccamRightProducerMonitoring;

  Destination* imgHazcamLeftDestinationMonitoring;
  MessageProducer* imgHazcamLeftProducerMonitoring;
  Destination* imgHazcamRightDestinationMonitoring;
  MessageProducer* imgHazcamRightProducerMonitoring;

  Destination* imgRearDestinationMonitoring;
  MessageProducer* imgRearProducerMonitoring;

  Destination* imgAutonavDestinationMonitoring;
  MessageProducer* imgAutonavProducerMonitoring;

  /********* dist **********/
  Destination* distMastDestinationMonitoring;
  MessageProducer* distMastProducerMonitoring;

  Destination* distPancamDestinationMonitoring;
  MessageProducer* distPancamProducerMonitoring;

  Destination* distNavcamDestinationMonitoring;
  MessageProducer* distNavcamProducerMonitoring;

  Destination* distFrontDestinationMonitoring;
  MessageProducer* distFrontProducerMonitoring;

  Destination* distLidarDestinationMonitoring;
  MessageProducer* distLidarProducerMonitoring;

  Destination* distTofDestinationMonitoring;
  MessageProducer* distTofProducerMonitoring;

  Destination* distLoccamDestinationMonitoring;
  MessageProducer* distLoccamProducerMonitoring;

  Destination* distHazcamDestinationMonitoring;
  MessageProducer* distHazcamProducerMonitoring;

  Destination* distRearDestinationMonitoring;
  MessageProducer* distRearProducerMonitoring;

  Destination* distAutonavDestinationMonitoring;
  MessageProducer* distAutonavProducerMonitoring;

  /********* pc **********/
  Destination* pcPancamDestinationMonitoring;
  MessageProducer* pcPancamProducerMonitoring;

  Destination* pcMastDestinationMonitoring;
  MessageProducer* pcMastProducerMonitoring;

  Destination* pcNavcamDestinationMonitoring;
  MessageProducer* pcNavcamProducerMonitoring;

  Destination* pcFrontDestinationMonitoring;
  MessageProducer* pcFrontProducerMonitoring;

  Destination* pcLidarDestinationMonitoring;
  MessageProducer* pcLidarProducerMonitoring;

  Destination* pcTofDestinationMonitoring;
  MessageProducer* pcTofProducerMonitoring;

  Destination* pcLoccamDestinationMonitoring;
  MessageProducer* pcLoccamProducerMonitoring;

  Destination* pcHazcamDestinationMonitoring;
  MessageProducer* pcHazcamProducerMonitoring;

  Destination* pcRearDestinationMonitoring;
  MessageProducer* pcRearProducerMonitoring;

  /********* dem **********/
  Destination* demPancamDestinationMonitoring;
  MessageProducer* demPancamProducerMonitoring;

  Destination* demMastDestinationMonitoring;
  MessageProducer* demMastProducerMonitoring;

  Destination* demNavcamDestinationMonitoring;
  MessageProducer* demNavcamProducerMonitoring;

  Destination* demFrontDestinationMonitoring;
  MessageProducer* demFrontProducerMonitoring;

  Destination* demLidarDestinationMonitoring;
  MessageProducer* demLidarProducerMonitoring;

  Destination* demTofDestinationMonitoring;
  MessageProducer* demTofProducerMonitoring;

  Destination* demLoccamDestinationMonitoring;
  MessageProducer* demLoccamProducerMonitoring;

  Destination* demHazcamDestinationMonitoring;
  MessageProducer* demHazcamProducerMonitoring;

  Destination* demRearDestinationMonitoring;
  MessageProducer* demRearProducerMonitoring;

  Destination* demAutonavDestinationMonitoring;
  MessageProducer* demAutonavProducerMonitoring;

  Destination* partialNavmapAutonavDestinationMonitoring;
  MessageProducer* partialNavmapAutonavProducerMonitoring;

  Destination* navmapAutonavDestinationMonitoring;
  MessageProducer* navmapAutonavProducerMonitoring;

  Destination* trajmapAutonavDestinationMonitoring;
  MessageProducer* trajmapAutonavProducerMonitoring;

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
