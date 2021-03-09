#include <MODEL.h>

void Parameter_Table_into_Vector_Entries ( Parameter_Table * P, gsl_vector * X,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = AssignStructValue_to_VectorEntry( key, P );
    gsl_vector_set(X, i, value);
  }
}

void Parameter_Table_into_Vector_Entries_Initial_Condition ( Parameter_Table * P, gsl_vector * X,
							     int * Index,
							     int No_of_PARAMETERS,
							     int No_of_IC)
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_IC; i++) {
    key = Index[i];
    value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, P );
    gsl_vector_set(X, i+No_of_PARAMETERS, value);
  }
}

double AssignStructValue_to_VectorEntry(int j, Parameter_Table * P)
{
  double value;

  switch(j)
    {
    case  0:  value = P->Gamma_0;    
      break;
    case  1:  value = P->k_0; 
      break;
    case  2:  value = P->Gamma_1; 
      break;
    case  3:  value = P->k_1; 
      break;
    case  4:  value = P->Gamma_2; 
      break;
    case  5:  value = P->k_2; 
      break;
    case  6:  value = P->Gamma_3;    
      break;
    case  7:  value = P->k_3; 
      break;
    case  8:  value = P->Gamma_4; 
      break;
    case  9:  value = P->k_4; 
      break;
    case 10:  value = P->Gamma_5; 
      break;
    case 11:  value = P->k_5; 
      break;
    case 12:  value = P->Gamma_6;    
      break;
    case 13:  value = P->k_6; 
      break;
    case 14:  value = P->Gamma_7; 
      break;
    case 15:  value = (double)P->No_of_GROUPS;
      break;
    case 16:  value = P->A_Rate; 
      break;

    default:
      printf(".... INVALID PARAMETER KEY (key = %d)\n", j);

      printf(".... The permited correspondences are:\n");
      printf("\n");
      fprintf_Model_Parameters(stdout, P);

      printf(" The maximum number of parameters is Number_PAR_MAX\n");
      printf(" The permited number of keys go from 0, to %d\n", MODEL_PARAMETERS_MAXIMUM-1);

      exit(0);
    }

  return(value);
}
