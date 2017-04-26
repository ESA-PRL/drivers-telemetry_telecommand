
#include <stdio.h>
#include <unistd.h>

#include "ActiveMQTMSender.h"
#include "GeneralSupportLibrary.h"


ActiveMQTMSender::~ActiveMQTMSender(){
  cleanup();
}

void ActiveMQTMSender::close() {
  this->cleanup();
}

void* ActiveMQTMSender::thread() {
  
  while (true) {
    
    if (!isConnected) {
      
      std::cout << "ActiveMQTMSender:" << " connecting" <<  std::endl;
      try {
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> 
	  connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
	
	// Create a Connection
	connectionMonitor = connectionFactory->createConnection();
	if (connectionMonitor == NULL) {
	  std::cerr << "ActiveMQTMSender - connection is null" << std::endl;
	  return NULL;
	}
	connectionMonitor->start();
	
	// Create a Session
	if (this->sessionTransacted) {
	  sessionMonitor = connectionMonitor->createSession(Session::SESSION_TRANSACTED);
	} else {
	  sessionMonitor = connectionMonitor->createSession(Session::AUTO_ACKNOWLEDGE);
	}
	
	if (sessionMonitor == NULL) {
	  std::cerr << "ActiveMQTMSender - sessionMonitor is null" << std::endl;
	  return NULL;
	}
	
 
	string gnc_str("GNC_STATE");
	string ptu_str("PTU_STATE");
	//string pancam_str("PANCAM_STATE");
	//string sa_str("SA_STATE");
	//string ade_str("ADE_STATE");
	//string image_str("IMAGE");
	//string dem_str("DEM");
	string img_mast_str("IMAGE_MAST");
	string dist_mast_str("DIST_MAST");
	string pc_mast_str("PC_MAST");
	string dem_mast_str("DEM_MAST");
	string img_front_str("IMAGE_FRONT");
	string dist_front_str("DIST_FRONT");
	string pc_front_str("PC_FRONT");
	string dem_front_str("DEM_FRONT");
	string img_lidar_str("IMAGE_LIDAR");
	string dist_lidar_str("DIST_LIDAR");
	string pc_lidar_str("PC_LIDAR");
	string dem_lidar_str("DEM_LIDAR");
	string img_tof_str("IMAGE_TOF");
	string dist_tof_str("DIST_TOF");
	string pc_tof_str("PC_TOF");
	string dem_tof_str("DEM_TOF");
	string img_hazcam_str("IMAGE_HAZCAM");
	string dist_hazcam_str("DIST_HAZCAM");
	string pc_hazcam_str("PC_HAZCAM");
	string dem_hazcam_str("DEM_HAZCAM");
	string img_rear_str("IMAGE_REAR");
	string dist_rear_str("DIST_REAR");
	string pc_rear_str("PC_REAR");
	string dem_rear_str("DEM_REAR");

	string file_str("ROVERFILETRANSFER");

    /******** GNC *********/
	gncDestinationMonitoring = sessionMonitor->createTopic(gnc_str);
	if (gncDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	gncProducerMonitoring = sessionMonitor->createProducer(gncDestinationMonitoring);
	if (gncProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	gncProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
    /******** PTU *********/
	ptuDestinationMonitoring = sessionMonitor->createTopic(ptu_str);
	if (ptuDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	ptuProducerMonitoring = sessionMonitor->createProducer(ptuDestinationMonitoring);
	if (ptuProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	ptuProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
       
    /******** FILE *********/
    fileDestinationMonitoring = sessionMonitor->createTopic(file_str);
	if (fileDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	fileProducerMonitoring = sessionMonitor->createProducer(fileDestinationMonitoring);
	if (fileProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	fileProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** IMG_MAST *********/
    imgMastDestinationMonitoring = sessionMonitor->createTopic(img_mast_str);
	if (imgMastDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgMastProducerMonitoring = sessionMonitor->createProducer(imgMastDestinationMonitoring);
	if (imgMastProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgMastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** IMG_LIDAR *********/
    imgLidarDestinationMonitoring = sessionMonitor->createTopic(img_lidar_str);
	if (imgLidarDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgLidarProducerMonitoring = sessionMonitor->createProducer(imgLidarDestinationMonitoring);
	if (imgLidarProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgLidarProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** IMG_FRONT *********/
    imgFrontDestinationMonitoring = sessionMonitor->createTopic(img_front_str);
	if (imgFrontDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgFrontProducerMonitoring = sessionMonitor->createProducer(imgFrontDestinationMonitoring);
	if (imgFrontProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgFrontProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** IMG_TOF *********/
    imgTofDestinationMonitoring = sessionMonitor->createTopic(img_tof_str);
	if (imgTofDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgTofProducerMonitoring = sessionMonitor->createProducer(imgTofDestinationMonitoring);
	if (imgTofProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgTofProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** IMG_HAZCAM *********/
    imgHazcamDestinationMonitoring = sessionMonitor->createTopic(img_hazcam_str);
	if (imgHazcamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgHazcamProducerMonitoring = sessionMonitor->createProducer(imgHazcamDestinationMonitoring);
	if (imgHazcamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgHazcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** IMG_REAR *********/
    imgRearDestinationMonitoring = sessionMonitor->createTopic(img_rear_str);
	if (imgRearDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imgRearProducerMonitoring = sessionMonitor->createProducer(imgRearDestinationMonitoring);
	if (imgRearProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imgRearProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DIST_MAST *********/
    distMastDestinationMonitoring = sessionMonitor->createTopic(dist_mast_str);
	if (distMastDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distMastProducerMonitoring = sessionMonitor->createProducer(distMastDestinationMonitoring);
	if (distMastProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distMastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DIST_LIDAR *********/
    distLidarDestinationMonitoring = sessionMonitor->createTopic(dist_lidar_str);
	if (distLidarDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distLidarProducerMonitoring = sessionMonitor->createProducer(distLidarDestinationMonitoring);
	if (distLidarProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distLidarProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DIST_FRONT *********/
    distFrontDestinationMonitoring = sessionMonitor->createTopic(dist_front_str);
	if (distFrontDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distFrontProducerMonitoring = sessionMonitor->createProducer(distFrontDestinationMonitoring);
	if (distFrontProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distFrontProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** DIST_TOF *********/
    distTofDestinationMonitoring = sessionMonitor->createTopic(dist_tof_str);
	if (distTofDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distTofProducerMonitoring = sessionMonitor->createProducer(distTofDestinationMonitoring);
	if (distTofProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distTofProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DIST_HAZCAM *********/
    distHazcamDestinationMonitoring = sessionMonitor->createTopic(dist_hazcam_str);
	if (distHazcamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distHazcamProducerMonitoring = sessionMonitor->createProducer(distHazcamDestinationMonitoring);
	if (distHazcamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distHazcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DIST_REAR *********/
    distRearDestinationMonitoring = sessionMonitor->createTopic(dist_rear_str);
	if (distRearDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	distRearProducerMonitoring = sessionMonitor->createProducer(distRearDestinationMonitoring);
	if (distRearProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	distRearProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** PC_MAST *********/
    pcMastDestinationMonitoring = sessionMonitor->createTopic(pc_mast_str);
	if (pcMastDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcMastProducerMonitoring = sessionMonitor->createProducer(pcMastDestinationMonitoring);
	if (pcMastProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcMastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** PC_LIDAR *********/
    pcLidarDestinationMonitoring = sessionMonitor->createTopic(pc_lidar_str);
	if (pcLidarDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcLidarProducerMonitoring = sessionMonitor->createProducer(pcLidarDestinationMonitoring);
	if (pcLidarProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcLidarProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** PC_FRONT *********/
    pcFrontDestinationMonitoring = sessionMonitor->createTopic(pc_front_str);
	if (pcFrontDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcFrontProducerMonitoring = sessionMonitor->createProducer(pcFrontDestinationMonitoring);
	if (pcFrontProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcFrontProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** PC_TOF *********/
    pcTofDestinationMonitoring = sessionMonitor->createTopic(pc_tof_str);
	if (pcTofDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcTofProducerMonitoring = sessionMonitor->createProducer(pcTofDestinationMonitoring);
	if (pcTofProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcTofProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** PC_HAZCAM *********/
    pcHazcamDestinationMonitoring = sessionMonitor->createTopic(pc_hazcam_str);
	if (pcHazcamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcHazcamProducerMonitoring = sessionMonitor->createProducer(pcHazcamDestinationMonitoring);
	if (pcHazcamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcHazcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** PC_REAR *********/
    pcRearDestinationMonitoring = sessionMonitor->createTopic(pc_rear_str);
	if (pcRearDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pcRearProducerMonitoring = sessionMonitor->createProducer(pcRearDestinationMonitoring);
	if (pcRearProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pcRearProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DEM_MAST *********/
    demMastDestinationMonitoring = sessionMonitor->createTopic(dem_mast_str);
	if (demMastDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demMastProducerMonitoring = sessionMonitor->createProducer(demMastDestinationMonitoring);
	if (demMastProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demMastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DEM_LIDAR *********/
    demLidarDestinationMonitoring = sessionMonitor->createTopic(dem_lidar_str);
	if (demLidarDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demLidarProducerMonitoring = sessionMonitor->createProducer(demLidarDestinationMonitoring);
	if (demLidarProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demLidarProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DEM_FRONT *********/
    demFrontDestinationMonitoring = sessionMonitor->createTopic(dem_front_str);
	if (demFrontDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demFrontProducerMonitoring = sessionMonitor->createProducer(demFrontDestinationMonitoring);
	if (demFrontProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demFrontProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** DEM_TOF *********/
    demTofDestinationMonitoring = sessionMonitor->createTopic(dem_tof_str);
	if (demTofDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demTofProducerMonitoring = sessionMonitor->createProducer(demTofDestinationMonitoring);
	if (demTofProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demTofProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DEM_HAZCAM *********/
    demHazcamDestinationMonitoring = sessionMonitor->createTopic(dem_hazcam_str);
	if (demHazcamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demHazcamProducerMonitoring = sessionMonitor->createProducer(demHazcamDestinationMonitoring);
	if (demHazcamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demHazcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    /******** DEM_REAR *********/
    demRearDestinationMonitoring = sessionMonitor->createTopic(dem_rear_str);
	if (demRearDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demRearProducerMonitoring = sessionMonitor->createProducer(demRearDestinationMonitoring);
	if (demRearProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demRearProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

    // Finished	
	std::cout << "ActiveMQTMSender:" << " connected" <<  std::endl;
	isConnected = true;
	
      } catch (CMSException& e) {
	e.printStackTrace();
	std::cerr << "ActiveMQTMSender - exception detected" << std::endl;
	sessionMonitor = NULL; 
	isConnected = false;
	
      }
    }
    else {
      sleep(3);
    }
  }
  return NULL;
}


void ActiveMQTMSender::cleanup() {
  
  if (connectionMonitor != NULL) {
    try {
      connectionMonitor->close();
    } catch (cms::CMSException& ex) {
      ex.printStackTrace();
    }
  }
  
  /*
  // Destroy resources.
  try {
    if ( producerMonitoring != NULL) {
      delete producerMonitoring;
      producerMonitoring = NULL;
    }
    if ( sessionMonitor != NULL) {
      delete sessionMonitor;
      sessionMonitor = NULL;
    }
    if ( connectionMonitor != NULL) {
      delete connectionMonitor;
      connectionMonitor = NULL;
    }
  } catch (CMSException& e) {
    e.printStackTrace();
  }
  */
}
 
