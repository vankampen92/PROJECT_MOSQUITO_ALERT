#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int function (double t, const double y[], double dydt[], void *params)
{
  int i, n, j, k;
  double sum;
  int No_ages_prop;

  No_ages_prop = No_of_Ages_PROP;
  Parameter_Table * Table = (Parameter_Table *)params;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
  Resetting_Mu_Gamma_K_Vectors (Table); 
  dydt[0]     = Table->A_Rate - (1  + Table->Gamma_Vector[0]) * y[0];
  n = 1; 
  for( k=0; k < Table->No_of_GROUPS; k++ ) { 
    for(i=0; i < Table->K_Vector[k] ; i++) {
      dydt[n] =  y[n-1] - (1 + Table->Gamma_Vector[k]) * y[n];
      n++; 
    }
  }
  // Compute the sum of the denominator.
  sum = 0;
  for(k=0; k < No_ages_prop; k++){
    
    sum = sum + (Table->prop_vec[k])*y[k]*(Table->rho);
  }
  //dydt[n+1] = sum;

  dydt[n+1] = 20;

  assert(Table->No_of_AGES == n);
   #if defined MADMODEL
  assert(Table->MODEL_STATE_VARIABLES == n && K == (n-1)); 
  #endif
   #if defined MADMODEL_FULL
  assert(Table->MODEL_STATE_VARIABLES == (n+1) && K == n); 
  #endif
  return GSL_SUCCESS;
}