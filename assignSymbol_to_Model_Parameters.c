#include "./Include/MODEL.h"

void AssignCPGPLOT_Symbol_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "\\gg\\d0\\u");   
      break;
    case  1:  p = strcat(Label, "k\\d0\\u");
      break;
    case  2:  p = strcat(Label, "\\gg\\d1\\u");   
      break;
    case  3:  p = strcat(Label, "k\\d1\\u");   
      break;
    case  4:  p = strcat(Label, "\\gg\\d2\\u");
      break;
    case  5:  p = strcat(Label, "k\\d2\\u");   
      break;
    case  6:  p = strcat(Label, "\\gg\\d3\\u");   
      break;
    case  7:  p = strcat(Label, "k\\d3\\u");
      break;
    case  8:  p = strcat(Label, "\\gg\\d4\\u");   
      break;
    case  9:  p = strcat(Label, "k\\d4\\u");   
      break;
    case 10:  p = strcat(Label, "\\gg\\d5\\u");
      break;
    case 11:  p = strcat(Label,"k\\d5\\u");   
      break;
    case 12:  p = strcat(Label, "\\gg\\d6\\u");   
      break;
    case 13:  p = strcat(Label, "k\\d6\\u");
      break;
    case 14:  p = strcat(Label, "\\gg\\d7\\u");   
      break;  
    case 15:  p = strcat(Label, "K");
      break;
    case 16:  p = strcat(Label, "A\\d0\\u");   
      break;
    case 17:  p = strcat(Label, "Rho\\d0\\u");   
      break;  
    
    default:
      printf(".... INVALID PARAMETER KEY [key=%d]\n", j);
      printf(".... The permited correspondences are (0 to 12):\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}

void AssignSymbol_to_Model_Parameters(int j, char * Label, Parameter_Table *P)
{
  /* Short Labels for Model Parameters */

  char * p;
  Label[0] = '\0';

  switch(j)
    {
    case  0:  p = strcat(Label, "Gamma_0");   
      break;
    case  1:  p = strcat(Label, "k_0");   
      break;
    case  2:  p = strcat(Label, "Gamma_1");   
      break;
    case  3:  p = strcat(Label, "k_1");   
      break;
    case  4:  p = strcat(Label, "Gamma_2");   
      break;
    case  5:  p = strcat(Label, "k_2");   
      break;
    case  6:  p = strcat(Label, "Gamma_3");   
      break;
    case  7:  p = strcat(Label, "k_3");   
      break;
    case  8:  p = strcat(Label, "Gamma_4");   
      break;
    case  9:  p = strcat(Label, "k_4");   
      break;
    case 10:  p = strcat(Label, "Gamma_5");   
      break;
    case 11:  p = strcat(Label, "k_5");   
      break;
    case 12:  p = strcat(Label, "Gamma_6");   
      break;
    case 13:  p = strcat(Label, "k_6");   
      break;
    case 14:  p = strcat(Label, "Gamma_7");   
      break;
    case 15:  p = strcat(Label, "K");
      break;
    case 16:  p = strcat(Label, "A");   
      break;
    case 17:  p = strcat(Label, "Rho");   
      break;  
    
      
    default:
      printf(".... INVALID PARAMETER KEY [key=%d]\n", j);
      printf(".... The permited correspondences are (0 to 12)\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);
      exit(0);
    }
}
