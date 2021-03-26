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
  //printf("\n**********Table->No_of_GROUPS:%d***\n", Table->No_of_GROUPS);
  Resetting_Mu_Gamma_K_Vectors (Table); 
  //for(k=0; k < Table->No_of_GROUPS; k++)printf("\n *******Table->K_Vector[%d]:%d\n", k, Table->K_Vector[k]);
  dydt[0]     = Table->A_Rate - (1  + Table->Gamma_Vector[0]) * y[0];
  //printf("\n***********FIRST****dydt[%d]:%g", 0, dydt[0]);
  n = 1; 
  for( k=0; k < Table->No_of_GROUPS; k++ ) { 
    for(i=0; i < Table->K_Vector[k] ; i++) {
      dydt[n] =  y[n-1] - (1 + Table->Gamma_Vector[k]) * y[n];
      //printf("\n******Edad : %d, n = %d***\n",i , n);
      //printf("\n*********dydt[%d]:%g", n, dydt[n]);
      n++; 
    }
  }
  //printf("\n***************** Table->No_of_AGES:%d == n:%d \n ", Table->No_of_AGES,n);
  //printf("\n***************** Table->MODEL_STATE_VARIABLES:%d == K:%d \n ", Table->MODEL_STATE_VARIABLES,K);
  assert(Table->No_of_AGES == n);
  assert(Table->MODEL_STATE_VARIABLES == n && K == (n-1)); 

  return GSL_SUCCESS;
}