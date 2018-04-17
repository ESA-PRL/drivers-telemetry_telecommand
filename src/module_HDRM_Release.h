#ifndef ORC_MOD_HDRM_Release_H
#define ORC_MOD_HDRM_Release_H

#include "module.h"

#include "module_HDRM_Release_Inc.h"

/** The model of the o/b controller */
namespace ControllerModelNamespace {
  
  class orc_Mod_HDRM_Release : public ModuleAlgo
  {
  public:
    int index;
    double current_time;
    double duration;
    char taskid[124];
  public:
    char task_param[30][124];
    int rtId;
    
    
  public:
    orc_Mod_HDRM_Release (/*ModuleTask* mt, int indexclk*/);
    virtual ~orc_Mod_HDRM_Release ();
    
    // Output Event Ports declaration
    int HDRM_Release_prec;
    int HDRM_Release_post;
    
    
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

// End class  orc_Mod_HDRM_Release

