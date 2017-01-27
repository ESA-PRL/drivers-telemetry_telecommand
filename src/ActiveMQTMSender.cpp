
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
	
 
	string gncexoter_str("GNC_STATE");
	string mast_str("MAST_STATE");
	string pancam_str("PANCAM_STATE");
	string sa_str("SA_STATE");
	string ade_str("ADE_STATE");
	string image_str("IMAGE");
	string dem_str("DEM");
	string img_floc_str("IMAGE_FLOC");
	string img_rloc_str("IMAGE_RLOC");
	string img_pan_cam_str("IMAGE_PANCAM");
	string dem_floc_str("DEM_FLOC");
	string dem_rloc_str("DEM_RLOC");
	string dem_pan_cam_str("DEM_PANCAM");



	gncexoterDestinationMonitoring = sessionMonitor->createTopic(gncexoter_str);
	if (gncexoterDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	gncexoterProducerMonitoring = sessionMonitor->createProducer(gncexoterDestinationMonitoring);
	if (gncexoterProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	gncexoterProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
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
  	
	pancamDestinationMonitoring = sessionMonitor->createTopic(pancam_str);
	if (pancamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	pancamProducerMonitoring = sessionMonitor->createProducer(pancamDestinationMonitoring);
	if (pancamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	pancamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
	
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

        imageDestinationMonitoring = sessionMonitor->createTopic(image_str);
	if (imageDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imageProducerMonitoring = sessionMonitor->createProducer(imageDestinationMonitoring);
	if (imageProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imageProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

        imageFLocDestinationMonitoring = sessionMonitor->createTopic(img_floc_str);
	if (imageFLocDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imageFLocProducerMonitoring = sessionMonitor->createProducer(imageFLocDestinationMonitoring);
	if (imageFLocProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imageFLocProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

        imageRLocDestinationMonitoring = sessionMonitor->createTopic(img_rloc_str);
	if (imageRLocDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imageRLocProducerMonitoring = sessionMonitor->createProducer(imageRLocDestinationMonitoring);
	if (imageRLocProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imageRLocProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

        imagePanCamDestinationMonitoring = sessionMonitor->createTopic(img_pan_cam_str);
	if (imagePanCamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	imagePanCamProducerMonitoring = sessionMonitor->createProducer(imagePanCamDestinationMonitoring);
	if (imagePanCamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	imagePanCamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

	demDestinationMonitoring = sessionMonitor->createTopic(dem_str);
	if (demDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demProducerMonitoring = sessionMonitor->createProducer(demDestinationMonitoring);
	if (demProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;
 
        demFLocDestinationMonitoring = sessionMonitor->createTopic(dem_floc_str);
	if (demFLocDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demFLocProducerMonitoring = sessionMonitor->createProducer(demFLocDestinationMonitoring);
	if (demFLocProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demFLocProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

        demRLocDestinationMonitoring = sessionMonitor->createTopic(dem_rloc_str);
	if (demRLocDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demRLocProducerMonitoring = sessionMonitor->createProducer(demRLocDestinationMonitoring);
	if (demRLocProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demRLocProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

        demPanCamDestinationMonitoring = sessionMonitor->createTopic(dem_pan_cam_str);
	if (demPanCamDestinationMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - destinationMonitoring is null" << std::endl;
	  return NULL;
	}
	demPanCamProducerMonitoring = sessionMonitor->createProducer(demPanCamDestinationMonitoring);
	if (demPanCamProducerMonitoring == NULL) {
	  std::cerr << "ActiveMQTMSender - producerMonitoring is null" << std::endl;
	  return NULL;
	}
	demPanCamProducerMonitoring->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
	isConnected = true;

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
 
