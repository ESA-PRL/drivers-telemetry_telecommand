
#include <stdio.h>

#include "ActiveMQClient.h"
#include "GeneralSupportLibrary.h"

//extern int handleTcMsg(AutomatonExecMach* canal, char *msg);
//extern orc_ProcRoverCtrl  *m_procRoverCtrl; 

ActiveMQClient::~ActiveMQClient(){
  cleanup();
}

void ActiveMQClient::close() {
  this->cleanup();
}

int ActiveMQClient::config() {
  FILE* configFile;
  char configFileName[1024];
  sprintf(configFileName, "./activeMQ.conf");
  if ((configFile = fopen(configFileName, "r")) == NULL) {
    std::cerr << configFileName << " file not identified" 
	      << std::endl;
    return ERROR;
  }
  
  if (GeneralSupport::read_int(configFile, "SIMULATOR_ID", 
			       &simVersionId) == ERROR) {
    return ERROR;
  }
  if (GeneralSupport::ReadString(configFile, "SIMULATOR_JOB_ID", 
			       simJobId) == ERROR) {
    return ERROR;
  }

  if (GeneralSupport::ReadString(configFile, "MONITORING_MQ_SERVER_URL", 
				 mqMonitoringServerURL) == ERROR) {
    return ERROR;
  }
  if (GeneralSupport::ReadString(configFile, "MANAGEMENT_MQ_SERVER_URL", 
				 mqManagementServerURL) == ERROR) {
    return ERROR;
  }
  if (GeneralSupport::ReadString(configFile, "SIMULATOR_USER_NAME", 
				 simUserName) == ERROR) {
    return ERROR;
  }

  return OK;
}

