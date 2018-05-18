#ifndef ORC_MOD_RV_Prepare4Travel_H
#define ORC_MOD_RV_Prepare4Travel_H
  
#include "module.h"
  
#include "module_RV_Prepare4Travel_Inc.h"

#include "module_ADE_SwitchOn.h"
#include "module_GNC_Initialise.h"
#include "module_DHS_Reduced2HighPwr.h"
#include "module_GNC_AbsLocalisation.h"
  
/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_RV_Prepare4Travel : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[20][124];
    int rtId;
    
    orc_Mod_ADE_SwitchOn        ADE_SwitchOn;
    orc_Mod_GNC_Initialise      GNC_Initialise;
    orc_Mod_DHS_Reduced2HighPwr DHS_Reduced2HighPwr;
    orc_Mod_GNC_AbsLocalisation GNC_AbsLocalisation;

    int ADE_SwitchOn_phase; 
    int GNC_Initialise_phase; 
    int DHS_Reduced2HighPwr_phase; 
    int GNC_AbsLocalisation_phase; 
    
  public:
    orc_Mod_RV_Prepare4Travel (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_RV_Prepare4Travel ();
    
    // Output Event Ports declaration
    int RV_Prepare4Travel_prec;
    int RV_Prepare4Travel_post;
    
    
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

// End class  orc_Mod_RV_Prepare4Travel

