
#ifndef CTRL_STATE_H
#define CTRL_STATE_H
//##################################################################################
//
//	This file shall contain all and only the indexes of the quantities assigned
//	to the different state vectors of the controller
//
//##################################################################################




//
// The CTRL_MAX_STATE_SIZE reflects the size of the symbol table data 
// in the muroco controller (it is defined there as MAX_STATE_SIZE 100)
//

static const short CTRL_MAX_STATE_SIZE =  100;

// used to put a termination flag.
static const short ABORT_INDEX =  99;
static const short ABORT_ERROR_INDEX =  98;

struct CtrlErrorType { const char* description; };

static const CtrlErrorType CtrlErrors[] =
{
	{ "Undefined Error" },
	{ "Lack of power on power line" },
	{ "Unknown action parameter" },
	{ "Subsystem is not in the proper operative state to allow action execution" }
};

static const CtrlErrorType SPDSCtrlErrors[] = {
  { "SPDS Undefined Error" },
  { "SPDS_SPDS_STATE_NOT_FOUND_ERROR" },
  { "SPDS_POWER_STATE_NOT_FOUND_ERROR" },
  { "SPDS_LACK_OF_POWER_ON_POWER_LINE_ERROR" },
  { "SPDS_SPDS_WRONG_STATE_ERROR" },
  { "SPDS_DS_WRONG_STATE_ERROR" },
  { "SPDS_SC_WRONG_STATE_ERROR" },
  { "SPDS_WARMUP_TIMEOUT_ERROR" },
  { "SPDS_DMA_INITIALISE_PARAMETERISATION_ERROR" },
  { "SPDS_DMA_MOVETO_PARAMETERISATION_ERROR" },
  { "SPDS_CSTM_DEPLOY_PARAMETERISATION_ERROR" },
  { "SPDS_PHR_NOT_IDENTIFIED_ERROR" },
  { "SPDS_SC_POSITION_SC_PARAMETERISATION_ERROR" }
};

enum SPDSCtrlErrorsId {
  SPDS_UNDEFINED_ERROR,
  SPDS_SPDS_STATE_NOT_FOUND_ERROR,
  SPDS_POWER_STATE_NOT_FOUND_ERROR,
  SPDS_LACK_OF_POWER_ON_POWER_LINE_ERROR,
  SPDS_SPDS_WRONG_STATE_ERROR,
  SPDS_DS_WRONG_STATE_ERROR,
  SPDS_SC_WRONG_STATE_ERROR,
  SPDS_WARMUP_TIMEOUT_ERROR,
  SPDS_DMA_INITIALISE_PARAMETERISATION_ERROR,
  SPDS_DMA_MOVETO_PARAMETERISATION_ERROR,
  SPDS_CSTM_DEPLOY_PARAMETERISATION_ERROR,
  SPDS_PHR_NOT_IDENTIFIED_ERROR,
  SPDS_SC_POSITION_SC_PARAMETERISATION_ERROR
};

static const CtrlErrorType GNCCtrlErrors[] = {
  { "GNC Undefined Error" },
  { "GNC_GNC_STATE_NOT_FOUND_ERROR" },
  { "GNC_POWER_STATE_NOT_FOUND_ERROR" },
  { "GNC_LACK_OF_POWER_ON_POWER_LINE_ERROR" },
  { "GNC_WRONG_STATE_ERROR" },
  { "GNC_WARMUP_TIMEOUT_ERROR" },
  { "GNC_POWER_LINE_TIMEOUT_ERROR" },
  { "GNC_GNC_MOVETO_PARAMETERISATION_ERROR" },
  { "GNC_PHR_NOT_IDENTIFIED_ERROR" },
  { "GNC_PATHFILE_NOT_FIND_ERROR" }
};

enum GNCCtrlErrorsId {
  GNC_UNDEFINED_ERROR,
  GNC_GNC_STATE_NOT_FOUND_ERROR,
  GNC_POWER_STATE_NOT_FOUND_ERROR,
  GNC_LACK_OF_POWER_ON_POWER_LINE_ERROR,
  GNC_WRONG_STATE_ERROR,
  GNC_WARMUP_TIMEOUT_ERROR,
  GNC_POWER_LINE_TIMEOUT_ERROR,
  GNC_GNC_MOVETO_PARAMETERISATION_ERROR,
  GNC_PHR_NOT_IDENTIFIED_ERROR,
  GNC_PATHFILE_NOT_FIND_ERROR
};

static const CtrlErrorType MastCtrlErrors[] = {
  { "Mast Undefined Error" },
  { "MAST_MAST_STATE_NOT_FOUND_ERROR" },
  { "MAST_POWER_STATE_NOT_FOUND_ERROR" },
  { "MAST_LACK_OF_POWER_ON_POWER_LINE_ERROR" },
  { "MAST_WRONG_STATE_ERROR" },
  { "MAST_WARMUP_TIMEOUT_ERROR" },
  { "MAST_POWER_LINE_TIMEOUT_ERROR" },
  { "MAST_DMA_INITIALISE_PARAMETERISATION_ERROR" },
  { "MAST_DMA_MOVETO_PARAMETERISATION_ERROR" },
  { "MAST_PHR_NOT_IDENTIFIED_ERROR" }
};

enum MastCtrlErrorsId {
  MAST_UNDEFINED_ERROR,
  MAST_MAST_STATE_NOT_FOUND_ERROR,
  MAST_POWER_STATE_NOT_FOUND_ERROR,
  MAST_LACK_OF_POWER_ON_POWER_LINE_ERROR,
  MAST_WRONG_STATE_ERROR,
  MAST_WARMUP_TIMEOUT_ERROR,
  MAST_POWER_LINE_TIMEOUT_ERROR,
  MAST_DMA_INITIALISE_PARAMETERISATION_ERROR,
  MAST_DMA_MOVETO_PARAMETERISATION_ERROR,
  MAST_PHR_NOT_IDENTIFIED_ERROR
};

#define ACTION_RET_ERROR        -1
#define ACTION_RET_OK           0
#define ACTION_RET_INITIALISING 1
#define ACTION_RET_RUNNING      2

// Here are all Action ID that have to be moved in a new .h dedicated file TODO
#define WSD_TRANSFER_DATA_ID       1103



//##################################################################################
//
//                          CONTROLLER STATE DEFINITION
//
//##################################################################################
static const int RAT_CONROLLER_OPER_MODE_INDEX = 0;
static const int RAT_CONROLLER_STANDBY_OPER_MODE = 1;
static const int RAT_CONROLLER_MAINT_OPER_MODE = 2;
static const int RAT_CONROLLER_SAFE_OPER_MODE = 3;
static const int RAT_CONROLLER_IA_OPER_MODE = 4;
static const int RAT_CONROLLER_TLM_OPER_MODE = 5;

//##################################################################################
//
//                          POWER S/S STATE DEFINITION
//
//##################################################################################

#define POWER_SOC_INDEX                50

//
// ORC POWER s/s state : lines voltages
//

// DC/DC 24 V - Main BUS
static const int ORC_POWER_RAT_ARMDRIVE_LINE_INDEX 	  = 1;
static const int ORC_POWER_RAT_WHEELSDRIVE_LINE_INDEX = 2;

//DC/DC 5V/20A
static const int ORC_POWER_RAT_DMSCPU1_LINE_INDEX 	= 3;
static const int ORC_POWER_RAT_RTCCCPU2_LINE_INDEX 	= 4;

//DC/DC 12V/12.5A (the following elements are on the same line)
static const int ORC_POWER_RAT_PTU_LINE_INDEX 	= 5;
static const int ORC_POWER_RAT_TOFCAM_LINE_INDEX 	= 6;
static const int ORC_POWER_RAT_SUNSENS_LINE_INDEX 	= 7;
static const int ORC_POWER_RAT_ARM_LINE_INDEX 	= 8;

