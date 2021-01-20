/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2011 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <MODEL.h>

#include "global.h"

/* This code scans a function that depends on model parameters as specified
   in Parameter_Table Structure.  Parameter ranges are defined via Parameter_Space
   structure. Parameters to scan are defined as input arguments.

   Any parametric function should be generically defined as:
   
   double Function (Parameter_Table * Table); 
  
   Compilation:
   
   . ~$ make 
   
   Execution:
                                                       
   . ~$ ./MADMODEL -y0 0 -G0 1 -G1 1 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -iP 0 -en 0 -eV 100.0 -sP 2 -KK 1 -k0 100 -z0 0.5 -g0 0.01 -I0 0 -m0 0.2 -M0 1.0 -d0 300 -I1 1 -m1 0.001 -M1 0.05 -d1 300 -tn 12 -t0 0.0 -t1 11.0 -t4 1 -tE 2.0 -xn 0 -xN 0.0 -xR 0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 2 -F0 Pseudo_Data_File.dat -Y0 12 -F1 Time_Dependent_Downloading_Rate.dat -Y1 12 -G14 "Function:\\(2749)\\gx\\u2\\d"
   
   . ~$ ./MADMODEL -y0 0 -G0 1 -G1 1 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -iP 0 -en 0 -eV 100.0 -sP 2 -KK 1 -k0 2377 -z0 1.9 -g0 0.5 -I0 0 -m0 0.0 -M0 5.0 -d0 100 -I1 1 -m1 0.0 -M1 1.0 -d1 100  -tn 2378 -t0 0.0 -t1 2377.0 -t4 1 -tE 2.0 -xn 0 -xN 0.0 -xR 0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 2 -F0 Time_Evo_Observed_Age_Dist_4FirstAges.data -Y0 2378 -F1 Downloads_Transposed.data -Y1 2354 -G14 "Function:\\(2749)\\gx\\u2\\d"

   -G14 is the title. This input argument only works when you are generating an only final 
   plot with only one panel as the single graphical output over all your code. What is written 
   there follows CPGPLOT syntax, for instance, \\(2749) codes for a space, \\gx codes for a
   the greek letter x (chi), \\u allows the 2 to go up (as a superscript), and \\d returns 
   level writing back to normal (\\d and \\u or \\u and \\d must be always used in pairs!!!).   
*/


gsl_rng * r; /* Global generator defined in main.c */

float * customized_contour_levels( Parameter_CPGPLOT * C )
{
    int i;

    /* for (i=0; i < C->NC; i++) { */
    /*   clevels[i] = 1.0; */
    /* } */
    /* Two contour levels */
    C->NC = 3;
    float * clevels = (float *)calloc( C->NC, sizeof(float) );
    clevels[0] = 10.0;
    clevels[1] = 20.0;
    clevels[2] = 50.0;
    
    return(clevels);
}

