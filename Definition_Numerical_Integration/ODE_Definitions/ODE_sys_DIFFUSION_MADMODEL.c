#include <MODEL.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

int function (double t, const double y[], double dydt[], void *params)
{
  int i, n, j, k;
  int Sp; 
  
  Parameter_Table * Table = (Parameter_Table *)params;

  Sp = Table->No_of_AGES; 

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>

  n= 0; 
  for (j=0; j<Table->No_of_CELLS; j++) {
    
    dydt[n++]     = Table->A_Rate - (1 + Table->Gamma_Vector[0]) * y[n];
    
    for( k=0; k < Table->No_of_GROUPS; k++ ) {
      
      for(i=0; i < Table->K_Vector[k]; i++) {
	if(i==0 && k > 0)
	  dydt[n] = y[n-1] - (1 + Table->Gamma_Vector[k]) * y[n];
	else
	  dydt[n] = y[n-1] - (1 + Table->Gamma_Vector[k]) * y[n];

	if( i == (Table->K_Vector[k]-1) && k == (Table->No_of_GROUPS-1) )
	  dydt[n] = y[n-1] - (1 + Table->Gamma_Vector[k]) * y[n];
 
	n++; 
      }
    }
  }
  
  n= 0; 
  for (j=0; j<Table->No_of_CELLS; j++) {  
    for(i=0; i<Sp; i++) { 
      dydt[n] += In_Mu(Table, n, i, j, y) - Out_Mu_Per_Capita(Table, 0, j) * y[n];;
      n++;
    }
  }
  
  return GSL_SUCCESS;
}
