#include "./Include/MODEL.h"

void AssignLabel_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "Gamma_0: Loss Rate 1st Group");
      break;
    case  1:  p = strcat(Label, "k_0: Threshold Age 1st Group");   
      break;
    case  2:  p = strcat(Label, "Gamma_1: Loss Rate 2nd Group");   
      break;
    case  3:  p = strcat(Label, "k_1: Threshold Age 2nd Group");     
      break;
    case  4:  p = strcat(Label, "Gamma_2: Loss Rate 3rd Group");    
      break;
    case  5:  p = strcat(Label, "k_2: Threshold Age 3rd Group");   
      break;
    case  6:  p = strcat(Label, "Gamma_3: Loss Rate 4th Group");   
      break;
    case  7:  p = strcat(Label, "k_3: Threshold Age 4th Group");   
      break;
    case  8:  p = strcat(Label, "Gamma_4: Loss Rate 5th Group");   
      break;
    case  9:  p = strcat(Label, "k_4: Threshold Age 5th Group");   
      break;
    case 10:  p = strcat(Label, "Gamma_5: Loss Rate 4th Group");   
      break;
    case 11:  p = strcat(Label, "k_5: Threshold Age 4th Group");   
      break;
    case 12:  p = strcat(Label, "Gamma_6: Loss Rate 5th Group");   
      break;
    case 13:  p = strcat(Label, "k_6: Threshold Age 4th Group");   
      break;
    case 14:  p = strcat(Label, "Gamma_7: Loss Rate 5th Group");   
      break;
    case 15:  p = strcat(Label, "Total Number of Groups");   
      break;
    case 16:  p = strcat(Label, "Downloading Rate");   
      break;
    case 17:  p = strcat(Label, "Encounter Rate");   
      break;
      
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are (0 to 6):\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
