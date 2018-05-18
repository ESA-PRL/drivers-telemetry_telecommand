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

	string ade_str("ADE_STATE");
	string sa_str("SA_STATE");
        string gnc_str("GNC_STATE");
        string mast_str("MAST_STATE");
	string dhs_str("DHS_STATE");
	string ttc_str("TTC_STATE");
        string locom_str("LOCOM_STATE");
        string img_pancam_left_str("PANCAM_LEFT_IMAGE");
        string img_pancam_right_str("PANCAM_RIGHT_IMAGE");
        string dist_pancam_str("PANCAM_DIST");
        string pc_pancam_str("PANCAM_PC");
        string dem_pancam_str("PANCAM_DEM");
        string img_mast_str("IMAGE_MAST");
        string dist_mast_str("DIST_MAST");
        string pc_mast_str("PC_MAST");
        string dem_mast_str("DEM_MAST");
        string img_navcam_left_str("NAVCAM_LEFT_IMAGE");
        string img_navcam_right_str("NAVCAM_RIGHT_IMAGE");
        string dist_navcam_str("NAVCAM_DIST");
        string pc_navcam_str("NAVCAM_PC");
        string dem_navcam_str("NAVCAM_DEM");
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
        string img_loccam_left_str("LOCCAM_LEFT_IMAGE");
        string img_loccam_right_str("LOCCAM_RIGHT_IMAGE");
        string dist_loccam_str("LOCCAM_DIST");
        string pc_loccam_str("LOCCAM_PC");
        string dem_loccam_str("LOCCAM_DEM");
        string img_hazcam_left_str("HAZCAM_LEFT");
        string img_hazcam_right_str("HAZCAM_RIGHT");
        string dist_hazcam_str("HAZCAM_DIST");
        string pc_hazcam_str("HAZCAM_PC");
        string dem_hazcam_str("HAZCAM_DEM");
        string img_rear_str("IMAGE_REAR");
        string dist_rear_str("DIST_REAR");
        string pc_rear_str("PC_REAR");
        string dem_rear_str("DEM_REAR");

        string file_str("ROVERFILETRANSFER");

	/******** ADE *********/
	adeDestinationMonitoring = sessionMonitor->createTopic(ade_str);
	if (adeDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	adeProducerMonitoring = sessionMonitor->createProducer(adeDestinationMonitoring);
	if (adeProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	adeProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

	/******** SA *********/
	saDestinationMonitoring = sessionMonitor->createTopic(sa_str);
	if (saDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	saProducerMonitoring = sessionMonitor->createProducer(saDestinationMonitoring);
	if (saProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	saProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** DHS *********/
	dhsDestinationMonitoring = sessionMonitor->createTopic(dhs_str);
	if (dhsDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	dhsProducerMonitoring = sessionMonitor->createProducer(dhsDestinationMonitoring);
	if (dhsProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	dhsProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
	/******** TTC *********/
	ttcDestinationMonitoring = sessionMonitor->createTopic(ttc_str);
	if (ttcDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	ttcProducerMonitoring = sessionMonitor->createProducer(ttcDestinationMonitoring);
	if (ttcProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	ttcProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
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

        /******** MAST *********/
        mastDestinationMonitoring = sessionMonitor->createTopic(mast_str);
        if (mastDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        mastProducerMonitoring = sessionMonitor->createProducer(mastDestinationMonitoring);
        if (mastProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        mastProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        /******** LOCOM *********/
        locomDestinationMonitoring = sessionMonitor->createTopic(locom_str);
        if (locomDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        locomProducerMonitoring = sessionMonitor->createProducer(locomDestinationMonitoring);
        if (locomProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        locomProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** IMG_PANCAM *********/
        imgPancamLeftDestinationMonitoring = sessionMonitor->createTopic(img_pancam_left_str);
        if (imgPancamLeftDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgPancamLeftProducerMonitoring = sessionMonitor->createProducer(imgPancamLeftDestinationMonitoring);
        if (imgPancamLeftProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgPancamLeftProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        imgPancamRightDestinationMonitoring = sessionMonitor->createTopic(img_pancam_right_str);
        if (imgPancamRightDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgPancamRightProducerMonitoring = sessionMonitor->createProducer(imgPancamRightDestinationMonitoring);
        if (imgPancamRightProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgPancamRightProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** IMG_NAVCAM *********/
        imgNavcamLeftDestinationMonitoring = sessionMonitor->createTopic(img_navcam_left_str);
        if (imgNavcamLeftDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgNavcamLeftProducerMonitoring = sessionMonitor->createProducer(imgNavcamLeftDestinationMonitoring);
        if (imgNavcamLeftProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgNavcamLeftProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        imgNavcamRightDestinationMonitoring = sessionMonitor->createTopic(img_navcam_right_str);
        if (imgNavcamRightDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgNavcamRightProducerMonitoring = sessionMonitor->createProducer(imgNavcamRightDestinationMonitoring);
        if (imgNavcamRightProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgNavcamRightProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** IMG_LOCCAM *********/
        imgLoccamLeftDestinationMonitoring = sessionMonitor->createTopic(img_loccam_left_str);
        if (imgLoccamLeftDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgLoccamLeftProducerMonitoring = sessionMonitor->createProducer(imgLoccamLeftDestinationMonitoring);
        if (imgLoccamLeftProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgLoccamLeftProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        imgLoccamRightDestinationMonitoring = sessionMonitor->createTopic(img_loccam_right_str);
        if (imgLoccamRightDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgLoccamRightProducerMonitoring = sessionMonitor->createProducer(imgLoccamRightDestinationMonitoring);
        if (imgLoccamRightProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgLoccamRightProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        /******** IMG_HAZCAM *********/
        imgHazcamLeftDestinationMonitoring = sessionMonitor->createTopic(img_hazcam_left_str);
        if (imgHazcamLeftDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgHazcamLeftProducerMonitoring = sessionMonitor->createProducer(imgHazcamLeftDestinationMonitoring);
        if (imgHazcamLeftProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgHazcamLeftProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
        isConnected = true;

        imgHazcamRightDestinationMonitoring = sessionMonitor->createTopic(img_hazcam_right_str);
        if (imgHazcamRightDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        imgHazcamRightProducerMonitoring = sessionMonitor->createProducer(imgHazcamRightDestinationMonitoring);
        if (imgHazcamRightProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        imgHazcamRightProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DIST_PANCAM *********/
        distPancamDestinationMonitoring = sessionMonitor->createTopic(dist_pancam_str);
        if (distPancamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        distPancamProducerMonitoring = sessionMonitor->createProducer(distPancamDestinationMonitoring);
        if (distPancamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        distPancamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DIST_NAVCAM *********/
        distNavcamDestinationMonitoring = sessionMonitor->createTopic(dist_navcam_str);
        if (distNavcamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        distNavcamProducerMonitoring = sessionMonitor->createProducer(distNavcamDestinationMonitoring);
        if (distNavcamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        distNavcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DIST_LOCCAM *********/
        distLoccamDestinationMonitoring = sessionMonitor->createTopic(dist_loccam_str);
        if (distLoccamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        distLoccamProducerMonitoring = sessionMonitor->createProducer(distLoccamDestinationMonitoring);
        if (distLoccamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        distLoccamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** PC_PANCAM *********/
        pcPancamDestinationMonitoring = sessionMonitor->createTopic(pc_pancam_str);
        if (pcPancamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        pcPancamProducerMonitoring = sessionMonitor->createProducer(pcPancamDestinationMonitoring);
        if (pcPancamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        pcPancamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** PC_NAVCAM *********/
        pcNavcamDestinationMonitoring = sessionMonitor->createTopic(pc_navcam_str);
        if (pcNavcamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        pcNavcamProducerMonitoring = sessionMonitor->createProducer(pcNavcamDestinationMonitoring);
        if (pcNavcamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        pcNavcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** PC_LOCCAM *********/
        pcLoccamDestinationMonitoring = sessionMonitor->createTopic(pc_loccam_str);
        if (pcLoccamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        pcLoccamProducerMonitoring = sessionMonitor->createProducer(pcLoccamDestinationMonitoring);
        if (pcLoccamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        pcLoccamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DEM_PANCAM *********/
        demPancamDestinationMonitoring = sessionMonitor->createTopic(dem_pancam_str);
        if (demPancamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        demPancamProducerMonitoring = sessionMonitor->createProducer(demPancamDestinationMonitoring);
        if (demPancamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        demPancamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DEM_NAVCAM *********/
        demNavcamDestinationMonitoring = sessionMonitor->createTopic(dem_navcam_str);
        if (demNavcamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        demNavcamProducerMonitoring = sessionMonitor->createProducer(demNavcamDestinationMonitoring);
        if (demNavcamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        demNavcamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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

        /******** DEM_LOCCAM *********/
        demLoccamDestinationMonitoring = sessionMonitor->createTopic(dem_loccam_str);
        if (demLoccamDestinationMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
          return NULL;
        }
        demLoccamProducerMonitoring = sessionMonitor->createProducer(demLoccamDestinationMonitoring);
        if (demLoccamProducerMonitoring == NULL) {
          std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
          return NULL;
        }
        demLoccamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
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
