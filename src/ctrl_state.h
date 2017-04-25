
#ifndef CTRL_STATE_H
#define CTRL_STATE_H
//##################################################################################
//
//	This file shall contain all and only the indexes of the quantities assigned
//	to the different state vectors of the controller
//
//##################################################################################


#define ACTION_RET_ERROR        -1
#define ACTION_RET_OK           0
#define ACTION_RET_INITIALISING 1
#define ACTION_RET_RUNNING      2


//
// The CTRL_MAX_STATE_SIZE reflects the size of the symbol table data 
// in the muroco controller (it is defined there as MAX_STATE_SIZE 100)
//

static const short CTRL_MAX_STATE_SIZE =  100;

// used to put a termination flag.
static const short ABORT_INDEX =  99;
static const short ABORT_ERROR_INDEX =  98;



//##################################################################################
//                          DHS PARAMETERS DEFINITION
//
//##################################################################################
#define DHS_STATUS_INDEX          0
#define DHS_POWER_CONS_INDEX      1
#define DHS_DATARATE_INDEX        2

#define DHS_ACTION_ID_INDEX        10 
#define DHS_ACTION_RET_INDEX       11 

#define DHS_OPER_MODE_OFF       0
#define DHS_OPER_MODE_POWER_UP  1
#define DHS_OPER_MODE_BOOT      2
#define DHS_OPER_MODE_HIBERNATE 3
#define DHS_OPER_MODE_LOWPOWER  4
#define DHS_OPER_MODE_REDUCED   5
#define DHS_OPER_MODE_NOMINAL   6
#define DHS_OPER_MODE_HIGHPOWER 7
#define DHS_OPER_MODE_RECOVERY  8

#define ORC_TC_OFF    0
#define ORC_TC_WH_RX  1
#define ORC_TC_LST_RX 2

//
// The same Ids as in the CommsModel
//
#define ORC_COMMS_STATE_OFF  0 
#define ORC_COMMS_STATE_INIT 1
#define ORC_COMMS_STATE_WH_RX 2 
#define ORC_COMMS_STATE_WH_HAILING 3 
#define ORC_COMMS_STATE_LST_RX 4
#define ORC_COMMS_STATE_LST_HAILING 5
#define ORC_COMMS_STATE_WH_RXTX 6
#define ORC_COMMS_STATE_LST_RXTX 7

//##################################################################################
//
//                          COMMS PARAMETERS DEFINITION
//
//##################################################################################
#define COMMS_CMD_INDEX 0
#define TTC_DEFAULT_MIN_LINE_VOLTAGE  10

#define COMMS_MAIN_STATUS_INDEX      0
#define COMMS_REDUNDANT_STATUS_INDEX 1
#define COMMS_MAIN_CMD_INDEX         2
#define COMMS_REDUNDANT_CMD_INDEX    3

#define COMMS_ACTION_ID_INDEX        10 
#define COMMS_ACTION_RET_INDEX       11 


//
// RAMPS STATUS INFORMATION
//
#define RAMPS_FL_STATUS_INDEX 0
#define RAMPS_FR_STATUS_INDEX 1
#define RAMPS_RL_STATUS_INDEX 2
#define RAMPS_RR_STATUS_INDEX 3

#define RAMPS_STATUS_FOLDED 0
#define RAMPS_STATUS_DEPLOYED 1

//
// HDRM STATUS
//
#define HDRM_1_SA_LEFT_STATUS_INDEX 0
#define HDRM_2_SA_LEFT_STATUS_INDEX 1
#define HDRM_3_SA_LEFT_STATUS_INDEX 2
#define HDRM_1_SA_RIGHT_STATUS_INDEX 3
#define HDRM_2_SA_RIGHT_STATUS_INDEX 4
#define HDRM_3_SA_RIGHT_STATUS_INDEX 5 

#define HDRM_STATUS_OFF 0
#define HDRM_STATUS_ON  1


