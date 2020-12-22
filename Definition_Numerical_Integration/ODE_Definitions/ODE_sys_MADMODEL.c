#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int function (double t, const double y[], double dydt[], void *params)
{
  int i, n, j, k;
  
  Parameter_Table * Table = (Parameter_Table *)params;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  dydt[0]     = Table->A_Rate - (Table->Mu_Vector[0]  + Table->Gamma_Vector[0]) * y[0];

  n= 1; 
  for( k=0; k < Table->No_of_GROUPS; k++ ) {
      
    for(i=0; i < Table->K_Vector[k]; i++) {
      if(i == 0 && k > 0)
	dydt[n] = Table->Mu_Vector[k-1]* y[n-1] - (Table->Mu_Vector[k] + Table->Gamma_Vector[k]) * y[n];
      else
	dydt[n] = Table->Mu_Vector[k]* y[n-1] - (Table->Mu_Vector[k] + Table->Gamma_Vector[k]) * y[n];
      
      if( i == (Table->K_Vector[k]-1) && k == (Table->No_of_GROUPS-1) )
	dydt[n] = Table->Mu_Vector[k]* y[n-1] - (Table->Gamma_Vector[k]) * y[n];
      
      n++; 
    }
  }
  
  assert(Table->No_of_AGES == n);
  
  assert(Table->MODEL_STATE_VARIABLES == n && K == (n-1)); 

  return GSL_SUCCESS;
}
