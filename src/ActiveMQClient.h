#ifndef ActiveMQClient_H
#define ActiveMQClient_H

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

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

#define ORC_LOGFILES_NBR 11
#define ORC_MAX_PATHNAME_SIZE 240

// extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
// extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

class ActiveMQClient {

 public:
  static const int MONITORING_TYPE = 1;
  
  static const int MANAGEMENT_TYPE = 2;
  
  int mqType;
  
 private:
  
  Connection* connectionAdmin;
  Connection* connectionMonitor;
  Session* sessionAdmin;
  Session* sessionMonitor;
  Destination* destinationInternalStatus;
  Destination* destinationMonitoring;
  MessageProducer* producerInternalStatus;
  MessageProducer* producerMonitoring;
  //  MessageConsumer* telecommandConsumer;
  
  int numMessages;
  bool useTopic;
  bool sessionTransacted;
 
  int simVersionId;
  char simJobId[80];
  char simUserName[80];
  char mqMonitoringServerURL[80];
  char mqManagementServerURL[80];


private:
 
    ActiveMQClient(const ActiveMQClient&);
    ActiveMQClient& operator=(const ActiveMQClient&);
 
public:
    
    ActiveMQClient(int numMessages, 
		   bool useTopic = false, 
		   bool sessionTransacted = false) :
      connectionAdmin(NULL),
      connectionMonitor(NULL),
      sessionAdmin(NULL),
      sessionMonitor(NULL),
      destinationInternalStatus(NULL),
      destinationMonitoring(NULL),
      producerInternalStatus(NULL),
      producerMonitoring(NULL),
      numMessages(numMessages),
      useTopic(useTopic),
      sessionTransacted(sessionTransacted)
      //      telecommandConsumer(NULL)
      //,brokerURI(brokerURI) 
	{

	};

      int init(char *user_name, char *mgmnt_url, char *monitor_url, char * job_id);
      int initMonitor(char *user_name, char *mgmnt_url, char *monitor_url, char *job_id, int sim_id);
      int initAdmin(char *user_name, char *mgmnt_url, char *monitor_url, char *job_id, int sim_id);
      int initTelecommandConsumer(char *user_name, char *mgmnt_url, char *monitor_url, char *job_id, int sim_id);
 
      virtual ~ActiveMQClient();
 
      int config();
      int sendMessage(string msg);
      int sendStartActivityMsg(const char *msg);
      int sendEndActivityMsg();
      int sendSimCompletedMsg(int ,char logfilename[ORC_LOGFILES_NBR][ORC_MAX_PATHNAME_SIZE]);
      int sendSimAliveMsg();

    void close();
private:
 
    void cleanup();
};
 
#endif
