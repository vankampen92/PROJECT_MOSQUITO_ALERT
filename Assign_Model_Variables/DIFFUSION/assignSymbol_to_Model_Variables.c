#include <MODEL.h>

void AssignSymbol_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  int n,m; 
  char * pCell= (char *)calloc(10, sizeof(char) );

  n = j%Table->No_of_AGES; 
  m = j/Table->No_of_AGES;

  Label[0]='\0';
  if( m < Table->No_of_CELLS ) { 
    
    sprintf(pCell, "%d", m);
    pFile = strcat(Label, "n\\d");
    pFile = strcat(Label, pCell);
    pFile = strcat(Label, "\\u");
    pFile = strcat(Label, "[");
    pCell[0]='\0';
    sprintf(pCell, "%d", n);
    pFile = strcat(Label, pCell);
    pFile = strcat(Label, "]");
    
  }  
  else{
    printf(".... INVALID VARIABLE KEY [key = %d]\n", j);
    printf(".... Provided Model Variable Codes have been correcly defined,\n");
    printf(".... the permited correspondences are:\n");
    printf(".... from key = 0 to key = %d\n", Table->MODEL_STATE_VARIABLES-1);
    printf(".... The program will exit\n");
    exit(0);
  }
  
  free(pCell); 
}