//
// GNC indexes and modes
//
static const short GNC_STATUS_INDEX      =  0;
static const short GNC_OPER_MODE_INDEX      =  0;
static const short GNC_ROVER_BEMA_Q1_INDEX  = 13;
static const short GNC_ROVER_BEMA_Q2_INDEX  = 14;
static const short GNC_ROVER_BEMA_Q3_INDEX  = 15;
static const short GNC_ROVER_BEMA_Q4_INDEX = 16;
static const short GNC_ROVER_BEMA_Q5_INDEX = 17;
static const short GNC_ROVER_BEMA_Q6_INDEX = 18;
static const short GNC_BMC1_TEMPERATURE_INDEX = 19;
static const short GNC_BMC2_TEMPERATURE_INDEX  = 20;
static const short GNC_BMC3_TEMPERATURE_INDEX = 21;
static const short GNC_WHEEL_TEMPERATURE_INDEX = 22;
static const short GNC_ROVER_POSEX_INDEX  = 23;
static const short GNC_ROVER_POSEY_INDEX  = 24;
static const short GNC_ROVER_POSEZ_INDEX  = 25;
static const short GNC_ROVER_POSERX_INDEX = 26;
static const short GNC_ROVER_POSERY_INDEX = 27;
static const short GNC_ROVER_POSERZ_INDEX = 28;
static const short GNC_TEMPERATURE_INDEX  = 29;
static const short GNC_DATARATE_INDEX     = 30;
static const short GNC_ACTION_ID_INDEX    = 31;
static const short GNC_ACTION_RET_INDEX   = 32;
static const short GNC_POWER_CONS_INDEX  = 37;
static const short GNC_TOTAL_TRAVELED_DISTANCE_INDEX = 39;
static const short GNC_TEMPERATURE_WHEEL1_INDEX  = 40;
static const short GNC_TEMPERATURE_WHEEL2_INDEX  = 41;
static const short GNC_TEMPERATURE_WHEEL3_INDEX  = 42;
static const short GNC_TEMPERATURE_WHEEL4_INDEX  = 43;
static const short GNC_TEMPERATURE_WHEEL5_INDEX  = 44;
static const short GNC_TEMPERATURE_WHEEL6_INDEX  = 45;
static const short GNC_TRAJECTORY_STATUS_INDEX  =  50;
static const short GNC_ROVER_WHEEL1_SPEED_INDEX = 51;
static const short GNC_ROVER_WHEEL2_SPEED_INDEX = 52;
static const short GNC_ROVER_WHEEL3_SPEED_INDEX = 53;
static const short GNC_ROVER_WHEEL4_SPEED_INDEX = 54;
static const short GNC_ROVER_WHEEL5_SPEED_INDEX = 55;
static const short GNC_ROVER_WHEEL6_SPEED_INDEX = 56;
static const short GNC_ROVER_STEER1_POSITION_INDEX = 57;
static const short GNC_ROVER_STEER2_POSITION_INDEX = 58;
static const short GNC_ROVER_STEER5_POSITION_INDEX = 59;
static const short GNC_ROVER_STEER6_POSITION_INDEX = 60;
static const short GNC_ROVER_WHEEL1_CURRENT_INDEX = 61;
static const short GNC_ROVER_WHEEL2_CURRENT_INDEX = 62;
static const short GNC_ROVER_WHEEL3_CURRENT_INDEX = 63;
static const short GNC_ROVER_WHEEL4_CURRENT_INDEX = 64;
static const short GNC_ROVER_WHEEL5_CURRENT_INDEX = 65;
static const short GNC_ROVER_WHEEL6_CURRENT_INDEX = 66;
static const short GNC_ROVER_LEFT_ROCKER_INDEX = 67;
static const short GNC_ROVER_RIGHT_ROCKER_INDEX = 68;
static const short GNC_ROVER_LEFT_BOGIE_INDEX = 69;
static const short GNC_ROVER_RIGHT_BOGIE_INDEX = 70;


// constants for the status
#define GNC_STATUS_FLAG_OFF    0
#define GNC_STATUS_FLAG_STNDBY 1
#define GNC_STATUS_FLAG_OPER   2

#define GNC_OPER_MODE_OFF                0
#define GNC_OPER_MODE_MONO               1
#define GNC_OPER_MODE_INITIALISING       2
#define GNC_OPER_MODE_STNDBY             3
#define GNC_OPER_MODE_ABS_LOC            4
#define GNC_OPER_MODE_NAVCAM_IMAGING     5
#define GNC_OPER_MODE_LOCCAM_IMAGING     6
#define GNC_OPER_MODE_NAV_PREP_PERC_EVAL 7
#define GNC_OPER_MODE_PP_TRAV            8
#define GNC_OPER_MODE_FPATH_TRAV_MOVE    9
#define GNC_OPER_MODE_FPATH_TRAV_STNDBY  10
#define GNC_OPER_MODE_PP_DRILL           11
#define GNC_OPER_MODE_FPATH_DRILL_MOVE   12
#define GNC_OPER_MODE_FPATH_DRILL_STNDBY 13
#define GNC_OPER_MODE_LLO                14
#define GNC_OPER_MODE_BEMA_DEPLOYMENT_1  15
#define GNC_OPER_MODE_BEMA_DEPLOYMENT_2  16


