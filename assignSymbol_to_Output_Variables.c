#include <MODEL.h>

void AssignSymbol_to_Output_Variables(int j, char * Label, Parameter_Table * Table)
{
  char * p;
  Label[0] = '\0';

  int PUTA = OUTPUT_VARIABLES_GENUINE;
  printf("0: (j-%d) The number of output variables genuine is %d\n", j, PUTA);
  
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else {     
    switch(j)
      {
      case  0:
	p = strcat(Label , "<n>");       /*  Average Number of Participants per Age Class */
        break;
      case  1:
	p = strcat(Label , "A");         /*  Average Age of Participants */
        break;
      case  2:
	p = strcat(Label , "N");         /*  Total Number of Participants  */
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
  Label[0] = '\0';

  int PUTA = OUTPUT_VARIABLES_GENUINE;
  printf("1: (j-%d) The number of output variables genuine is %d\n", j, PUTA);
  
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignSymbol_to_Model_Variables(j, Label, Table);
  }
  else {
    
    switch(j)
      {
      case  0:
	p = strcat(Label , "<n>");       /*  Average Number of Participants per Age Class */
	break;
      case  1:
	p = strcat(Label , "A");         /*  Averagee Age of Participants */
        break;
      case  2:
	p = strcat(Label , "N");         /*  Total Number of Participants  */
        break;
     	
      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 4\n");
        exit(0);
      }
  }
}