static const int ORC_POWER_RAT_PANCAMCOMPR_LINE_INDEX = 9;
static const int ORC_POWER_RAT_PTUCTRL_LINE_INDEX 	= 10;
static const int ORC_POWER_RAT_NAVCAM_LINE_INDEX 	= 11;
static const int ORC_POWER_RAT_PANCAM_LINE_INDEX 	= 12;
static const int ORC_POWER_RAT_MINICAM_LINE_INDEX 	= 13;
static const int ORC_POWER_RAT_HAZCAM1_LINE_INDEX 	= 14;
static const int ORC_POWER_RAT_HAZCAM2_LINE_INDEX 	= 15;
static const int ORC_POWER_RAT_HAZCAM3_LINE_INDEX 	= 16;

static const int ORC_POWER_RAT_IMU_LINE_INDEX 	= 17;
static const int ORC_POWER_RAT_INCLINO_LINE_INDEX 	= 18;


static const short ORC_POWER_BMC_RT_LINE_INDEX		  = 20;
static const short ORC_POWER_BMC_RR_LINE_INDEX		  = 21;
static const short ORC_POWER_BMC_L_LINE_INDEX		  = 22;

static const short ORC_POWER_IMU_LINE_INDEX		  = 23;






//
// ORC POWER s/s state : lines switch commands
//

// cmd index of the controller state

// DC/DC 24 V - Main BUS
static const int ORC_POWER_RAT_ARMDRIVE_CMD_INDEX 	  = 30;
static const int ORC_POWER_RAT_WHEELSDRIVE_CMD_INDEX      = 31;

//DC/DC 5V/20A
static const int ORC_POWER_RAT_DMSCPU1_CMD_INDEX 	= 32;
static const int ORC_POWER_RAT_RTCCCPU2_CMD_INDEX 	= 33;

//DC/DC 12V/12.5A (the following elements are on the same line)
static const int ORC_POWER_RAT_PTU_CMD_INDEX 	        = 34;
static const int ORC_POWER_RAT_TOFCAM_CMD_INDEX 	= 35;
static const int ORC_POWER_RAT_SUNSENS_CMD_INDEX 	= 36;
static const int ORC_POWER_RAT_ARM_CMD_INDEX 	        = 37;

static const int ORC_POWER_RAT_PANCAMCOMPR_CMD_INDEX    = 38;
static const int ORC_POWER_RAT_PTUCTRL_CMD_INDEX 	= 39;
static const int ORC_POWER_RAT_NAVCAM_CMD_INDEX 	= 40;
static const int ORC_POWER_RAT_PANCAM_CMD_INDEX 	= 41;
static const int ORC_POWER_RAT_MINICAM_CMD_INDEX 	= 42;
static const int ORC_POWER_RAT_HAZCAM1_CMD_INDEX 	= 43;
static const int ORC_POWER_RAT_HAZCAM2_CMD_INDEX 	= 44;
static const int ORC_POWER_RAT_HAZCAM3_CMD_INDEX 	= 45;

static const int ORC_POWER_RAT_IMU_CMD_INDEX 	        = 46;
static const int ORC_POWER_RAT_INCLINO_CMD_INDEX 	= 47;

static const short ORC_POWER_BMC_RT_CMD_INDEX		  = 48;
static const short ORC_POWER_BMC_RR_CMD_INDEX		  = 49;
static const short ORC_POWER_BMC_L_CMD_INDEX		  = 50;
static const short ORC_POWER_IMU_CMD_INDEX		  = 51;


static const short POWER_ACTION_ID_INDEX   	= 55; 
static const short POWER_ACTION_RET_INDEX   	= 56; 


// Solar Arrays
//line voltage
//static const short ORC_POWER_SADE_RIGHT_N_LINE_INDEX 	= 54;
//static const short ORC_POWER_SADE_RIGHT_R_LINE_INDEX 	= 55;
//static const short ORC_POWER_SADE_LEFT_N_LINE_INDEX  	= 56;
//static const short ORC_POWER_SADE_LEFT_R_LINE_INDEX  	= 57;
//static const short ORC_HEATER_SADE_N_LINE_INDEX		= 58;
//static const short ORC_HEATER_SADE_R_LINE_INDEX 	= 59;
// line cmd
//static const short ORC_POWER_SADE_RIGHT_N_CMD_INDEX 	= 60;
//static const short ORC_POWER_SADE_RIGHT_R_CMD_INDEX 	= 61;
//static const short ORC_POWER_SADE_LEFT_N_CMD_INDEX 	= 62;
//static const short ORC_POWER_SADE_LEFT_R_CMD_INDEX 	= 63;
//static const short ORC_HEATER_SADE_N_CMD_INDEX 		= 64;
//static const short ORC_HEATER_SADE_R_CMD_INDEX 		= 65;
// Comms
//static const short ORC_POWER_UHF1_LINE_INDEX  		= 66;
//static const short ORC_POWER_UHF2_LINE_INDEX 		= 67;



//-----------------------------------------------------------------------
// ATMOSPHERE MODEL
//-----------------------------------------------------------------------
static const short  ORC_ATMOSPHERE_GROUND_TEMP_INDEX      = 0;
static const short  ORC_ATMOSPHERE_MAX_GROUND_TEMP_INDEX  = 1;
static const short  ORC_ATMOSPHERE_MEAN_GROUND_TEMP_INDEX = 2; 
static const short  ORC_ATMOSPHERE_SKY_TEMP_INDEX         = 3;
static const short  ORC_ATMOSPHERE_SOLAR_FLUX_INDEX       = 4; 
static const short  ORC_ATMOSPHERE_SKY_IR_FLUX_INDEX      = 5; 
static const short  ORC_ATMOSPHERE_DIRECT_FLUX_INDEX      = 6;
static const short  ORC_ATMOSPHERE_SCATTERED_FLUX_INDEX   = 7; 
static const short  ORC_ATMOSPHERE_INCIDENT_FLUX_INDEX    = 8;
  
//-----------------------------------------------------------------------
// ORBITAL MODEL
//-----------------------------------------------------------------------
static const short  ORC_ORBITAL_ROVER2ORBITERAZIMUTH_INDEX   = 0;
static const short  ORC_ORBITAL_ROVER2ORBITERELEVATION_INDEX = 1;
static const short  ORC_ORBITAL_ROVER2ORBITERRANGE_INDEX     = 2;
// GCS to LANDER information
static const short  ORC_ORBITAL_GCS2LANDERAZIMUTH_INDEX   = 3; 
static const short  ORC_ORBITAL_GCS2LANDERELEVATION_INDEX = 4;
static const short  ORC_ORBITAL_GCS2LANDERRANGE_INDEX     = 5;
// GCS to ROVER information
static const short  ORC_ORBITAL_GCS2ROVERAZIMUTH_INDEX   = 6; 
static const short  ORC_ORBITAL_GCS2ROVERELEVATION_INDEX = 7;
static const short  ORC_ORBITAL_GCS2ROVERRANGE_INDEX     = 8;
// GCS to ORBITER information
static const short  ORC_ORBITAL_GCS2ORBITERAZIMUTH_INDEX   = 9;
static const short  ORC_ORBITAL_GCS2ORBITERELEVATION_INDEX = 10;
static const short  ORC_ORBITAL_GCS2ORBITERRANGE_INDEX     = 11;  
// ROVER to LANDER information
static const short  ORC_ORBITAL_ROVER2LANDERAZIMUTH_INDEX   = 12;
static const short  ORC_ORBITAL_ROVER2LANDERELEVATION_INDEX = 13;
static const short  ORC_ORBITAL_ROVER2LANDERRANGE_INDEX     = 14;
// SUN position information
static const short  ORC_ORBITAL_SUNAZIMUTH_INDEX   = 15;
static const short  ORC_ORBITAL_SUNELEVATION_INDEX = 16; 
static const short  ORC_ORBITAL_SUNRANGE_INDEX     = 17;
// rover longitude/latitude
static const short  ORC_ORBITAL_ROVER_LONGITUDE_INDEX = 18;
static const short  ORC_ORBITAL_ROVER_LATITUDE_INDEX  = 19;

