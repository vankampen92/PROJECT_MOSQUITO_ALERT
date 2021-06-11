#include "./Include/MODEL.h"

void AssignCodes_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "-g0");   /* Gamma Per Capita Movement Rate */  
	break;
    case  1:  p = strcat(Label, "-k0");  
      break;
    case  2:  p = strcat(Label, "-g1");
      break;
    case  3:  p = strcat(Label, "-k1");  
      break;
    case  4:  p = strcat(Label, "-g2");
      break;
    case  5:  p = strcat(Label, "-k2");
      break;
    case  6:  p = strcat(Label, "-g3");
      break;
    case  7:  p = strcat(Label, "-k3");
      break;
    case  8:  p = strcat(Label, "-g4");
      break;
    case  9:  p = strcat(Label, "-k4");
      break;
    case 10:  p = strcat(Label, "-g5");
      break;
    case 11:  p = strcat(Label, "-k5");
      break;
    case 12:  p = strcat(Label, "-g6");
      break;
    case 13:  p = strcat(Label, "-k6");
      break;
    case 14:  p = strcat(Label, "-g7");
      break;
    case 15:  p = strcat(Label, "-KK");
      break;
    case 16:  p = strcat(Label, "-rA");
      break;
    case 17:  p = strcat(Label, "-oR");
      break;
      
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are 0 to 6:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