int ActiveMQClient::initAdmin(char *user_name, 
			      char *mgmnt_url, 
			      char *monitor_url, 
			      char *job_id, 
			      int sim_id) {
  
  try {
    
    FILE* configFile;
    if ((configFile = fopen("./activeMQ.conf", "r")) == NULL) {
      std::cerr << "activeMQ.conf config file not identified" 
		<< std::endl;
      return ERROR;
    }
    
    // set the user name
    if (user_name == NULL) {
      if (GeneralSupport::ReadString(configFile, "SIMULATOR_USER_NAME", 
				     simUserName) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(simUserName, user_name);
    }
    
    // set the management queue url
    if (mgmnt_url == NULL) {
      if (GeneralSupport::ReadString(configFile, "MANAGEMENT_MQ_SERVER_URL", 
				     mqManagementServerURL) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(mqManagementServerURL, mgmnt_url);
    }

    // set the monitor queue url
    if (monitor_url == NULL) {

      if (GeneralSupport::ReadString(configFile, "MONITORING_MQ_SERVER_URL", 
				     mqMonitoringServerURL) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(mqMonitoringServerURL, monitor_url);
    }

    // get the job id
    if (job_id == NULL) {

      if (GeneralSupport::ReadString(configFile, "SIMULATOR_JOB_ID", 
				     simJobId) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(simJobId, job_id);
    }

    if (simVersionId == -1) {
      if (GeneralSupport::read_int(configFile, "SIMULATOR_ID", 
				   &simVersionId) == ERROR) {
	return ERROR;
      }
    }
    else {
      simVersionId = sim_id;
    }
    
    string broker_uri("tcp://" + string(mqManagementServerURL) + "?timeout=3000");
    // Create a ConnectionFactory
    auto_ptr<ConnectionFactory> 
      connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
    
    // Create a Connection
    connectionAdmin = connectionFactory->createConnection();
    if (connectionAdmin == NULL) {
      std::cerr << "ActiveMQClient - connectionAdmin is null" << std::endl;
      return ERROR;
    }
    connectionAdmin->start();
    
    // Create a Session
    if (this->sessionTransacted) {
      sessionAdmin = connectionAdmin->createSession(Session::SESSION_TRANSACTED);
    } else {
      sessionAdmin = connectionAdmin->createSession(Session::AUTO_ACKNOWLEDGE);
    }
    
    if (sessionAdmin == NULL) {
      std::cerr << "ActiveMQClient - sessionAdmin is null" << std::endl;
      return ERROR;
    }
    // create the 'internal status' topic    
    string internal_status_topic("ROVER.STATUS");

    destinationInternalStatus = sessionAdmin->createTopic(internal_status_topic);
    if (destinationInternalStatus == NULL) {
      std::cerr << "ActiveMQClient - destinationInternalStatus is null" << std::endl;
      return ERROR;
    }
    
    // Create a MessageProducer from the Session to the Topic or Queue
    producerInternalStatus = sessionAdmin->createProducer(destinationInternalStatus);
    if (producerInternalStatus == NULL) {
      std::cerr << "ActiveMQClient - producerInternalStatus is null" << std::endl;
      return ERROR;
    }
    producerInternalStatus->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
    
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cerr << "ActiveMQClient - exception detected" << std::endl;
    sessionAdmin = NULL;
    producerInternalStatus = NULL;
    producerMonitoring = NULL;
  }
  return OK;
}

int ActiveMQClient::initMonitor(char *user_name, char *mgmnt_url, char *monitor_url, char *job_id, int sim_id) {
  
  try {

    FILE* configFile;
    char configFileName[1024];
    char *sim_env_var = getenv("RELEASE_HOME");
    sprintf(configFileName, "%s/configFiles/activeMQ.conf", sim_env_var);
    if ((configFile = fopen(configFileName, "r")) == NULL) {
      std::cerr << configFileName << " file not identified" 
		<< std::endl;
      return ERROR;
    }

    // set the user name
    if (user_name == NULL) {
      if (GeneralSupport::ReadString(configFile, "SIMULATOR_USER_NAME", 
				     simUserName) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(simUserName, user_name);
    }

    // set the management queue url
    if (mgmnt_url == NULL) {
      if (GeneralSupport::ReadString(configFile, "MANAGEMENT_MQ_SERVER_URL", 
				     mqManagementServerURL) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(mqManagementServerURL, mgmnt_url);
    }

    // set the monitor queue url
    if (monitor_url == NULL) {

      if (GeneralSupport::ReadString(configFile, "MONITORING_MQ_SERVER_URL", 
				     mqMonitoringServerURL) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(mqMonitoringServerURL, monitor_url);
    }

    // get the job id
    if (job_id == NULL) {

      if (GeneralSupport::ReadString(configFile, "SIMULATOR_JOB_ID", 
				     simJobId) == ERROR) {
	return ERROR;
      }
    }
    else {
      strcpy(simJobId, job_id);
    }

    if (simVersionId == -1) {
      if (GeneralSupport::read_int(configFile, "SIMULATOR_ID", 
				   &simVersionId) == ERROR) {
	return ERROR;
      }
    }
    else {
      simVersionId = sim_id;
    }

    
    string broker_uri("tcp://"+ string(mqMonitoringServerURL) +"?timeout=3000");
    // Create a ConnectionFactory
    auto_ptr<ConnectionFactory> 
      connectionFactory(ConnectionFactory::createCMSConnectionFactory(broker_uri));
    
    // Create a Connection
    connectionMonitor = connectionFactory->createConnection();
    if (connectionMonitor == NULL) {
      std::cerr << "ActiveMQClient - connection is null" << std::endl;
      return ERROR;
    }
    connectionMonitor->start();
    
    // Create a Session
    if (this->sessionTransacted) {
      sessionMonitor = connectionMonitor->createSession(Session::SESSION_TRANSACTED);
    } else {
      sessionMonitor = connectionMonitor->createSession(Session::AUTO_ACKNOWLEDGE);
    }
    
    if (sessionMonitor == NULL) {
      std::cerr << "ActiveMQClient - sessionMonitor is null" << std::endl;
      return ERROR;
    }

    string sim_version_id_str(simJobId);

    ostringstream convert;
    convert << simVersionId ;
    string sim_id_str = convert.str();
    // create the 'monitoring' topic
    // string monitoring_topic("SIMULATOR." + sim_id_str + ".MONITORING");
    string monitoring_topic("ROVERTM");


    // std::to_string(simJobId) + "

    destinationMonitoring = sessionMonitor->createTopic(monitoring_topic);
    if (destinationMonitoring == NULL) {
      std::cerr << "ActiveMQClient - destinationMonitoring is null" << std::endl;
      return ERROR;
    }
    
    
    // Create a MessageProducer from the Session to the Topic or Queue
    producerMonitoring = sessionMonitor->createProducer(destinationMonitoring);
    if (producerMonitoring == NULL) {
      std::cerr << "ActiveMQClient - producerMonitoring is null" << std::endl;
      return ERROR;
    }
    producerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
    
  } catch (CMSException& e) {
    e.printStackTrace();
    std::cerr << "ActiveMQClient - exception detected" << std::endl;
    sessionMonitor = NULL;
    producerInternalStatus = NULL;
    producerMonitoring = NULL;
  }
  return OK;
}

int ActiveMQClient::sendMessage(string msg) {
  if (sessionMonitor == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionMonitor->createTextMessage(msg));
  message->setStringProperty("JOBID", sim_job_str);
  message->setStringProperty("STATUS", "SIMALIVE");
  if (producerMonitoring != NULL) {
    producerMonitoring->send(message.get());
  }
}
int ActiveMQClient::sendStartActivityMsg(const char *msg_text) {
  if (sessionMonitor == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionMonitor->createTextMessage(msg_text));
  message->setStringProperty("JOBID", sim_job_str);
  message->setStringProperty("STATUS", "SIMALIVE");
  if (producerMonitoring != NULL) {
    producerMonitoring->send(message.get());
  }
}
int ActiveMQClient::sendEndActivityMsg() {
  if (sessionMonitor == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionMonitor->createTextMessage("sendEndActivityMsg"));
  message->setStringProperty("JOBID", sim_job_str);
  message->setStringProperty("STATUS", "SIMALIVE");
  if (producerMonitoring != NULL) {
    producerMonitoring->send(message.get());
  }
}
int ActiveMQClient::sendSimAliveMsg() {
  if (sessionAdmin == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionAdmin->createTextMessage("ROVER.STATUS"));
  message->setStringProperty("STATUSMSG", "ROVERALIVE (1)");
  message->setStringProperty("ACTION", "ROVER.STATUS");
  message->setStringProperty("IPINFO", "localhost-test");
  message->setStringProperty("HOSTNAME", "localhost-test");

  if (producerInternalStatus != NULL) {
    producerInternalStatus->send(message.get());
  }
}

int ActiveMQClient::sendSimCompletedMsg(int files_nbr, 
					char logfilename[ORC_LOGFILES_NBR][ORC_MAX_PATHNAME_SIZE]) {
  if (sessionAdmin == NULL) {
    return ERROR;
  }
  string sim_job_str(simJobId);
  std::auto_ptr<TextMessage> message(sessionAdmin->createTextMessage("JOBSTATUS"));
  message->setStringProperty("JOBID", sim_job_str);
  message->setStringProperty("JOBSTATUS", "SIMCOMPLETE");
  message->setStringProperty("INFO", "any information");

  char filelocation[1024];
  message->setIntProperty("FILESAVAILABLE", files_nbr);
  for (int i=0; i<files_nbr; i++) {
    sprintf(filelocation, "FILELOCATION%d", i+1);
    message->setStringProperty(filelocation, logfilename[i]);
  }

  if (producerInternalStatus != NULL) {
    producerInternalStatus->send(message.get());
  }
  cleanup();
}

void ActiveMQClient::cleanup() {
  
  if (connectionAdmin != NULL) {
    try {
      connectionAdmin->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  if (connectionMonitor != NULL) {
    try {
      connectionMonitor->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  // Destroy resources.
  try {
    if ( destinationInternalStatus != NULL) {
      delete destinationInternalStatus;
      destinationInternalStatus = NULL;
    }
    if ( producerInternalStatus != NULL) {
      delete producerInternalStatus;
      producerInternalStatus = NULL;
    }
    if ( producerMonitoring != NULL) {
      delete producerMonitoring;
      producerMonitoring = NULL;
    }
    if ( sessionAdmin != NULL) {
      delete sessionAdmin;
      sessionAdmin = NULL;
    }
    if ( sessionMonitor != NULL) {
      delete sessionMonitor;
      sessionMonitor = NULL;
    }
    if ( connectionAdmin != NULL) {
      delete connectionAdmin;
      connectionAdmin = NULL;
    }
    if ( connectionMonitor != NULL) {
      delete connectionMonitor;
      connectionMonitor = NULL;
    }
  } catch (CMSException& e) {
    e.printStackTrace();
  }
}
 
