#include <MODEL.h>

void AssignSymbol_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  int n,m; 
  char * pCell= (char *)calloc(10, sizeof(char) );

  n = j%Table->No_of_AGES; 

  assert( n == j ); 
  assert(Table->No_of_CELLS == 1);
  
  Label[0]='\0';
  pFile = strcat(Label, "P[");
  pCell[0]='\0';
  sprintf(pCell, "%d", n);
  pFile = strcat(Label, pCell);
  pFile = strcat(Label, "]");
  
  free(pCell); 
}

