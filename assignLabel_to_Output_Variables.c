#include <MODEL.h>

void AssignLabel_to_Output_Variables(int j, char * Label, Parameter_Table * P)
{
  char * p;
  Label[0] = '\0';

  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignLabel_to_Model_Variables(j, Label, P);
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

void AssignLongLabel_to_Output_Variables(int j, char * Label, Parameter_Table * P)
{
  char * p;
  Label[0] = '\0';
  if (j >= OUTPUT_VARIABLES_GENUINE) {
    j -= OUTPUT_VARIABLES_GENUINE;
    /* The first output variables are the model variables */
    AssignLabel_to_Model_Variables(j, Label, P);
  }
  else {

    switch(j)
      {
      case  0:
	p = strcat(Label , "Average Number of Participants per Age Class");
        break;
      case  1:
	p = strcat(Label , "Average Age of Participants");
        break;
      case  2:
	p = strcat(Label , "Total Number of Participants");
        break;

      default:
        printf(".... INVALID OUTPUT VARIABLE KEY [key = %d]\n", j);
        printf(".... The permited correspondences are:\n");
        printf(".... from 0 to 4\n");
        exit(0);
      }
  }
}
