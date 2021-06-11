#include <MODEL.h>

void AssignSymbol_to_Model_Variables(int j, char * Label, Parameter_Table * Table)
{
  char *pFile;
  int n,m; 
  char * pCell= (char *)calloc(10, sizeof(char) );

  n = j%Table->No_of_AGES; 

  //assert( n == j ); 
  assert(Table->No_of_CELLS == 1);
  

  if( j<Table->No_of_AGES ){
      Label[0]='\0';
      pFile = strcat(Label, "P[");
      pCell[0]='\0';
      sprintf(pCell, "%d", n);
      pFile = strcat(Label, pCell);
      pFile = strcat(Label, "]");
  }else if(j==Table->No_of_AGES){
      Label[0]='\0';
      pFile = strcat(Label, "R[");
      pCell[0]='\0';
      sprintf(pCell, "%d", n);
      pFile = strcat(Label, pCell);
      pFile = strcat(Label, "]");
  }else{
    printf("\n Problem assign_Model_variables \n");
    exit(200);
  }
  
  free(pCell); 
}