//-----------------------------------------------------------------------
// COMMS MODEL
//-----------------------------------------------------------------------

static const short  COMMS_ROVER2ORBITER_LINKBITRATE_INDEX  = 0;
static const short  COMMS_ROVER2ORBITER_TARGETINVIEW_INDEX = 1;

static const short  COMMS_GCS2ROVER_LINKBITRATE_INDEX  = 2;
static const short  COMMS_GCS2ROVER_TARGETINVIEW_INDEX = 3;

static const short  COMMS_GCS2ORBITER_LINKBITRATE_INDEX  = 4;
static const short  COMMS_GCS2ORBITER_TARGETINVIEW_INDEX = 5;

static const short  COMMS_ROVER2LANDER_LINKBITRATE_INDEX  = 6;
static const short  COMMS_ROVER2LANDER_TARGETINVIEW_INDEX = 7;

static const short  COMMS_TC_PACKET_DELAY_INDEX = 20;
static const short  COMMS_TC_PACKET_DROP_RATE_INDEX = 21;
static const short  COMMS_TC_UPLOAD_CAPACITY_LIMIT_INDEX = 22;
static const short  COMMS_TM_POWNLOAD_CAPACITY_LIMIT_INDEX = 23;
static const short  COMMS_TM_PACKET_DELAY_INDEX = 24;
static const short  COMMS_TM_PACKET_DROP_RATE_INDEX = 25;
static const short  COMMS_LOG_VERBOSITY_LEVEL_INDEX = 26;


//-----------------------------------------------------------------------
// ORC MAST
//-----------------------------------------------------------------------
static const short LRM_MAST_STATUS_INDEX	= 0;
static const short LRM_MAST_OPER_MODE_INDEX	= 0;
static const short LRM_MAST_TEMPERATURE_INDEX	= 1;

static const short LRM_MAST_DES_Q1_INDEX	= 4;
static const short LRM_MAST_DES_Q2_INDEX	= 5;

static const short LRM_MAST_CURRENT_Q1_INDEX	= 6;
static const short LRM_MAST_CURRENT_Q2_INDEX	= 7;

static const short LRM_MAST_TRAJ_DUR_INDEX     = 8;
static const short LRM_MAST_POWER_CONS_INDEX   = 9;
static const short LRM_MAST_DATARATE_INDEX     = 10;

static const short LRM_MAST_Q1_INIT_INDEX	= 12;
static const short LRM_MAST_Q2_INIT_INDEX	= 13;

static const short LRM_MAST_Q1_FINAL_INDEX	 = 14;
static const short LRM_MAST_Q2_FINAL_INDEX	 = 15;
static const short LRM_MAST_CURR_TRAJ_TIME_INDEX = 16;

static const short LRM_MAST_ACTION_ID_INDEX    = 20;
static const short LRM_MAST_ACTION_RET_INDEX   = 21;


//
// ORC RRP
//
static const short RRP_STATUS_INDEX		= 0;
static const short RRP_OPER_MODE_INDEX		= 0;
static const short RRP_TEMPERATURE_INDEX	= 1;

static const short RRP_CURRENT_Q1_INDEX	= 2;
static const short RRP_CURRENT_Q2_INDEX	= 3;
static const short RRP_CURRENT_Q3_INDEX	= 4;
static const short RRP_CURRENT_Q4_INDEX	= 5;
static const short RRP_CURRENT_Q5_INDEX	= 6;

static const short RRP_DES_Q1_INDEX	= 7;
static const short RRP_DES_Q2_INDEX	= 8;
static const short RRP_DES_Q3_INDEX	= 9;
static const short RRP_DES_Q4_INDEX	= 10;
static const short RRP_DES_Q5_INDEX	= 11;

static const short RRP_CURRENT_X_INDEX	= 12;
static const short RRP_CURRENT_Y_INDEX	= 13;
static const short RRP_CURRENT_Z_INDEX	= 14;
static const short RRP_CURRENT_RX_INDEX	= 15;
static const short RRP_CURRENT_RY_INDEX	= 16;
static const short RRP_CURRENT_RZ_INDEX	= 17;

static const short RRP_DES_DX_INDEX	= 18;
static const short RRP_DES_DY_INDEX	= 19;
static const short RRP_DES_DZ_INDEX	= 20;
static const short RRP_DES_DRX_INDEX	= 21;
static const short RRP_DES_DRY_INDEX	= 22;
static const short RRP_DES_DRZ_INDEX	= 23;

static const short RRP_TRAJ_DUR_INDEX     = 24;
static const short RRP_POWER_CONS_INDEX   = 25;
static const short RRP_DATARATE_INDEX     = 26; 

static const short RRP_ACTION_ID_INDEX    = 27; 
static const short RRP_ACTION_RET_INDEX   = 28; 

static const short RRP_Q1_INIT_INDEX	= 30;
static const short RRP_Q2_INIT_INDEX	= 31;
static const short RRP_Q3_INIT_INDEX	= 32;
static const short RRP_Q4_INIT_INDEX	= 33;
static const short RRP_Q5_INIT_INDEX	= 34;

static const short RRP_Q1_FINAL_INDEX	= 35;
static const short RRP_Q2_FINAL_INDEX	= 36;
static const short RRP_Q3_FINAL_INDEX	= 37;
static const short RRP_Q4_FINAL_INDEX	= 38;
static const short RRP_Q5_FINAL_INDEX	= 39;

static const short RRP_CURR_TRAJ_TIME_INDEX = 40;

// (m/sec, deg/sec) 
#define RRP_MAX_TRANSLATION_SPEED 0.05 
#define RRP_MAX_ROTATION_SPEED    3.0  
#define RRP_MIN_OPER_TEMPERATURE  260.0
#define RRP_WARMUP_TIMEOUT        1000
#define RRP_MIN_LINE_VOLTAGE      2
#define RRP_SWITCH_OFF_TIME       2 

#define RRP_DOF                   5
#define RRP_OPER_MODE_OFF         0
#define RRP_OPER_MODE_STNDBY      1
#define RRP_OPER_MODE_MOVING           2
#define RRP_OPER_MODE_INITIALISING     3
#define RRP_OPER_MODE_SWITCHING_OFF    4
//
//  Solar Array
//
// indexes of the controller state vector
static const short SA_STATUS_INDX 	= 0;
static const short SA_CURRENT_Q1_INDX	= 2;
static const short SA_CURRENT_Q2_INDX	= 3;
static const short SA_CURRENT_Q3_INDX	= 4;
static const short SA_CURRENT_Q4_INDX	= 5;

static const short SA_TEMPERATURE_INDX	= 1;
static const short SA_DES_Q1_INDX	= 7;
static const short SA_DES_Q2_INDX	= 8;
static const short SA_DES_Q3_INDX	= 9;
static const short SA_DES_Q4_INDX	= 10;
static const short SA_TRAJ_DUR_INDX	= 13;
static const short SA_POWER_CONS_INDEX	= 14;
static const short SA_TEMPERATURE_INDEX	= 15;
static const short SA_DATARATE_INDEX	= 16;

static const short SA_ACTION_ID_INDEX   = 17; // 12-nov-2010 (Action ID)
static const short SA_ACTION_RET_INDEX  = 18; // 12-nov-2010 (OK/ERROR/RUNNING)

//##################################################################################
//
//                          DATA LINES CONSTANTS DEFINITION
//
//##################################################################################

static const short DHS_RAT_ARMDRIVE_LINE_INDEX 	  = 1;
static const short DHS_RAT_WHEELSDRIVE_LINE_INDEX = 2;

//DC/DC 5V/20A
static const short DHS_RAT_DMSCPU1_LINE_INDEX 	= 3;
static const short DHS_RAT_RTCCCPU2_LINE_INDEX 	= 4;

