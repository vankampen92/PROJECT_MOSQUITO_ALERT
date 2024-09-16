#include "./Include/MODEL.h"

void AssignLabel_to_Model_Parameters__LATEX(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "Loss Rate 1st Group");   
      break;
    case  1:  p = strcat(Label, "Threshold Age 1st Group");   
      break;
    case  2:  p = strcat(Label, "Loss Rate 2st Group");   
      break;
    case  3:  p = strcat(Label, "Threshold Age 2st Group");   
      break;
    case  4:  p = strcat(Label, "Loss Rate 3nd Group");   
      break;
    case  5:  p = strcat(Label, "Threshold Age 3nd Group");   
      break;
    case  6:  p = strcat(Label, "Loss Rate 4st Group");   
      break;
    case  7:  p = strcat(Label, "Threshold Age 4st Group");   
      break;
    case  8:  p = strcat(Label, "Loss Rate 5st Group");   
      break;
    case  9:  p = strcat(Label, "Threshold Age 5st Group");   
      break;
    case 10:  p = strcat(Label, "Loss Rate 6th Group");   
      break;
    case 11:  p = strcat(Label, "Threshold Age 6th Group");   
      break;
    case 12:  p = strcat(Label, "Loss Rate 7st Group");   
      break;
    case 13:  p = strcat(Label, "Threshold Age 7st Group");   
      break;
    case 14:  p = strcat(Label, "Loss Rate 8st Group");   
      break;
    case 15:  p = strcat(Label, "No of GROUPS");   
      break;
    case 16:  p = strcat(Label, "Downloading Rate");   
      break;    
    case 17:  p = strcat(Label, "Encounter Rate");   
      break;  
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}

void AssignLabel_to_Model_Parameters__LATEX__SYMBOL(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "$\\gamma_0$");
      break;
    case  1:  p = strcat(Label, "$k_0$");      
      break;
    case  2:  p = strcat(Label, "$\\gamma_1$");        
      break;
    case  3:  p = strcat(Label, "$k_1$");
      break;
    case  4:  p = strcat(Label, "$\\gamma_2$");      
      break;
    case  5:  p = strcat(Label, "$k_2$");        
      break;
    case  6:  p = strcat(Label, "$\\gamma_3$");
      break;
    case  7:  p = strcat(Label, "$k_3$");      
      break;
    case  8:  p = strcat(Label, "$\\gamma_41$");        
      break;
    case  9:  p = strcat(Label, "$k_4$");
      break;
    case 10:  p = strcat(Label, "$\\gamma_5$");      
      break;
    case 11:  p = strcat(Label, "$k_5$");        
      break;
    case 12:  p = strcat(Label, "$\\gamma_6$");
      break;
    case 13:  p = strcat(Label, "$k_6$");      
      break;
    case 14:  p = strcat(Label, "$\\gamma_7$");        
      break;
    case 15:  p = strcat(Label, "$K$");      
      break;
    case 16:  p = strcat(Label, "$A$");        
      break;
    case 17:  p = strcat(Label, "$Rho$");        
      break;
      
      
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