#define GNC_MIN_OPER_TEMPERATURE 210
#define GNC_WARMUP_TIMEOUT       1000


//
// SA STATUS
//
static const short SA_STATUS_INDEX 	          = 0;
static const short SA_LEFT_PRIMARY_STATUS_INDEX   = 1;
static const short SA_LEFT_SECONDARY_STATUS_INDEX  = 2;
static const short SA_RIGHT_PRIMARY_STATUS_INDEX   = 3;
static const short SA_RIGHT_SECONDARY_STATUS_INDEX = 4;
static const short SA_CURRENT_Q1_INDEX	= 5;
static const short SA_CURRENT_Q2_INDEX	= 6;
static const short SA_CURRENT_Q3_INDEX	= 7;
static const short SA_CURRENT_Q4_INDEX	= 8;

static const short SA_DOF               = 4;
static const short SA_DES_Q1_INDEX	= 9;
static const short SA_DES_Q2_INDEX	= 10;
static const short SA_DES_Q3_INDEX	= 11;
static const short SA_DES_Q4_INDEX	= 12;
static const short SA_TRAJ_DUR_INDEX	= 13;
static const short SA_LEFT_POWER_CONS_INDEX	= 14;
static const short SA_RIGHT_POWER_CONS_INDEX	= 15;
static const short SA_TEMPERATURE_INDEX	= 16;
static const short SA_LEFT_DATARATE_INDEX	= 17;
static const short SA_RIGHT_DATARATE_INDEX	= 18;

static const short SA_LEFT_WARMUP_TIME_INDEX	= 19;
static const short SA_RIGHT_WARMUP_TIME_INDEX	= 20;

static const short SA_ACTION_ID_INDEX   = 21; // 12-nov-2010 (Action ID)
static const short SA_ACTION_RET_INDEX  = 22;


#define SA_DOF 4
// Modes definitions
#define SA_OPER_MODE_OFF          0
#define SA_OPER_MODE_INITIALISING 1
#define SA_OPER_MODE_STNDBY       2
#define SA_OPER_MODE_MOVING       3
#define SA_OPER_MODE_SEC_MOVING   4
// (m/sec, deg/sec) 
#define SA_MAX_ROTATION_SPEED 3
#define DEFAULT_SA_MIN_LINE_VOLTAGE 15
#define DEFAULT_SA_WARMUP_TIME 60


//
// MAST STATUS
//

static const short MAST_STATUS_INDEX		= 0;
static const short MAST_TEMPERATURE_INDEX	= 1;

static const short MAST_CURRENT_Q1_INDEX	= 2;
static const short MAST_CURRENT_Q2_INDEX	= 3;
static const short MAST_CURRENT_Q3_INDEX	= 4;
static const short MAST_CURRENT_Q4_INDEX	= 5;
static const short MAST_CURRENT_Q5_INDEX	= 6;

static const short MAST_DES_Q1_INDEX	= 7;
static const short MAST_DES_Q2_INDEX	= 8;
static const short MAST_DES_Q3_INDEX	= 9;
static const short MAST_DES_Q4_INDEX	= 10;
static const short MAST_DES_Q5_INDEX	= 11;

static const short MAST_TRAJ_DUR_INDEX     = 12;
static const short MAST_POWER_CONS_INDEX   =  13;
static const short MAST_DATARATE_INDEX     =  14;  // 3-11-2010

static const short MAST_WARMUP_TIME_PTU_INDEX = 15;
static const short MAST_WARMUP_TIME_DEP_INDEX = 16;

static const short MAST_ACTION_ID_INDEX    = 17; // 12-nov-2010 (Action ID)
static const short MAST_ACTION_RET_INDEX   = 18; // 12-nov-2010 (OK/ERROR/RUNNING)


// (m/sec, deg/sec) 
#define MAST_MAX_TRANSLATION_SPEED 0.05 
#define MAST_MAX_ROTATION_SPEED    3.0  
#define MAST_MIN_OPER_TEMPERATURE  260.0
#define MAST_INITIALISE_TIME       1800
#define MAST_PTU_MIN_LINE_VOLTAGE 10
#define MAST_SWITCH_OFF_TIME      2 
#define MAST_WARMUP_TIMEOUT       10