//DC/DC 12V/12.5A (the following elements are on the same line)
static const short DHS_RAT_PTU_LINE_INDEX 	= 5;
static const short DHS_RAT_TOFCAM_LINE_INDEX 	= 6;
static const short DHS_RAT_SUNSENS_LINE_INDEX 	= 7;
static const short DHS_RAT_ARM_LINE_INDEX 	= 8;

static const short DHS_RAT_PANCAMCOMPR_LINE_INDEX = 9;
static const short DHS_RAT_PTUCTRL_LINE_INDEX 	  = 10;
static const short DHS_RAT_NAVCAM_LINE_INDEX 	  = 11;
static const short DHS_RAT_PANCAM_LINE_INDEX 	  = 12;
static const short DHS_RAT_MINICAM_LINE_INDEX 	  = 13;
static const short DHS_RAT_HAZCAM_LINE_INDEX 	  = 14;

static const short DHS_RAT_IMU_LINE_INDEX 	  = 15;
static const short DHS_RAT_INCLINO_LINE_INDEX 	  = 16;

static const short DHS_GNC_LINE_INDEX             = 17;


//##################################################################################
//
//                          PAN CAM CONSTANTS DEFINITION
//
//##################################################################################

// PanCam Indexes

static const short LRM_PANCAM_OPER_MODE_INDEX   = 0;
static const short LRM_PANCAMALL_OPER_MODE_INDEX  = 1;
static const short LRM_PANCAM1_OPER_MODE_INDEX  = 2;
static const short LRM_PANCAM2_OPER_MODE_INDEX   = 3;
static const short LRM_PANCAM3_OPER_MODE_INDEX  = 4;
static const short LRM_PANCAM4_OPER_MODE_INDEX  = 5;
static const short LRM_PANCAM5_OPER_MODE_INDEX   = 6;
static const short LRM_PANCAM6_OPER_MODE_INDEX   = 7;
static const short LRM_PANCAM_TEMPERATURE_INDEX	= 8;
static const short LRM_PANCAM_DATARATE_INDEX	= 9; 
static const short LRM_PANCAM_POWERCONS_INDEX	= 10; 
static const short LRM_PANCAM1_ACQ_PERIOD_INDEX	= 12;
static const short LRM_PANCAM1_COMPR_LEVEL_INDEX = 13;
static const short LRM_PANCAM2_ACQ_PERIOD_INDEX	= 14;
static const short LRM_PANCAM2_COMPR_LEVEL_INDEX = 15;
static const short LRM_PANCAM3_ACQ_PERIOD_INDEX	= 16;
static const short LRM_PANCAM3_COMPR_LEVEL_INDEX = 17;
static const short LRM_PANCAM4_ACQ_PERIOD_INDEX	= 18;
static const short LRM_PANCAM4_COMPR_LEVEL_INDEX = 19;
static const short LRM_PANCAM5_ACQ_PERIOD_INDEX	= 20;
static const short LRM_PANCAM5_COMPR_LEVEL_INDEX = 21;
static const short LRM_PANCAM6_ACQ_PERIOD_INDEX	= 22;
static const short LRM_PANCAM6_COMPR_LEVEL_INDEX = 23;
static const short LRM_PANCAM1_DOWNSAMPLE_INDEX  = 24;
static const short LRM_PANCAM2_DOWNSAMPLE_INDEX  = 25;
static const short LRM_PANCAM3_DOWNSAMPLE_INDEX  = 26;
static const short LRM_PANCAM4_DOWNSAMPLE_INDEX  = 27;
static const short LRM_PANCAM5_DOWNSAMPLE_INDEX  = 28;
static const short LRM_PANCAM6_DOWNSAMPLE_INDEX  = 29;

static const short LRM_PANCAM_ACTION_ID_INDEX       = 30; 
static const short LRM_PANCAM_ACTION_RET_INDEX      = 31; 

//##################################################################################
//
//                          INCLINO CONSTANTS DEFINITION
//
//##################################################################################

// Inclino Indexes
static const short INCLINO_OPER_MODE_INDEX	= 0;
static const short INCLINO_TEMPERATURE_INDEX	= 1;
static const short INCLINO_DATARATE_INDEX	= 2;

static const short INCLINO_ROVER_POSE_X = 3;
static const short INCLINO_ROVER_POSE_Y = 4;
static const short INCLINO_ROVER_POSE_Z = 5;
static const short INCLINO_ROVER_POSE_RX = 6;
static const short INCLINO_ROVER_POSE_RY = 7;
static const short INCLINO_ROVER_POSE_RZ = 8;
static const short INCLINO_ROVER_ROLL  = 9;
static const short INCLINO_ROVER_PITCH = 10;

static const short INCLINO_ACTION_ID_INDEX       = 20;
static const short INCLINO_ACTION_RET_INDEX      = 21;

//##################################################################################
//
//                          SUNSENS CONSTANTS DEFINITION
//
//##################################################################################

// SunSens Indexes
static const short SUNSENS_OPER_MODE_INDEX	= 0;
static const short SUNSENS_TEMPERATURE_INDEX	= 1;
static const short SUNSENS_DATARATE_INDEX	= 2;
static const short SUNSENS_POWERCONS_INDEX	= 3; 

static const short SUNSENS_ACTION_ID_INDEX       = 4;
static const short SUNSENS_ACTION_RET_INDEX      = 5;

//##################################################################################
//
//                          IMU CONSTANTS DEFINITION
//
//##################################################################################

// IMU Indexes
static const short IMU_OPER_MODE_INDEX	 = 0;
static const short IMU_TEMPERATURE_INDEX = 1;
static const short IMU_DATARATE_INDEX	 = 2;
static const short IMU_POWERCONS_INDEX	=  3; 

static const short IMU_ROVER_V_X = 3;
static const short IMU_ROVER_V_Y = 4;
static const short IMU_ROVER_V_Z = 5;
static const short IMU_ROVER_V_RX = 6;
static const short IMU_ROVER_V_RY = 7;
static const short IMU_ROVER_V_RZ = 8;

static const short IMU_ROVER_DV_X = 9;
static const short IMU_ROVER_DV_Y = 10;
static const short IMU_ROVER_DV_Z = 11;
static const short IMU_ROVER_DV_RX = 12;
static const short IMU_ROVER_DV_RY = 13;
static const short IMU_ROVER_DV_RZ = 14;

static const short IMU_ACTION_ID_INDEX   = 20;
static const short IMU_ACTION_RET_INDEX  = 21;

//##################################################################################
//
//                          TOF CAM CONSTANTS DEFINITION
//
//##################################################################################

// TOF Cam Indexes
static const short LRM_TOFCAM_OPER_MODE_INDEX	= 0;
static const short LRM_TOFCAM_TEMPERATURE_INDEX	= 1;
static const short LRM_TOFCAM_DATARATE_INDEX	= 2;
static const short LRM_TOFCAM_POWERCONS_INDEX	= 3; 
static const short LRM_TOFCAM_DOWNSAMPLE_INDEX  = 4;

static const short LRM_TOFCAM_ACTION_ID_INDEX       = 5;
static const short LRM_TOFCAM_ACTION_RET_INDEX      = 6;

//##################################################################################
//
//                          MINI CAM CONSTANTS DEFINITION
//
//##################################################################################

// MiniCam Indexes
static const short LRM_MINICAM_OPER_MODE_INDEX	 = 0;
static const short LRM_MINICAM_TEMPERATURE_INDEX = 1;
static const short LRM_MINICAM_DATARATE_INDEX	 = 2;
static const short LRM_MINICAM_POWERCONS_INDEX	 = 3; 
static const short LRM_MINICAM_ACQ_PERIOD_INDEX	 = 4;
static const short LRM_MINICAM_COMPR_LEVEL_INDEX = 5;
static const short LRM_MINICAM_DOWNSAMPLE_INDEX  = 6;

