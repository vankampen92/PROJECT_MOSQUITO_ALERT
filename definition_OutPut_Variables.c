#include <MODEL.h>

double definition_Scan_Function( Parameter_Table * P )
{
  double x;
  double * y;

  int j = P->OUTPUT_VARIABLE_INDEX[0];

  x = definition_OutPut_Variables( j, y, 0.0, P );

  return (x);
}

double definition_OutPut_Variables(int j, double * y, const double t, Parameter_Table * Table)
{
  int i, N;
  double x = 0.0;

  /* Definition of the numerical order, from 0 to n, of model variables */
  #include <Model_Variables_Code.Include.c>

  if (Table->T->TYPE_of_TIME_DEPENDENCE == 0 ) N = 0; 
  else                                         N = Table->TDC->TIME_DEPENDENT_PARAMETERS;

  /* Genuine output variables are those that derive from the state of the system and,
   * therefore, should be evaluated as a funcion of system state variables
   */
  if (j < OUTPUT_VARIABLES_GENUINE ) {
    /* Derived output variables from model dynamic variables and parameters */
    switch(j)
    {
    
    case 0:  x = Average_Participant_Density ( y, Table );
      break;
    
    case 1:  x = Average_Participant_Age ( y, Table );
      break;

    case 2:  x = Total_Number_of_Participants( y, Table);
      break;
      
    default:
      printf(" INVALID VARIABLE CODE in ./definition_OutPut_Variables.c (variable = %d)\n", j);
      printf(" Output Variables range from 0 to 2: Program will exit!  ");
      printf(" Press any key..."); getchar();
      exit(0);
    }
  }
  /* Time depenendet parameters can be plotted as output variables too  */
  else if (j >= OUTPUT_VARIABLES_GENUINE && j < OUTPUT_VARIABLES_GENUINE + N) {
    j -= OUTPUT_VARIABLES_GENUINE;
    
    i = Discret_Time_Choice_Interpolation(t, Table->T->Time_Vector, Table->T->I_Time);
    x = Table->TDC->Dependent_Parameter[j][i];
  }
  /* The last MODEL_STATE_VARIABLES output variables are the MODEL_STATE_VARIABLES */
  else {
    j -= (OUTPUT_VARIABLES_GENUINE + N); /* #defined in MODEL.h */
    assert( j < Table->MODEL_STATE_VARIABLES );
    x = y[j];
  }

  return (x);
}
