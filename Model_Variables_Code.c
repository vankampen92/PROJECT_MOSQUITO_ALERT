#include <MODEL.h>

void Model_Variables_Code_into_Parameter_Table (Parameter_Table * Table)
{
  int i, j, n;
  int TYPE_of_MODEL;

  TYPE_of_MODEL = Table->TYPE_of_MODEL;

  switch( TYPE_of_MODEL )
    {

    case 0: /* MADMODEL * * * * * * * * * * * * * * * * * * * * * * */

      /* Number of events that can occur to a single Species: */
      Table->No_of_EVENTS                 = 2;              /* Transition or loss */  
      Table->TOTAL_No_of_EVENTS           = Table->No_of_EVENTS * Table->No_of_AGES;
      Table->TOTAL_No_of_MODEL_PARAMETERS = MODEL_PARAMETERS_MAXIMUM;
      
      n = 0;
      for(i=0; i<Table->No_of_CELLS; i++)
	for(j=0; j<Table->No_of_AGES; j++)
	  n++;
	    
      /* Conventions */
      Table->K   = n-1;     /* Label of the very last class */

      /* List of (Potentially searcheable) model parameters */
      n = 0; 
      for (i=0; i < Table->No_of_GROUPS; i++) {
	      Table->Index[n++] = 2*i; Table->Index[n++] = 2*i+1;
      }
      Table->Index[n++] = 15; Table->Index[n++] = 16; 
      
      Table->TOTAL_No_of_MODEL_PARAMETERS = n; 
      
      break;

    default:
      printf(" This TYPE_of_MODEL (%d) code is not defined.\n", TYPE_of_MODEL);
      printf(" Check input argument list\n");
      exit(0);
   }
  /* Conventionally, the last label in the argument list of

     Model_Variables_Code_into_Parameter_Table (...),

     (*K), should be the label of the last model state variable.
     Then ( * K) + 1 becomes de total number of dynamic variables.
  */
}

void Model_Variables_Code_into_Parameter_Model (Parameter_Model * P)
{
  int i, j, n;
  int TYPE_of_MODEL;

  TYPE_of_MODEL = P->TYPE_of_MODEL;

  switch( TYPE_of_MODEL )
    {

    case 0: /* MADMODEL * * * * * * * * * * * * * * * * * * * * * * */
      
      n = 0;
      for(i=0; i<P->No_of_CELLS; i++)
	for(j=0; j<P->No_of_AGES; j++)
	  n++;	    
      /* Conventions */
      P->K   = n-1;     /* Label of the very last class */

      break;
      
    default:
      printf(" This TYPE_of_MODEL (%d) code is not defined.\n", TYPE_of_MODEL);
      printf(" Check input argument list\n");
      exit(0);
   }
}
