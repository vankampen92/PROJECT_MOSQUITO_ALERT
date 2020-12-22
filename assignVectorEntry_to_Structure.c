#include <MODEL.h>

void Vector_Entries_into_Parameter_Table ( const gsl_vector * X, Parameter_Table * P,
					   int * Parameter_Index, int No_of_PARAMETERS )
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_PARAMETERS; i++) {
    key = Parameter_Index[i];
    value = gsl_vector_get(X, i);
    AssignVectorEntry_to_Structure( P, key, value );
  }
}

void Vector_Entries_into_Parameter_Table_Initial_Condition ( const gsl_vector * X,
							     Parameter_Table * P,
							     int * Index,
							     int No_of_PARAMETERS,
							     int No_of_IC)
{
  int i;
  int key;
  double value;

  for( i=0; i<No_of_IC; i++) {
    key = Index[i];
    value = gsl_vector_get(X, i+No_of_PARAMETERS);
    Vector_Entry_into_Model_Variable_Initial_Condition_Table( value, key, P );
  }
}

void AssignVectorEntry_to_Structure(Parameter_Table * P, int j, double value)
{

  switch(j)
    {
    case  0:  P->Mu_0 = value;    
      break;
    case  1:  P->Gamma_0 = value; 
      break;
    case  2:  P->k_0 = value; 
      break;
    case  3:  P->Mu_1 = value; 
      break;
    case  4:  P->Gamma_1 = value; 
      break;
    case  5:  P->k_1 = value; 
      break;
    case  6:  P->Mu_2 = value;    
      break;
    case  7:  P->Gamma_2 = value; 
      break;
    case  8:  P->k_2 = value; 
      break;
    case  9:  P->Mu_3 = value; 
      break;
    case 10:  P->Gamma_3 = value; 
      break;
    case 11:  P->k_3 = value; 
      break;
    case 12:  P->Mu_4 = value;    
      break;
    case 13:  P->Gamma_4 = value; 
      break;
    case 14:  P->k_4 = value; 
      break;
    case 15:  P->No_of_GROUPS =  (int)value;
      break;
    case 16:  P->A_Rate       = value; 
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
}