static const short LRM_MINICAM_ACTION_ID_INDEX       = 8;
static const short LRM_MINICAM_ACTION_RET_INDEX      = 9;

//##################################################################################
//
//                          HAZ CAM CONSTANTS DEFINITION
//
//##################################################################################

// HazCam Indexes
static const short LRM_HAZCAM_OPER_MODE_INDEX	= 0;
static const short LRM_HAZCAM1_OPER_MODE_INDEX	= 1;
static const short LRM_HAZCAM2_OPER_MODE_INDEX	= 2;
static const short LRM_HAZCAM3_OPER_MODE_INDEX	= 3;
static const short LRM_HAZCAM_TEMPERATURE_INDEX	= 4;
static const short LRM_HAZCAM_DATARATE_INDEX	= 5;
static const short LRM_HAZCAM_POWERCONS_INDEX	= 6; 
static const short LRM_HAZCAM1_ACQ_PERIOD_INDEX	= 7;
static const short LRM_HAZCAM1_COMPR_LEVEL_INDEX= 8;
static const short LRM_HAZCAM2_ACQ_PERIOD_INDEX	= 9;
static const short LRM_HAZCAM2_COMPR_LEVEL_INDEX = 10;
static const short LRM_HAZCAM3_ACQ_PERIOD_INDEX	 = 11;
static const short LRM_HAZCAM3_COMPR_LEVEL_INDEX = 12;
static const short LRM_HAZCAM1_DOWNSAMPLE_INDEX  = 13;
static const short LRM_HAZCAM2_DOWNSAMPLE_INDEX  = 14;
static const short LRM_HAZCAM3_DOWNSAMPLE_INDEX  = 15;
static const short LRM_HAZCAM_ACTION_ID_INDEX   = 16;
static const short LRM_HAZCAM_ACTION_RET_INDEX  = 17;



//##################################################################################
//
//                          NAV CAM INDEXES CONSTANTS DEFINITION
//
//##################################################################################

static const short LRM_NAVCAM_OPER_MODE_INDEX  = 0;
static const short LRM_NAVCAM1_OPER_MODE_INDEX = 1;
static const short LRM_NAVCAM2_OPER_MODE_INDEX = 2;
static const short LRM_NAVCAM3_OPER_MODE_INDEX = 3;
static const short LRM_NAVCAM_TEMPERATURE_INDEX	= 4;
static const short LRM_NAVCAM_DATARATE_INDEX	= 5;
static const short LRM_NAVCAM_POWERCONS_INDEX	= 6; 
static const short LRM_NAVCAM1_ACQ_PERIOD_INDEX	 = 7;
static const short LRM_NAVCAM1_COMPR_LEVEL_INDEX = 8; 
static const short LRM_NAVCAM2_ACQ_PERIOD_INDEX	 = 9;
static const short LRM_NAVCAM2_COMPR_LEVEL_INDEX = 10; 
static const short LRM_NAVCAM3_ACQ_PERIOD_INDEX	 = 11;
static const short LRM_NAVCAM3_COMPR_LEVEL_INDEX = 12;
static const short LRM_NAVCAM1_DOWNSAMPLE_INDEX  = 13;
static const short LRM_NAVCAM2_DOWNSAMPLE_INDEX  = 14;
static const short LRM_NAVCAM3_DOWNSAMPLE_INDEX  = 15;


static const short NAVCAM_ACTION_ID_INDEX       = 16; // 12-nov-2010 (Action ID)
static const short NAVCAM_ACTION_RET_INDEX      = 17; // 12-nov-2010 (OK/ERROR/RUNNING)



//##################################################################################
//
// INDEXES FOR THE ORBITER AND TIMEKEEPING
//
//##################################################################################

static const short OT_SUN_ELEVATION_INDX	= 0;
static const short OT_SUN_AZIMUTH_INDX		= 1;

static const short OT_R2O_ELEVATION_INDX	= 2;
static const short OT_R2O_AZIMUTH_INDX		= 3;

static const short OT_O2E_OUT_RADIAL_INDX	= 4;
static const short OT_O2E_OUT_TRANSVERSE_INDX	= 5;
static const short OT_O2E_OUT_NORMAL_INDX	= 6;

static const short OT_DTE_ELEVATION_TO_INDX	= 7;
static const short OT_DTE_AZIMUTH_TO_INDX	= 8;
static const short OT_DTE_ELEVATION_FROM_INDX	= 9;
static const short OT_DTE_AZIMUTH_FROM_INDX	= 10;

//##################################################################################
//
// INDEXES FOR THE ATMOSPHERE
//
//##################################################################################
static const short ATM_TEMPERATURE_INDX		= 0;
static const short ATM_SURF_TEMPERATURE_INDX	= 1;
static const short ATM_SURF_IRRADIANCE_INDX	= 2;
static const short ATM_SURF_THERMAL_IRRADIACE_INDX	= 3;
static const short ATM_OPTICAL_DEPTH_INDX	= 4;
static const short ATM_WIND_VEL_X_INDX		= 5;
static const short ATM_WIND_VEL_Y_INDX		= 6;
static const short ATM_WIND_VEL_Z_INDX		= 7;
//##################################################################################
//
//                          LRM CONSTANTS DEFINITION
//
//##################################################################################

#define LRM_OPER_MODE_INDEX        0


#define LRM_DRIVING_ANGLE_FL_INDEX 5
#define LRM_DRIVING_ANGLE_FR_INDEX 6
#define LRM_DRIVING_ANGLE_RL_INDEX 7
#define LRM_DRIVING_ANGLE_RR_INDEX 8

#define LRM_DRIVING_SPEED_FL_INDEX 9
#define LRM_DRIVING_SPEED_FR_INDEX 10
#define LRM_DRIVING_SPEED_RL_INDEX 11
#define LRM_DRIVING_SPEED_RR_INDEX 12

#define LRM_STEERING_ANGLE_FL_INDEX 13
#define LRM_STEERING_ANGLE_FR_INDEX 14
#define LRM_STEERING_ANGLE_RL_INDEX 15
#define LRM_STEERING_ANGLE_RR_INDEX 16

#define LRM_STEERING_SPEED_FL_INDEX 17
#define LRM_STEERING_SPEED_FR_INDEX 18
#define LRM_STEERING_SPEED_RL_INDEX 19
#define LRM_STEERING_SPEED_RR_INDEX 20

#define LRM_WMC_TEMPERATURE_INDEX  21

#define LRM_ROVER_POSEX_INDEX   23
#define LRM_ROVER_POSEY_INDEX   24
#define LRM_ROVER_POSEZ_INDEX   25
#define LRM_ROVER_POSERX_INDEX  26
#define LRM_ROVER_POSERY_INDEX  27
#define LRM_ROVER_POSERZ_INDEX  28

#define LRM_TEMPERATURE_INDEX   29
#define LRM_DATARATE_INDEX      30

#define LRM_ACTION_ID_INDEX     31 // 12-nov-2010 (Action ID)
#define LRM_ACTION_RET_INDEX    32 // 12-nov-2010 (OK/ERROR/RUNNING)
#define GNC_ACTION_ID_INDEX     31 // For compatibility in the controller
#define GNC_ACTION_RET_INDEX    32 // For compatibility in the controller

#define LRM_ROVER_ACCX_INDEX   33
#define LRM_ROVER_ACCY_INDEX   34
#define LRM_ROVER_ACCZ_INDEX   35
#define LRM_ROVER_VELRX_INDEX  36
#define LRM_ROVER_VELRY_INDEX  37
#define LRM_ROVER_VELRZ_INDEX  38

#define LRM_DRIVING_LINSPEED_INDEX  39
#define LRM_DRIVING_ACKANGLE_INDEX 40

#define LRM_REQ_DRIVING_SPEED_FL_INDEX 51
#define LRM_REQ_DRIVING_SPEED_FR_INDEX 52
#define LRM_REQ_DRIVING_SPEED_RL_INDEX 53
#define LRM_REQ_DRIVING_SPEED_RR_INDEX 54

