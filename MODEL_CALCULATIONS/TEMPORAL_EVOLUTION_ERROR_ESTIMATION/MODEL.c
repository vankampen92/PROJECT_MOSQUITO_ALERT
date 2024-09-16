#include <MODEL.h>

extern gsl_rng * r;

int M_O_D_E_L( Parameter_Table * Table )
{
  double x;

  int i,k, n;
  int I_Time, no_Patch;
  int Bad_Times;

  I_Time    = Table->T->I_Time;

  Parameter_Model * P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);
  Table->P  = P;

  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  int MODEL_STATE_VARIABLES = K+1;
  Table->MODEL_STATE_VARIABLES = MODEL_STATE_VARIABLES;

  Table->Vector_Model_Variables_Time_0 = (double *)calloc(MODEL_STATE_VARIABLES, sizeof(double));
  Table->Vector_Model_Variables = (double *)calloc(MODEL_STATE_VARIABLES, sizeof(double));

  /* BEGIN : -------------------------------------------------------------------------
   * Definition Initial Condition (initializing 'Table->Vector_Model_Variables_Time_0' vector):
   */
  /// Number of participants at the zero class at time 0.0:
  double P_0 = 0.0;  
  Initial_Condition_Partipants_at_Time_0 (Table, P_0);
  assert(Table->No_of_IC == 0); 
  /* END ----------------------------------------------------------------------------
   */
  
  int State = D_E_T_E_R_M_I_N_I_S_T_I_C___T_I_M_E___D_Y_N_A_M_I_C_S( Table ) ;
  
  free( Table->Vector_Model_Variables_Time_0);
  free( Table->Vector_Model_Variables );
  
  free ( P );

  return(State);
}