#define MAST_DOF                       3
#define MAST_OPER_MODE_OFF             0
#define MAST_OPER_MODE_PTU_INITIALISE  1
#define MAST_OPER_MODE_PTU_STNDBY      2
#define MAST_OPER_MODE_PTU_MOVING      3
#define MAST_OPER_MODE_DEP_INITIALISE  4
#define MAST_OPER_MODE_DEP_STNDBY      5
#define MAST_OPER_MODE_DEP_MOVING      6

//
// ADE
//

static const short ADE_STATUS_LEFT_INDEX      = 0;
static const short ADE_STATUS_RIGHT_INDEX     = 1;
static const short ADE_LEFT_TEMPERATURE_INDEX = 2;
static const short ADE_RIGHT_TEMPERATURE_INDEX = 3;


static const short ADE_LEFT_POWER_CONS_INDEX   =  11;
static const short ADE_RIGHT_POWER_CONS_INDEX  =  12;
static const short ADE_POWER_CONS_INDEX   =  13;
static const short ADE_DATARATE_INDEX     =  14;

static const short ADE_LEFT_WARMUP_TIME_INDEX  = 15;
static const short ADE_RIGHT_WARMUP_TIME_INDEX = 16;

static const short ADE_ACTION_ID_INDEX    = 17;
static const short ADE_ACTION_RET_INDEX   = 18;

static const short HDRM_BODY_1_STATUS_INDEX = 20;
static const short HDRM_BODY_2_STATUS_INDEX = 21; 
static const short HDRM_BODY_3_STATUS_INDEX = 22; 
static const short HDRM_DRILL_1_STATUS_INDEX = 23;
static const short HDRM_DRILL_2_STATUS_INDEX = 24; 
static const short HDRM_MAST_STATUS_INDEX = 25; 
static const short HDRM_SA_LEFT_1_STATUS_INDEX = 26; 
static const short HDRM_SA_LEFT_2_STATUS_INDEX = 27; 
static const short HDRM_SA_LEFT_3_STATUS_INDEX = 28; 
static const short HDRM_SA_RIGHT_1_STATUS_INDEX = 29; 
static const short HDRM_SA_RIGHT_2_STATUS_INDEX = 30; 
static const short HDRM_SA_RIGHT_3_STATUS_INDEX = 31; 
static const short HDRM_UMBILICAL_1_STATUS_INDEX = 32; 
static const short HDRM_UMBILICAL_2_STATUS_INDEX = 33; 
static const short HDRM_WHEEL_FL_STATUS_INDEX = 34; 
static const short HDRM_WHEEL_FR_STATUS_INDEX = 35;
static const short HDRM_WHEEL_ML_STATUS_INDEX = 36; 
static const short HDRM_WHEEL_MR_STATUS_INDEX = 37; 
static const short HDRM_WHEEL_RL_STATUS_INDEX = 38; 
static const short HDRM_WHEEL_RR_STATUS_INDEX = 39;


#define HDRM_OFF 0
#define HDRM_ON  1

#define ADE_MIN_OPER_TEMPERATURE  260.0
#define ADE_INITIALISATION_TIME   60
#define ADE_WARMUP_TIMEOUT       1000
#define ADE_MIN_LINE_VOLTAGE 10
#define ADE_SWITCH_OFF_TIME      2 
#define ADE_LEFT_WARMUP_TIME 10
#define ADE_RIGHT_WARMUP_TIME 10

#define ADE_OPER_MODE_OFF               0
#define ADE_OPER_MODE_WARMUP            1
#define ADE_OPER_MODE_INIT              2
#define ADE_OPER_MODE_STNDBY            3
#define ADE_OPER_MODE_OP_MOTORS         4
#define ADE_OPER_MODE_STNDBY_HDRM       5
#define ADE_OPER_MODE_OP_HDRM           6


//
// PanCam Indexes
//
static const short PANCAM_OPER_MODE_INDEX	= 0;
//static const short PANCAM_THERMAL_MODE_INDEX	= 1; // 3-11-2010
static const short PANCAM_WAC_L_MODE_INDEX	= 2;
static const short PANCAM_WAC_R_MODE_INDEX	= 3;
static const short PANCAM_HRC_MODE_INDEX	= 4;
static const short PANCAM_TEMPERATURE_INDEX	= 5;
static const short PANCAM_WACS_TEMPERATURE_INDEX= 6;
static const short PANCAM_HRC_TEMPERATURE_INDEX	= 7;
static const short PANCAM_DATARATE_INDEX	= 8; // 3-11-2010
static const short PANCAM_POWER_CONS_INDEX      = 9; // 3-11-2010
static const short PANCAM_WAC_L_FILTER_POSE_INDEX     = 10;
static const short PANCAM_WAC_R_FILTER_POSE_INDEX     = 11;

