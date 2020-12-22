#include "./Include/MODEL.h"

void AssignLabel_to_Model_Parameters__LATEX(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "Mu_0: Transition Rate 1st Group");   
      break;
    case  1:  p = strcat(Label, "Gamma_0: Loss Rate 1st Group");   
      break;
    case  2:  p = strcat(Label, "k_0: Threshold Age 1st Group");   
      break;
    case  3:  p = strcat(Label, "Mu_1: Transition Rate 2nd Group");   
      break;
    case  4:  p = strcat(Label, "Gamma_1: Loss Rate 2nd Group");   
      break;
    case  5:  p = strcat(Label, "k_1: Threshold Age 2nd Group");   
      break;
    case  6:  p = strcat(Label, "Mu_2: Transition Rate 3rd Group");   
      break;
    case  7:  p = strcat(Label, "Gamma_2: Loss Rate 3rd Group");   
      break;
    case  8:  p = strcat(Label, "k_2: Threshold Age 3rd Group");   
      break;
    case  9:  p = strcat(Label, "Mu_3: Transition Rate 4th Group");   
      break;
    case 10:  p = strcat(Label, "Gamma_3: Loss Rate 4th Group");   
      break;
    case 11:  p = strcat(Label, "k_3: Threshold Age 4th Group");   
      break;
    case 12:  p = strcat(Label, "Mu_4: Transition Rate 5th Group");   
      break;
    case 13:  p = strcat(Label, "Gamma_4: Loss Rate 5th Group");   
      break;
    case 14:  p = strcat(Label, "k_4: Threshold Age 5th Group");   
      break;
    case 15:  p = strcat(Label, "No of GROUPS");   
      break;
    case 16:  p = strcat(Label, "A_Rate: Downloading Rate");   
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
    case  0:  p = strcat(Label, "$\\mu_0$");
      break;
    case  1:  p = strcat(Label, "$\\gamma_0$");      
      break;
    case  2:  p = strcat(Label, "$k_0$");        
      break;
    case  3:  p = strcat(Label, "$\\mu_1$");
      break;
    case  4:  p = strcat(Label, "$\\gamma_1$");      
      break;
    case  5:  p = strcat(Label, "$k_1$");        
      break;
    case  6:  p = strcat(Label, "$\\mu_2$");
      break;
    case  7:  p = strcat(Label, "$\\gamma_2$");      
      break;
    case  8:  p = strcat(Label, "$k_2$");        
      break;
    case  9:  p = strcat(Label, "$\\mu_3$");
      break;
    case 10:  p = strcat(Label, "$\\gamma_3$");      
      break;
    case 11:  p = strcat(Label, "$k_3$");        
      break;
    case 12:  p = strcat(Label, "$\\mu_4$");
      break;
    case 13:  p = strcat(Label, "$\\gamma_4$");      
      break;
    case 14:  p = strcat(Label, "$k_4$");        
      break;
    case 15:  p = strcat(Label, "$K$");      
      break;
    case 16:  p = strcat(Label, "$A$");        
      break;
      
      
    default:
      printf(".... INVALID PARAMETER KEY [key = %d]\n", j);
      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