#define LRM_REQ_STEERING_ANGLE_FL_INDEX 55
#define LRM_REQ_STEERING_ANGLE_FR_INDEX 56
#define LRM_REQ_STEERING_ANGLE_RL_INDEX 57
#define LRM_REQ_STEERING_ANGLE_RR_INDEX 58

#define LRM_DES_DRIVING_SPEED_FL_INDEX 59
#define LRM_DES_DRIVING_SPEED_FR_INDEX 60
#define LRM_DES_DRIVING_SPEED_RL_INDEX 61
#define LRM_DES_DRIVING_SPEED_RR_INDEX 62

#define LRM_DES_STEERING_ANGLE_FL_INDEX 63
#define LRM_DES_STEERING_ANGLE_FR_INDEX 64
#define LRM_DES_STEERING_ANGLE_RL_INDEX 65
#define LRM_DES_STEERING_ANGLE_RR_INDEX 66

#define LRM_WHEEL_FL_FX_INDEX 70
#define LRM_WHEEL_FL_FY_INDEX 71
#define LRM_WHEEL_FL_FZ_INDEX 72
#define LRM_WHEEL_FR_FX_INDEX 73
#define LRM_WHEEL_FR_FY_INDEX 74
#define LRM_WHEEL_FR_FZ_INDEX 75
#define LRM_WHEEL_RL_FX_INDEX 76
#define LRM_WHEEL_RL_FY_INDEX 77
#define LRM_WHEEL_RL_FZ_INDEX 78
#define LRM_WHEEL_RR_FX_INDEX 79
#define LRM_WHEEL_RR_FY_INDEX 80
#define LRM_WHEEL_RR_FZ_INDEX 81

#define LRM_BEKKER_RES_INDEX 82

#define LRM_WHEEL_FL_POSEX_INDEX 83
#define LRM_WHEEL_FL_POSEY_INDEX 84
#define LRM_WHEEL_FL_POSEZ_INDEX 85
#define LRM_WHEEL_FR_POSEX_INDEX 86
#define LRM_WHEEL_FR_POSEY_INDEX 87
#define LRM_WHEEL_FR_POSEZ_INDEX 88
#define LRM_WHEEL_RL_POSEX_INDEX 89
#define LRM_WHEEL_RL_POSEY_INDEX 90
#define LRM_WHEEL_RL_POSEZ_INDEX 91
#define LRM_WHEEL_RR_POSEX_INDEX 92
#define LRM_WHEEL_RR_POSEY_INDEX 93
#define LRM_WHEEL_RR_POSEZ_INDEX 94




 
//
// Thermal (In the ThermalState)
//
#define THERMAL_WAC_DES_TEMP_INDX         1
#define THERMAL_HRC_DES_TEMP_INDX         2
#define THERMAL_WISDOM_DES_TEMP_INDX      3
#define THERMAL_CLUPI_DES_TEMP_INDX       4
#define THERMAL_RAMANLIBS_DES_TEMP_INDX   5
#define THERMAL_MIMOS_DES_TEMP_INDX       6
#define THERMAL_MIMA_DES_TEMP_INDX        7

#define THERMAL_WAC_CURR_TEMP_INDX        8
#define THERMAL_HRC_CURR_TEMP_INDX        9
#define THERMAL_WISDOM_CURR_TEMP_INDX    10
#define THERMAL_CLUPI_CURR_TEMP_INDX     11
#define THERMAL_RAMANLIBS_CURR_TEMP_INDX 12
#define THERMAL_MIMOS_CURR_TEMP_INDX     13
#define THERMAL_MIMA_CURR_TEMP_INDX      14

#define THERMAL_POWER_CONS_INDX          15

#define THERMAL_ACTION_ID_INDEX          16 // 12-nov-2010 (Action ID)
#define THERMAL_ACTION_RET_INDEX         17 // 12-nov-2010 (OK/ERROR/RUNNING)
//
// DHU (In the DHUState)
//
#define DHU_STATUS           1
#define DHU_INACTIVE         0
#define DHU_SWITCH_ON        1
#define DHU_UPLOAD_ORBITER   2
#define DHU_DOWNLOAD_ORBITER 3
#define DHU_DATA_VOLUME      4
#define DHU_DATA_UPLOADED    5

#define DHU_WAC_OPER_MODE_INDX 6
#define DHU_HRC_OPER_MODE_INDX 7
#define DHU_WISDOM_OPER_MODE_INDX 8
#define DHU_CLUPI_OPER_MODE_INDX 9
#define DHU_RAMANLIBS_OPER_MODE_INDX 10
#define DHU_MIMOS_OPER_MODE_INDX 11
#define DHU_MIMA_OPER_MODE_INDX 12
#define DHU_R2O_OPER_MODE_INDX 13

#define DHU_WAC_DATA_VOLUME_INDX 14
#define DHU_HRC_DATA_VOLUME_INDX 15
#define DHU_WISDOM_DATA_VOLUME_INDX 16
#define DHU_CLUPI_DATA_VOLUME_INDX 17
#define DHU_RAMANLIBS_DATA_VOLUME_INDX 18
#define DHU_MIMOS_DATA_VOLUME_INDX 19
#define DHU_MIMA_DATA_VOLUME_INDX 20
#define DHU_R2O_DATA_VOLUME_INDX 21

#define DHU_WAC_DATA_TRANSM_INDX 22
#define DHU_HRC_DATA_TRANSM_INDX 23
#define DHU_WISDOM_DATA_TRANSM_INDX 24
#define DHU_CLUPI_DATA_TRANSM_INDX 25
#define DHU_RAMANLIBS_DATA_TRANSM_INDX 26
#define DHU_MIMOS_DATA_TRANSM_INDX 27
#define DHU_MIMA_DATA_TRANSM_INDX 28
#define DHU_R2O_DATA_TRANSM_INDX 29

#define DHU_MEMMASS_EXCEEDED_INDX 30

#define DHU_MEMMASS_EXCEEDED 1
#define DHU_MEMMASS_NOT_EXCEEDED 0

// define the different modes of operations
#define DHU_WAC_INACTIVE_OPER_MODE 0
#define DHU_WAC_STANDBY_OPER_MODE 1
#define DHU_WAC_SINGLE_IMAGE_MODE 2
#define DHU_WAC_STEREO_PAIR_IMAGE_MODE 3 
#define DHU_WAC_SINGLE_FILTER_PANORAMA_MODE 4 
#define DHU_WAC_STEREO_FILTER_PANORAMA_MODE 5
#define DHU_WAC_RGB_FILTER_PANORAMA_MODE 6
#define DHU_WAC_GEOLOGY_PANORAMA_MODE 7
#define DHU_WAC_STELAR_NAVIGATION_MODE 8
#define DHU_WAC_SOLAR_IMAGING_SEQUENCE_MODE 9 


#define POWER_MAST_STATE_INDX            45
#define POWER_HRC_STATE_INDX            46
#define POWER_DRILLANDSPDS_CE_STATE_INDX 47

//
// INDEXES FOR THE LOCOMOTION
//
#define LOC_STATUS   1
#define LOC_POSX     2
#define LOC_POSY     3
#define LOC_POSZ     4
#define LOC_POSRZ    5
#define LOC_IMU_DX   6
#define LOC_IMU_DY   7
#define LOC_IMU_DZ   8
#define LOC_SPEED_W1 9
#define LOC_SPEED_W2 10
#define LOC_SPEED_W3 11
#define LOC_SPEED_W4 12
#define LOC_SPEED_W5 13
#define LOC_SPEED_W6 14
#define LOC_POS_W1   15
#define LOC_POS_W2   16
#define LOC_POS_W5   17
#define LOC_POS_W6   18
#define LOC_POWER_CONS_INDX   19

