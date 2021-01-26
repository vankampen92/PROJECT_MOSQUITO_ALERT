/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2018 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code estimates ODE model parameters from data. Observed data are
   given as an input file (in matrix structure: a first row of times and
   as many rows as observed variables in the following rows). If there is
   time dependence (for instance, in just parameter 16, the 'downloading
   rate': -t4 1 -DP 1 -DC- -D0 0 -D1 1 -D2 0 -P0 16), then a time dependent
   file should be also provided through the input agument list.

   Compilation:

   . ~$ make

   Execution:

   (1 single age group, 100 ages classe)
   . ~$ ./MADMODELNW -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -sT 1.0E-04 -sN 300 -sP 2 -KK 1 -k0 100 -I0 0 -z0 0.5 -m0 0.0 -M0 5.0 -A0 0.001 -I1 1 -g0 0.01 -m1 0.0 -M1 1.0 -A1 0.001 -iP 0 -en 0 -eV 100.0 -tn 12 -t0 0.0 -t1 11.0 -t4 1 -tE 2.0 -tR 100 -xn 0 -xN 0.0 -xR 0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 2 -F0 Pseudo_Data_File_12P_KK1.dat -Y0 12 -F1 Time_Dependent_Downloading_Rate_12P_KK1.dat -Y1 12

   (True parameters: -KK 1 -z0 0.5 -g0 0.01 -k0 100) (Results file renamed as Full_Parameter_Set_Ordered_KK1.dat)

   (3 age groups, 50 ages classes per group)
   . ~$ GSL_RND_SEED=98776 ./MADMODELNW -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -sT 1.0E-04 -sN 300 -sP 6 -KK 3 -k0 50 -k1 50 -k2 50 -I0 0 -m0 0.0 -M0 10.0 -A0 0.001 -I1 1 -m1 0.0 -M1 1.0 -A1 0.001 -I2 3 -m2 0.0 -M2 10.0 -A2 0.001 -I3 4 -m3 0.0 -M3 0.1 -A3 0.001 -I4 6 -m4 0.0 -M4 10.0 -A4 0.001 -I5 7 -m5 0.0 -M5 0.1 -A5 0.001 -iP 0 -en 0 -eV 100.0 -tn 100 -t0 0.0 -t1 24.0 -t4 1 -tE 2.0 -tR 100 -xn 0 -xN 0.0 -xR 0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 2 -F0 Pseudo_Data_File_100P_KK3.dat -Y0 100 -F1 Time_Dependent_Downloading_Rate_25P.dat -Y1 25
    
   (True parameters: -KK 3 -z0 5.0 -g0 0.1 -k0 50 -z1 5.0 -g1 0.01 -k1 50 -z2 5.0 -g2 0.05 -k2 50) (Results file renamed as Full_Parameter_Set_Ordered_KK3.dat)

   Two important Notices: 
 1. -tn 100 and -Y0 100 should match!!! By contrast, -Y1 25 may or may not coincide, since 
    the funcion Time_Dependence_Control_Upload() uses splines to interpolate as many points as necessary 
    based on the points given in the file of time dependent parameters (here Time_Dependent_Downloading_Rate_25P.dat)
 2. -xn 1 (Random Intial Condition), then -xR 1 and -xN (total initial population) has to be
    non-zero. Otherwise, please, -xn 0 -xR 0  

   See file denition_OutPut_Variables.c for full -v?? input argument code definitions. Examples are:

   -v0  0
   -v1  1
   -v2  2

   / -en 0 -eP0 17 -eV 0.0103805                // Parameter Space of Error Model:        -en Number of Error Model-related parameters to be optimized: -eP0 [Error_Parameter_0] -eV [Variance]
   / -G0 2  -G1 2 -n 4  -v0 3 -v1 4 -v2 5 -v3 6 // Output/Observed Varables:              -n  Number of Observed Variables] to be plotted in 4 panels (-G0 2 -G1 2)
   / -iP 0                                      // Parameter Space of Initial Conditions: -iP Number of Initial Condition Variables to be optimized
   / -i0 9 -u0 0.0 -U0 100.0                    // Max (-U0) and Min (-u0) values to bound the search for suitable initial conditions at parameter 0
   / -tn 100 -t0 0.0 -t1 10.0 -t4 1 -xn 0 -xN 0.0 -tE 2.0  // Arguments Controling Numerical Integration
   / -DP 1 -DC- -D0 0 -D1 1 -D2 0 -P0 16 -a0 0  // Arguments controling type of time dependence of model parameters.
   / -tR 100                                    // Number of random seeds that will launched (parallel searches)
   / -Fn 2 -F0 Pseudo_Data_File.dat -F1 Time_Dependent_Downloading_Rate.dat // Two files to read!!! Therefore, they should be present in the execution directory.
   / -Y0 12 -Y1 12: number of columns. The same number is recomended.
*/

int main(int argc, char **argv)
{
  int i, j, k, n, s, z, key;
  double value, Min_Value, Data_Value, Theory_Value;
  double Likelihood_Value, Average_Likelihood_Value, Standard_Error_Value, Ave, Var;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  P_ARG = &Table;

#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc, argv);

/* This is important to update Output Variable Index vector and dependent parameter 
   vector according to imput parameters from the command line 
*/
#include <include.Time_Dependence_Control.default.aux.c>
#include <include.Output_Variables.default.aux.c>

#include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  Parameter_Model * Initial_Guess = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (&Table, Initial_Guess);
  printf(" Parameter_Model structure 'Initial_Guess' has been correctly allocated and initiated\n");

  /* B E G I N : Reserving memmory for Error Model Parameter Space */
  Parameter_Space * Error_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  if( No_of_ERROR_PARAMETERS > 0 ) {
#include <include.Error_Control.default.aux.c>
    Parameter_Space_Alloc( Error_Space, No_of_ERROR_PARAMETERS, d_Error);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Error_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Error_Space->Parameter_Acc);
    Parameter_Space_Error_Initialization( Error_Space,
					  No_of_ERROR_PARAMETERS, d_Error,
					  Index_Error, Ranges_Error, Acc_Error );
    printf("Error Model Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.E_Space = Error_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Initial Conditions Parameter Space */
  Parameter_Space * Initial_Condition_Space = (Parameter_Space *)calloc(1,
									sizeof(Parameter_Space));
  if( No_of_IC > 0 ) {
#include <include.Initial_Conditions.default.aux.c>
    Parameter_Space_Alloc( Initial_Condition_Space, No_of_IC, d_IC );
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_min, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_min);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_MAX);
    Parameter_Table_Copy_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc, &Table);
    Model_Variables_Code_into_Parameter_Model(Initial_Condition_Space->Parameter_Acc);
    Parameter_Space_IC_Initialization( Initial_Condition_Space,
				       No_of_IC, d_IC,
				       Index_IC, Ranges_IC, Acc_IC );
    printf("Initial Condition Parameter_Space structure has been correctly allocated and initiated\n");
  }
  Table.IC_Space = Initial_Condition_Space;
  /*     E N D : ------------------------------------- */

  /* B E G I N : Reserving memmory for Parameter Space */
