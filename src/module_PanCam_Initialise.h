#ifndef ORC_MOD_PanCam_Initialise_H
#define ORC_MOD_PanCam_Initialise_H

#include "module.h"

#include "module_PanCam_Initialise_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {

 /**
   * \brief Implements the **PanCam_Initialise** Action.To warm up and switch on the PanCam PIU.
   */
  class orc_Mod_PanCam_Initialise : public ModuleAlgo
{
 public:
#define PANCAM_INITIALISE_TIMEOUT 960   // Set to 960s warst case in RAPD.in definition

int rtId;     // Action Id
int index;

// the pan cam state
double PanCamState[MAX_STATE_SIZE];

double warmUpTimeout;

// the action execution status
int action_exec_status;

 public:
 orc_Mod_PanCam_Initialise (/*ModuleTask* mt, int indexclk*/);
  virtual ~orc_Mod_PanCam_Initialise ();

 public:
  // Output Event Ports declaration
  int PanCam_Initialise_prec;
int PanCam_Initialise_post;


  char moduleParams[1024];

  // Methods of computation
  void init ();
  void param (char *);
  void reparam (char *);
  void compute ();
  void end ();
};

}
#endif

// End class  orc_Mod_PanCam_Initialise