#define LOC_INACTIVE 0
#define LOC_HEATING  1
#define LOC_SWITCH_ON 2
#define LOC_MOVE   3
#define LOC_MOVING 4
#define LOC_MOTION_ENDED 5




//##################################################################################
//
//                          COMMS PARAMETERS DEFINITION
//
//##################################################################################
#define COMMS_CMD_INDEX 0
#define TTC_DEFAULT_MIN_LINE_VOLTAGE  10

static const short COMMS_ACTION_ID_INDEX       = 1; // 12-nov-2010 (Action ID)
static const short COMMS_ACTION_RET_INDEX      = 2; // 12-nov-2010 (OK/ERROR/RUNNING)

//##################################################################################
//
//                          IMU CONSTANTS DEFINITION
//
//##################################################################################
// TOFCam Operational Modes
#define IMU_OPER_MODE_OFF                    0
#define IMU_OPER_MODE_HEATING 		1
#define IMU_OPER_MODE_STANDBY 		2
#define IMU_OPER_MODE_OPERATING              3


//##################################################################################
//
//                          TOF CAM CONSTANTS DEFINITION
//
//##################################################################################
// TOFCam Operational Modes
#define LRM_TOFCAM_OPER_MODE_OFF                    0
#define LRM_TOFCAM_OPER_MODE_HEATING 		1
#define LRM_TOFCAM_OPER_MODE_STANDBY 		2
#define LRM_TOFCAM_OPER_MODE_OPERATING              3

//##################################################################################
//
//                          MINI CAM CONSTANTS DEFINITION
//
//##################################################################################
// MINICam Operational Modes
#define LRM_MINICAM_OPER_MODE_OFF                    0
#define LRM_MINICAM_OPER_MODE_HEATING 		1
#define LRM_MINICAM_OPER_MODE_STANDBY 		2
#define LRM_MINICAM_OPER_MODE_OPERATING              3

//##################################################################################
//
//                          HAZ CAM CONSTANTS DEFINITION
//
//##################################################################################
// HAZCam Operational Modes
#define LRM_HAZCAM_OPER_MODE_OFF                    0
#define LRM_HAZCAM_OPER_MODE_HEATING 		1
#define LRM_HAZCAM_OPER_MODE_STANDBY 		2
#define LRM_HAZCAM_OPER_MODE_OPERATING              3

//##################################################################################
//
//                          PAN CAM CONSTANTS DEFINITION
//
//##################################################################################

// PanCam Operational Modes
#define LRM_PANCAM_OPER_MODE_OFF                    0
#define LRM_PANCAM_OPER_MODE_HEATING 		1
#define LRM_PANCAM_OPER_MODE_STANDBY 		2
#define LRM_PANCAM_OPER_MODE_OPERATING              3


//##################################################################################
//
//                          PAN CAM CONSTANTS DEFINITION
//
//##################################################################################

// PanCam Operational Modes
#define LRM_NAVCAM_OPER_MODE_OFF                    0
#define LRM_NAVCAM_OPER_MODE_HEATING 		1
#define LRM_NAVCAM_OPER_MODE_STANDBY 		2
#define LRM_NAVCAM_OPER_MODE_OPERATING              3
#define LRM_NAVCAM_OPER_MODE_ACQUIRING              3


// resources consumption constants

// pan cam in general
#define PANCAM_OPER_MODE_OFF_POWER_CONS                      0.0
// #define PANCAM_OPER_MODE_STANDBY_POWER_CONS                  4.08
// #define PANCAM_OPER_MODE_OPERATING_POWER_CONS                3
// wac l
#define PANCAM_OPER_MODE_WAC_L_OFF_POWER_CONS                0.0
// #define PANCAM_OPER_MODE_WAC_L_STANDBY_POWER_CONS            6.86
// #define PANCAM_OPER_MODE_WAC_L_FILTER_SELECTION_POWER_CONS   6.24
// #define PANCAM_OPER_MODE_WAC_L_ACQUIRING_IMAGE_POWER_CONS    9.18
// wac r
#define PANCAM_OPER_MODE_WAC_R_OFF_POWER_CONS                0.0
// #define PANCAM_OPER_MODE_WAC_R_STANDBY_POWER_CONS            4.08
// #define PANCAM_OPER_MODE_WAC_R_FILTER_SELECTION_POWER_CONS   6.24
// #define PANCAM_OPER_MODE_WAC_R_ACQUIRING_IMAGE_POWER_CONS    9.18
// hrc
#define PANCAM_OPER_MODE_HRC_OFF_POWER_CONS                  0.0
// #define PANCAM_OPER_MODE_HRC_STANDBY_POWER_CONS           6.86
// #define PANCAM_OPER_MODE_HRC_ACQUIRING_IMAGE_POWER_CONS   7.62
// #define PANCAM_OPER_MODE_HRC_FOCUSSING_POWER_CONS         9.41

// pan cam in general
#define PANCAM_OPER_MODE_OFF_DATARATE                      0.0
// #define PANCAM_OPER_MODE_STANDBY_DATARATE                  0.0
// #define PANCAM_OPER_MODE_OPERATING_DATARATE                0.0
// wac l
#define PANCAM_OPER_MODE_WAC_L_OFF_DATARATE                0.0
// #define PANCAM_OPER_MODE_WAC_L_STANDBY_DATARATE            0.0
// #define PANCAM_OPER_MODE_WAC_L_FILTER_SELECTION_DATARATE   0.0
// #define PANCAM_OPER_MODE_WAC_L_ACQUIRING_IMAGE_DATARATE    100
// wac r
#define PANCAM_OPER_MODE_WAC_R_OFF_DATARATE                0.0
// #define PANCAM_OPER_MODE_WAC_R_STANDBY_DATARATE            0.0
// #define PANCAM_OPER_MODE_WAC_R_FILTER_SELECTION_DATARATE   0.0
// #define PANCAM_OPER_MODE_WAC_R_ACQUIRING_IMAGE_DATARATE    100.0
// hrc
#define PANCAM_OPER_MODE_HRC_OFF_DATARATE                  0.0
// #define PANCAM_OPER_MODE_HRC_STANDBY_DATARATE              0.0
// #define PANCAM_OPER_MODE_HRC_ACQUIRING_IMAGE_DATARATE      100.0
// #define PANCAM_OPER_MODE_HRC_FOCUSSING_DATARATE            10.0 

//#define PANCAM_NOTOPER_TEMPERATURE 180.0



//##################################################################################
//
//                          PAN CAM INDEXES CONSTANTS DEFINITION
//
//##################################################################################



//----------------------------------------------
//  GNC PARAMETERS
//----------------------------------------------


#define LRM_GNC_OPER_MODE_OFF           0
#define LRM_GNC_OPER_MODE_INITIALISING  1
#define LRM_GNC_OPER_MODE_STANDBY       2
#define LRM_GNC_OPER_MODE_MOVING        3



#define LOCCAM_VOLTAGE_ON_LINE 10.0
#define NAVCAM_VOLTAGE_ON_LINE 10.0
#define IMU_VOLTAGE_ON_LINE 10.0
#define COPRO_VOLTAGE_ON_LINE 10.0

// constants on power consumption

#define LRM_HEAT_CAPACITY          3000.0


#define BMC_MODE_OFF_POWER_CONS          0.0
#define BMC_MODE_STNDBY_POWER_CONS       1.9
#define BMC_MODE_MOVING_POWER_CONS       2.5
#define LOCCAM_MODE_OFF_POWER_CONS       0.0
#define LOCCAM_MODE_STNDBY_POWER_CONS    1.2
#define LOCCAM_MODE_ACQUIRING_POWER_CONS 2.5
#define NAVCAM_MODE_OFF_POWER_CONS       0.0
#define NAVCAM_MODE_STNDBY_POWER_CONS    2.1
#define NAVCAM_MODE_ACQUIRING_POWER_CONS 4.5
#define IMU_MODE_OFF_POWER_CONS       0.0
#define IMU_MODE_STNDBY_POWER_CONS    1.3
#define IMU_MODE_ACQUIRING_POWER_CONS 2.7
#define LOCMOTOR_MODE_OFF_POWER_CONS       0.0
#define LOCMOTOR_MODE_STNDBY_POWER_CONS    3.0
#define LOCMOTOR_MODE_MOVING_POWER_CONS    15.5
#define COPRO_MODE_OFF_POWER_CONS          0.0
#define COPRO_MODE_STNDBY_POWER_CONS       3.1
#define COPRO_MODE_PROCESSING_POWER_CONS   15.5