#include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);  // -sP 2
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  Table.S = Space;
  printf("Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME);
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");  // Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif
 // Press_Key();
  
  char   ** Name_of_Rows          = (char **)calloc(SUB_OUTPUT_VARIABLES, sizeof(char *) );
  double ** Empirical_Data_Matrix = (double **)calloc( SUB_OUTPUT_VARIABLES, sizeof(double *) );
  // Matrix with the full Empirical Data. After to be filter.
  double ** Empirical_Data_Matrix_Full = (double **)calloc( No_of_MAX_TIMES, sizeof(double *) );
  for (i=0; i<No_of_MAX_TIMES; i++) {
    Empirical_Data_Matrix_Full[i] = (double *)calloc( No_of_MAX_TIMES, sizeof(double) );
  }

  for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    Name_of_Rows[i]         = Table.Output_Variable_Symbol[key];
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );
  }

  /* B E G I N : Time Dependent Parameters, Observed Data, and Output files           */
  char * pF;
  char * TIME_PARAMETERS_FILE = (char *)calloc(1000, sizeof(char) ); /* Input files   */
  char * OBSERVED_DATA_FILE   = (char *)calloc(1000, sizeof(char) ); /* Input files   */
  char * PARAMETER_SET_FILE   = (char *)calloc(1000, sizeof(char) ); /* Output files  */

  FILE * DEMO;
  PARAMETER_SET_FILE[0] = '\0';
  pF = strcat(PARAMETER_SET_FILE, "Full_Parameter_Set.dat");
  DEMO = fopen(PARAMETER_SET_FILE, "w");

  /* In order for these default names to work properly, you need -Fn 0 in command line */
  OBSERVED_DATA_FILE[0] = '\0';
  pF = strcat(OBSERVED_DATA_FILE, "Observed_Data_File.dat");          /* Default Name */
  if( No_of_FILES > 0) strcpy(OBSERVED_DATA_FILE, Name_of_FILE[0]);   // -Fn 2

  TIME_PARAMETERS_FILE[0] = '\0';
  pF = strcat(TIME_PARAMETERS_FILE, "Time_Dependent_Parameters.dat"); /* Default Name */
  if( No_of_FILES > 1) strcpy(TIME_PARAMETERS_FILE, Name_of_FILE[1]);
  /*     E N D -----------------------------------------------------------------------*/

  if (TYPE_of_TIME_DEPENDENCE == 0) {                                 // -t4 1
    printf(" No Time Dependence!!!\n");
    printf(" Check -t4 argument. It should be: -t4 1, but it is: -t4 %d\n",
	   TYPE_of_TIME_DEPENDENCE);
    printf(" The program will exit.\n");
    exit(0);
  }
  else {
#include <include.Time_Dependence_Control.default.aux.c>
    printf(" Time_Dependence_Control and Time_Control structures will be allocated: \n");
    printf(" %d output variables of length %d points will be allocated\n",
	   SUB_OUTPUT_VARIABLES, I_Time);
    Time_Dependence_Control_Alloc(&Time, &Time_Dependence, &Table,
				  I_Time, TIME_DEPENDENT_PARAMETERS, No_of_COVARIATES);
    printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
    printf(" correctly allocated\n");
    
    int No_of_EMPIRICAL_TIMES = F_y_GRID[1]; // No of Cols the time-dependent parameter file
                                             // For example, -Y1 12 (see input argument list)
    Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
				   I_Time, No_of_EMPIRICAL_TIMES,
				   TIME_DEPENDENT_PARAMETERS,
				   TYPE_of_TIME_DEPENDENCE,        // -t4 1
				   TYPE_0_PARAMETERS,              // -D0 0
				   TYPE_1_PARAMETERS,              // -D1 1
				   TYPE_2_PARAMETERS,              // -D2 0
				   No_of_COVARIATES,               // -DC 0
				   dependent_parameter, forcing_pattern, // -P0 16
				   "File_of_Covariates.dat",
				   TIME_PARAMETERS_FILE);
    printf(" Time denpencies have been incluced\n");
  }

  
  int No_of_COLS_full = No_of_MAX_TIMES; // No of Columns in Observed Data File always the same size.
  int * DUMMY_POINTER = No_of_MAX_TIMES; // Dummy pointer since Reading_Standard_Data_Matrix_from_File needs a int pointer as third argument.
  //int No_of_COLS = F_y_GRID[0]; // No of Columns in Observed Data File
  Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE,
					  Empirical_Data_Matrix_Full,
					  &DUMMY_POINTER,
					  No_of_MAX_TIMES, 
					  0, Name_of_Rows,
					  1, Time.Time_Vector );
  /*Writing_Standard_Data_Matrix( Empirical_Data_Matrix_Full,
				No_of_MAX_TIMES,
        No_of_MAX_TIMES ,
				0,
         Name_of_Rows,
				0,
         Time.Time_Vector);
         */
  // Press_Key(); 
  /* B E G I N :   Reserving memmory for Observed Data and Fitting Structure */
  Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
  Observed_Data_Alloc( Data, SUB_OUTPUT_VARIABLES, I_Time);
  
 //Observed_Data_Initialization( Data, SUB_OUTPUT_VARIABLES,
 //				I_Time, Empirical_Data_Matrix,
 //				"" );
  for(j=0; j < 60; j++)printf("%d \t",Table.OUTPUT_VARIABLE_INDEX[j]);
  int * Index_Output_Variables_fil = Table.OUTPUT_VARIABLE_INDEX;
  Observed_Data_Initialization_Fil( Data, SUB_OUTPUT_VARIABLES,
                              I_Time, Empirical_Data_Matrix_Full,
                              Index_Output_Variables_fil ,"" );

  // Uncomment To chech whether the Observed Data file is well read.
  /*printf("\n Observed Data filter:");
  for(i=0; i < SUB_OUTPUT_VARIABLES; i++){
    Press_Key();
    printf("\n Row %d \n", i);
     for(j=0; j < 100; j++)printf("%g\t", Data->N[i][j]);
    }
  */
  printf(" Observed_Data structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

  /* B E G I N :   Defining first row of "Full_Parameter_Set.dat" file
   */
  fprintf(DEMO, "ID\t");
  for(i=0; i<Table.TOTAL_No_of_MODEL_PARAMETERS; i++) {
    key = Table.Index[i];
    fprintf(DEMO, "%s\t", Table.Symbol_Parameters[key]);
  }
  for(i=0; i<No_of_IC; i++) {
    key = Initial_Condition_Space->Parameter_Index[i];
    fprintf(DEMO, "%s\t", Table.Model_Variable_Symbol[key]);
  }
  for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
    key = Error_Space->Parameter_Index[i];
    if(key < OUTPUT_VARIABLES_GENUINE)
      fprintf(DEMO, "Error(%s)\t", Table.Output_Variable_Symbol[key]);
    else
      fprintf(DEMO, "Error_Parameter_%d\t", i);
  }
  fprintf(DEMO, "NegLogLike\n");
  /*     E N D : --------------------------------------------------------
   */
  Press_Key();
  s = 0;
  int s_Attemps   = 0;   /* This counter will count number of random seeds */
  int Total_Tries = Realizations;                                // -tR 1000
  for(z=0; z<Realizations; z++) {  

    Parameter_Model_Copy_into_Parameter_Table(&Table, Initial_Guess);
    Random_Initial_Guess_within_Boundaries_Table(&Table, Space);

    /* Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table, */
    /* 				   I_Time, No_of_EMPIRICAL_TIMES, */
    /* 				   TIME_DEPENDENT_PARAMETERS, */
    /* 				   TYPE_of_TIME_DEPENDENCE,        // -t4 1 */
    /* 				   TYPE_0_PARAMETERS,              // -D0 0 */
    /* 				   TYPE_1_PARAMETERS,              // -D1 1 */
    /* 				   TYPE_2_PARAMETERS,              // -D2 0 */
    /* 				   No_of_COVARIATES,               // -DC 0 */
    /* 				   dependent_parameter, forcing_pattern, // -P0 16 */
    /* 				   "File_of_Covariates.dat", */
    /* 				   TIME_PARAMETERS_FILE);  */

    assert( Time_Dependence.No_of_TIMES == I_Time );

    /* Initial conditions from empirical data at the initial time ( -xn 0 )      */
    /* Initial_Condition_from_Data_into_Parameter_Table (&Table,                 */
    /*                                                   Empirical_Data_Matrix); */

    Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
    F->Data                  = Data;
    F->Space                 = Space;
    F->Table                 = &Table;
    F->Minimization          = 1;     // 1: Function Minimization  // 0: Function Evaluation
    F->Bounded_Parameter_Set = 1;
    F->Function              = GSL_Function_to_Minimize;
#if defined VERBOSE
    F->Verbose               = 1;     // 1: Verbose                // 0: Non Verbose
#else
    F->Verbose               = 0;     // 1: Verbose                // 0: Non Verbose
#endif
    F->Iteration             = z;
    
    if(F->Verbose == 1) {
      if(No_of_IC > 0)
	Parameter_Space_Write_Min_Max_IC_Values (Initial_Condition_Space, &Table );
      printf("\n");
      if(No_of_ERROR_PARAMETERS > 0)
	Parameter_Space_Write_Min_Max_Error_Values (Error_Space, &Table );
      printf("\n");
      Parameter_Space_Write_Min_Max_Values (Space, &Table );
      printf("\n");
    }

    // printf("... Simplex bounded optimization starts right at this point within the\n");
    // printf("... parameter space boundaries given above\n");
    // getchar();

    /* B E G I N :  This line of code invoques the optimizaton process for this random seed */
    Min_Value = GSL_Minimization_Driver( F );
    /*     E N D :  ----------------------------------------------------------------------- */

    if (F->Bounded_Parameter_Set == 1) {
      printf(" Min Value: NLL=%g\t Best Estimates: ", Min_Value);

      fprintf(DEMO, "%d:\t", s_Attemps);

      for(i=0; i<Table.TOTAL_No_of_MODEL_PARAMETERS; i++) {
	key = Table.Index[i];
	value = AssignStructValue_to_VectorEntry(key, &Table);
	printf(" %s  = %g  ", Table.Symbol_Parameters[key], value);
	fprintf(DEMO, "%g\t", value);
      }
      for(i=0; i<No_of_IC; i++) {
	key = Initial_Condition_Space->Parameter_Index[i];
	value = Model_Variable_Initial_Condition_into_Vector_Entry_Table( key, &Table );
	printf("%s = %g  ", Table.Model_Variable_Symbol[key], value);
	fprintf(DEMO, "%g\t", value);
      }
      for(i=0; i<No_of_ERROR_PARAMETERS; i++) {
	key = Error_Space->Parameter_Index[i];
	value = Error_Model_into_Vector_Entry_Table( key, &Table );
	if(key < OUTPUT_VARIABLES_GENUINE)
	  printf("%s = %g  ", Table.Output_Variable_Symbol[key], value);
	else
	  printf("Error_Parameter_%d = %g  ", i, value);
	fprintf(DEMO, "%g\t", value);
      }
      fprintf(DEMO, "%g\n", Min_Value);

      s++; // Counting Successful attemts!!! 
    }
    printf("\n");

    free(F);

    s_Attemps++;

    printf(" Parameter Set Attemp No: %d\t Remaining Attemps: %d\t Successful Attemps: %d\n",
	   s_Attemps, Total_Tries-s_Attemps, s );
  }
  fclose(DEMO);

  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */ 
  Observed_Data_Free(Data); free(Data);

  Time_Dependence_Control_Free( &Time_Dependence, &Table );

#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );

  if( No_of_IC > 0 ) {
  #include <include.Initial_Conditions.default.free.c>
    Parameter_Space_Free(Initial_Condition_Space, No_of_IC);
  }
  free(Initial_Condition_Space);

  if( No_of_ERROR_PARAMETERS > 0 ) {
  #include <include.Error_Control.default.free.c>
    Parameter_Space_Free(Error_Space, No_of_IC);
  }
  free(Error_Space);

  #include <include.Output_Variables.default.free.c>

  #include <include.Time_Dependence_Control.default.free.c>

  free(Name_of_Rows);
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++)  free(Empirical_Data_Matrix[i]);
  free(Empirical_Data_Matrix);

  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  free(PARAMETER_SET_FILE);

  free(Initial_Guess);

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */

  printf("\nEnd of progam\n");
  return (0);
}