int main(int argc, char **argv)
{
  int i, key; 
  Parameter_Table Table;
  double Value_0, Value_1; 
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  
  P_ARG = &Table;

#include "default.c"
  
  /* Extra default values */
  int No_of_POINTS_1    = 400;
  int Input_Parameter_1 = 12; 
  int No_of_POINTS_2    = 400;
  int Input_Parameter_2 = 25;

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  /* This is important to update Output Variable Index vector and dependent parameter 
     vector according to imput parameters from the command line 
  */
  #include <include.Time_Dependence_Control.default.aux.c>
  #include "include.Output_Variables.default.aux.c"
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");

  Parameter_Model * Parameter_True_Values = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );
  P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (&Table, Parameter_True_Values);
  printf(" Parameter_Model structure 'Parameter_True_Values' has been correctly allocated and initiated\n");
  
  /* B E G I N : Reserving memmory for Parameter Space */
  Parameter_Space * Error_Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  assert( No_of_ERROR_PARAMETERS == 0 );
  Table.E_Space = Error_Space;
 
  Parameter_Space * Initial_Condition_Space = (Parameter_Space *)calloc(1,
									sizeof(Parameter_Space));
  assert( No_of_IC == 0 );
  Table.IC_Space = Initial_Condition_Space;
  
  #include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
				  d, Index, Ranges, Acc);
  Table.S = Space;
  printf("Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

  No_of_POINTS_1    = Space->N[0];
  Input_Parameter_1 = Space->Parameter_Index[0]; 
  No_of_POINTS_2    = Space->N[1];
  Input_Parameter_2 = Space->Parameter_Index[1];
  
#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME);
  printf(" Parameter_CPGPLOT plotting structure has been correctly allocated and initiated\n");
#endif

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  int i;
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n"); //Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif
  
  char   ** Name_of_Rows          = (char **)calloc(SUB_OUTPUT_VARIABLES, sizeof(char *) );
  double ** Empirical_Data_Matrix = (double **)calloc( SUB_OUTPUT_VARIABLES, sizeof(double *) );
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++) {
    key = Table.OUTPUT_VARIABLE_INDEX[i];
    Name_of_Rows[i]         = Table.Output_Variable_Symbol[key];
    Empirical_Data_Matrix[i] = (double *)calloc( I_Time, sizeof(double) );
  }

  /* B E G I N : Time Dependent Parameters, Observed Data, and Output files           */
  char * pF;
  char * TIME_PARAMETERS_FILE = (char *)calloc(1000, sizeof(char) ); /* Input files   */
  char * OBSERVED_DATA_FILE   = (char *)calloc(1000, sizeof(char) ); /* Input files   */

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
  }

  int No_of_COLS = F_y_GRID[0]; // No of Columns in Observed Data File
  Reading_Standard_Data_Matrix_from_File( OBSERVED_DATA_FILE,
					  Empirical_Data_Matrix,
					  &SUB_OUTPUT_VARIABLES,
					  No_of_COLS, 
					  0, Name_of_Rows,
					  1, Time.Time_Vector );

  Writing_Standard_Data_Matrix( Empirical_Data_Matrix,
				SUB_OUTPUT_VARIABLES, I_Time,
				1, Name_of_Rows,
				0, Time.Time_Vector);
  Press_Key(); 
  /* B E G I N :   Reserving memmory for Observed Data and Fitting Structure */
  Observed_Data * Data = (Observed_Data *)calloc(1, sizeof(Observed_Data));
  Observed_Data_Alloc( Data, SUB_OUTPUT_VARIABLES, I_Time);
  Observed_Data_Initialization( Data, SUB_OUTPUT_VARIABLES,
				I_Time, Empirical_Data_Matrix,
				"" );
  printf(" Observed_Data structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

  Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
  F->Data                  = Data;
  F->Space                 = Space;
  F->Table                 = &Table;
  F->Minimization          = 0;  // 0: Function Evaluation
  F->Bounded_Parameter_Set = 1;
  F->Function              = GSL_Function_to_Minimize;
#if defined VERBOSE
  F->Verbose               = 1;     // 1: Verbose                // 0: Non Verbose
#else
  F->Verbose               = 0;     // 1: Verbose                // 0: Non Verbose
#endif
  F->Iteration             = 0;
  
  Table.Fitting_Data       = (void *)F;  /* Table and F structures point to each other */

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
  assert( Time_Dependence.No_of_TIMES == I_Time );
  assert( TYPE_2_PARAMETERS           == 0);         
  
  double * W_GRID = (double *)malloc( No_of_POINTS_1 * No_of_POINTS_2 * sizeof(double) );
  int Status =  generic_Function_Parameter_2Dim_Scan(&Table, 
						     No_of_POINTS_1, Input_Parameter_1,
						     No_of_POINTS_2, Input_Parameter_2,
						     Function_to_Minimize, 
						     W_GRID, "Goodness_of_Fit.dat");
#if defined CPGPLOT_REPRESENTATION
/* BEGIN : 2D GRID cpgplot representation */
  /*********************************************************************/
  Table.CPG->X_label   = Table.Symbol_Parameters_Greek_CPGPLOT[Input_Parameter_1]; 
  Table.CPG->Y_label   = Table.Symbol_Parameters_Greek_CPGPLOT[Input_Parameter_2]; 
  /*********************************************************************/
  // Boundary(Input_Parameter_1, &Value_0, &Value_1);
  Value_0 = Parameter_Model_into_Vector_Entry( Input_Parameter_1, Space->Parameter_min );
  Value_1 = Parameter_Model_into_Vector_Entry( Input_Parameter_1, Space->Parameter_MAX );
  
  Table.CPG->ORIGIN_X    = Value_0;
  Table.CPG->X_Dimension = (Value_1 - Value_0);

    // Boundary(Input_Parameter_2, &Value_0, &Value_1);
    Value_0 = Parameter_Model_into_Vector_Entry( Input_Parameter_2, Space->Parameter_min );
    Value_1 = Parameter_Model_into_Vector_Entry( Input_Parameter_2, Space->Parameter_MAX );
    
    Table.CPG->ORIGIN_Y = Value_0;
    Table.CPG->Y_Dimension = (Value_1 - Value_0);

    Table.CPG->x_GRID  = No_of_POINTS_1; 
    Table.CPG->y_GRID  = No_of_POINTS_2;

    int Output_Variable  = Table.OUTPUT_VARIABLE_INDEX[0];
    Table.CPG->W_label   = Table.Output_Variable_Name[Output_Variable];

    int FIRST_PLOT = 0;
    double i_PLOT  = 0.0;
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___S_H_A_D_E_S( Table.CPG,
							  W_GRID, 
							  FIRST_PLOT,
							  Table.CPG->CPG_SCALE_W, 
							  Table.CPG->CPG_RANGE_W_0,
							  Table.CPG->CPG_RANGE_W_1,
							  i_PLOT );

    FIRST_PLOT = 1;
    Table.CPG->AUTOMATIC_CONTOUR = 0;
    /* If AUTOMATIC_CONTOUR is 0, the user should customized contours through
       the function customized_contour_levels(...);
    */
    Table.CPG->contour_level = customized_contour_levels ( Table.CPG );
    C_P_G___P_L_O_T_T_I_N_G___2d___G_R_I_D___C_O_N_T_O_U_R( Table.CPG,
							    W_GRID, 
							    FIRST_PLOT,
							    Table.CPG->CPG_SCALE_W, 
							    Table.CPG->CPG_RANGE_W_0,
							    Table.CPG->CPG_RANGE_W_1,
							    i_PLOT );
    
    /* Annotating the countours by hand */
    // cpgptxt(float x, float y, float angle, float fjust,  const char *text);
    
    cpgslw(3);
    cpgptxt(0.00006, 60.0, 0.0, 0.0,  "10.0");
    cpgptxt(0.0003, 60.0, 0.0, 0.0,   "20.0");
    cpgptxt(0.00082, 75.0, 0.0, 0.0,  "50.0");

    key = Space->Parameter_Index[0]; 
    double Px = Parameter_Model_into_Vector_Entry ( key, Parameter_True_Values );

    key = Space->Parameter_Index[1]; 
    double Py = Parameter_Model_into_Vector_Entry ( key, Parameter_True_Values );
    
    cpgpt1(Px, Py, 4);

    // cpg_XY_same_arrow( N, xs, ys, CPG->color_Index, CPG->type_of_Line, CPG->type_of_Width );
    float * xs = (float *)calloc(2, sizeof(float) );
    float * ys = (float *)calloc(2, sizeof(float) );
    xs[0] = 0.5;    xs[1] = 0.5;
    ys[0] = 0.0;    ys[1] = 0.01;
    cpg_XY_same_arrow( 2, xs, ys, 4, 1, 4);
    free(xs);
    free(ys); 
#endif  	

  free (W_GRID);

  free(F); 
  
  Observed_Data_Free(Data); free(Data);
  Time_Dependence_Control_Free( &Time_Dependence, &Table );
  
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif  

  #include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );
  free(Initial_Condition_Space);  
  free(Error_Space);

  #include <include.Output_Variables.default.free.c>
  free(Parameter_True_Values);

  #include <include.Time_Dependence_Control.default.free.c>
  
  free(Name_of_Rows);
  for (i=0; i<SUB_OUTPUT_VARIABLES; i++)  free(Empirical_Data_Matrix[i]);
  free(Empirical_Data_Matrix);
  
  free(TIME_PARAMETERS_FILE);
  free(OBSERVED_DATA_FILE);
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */
  
  printf("\nEnd of progam\n");
  return (0);
}