#define BMC_MODE_OFF_DATARATE          0.0
#define BMC_MODE_STNDBY_DATARATE       1.7
#define BMC_MODE_MOVING_DATARATE       2.5
#define LOCCAM_MODE_OFF_DATARATE       0.0
#define LOCCAM_MODE_STNDBY_DATARATE    1.2
#define LOCCAM_MODE_ACQUIRING_DATARATE 2.5
#define NAVCAM_MODE_OFF_DATARATE       0.0
#define NAVCAM_MODE_STNDBY_DATARATE    2.3
#define NAVCAM_MODE_ACQUIRING_DATARATE 4.5
#define IMU_MODE_OFF_DATARATE       0.0
#define IMU_MODE_STNDBY_DATARATE    1.1
#define IMU_MODE_ACQUIRING_DATARATE 2.5
#define LOCMOTOR_MODE_OFF_DATARATE       0.0
#define LOCMOTOR_MODE_STNDBY_DATARATE    3.0
#define LOCMOTOR_MODE_MOVING_DATARATE    15.5
#define COPRO_MODE_OFF_DATARATE          0.0
#define COPRO_MODE_STNDBY_DATARATE       3.0
#define COPRO_MODE_PROCESSING_DATARATE   15.5

#define BMC_MODE_OFF_NON_OPER_TEMPERATURE          0.0
#define BMC_MODE_STNDBY_NON_OPER_TEMPERATURE       1.0
#define BMC_MODE_MOVING_NON_OPER_TEMPERATURE       2.5
#define LOCCAM_MODE_OFF_NON_OPER_TEMPERATURE       0.0
#define LOCCAM_MODE_STNDBY_NON_OPER_TEMPERATURE    1.0
#define LOCCAM_MODE_ACQUIRING_NON_OPER_TEMPERATURE 2.5
#define NAVCAM_MODE_OFF_NON_OPER_TEMPERATURE       0.0
#define NAVCAM_MODE_STNDBY_NON_OPER_TEMPERATURE    2.0
#define NAVCAM_MODE_ACQUIRING_NON_OPER_TEMPERATURE 4.5
#define IMU_MODE_OFF_NON_OPER_TEMPERATURE       0.0
#define IMU_MODE_STNDBY_NON_OPER_TEMPERATURE    1.0
#define IMU_MODE_ACQUIRING_NON_OPER_TEMPERATURE 2.5
#define LOCMOTOR_MODE_OFF_NON_OPER_TEMPERATURE       0.0
#define LOCMOTOR_MODE_STNDBY_NON_OPER_TEMPERATURE    3.0
#define LOCMOTOR_MODE_MOVING_NON_OPER_TEMPERATURE    15.5
#define COPRO_MODE_OFF_NON_OPER_TEMPERATURE          0.0
#define COPRO_MODE_STNDBY_NON_OPER_TEMPERATURE       3.0
#define COPRO_MODE_PROCESSING_NON_OPER_TEMPERATURE   15.5

#define BMC_MODE_OFF_OPER_TEMPERATURE          0.0
#define BMC_MODE_STNDBY_OPER_TEMPERATURE       1.0
#define BMC_MODE_MOVING_OPER_TEMPERATURE       2.5
#define LOCCAM_MODE_OFF_OPER_TEMPERATURE       0.0
#define LOCCAM_MODE_STNDBY_OPER_TEMPERATURE    1.0
#define LOCCAM_MODE_ACQUIRING_OPER_TEMPERATURE 2.5
#define NAVCAM_MODE_OFF_OPER_TEMPERATURE       0.0
#define NAVCAM_MODE_STNDBY_OPER_TEMPERATURE    2.0
#define NAVCAM_MODE_ACQUIRING_OPER_TEMPERATURE 4.5
#define IMU_MODE_OFF_OPER_TEMPERATURE       0.0
#define IMU_MODE_STNDBY_OPER_TEMPERATURE    1.0
#define IMU_MODE_ACQUIRING_OPER_TEMPERATURE 2.5
#define LOCMOTOR_MODE_OFF_OPER_TEMPERATURE       0.0
#define LOCMOTOR_MODE_STNDBY_OPER_TEMPERATURE    3.0
#define LOCMOTOR_MODE_MOVING_OPER_TEMPERATURE    15.5
#define COPRO_MODE_OFF_OPER_TEMPERATURE          0.0
#define COPRO_MODE_STNDBY_OPER_TEMPERATURE       3.0
#define COPRO_MODE_PROCESSING_OPER_TEMPERATURE   15.5
//
// Locomotion parameters
//
#define LOC_WORKING_TEMPERATURE 210
#define LOC_NOTOPER_TEMPERATURE 200


//
// Parameters read by the PhR_GNC
//
#define LRM_MIN_OPER_TEMPERATURE 210
#define LRM_WARMUP_TIMEOUT       1000
#define LRM_BMC_MIN_LINE_VOLTAGE 10
#define LRM_IMU_MIN_LINE_VOLTAGE 5
#define LRM_LINE_VOLTAGE_TIMEOUT 100

//
// Thermal parameters (In the ThermalState)
//
#define THERMAL_WAC_MIN_NOT_OPER 204
#define THERMAL_WAC_MIN_OPER 221
#define THERMAL_WAC_MAX_NOT_OPER 306 
#define THERMAL_WAC_MAX_OPER 224 
#define THERMAL_HRC_MIN_NOT_OPER 204 
#define THERMAL_HRC_MIN_OPER 221
#define THERMAL_HRC_MAX_NOT_OPER 306
#define THERMAL_HRC_MAX_OPER 224
#define THERMAL_WISDOM_MIN_NOT_OPER 204
#define THERMAL_WISDOM_MIN_OPER 221
#define THERMAL_WISDOM_MAX_NOT_OPER 306 
#define THERMAL_WISDOM_MAX_OPER 224
#define THERMAL_CLUPI_MIN_NOT_OPER 209 
#define THERMAL_CLUPI_MIN_OPER 209
#define THERMAL_CLUPI_MAX_NOT_OPER 321 
#define THERMAL_CLUPI_MAX_OPER 321
#define THERMAL_RAMANLIBS_MIN_NOT_OPER 264 
#define THERMAL_RAMANLIBS_MIN_OPER 267
#define THERMAL_RAMANLIBS_MAX_NOT_OPER 284 
#define THERMAL_RAMANLIBS_MAX_OPER 297
#define THERMAL_MIMOS_MIN_NOT_OPER 201
#define THERMAL_MIMOS_MIN_OPER 201
#define THERMAL_MIMOS_MAX_NOT_OPER 316 
#define THERMAL_MIMOS_MAX_OPER 316
#define THERMAL_MIMA_MIN_NOT_OPER 201
#define THERMAL_MIMA_MIN_OPER 201
#define THERMAL_MIMA_MAX_NOT_OPER 316 
#define THERMAL_MIMA_MAX_OPER  316


//
// Comms s/s - (TTC) parameters 
//
// 1 = TC_RX1_OFF, 2 = TC_RX2_OFF, 3 = TC_RX1_ON, 4 = TC_RX2_ON
enum CommsCmds { 
  TC_RX1_OFF = 1, 
  TC_RX2_OFF, 
  TC_RX1_ON, 
  TC_RX2_ON};


#endif
