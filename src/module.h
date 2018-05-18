#ifndef ORC_MOD_ALGO_H
#define ORC_MOD_ALGO_H


namespace ControllerModelNamespace {
  
  class ModuleAlgo {
  public:
    int param_completed, 
      init_completed,
      compute_completed,
      end_completed;

  public:
    ModuleAlgo(){
      param_completed = 0;
      init_completed = 0;
      compute_completed = 0;
      end_completed = 0;
    };
    void execute(char *rtParams) {
      if (param_completed == 0){
	param(rtParams);
	param_completed = 1;
      }
      if (param_completed == 1 && init_completed == 0){
	init();
	init_completed = 1;
      }
      if (init_completed == 1 && compute_completed == 0){
	compute();
      }
      if (compute_completed == 1 && end_completed == 0){
	end();
	end_completed = 1;
      }
    }

    // Methods of computation
    virtual void init (){};
    virtual void param (char *){};
    virtual void reparam (char *){};
    virtual void compute (){};
    virtual void end (){};

    void reset() {
      param_completed = 0;
      init_completed = 0;
      compute_completed = 0;
      end_completed = 0;
    }
  };
}


#endif
