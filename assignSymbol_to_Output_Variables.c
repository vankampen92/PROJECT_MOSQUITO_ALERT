#include <MODEL.h>

extern int TIME_DEPENDENT_PARAMETERS;
extern int * dependent_parameter; 

void AssignSymbol_to_Output_Variables(int j, char * Label, Parameter_Table * Table)
{
  int key, N;
  char * p;

  Label[0] = '\0';

  N = TIME_DEPENDENT_PARAMETERS; 
  
  if (j >= OUTPUT_VARIABLES_GENUINE + N) {
    j -= (OUTPUT_VARIABLES_GENUINE + N); 
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else if (j >= OUTPUT_VARIABLES_GENUINE ) {
    j -= OUTPUT_VARIABLES_GENUINE;
    key = dependent_parameter[j]; 
    AssignSymbol_to_Model_Parameters(key, Label, Table);
    p = strcat(Label, "[t]");
  }
  else {

    switch(j)
      {
      case  0:
	p = strcat(Label , "<n>");       /*  0: Average Number of Participants per Age Class */
        break;
      case  1:
	p = strcat(Label , "n_A");       /*  1: Average Age of Participants */
        break;
      case  2:
	p = strcat(Label , "N");         /*  2: Total No of Participants  */
        break;

      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 4\n");
        exit(0);
      }
  }
}

void AssignCPGPLOT_Symbol_to_Output_Variables(int j, char * Label, Parameter_Table * Table)
{
  char * p;
  int N, key;
  
  Label[0] = '\0';

  N = TIME_DEPENDENT_PARAMETERS; 
  
  if (j >= OUTPUT_VARIABLES_GENUINE + N) {
    j -= (OUTPUT_VARIABLES_GENUINE + N); 
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else if (j >= OUTPUT_VARIABLES_GENUINE ) {
    j -= OUTPUT_VARIABLES_GENUINE;
    key = dependent_parameter[j]; 
    AssignCPGPLOT_Symbol_to_Model_Parameters(key, Label, Table);
    p = strcat(Label, "[t]");
  }
  else {

    switch(j)
      {
      case  0:
	p = strcat(Label , "<n>");       /*  0: Average Number of Participants per Age Class */
        break;
      case  1:
	p = strcat(Label , "n_A");       /*  1: Average Age of Participants */
        break;
      case  2:
	p = strcat(Label , "N");         /*  2: Total No of Participants  */
        break;

      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 4\n");
        exit(0);
      }
  }
}
