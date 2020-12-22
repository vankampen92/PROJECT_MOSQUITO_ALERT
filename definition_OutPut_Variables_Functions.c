#include <MODEL.h>

double Average_Participant_Age(double * Y, Parameter_Table * Table)
{
  double x, N;
  int i;

  /* This total population is calculated over all species in the system.
     It is rather a total community size if the number of species is larger than 1 
  */
  if (Table->TYPE_of_MODEL == 0) {
    x = 0.0;
    for(i=0; i<Table->MODEL_STATE_VARIABLES; i++) {
      x += (double)i*Y[i];
      N += Y[i]; 
    }
  }

  x /= N; 
  
  return(x); 
}

double Total_Number_of_Participants( double * Y, Parameter_Table * Table)
{
  double x;
  int i;

  /* This total population is calculated over all species in the system.
     It is rather a total community size if the number of species is larger than 1 
  */
  if (Table->TYPE_of_MODEL == 0) {
    x = 0.0;
    for(i=0; i<Table->MODEL_STATE_VARIABLES; i++) 
      x += Y[i]; 
  }

  return(x); 
}


double Average_Participant_Density  ( double * y, Parameter_Table * Table )
{
  double x, x_0, x_1;
  int i;

  /* Definition of the state vector numerical order, from 0 to K, of model variables */
  #include <Model_Variables_Code.Include.c>
 
   if (Table->TYPE_of_MODEL == 0) {
      x = Average_double_Vector(y, Table->MODEL_STATE_VARIABLES);
   }
   else {
     printf(" Type of Model is ill-defined. Check input arguments. TYPE of MODEL is %d\n",
	    Table->TYPE_of_MODEL);
     printf(" The program will exit\nm");
     exit(0);
   }
   
  return (x);
}