static const short PANCAM_HRC_COMPRESSION_LEVEL_INDEX = 12;

static const short PANCAM_ACTION_ID_INDEX       = 13; // 12-nov-2010 (Action ID)
static const short PANCAM_ACTION_RET_INDEX      = 14; // 12-nov-2010 (OK/ERROR/RUNNING)
static const short PANCAM_WAC_L_INDEX           = 15; // Index of stored images
static const short PANCAM_WAC_R_INDEX           = 16; // Index of stored images
static const short PANCAM_PAN_STEREO_INDEX      = 17; // Index of stored images
static const short LOCCAM_FLOC_L_INDEX          = 18; // Index of stored images
static const short LOCCAM_FLOC_R_INDEX          = 19; // Index of stored images
static const short LOCCAM_FLOC_STEREO_INDEX     = 20; // Index of stored images
static const short LOCCAM_RLOC_L_INDEX          = 21; // Index of stored images
static const short LOCCAM_RLOC_R_INDEX          = 22; // Index of stored images
static const short LOCCAM_RLOC_STEREO_INDEX     = 23; // Index of stored images
static const short HAZCAM_FHAZ_STEREO_INDEX     = 24; // Index of stored images
static const short TOF_INDEX                    = 25; // Index of stored images
static const short LIDAR_INDEX                  = 26; // Index of stored images

// PanCam Operational Modes
#define PANCAM_OPER_MODE_OFF                    0
#define PANCAM_OPER_MODE_INITIALISING 		    1
#define PANCAM_OPER_MODE_WACS_INITIALISE        2    
#define PANCAM_OPER_MODE_HRC_INITIALISE         3    
#define PANCAM_OPER_MODE_STNDBY                 4
#define PANCAM_OPER_MODE_OPERATING              5
#define PANCAM_OPER_MODE_SWITCHING_OFF          6
#define PANCAM_OPER_MODE_FAIL                   7


#define PANCAM_OPER_MODE_WAC_OFF                0
#define PANCAM_OPER_MODE_WAC_STANDBY            1
#define PANCAM_OPER_MODE_WAC_FILTER_SELECTION   2
#define PANCAM_OPER_MODE_WAC_ACQUIRING_RRGB_IMAGE       3
#define PANCAM_OPER_MODE_WAC_ACQUIRING_GEOLOGY_IMAGE    4
#define PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSLESS     5
#define PANCAM_OPER_MODE_WAC_GETTING_IMAGE_LOSSY        6
#define PANCAM_OPER_MODE_WAC_GETTING_IMAGE_THUMBNAIL    7

#define PANCAM_OPER_MODE_HRC_OFF             0
#define PANCAM_OPER_MODE_HRC_STANDBY         1   
#define PANCAM_OPER_MODE_HRC_GETTING_IMAGE   2 
#define PANCAM_OPER_MODE_HRC_ACQUIRING_AF_AE_IMAGE 3
#define PANCAM_OPER_MODE_HRC_ACQUIRING_AF_ME_IMAGE 4
#define PANCAM_OPER_MODE_HRC_ACQUIRING_MF_AE_IMAGE 5
#define PANCAM_OPER_MODE_HRC_ACQUIRING_MF_ME_IMAGE 6
#define PANCAM_OPER_MODE_HRC_FOCUSSING_IMAGE 7
#define PANCAM_OPER_MODE_HRC_EXPOSURE        8 

#define PANCAM_COMPRESSION_LEVEL_LOSSLESS  1
#define PANCAM_COMPRESSION_LEVEL_LOSSY     2
#define PANCAM_COMPRESSION_LEVEL_THUMBNAIL 3

//#define PANCAM_THERMAL_MODE_NONOPERATIONAL 0
//#define PANCAM_THERMAL_MODE_OPERATIONAL    1

// resources consumption constants
#define PANCAM_WARMUP_TIMEOUT 10
#define PANCAM_WAC_GETTING_IMAGE_TIME 10
#define PANCAM_HRC_GETTING_IMAGE_TIME 10

#endif
