/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            David Alonso, 2021 (c)                         */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <Include/MODEL.h>

#include "global.h"

gsl_rng * r; /* Global generator defined in main.c */

/* This code calculates ODE model temporal evolution for a range COVID19 models

   Compilation (see makefile environtment variable 'MODEL'):

   . ~$ make

   Execution (without time-dependence -t4 0):
   
   One single group example: 
   .~$ ./MADMODEL -y0 0 -n 1 -v0 4 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 10.0 -t4 0 -tR 1 -xn 0 -xN 0.0  -KK 1 -z0 0.5 -g0 0.01 -k0 100 -rA 100.0

   3 groups example: 
   .~$ ./MADMODEL -y0 0  -n 1 -v0 2 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 30.0 -t4 0 -tR 1 -xn 0 -xN 0.0-KK 3 -g0 0.01 -k0 100 -g1 0.01 -k1 100 -g2 0.01 -k2 100 -rA 100.0

   .~$ ./MADMODEL -y0 0  -n 1 -v0 1 -G0 1 -G1 1 -tn 20 -t0 0.0 -t1 5.0 -t4 0 -tR 1 -xn 0 -xN 0.0  -KK 3 -g0 0.01 -k0 100 -g1 0.001 -k1 100 -g2 0.01 -k2 100 -rA 100.0

   4 groups example:  
   .~$ ./MADMODEL -y0 0 -n 1 -v0 0 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 30.0 -t4 0 -tR 1 -xn 0 -xN 0.0 -KK 3 -g0 0.01 -k0 100 -g1 0.01 -k1 100  -g2 0.01 -k2 100 -g3 0.01 -k3 100 -rA 100.0

   (See denition_OutPut_Variables.c to understand the difference between Genuine Output Variable and plain model variables):
   
   Execution (with time-dependence -t4 1):

   .~$ ./MADMODEL -y0 0 -n 1 -v0 4 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tR 1 -xn 0 -xN 0.0  -KK 1 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0

   (with generation of 4 output variables: A, P[0], P[1], P[2] )
   .~$ ./MADMODEL -y0 0 -n 4 -v0 3 -v1 4 -v2 5 -v3 6 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tR 1 -xn 0 -xN 0.0  -KK 1 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0 

   (with generation of 4 output variables: P[0], P[1], P[2], P[3] that will become psedodata with
   additional Gaussian noise in Psedo_Data_File)
   .~$ ./MADMODEL -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tcd R 1 -xn 0 -xN 0.0  -KK 1 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0 

   (with generation of 4 output variables: P[0], P[1], P[2], P[3] that will become psedodata with
   additional Gaussian noise in Psedo_Data_File, but now 3 different age groups and 150 ages classe)
   .~$ ./MADMODEL -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 24.0 -t4 1 -tR 1 -xn 0 -xN 0.0 -xR 0 -KK 3 -g0 0.1 -k0 50 -g1 0.01 -k1 50  -g2 0.05 -k2 50 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 1 -F0 Time_Dependent_Downloading_Rate_25P.dat -Y0 25

   (with the real downloading data file and generation of 6 output variables: A(t), P[0], P[2], P[3], P[100], and P[101] 
   that may become psedodata with additional Gaussian noise in Psedo_Data_File.dat, but now 3 different age groups  
   and 2001 (20 + 1500 + 480) ages classes in total)
   .~$ ./MADMODEL -y0 0 -n 6 -v0 3 -v1 4 -v2 5 -v3 6 -v4 104 -v5 105 -G0 3 -G1 2 -tn 2354 -t0 0.0 -t1 2385.0 -t4 1 -tR 1 -xn 0 -xN 0.0 -xR 0 -KK 3 -g0 0.1 -k0 20 -g1 0.01 -k1 1500 -g2 0.05 -k2 480 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 1 -F0 Downloads_Transposed.data -Y0 2354

   ./MADMODEL -y0 0 -n 100 -G0 10 -G1 10 -tn 2354 -t0 0.0 -t1 2385.0 -t4 1 -tR 1 -xn 0 -xN 0.0 -xR 0 -KK 3 -g0 0.1 -k0 20 -g1 0.01 -k1 1500 -g2 0.05 -k2 480 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 1 -F0 Downloads_Transposed.data -Y0 2354
*/

int main(int argc, char **argv)
{
  int i;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  int No_of_EMPIRICAL_TIMES;
  double * propen_vec;
  int No_ages_PROP;
  
  No_ages_PROP = No_of_Ages_PROP;
  P_ARG = &Table;

  propen_vec = (double *)calloc(No_ages_PROP, sizeof(double) );

    char * File_prop;

  File_prop = "prop_vec.dat";
  
#include "default.c"

  /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  /* This is important to update Output Variable Index vector and dependent parameter 
     vector according to imput parameter from the command line 
  */
#include <include.Time_Dependence_Control.default.aux.c>
#include "include.Output_Variables.default.aux.c"
  
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C(   &Table );
  P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( &Table, Index_Output_Variables );
  printf(" Parameter_Table structure has been correctly allocated and initiated\n");


  upload_extra_vec_to_ParameterTable(File_prop, propen_vec,No_ages_PROP,&Table);
  
  
  /* B E G I N : Reserving memmory for Parameter Space */
#include <include.Parameter_Space.default.aux.c>
  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space));
  Parameter_Space_Alloc( Space, No_of_PARAMETERS, d);
  Parameter_Space_Initialization( Space, No_of_PARAMETERS, TOLERANCE, MAX_No_of_ITERATIONS,
    d, Index, Ranges, Acc);
  Table.S = Space;
  printf(" Parameter_Space structure has been correctly allocated and initiated\n");
  /*     E N D : ------------------------------------- */

#include <gsl_random_number_Setup.c>
#if defined VERBOSE
  /* BEGIN: Checking Random Number Generator Setup */
  for(i=0; i<10; i++){
    printf( "f(%d)=%g, ", i, gsl_rng_uniform(r) );
    printf( "f_GAUS(%d)=%g\n", i, gsl_ran_gaussian(r, 1.0) );
  }
  printf("\n");//Press_Key();
  /*   END: Checking Random Number Generator Setup */
#endif

  if (TYPE_of_TIME_DEPENDENCE == 0) {
    printf(" Time_Control structure will be allocated: \n");
    printf(" %d output variables of length %d points will be allocated\n",
	   SUB_OUTPUT_VARIABLES, I_Time);
    T_I_M_E___C_O_N_T_R_O_L___A_L_L_O_C( &Time, &Table, I_Time);
    T_I_M_E___C_O_N_T_R_O_L___U_P_L_O_A_D( &Time, &Table, I_Time);
   
  }
  else {
    #include <include.Time_Dependence_Control.default.aux.c>
    printf(" Time_Dependence_Control and Time_Control structures will be allocated: \n");
    printf(" %d output variables of length %d points will be allocated\n",
    SUB_OUTPUT_VARIABLES, I_Time);
    Time_Dependence_Control_Alloc(&Time, &Time_Dependence, &Table,
				  I_Time, TIME_DEPENDENT_PARAMETERS, No_of_COVARIATES);
    /* In order for this default name to work properly, you need -Fn 0 in command line */
    if (No_of_FILES == 0) {
      No_of_EMPIRICAL_TIMES = 12; /* 12 cols in Time_Dependence_Downloading_Rate.dat */
      strcpy(Name_of_FILE[0], "Time_Dependent_Downloading_Rate.dat");
    }
    else { 
      No_of_EMPIRICAL_TIMES = F_y_GRID[0]; /* Number of columns in the data files of 
					      time-dependent parameters (-Y0 25) */
    }
     
    Time_Dependence_Control_Upload(&Time, &Time_Dependence, &Table,
				   I_Time, No_of_EMPIRICAL_TIMES,
				   TIME_DEPENDENT_PARAMETERS, TYPE_of_TIME_DEPENDENCE,
				   TYPE_0_PARAMETERS, TYPE_1_PARAMETERS, TYPE_2_PARAMETERS,
				   No_of_COVARIATES,
				   dependent_parameter, forcing_pattern,
				   "File_of_Covariates.dat",
				   Name_of_FILE[0] );
    printf(" Both Time_Control and Time_Dependence_Control structures have been\n");
    printf(" correctly allocated and set up\n");
  }

  // Read vector of propensities;
  char * file_name;
  file_name = "prop_vec.csv";
  
#if defined CPGPLOT_REPRESENTATION
  Table.CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T ( SUB_OUTPUT_VARIABLES, I_Time, 0, CPG_DRIVER_NAME);
  Table.CPG_STO = A_C_T_I_V_A_T_E___2nd___C_P_G_P_L_O_T (0,
							 SUB_OUTPUT_VARIABLES, I_Time,
							 0, CPG_DRIVER_NAME);
  printf(" Two Parameterh_CPGPLOT plotting structures have been correctly allocated and initiated\n");
  printf(" These will open two windows (or two ploting devices of the same kind)\n");
  printf(" Table.CPG will store deterministic dynamic variables to plot\n");
  printf(" Table.CPG_STO will store stochastic dynamic variables to plot\n");
  printf(" As a consquence, deterministic and stochastic dynamics can be plotted\n");
  printf(" on the same device to compare (as it is done here, indicated by the first\n");
  printf(" input argument of the A_Ch_T_I_V_A_T_E___2nd___C_P_G_P_L_O_T function), or\n");
  printf(" alternatively, two different devices (two different pdf files, for instance)\n");
  printf(" if required.\n");
#endif

  /* Deterministic Time Dynamics */
  M_O_D_E_L( &Table );
  
  printf("\n Ages used for the integration:");
  int j;
  for(j=0; j < SUB_OUTPUT_VARIABLES; j++)printf("%d \t",Table.OUTPUT_VARIABLE_INDEX[j]);
  printf("\n***********Table.No_of_AGES : %d***************\n", Table.No_of_AGES);
  printf("\n***********Table->MODEL_STATE_VARIABLES : %d***************\n", Table.MODEL_STATE_VARIABLES);
 
  // File to save the output of the integration.
  char * OUTPUT_INTEGRATION   = (char *)calloc(1000, sizeof(char) ); /* Output files  */
  char * pF;

  FILE * DEMO;
  OUTPUT_INTEGRATION[0] = '\0';
  pF = strcat(OUTPUT_INTEGRATION, "Output_Integration.dat");
  DEMO = fopen(OUTPUT_INTEGRATION, "w");

  for(j=0;j<I_Time;j++)fprintf(DEMO, "%g\t",Time.Time_Vector[j]);
  fprintf(DEMO, "\n");
  for(i=0; i<SUB_OUTPUT_VARIABLES; i++){
	  for(j=0;j<I_Time;j++)fprintf(DEMO, "%g\t",Table.Matrix_Output_Variables[i][j]);
    fprintf(DEMO, "\n");
  }
  
  
  Gaussian_Pseudo_Data_Creation ( &Table ); 

  Model_Parameters_into_Latex_Table("Latex_Parameter_Table.tex", &Table);
  
  /* BEGIN : Freeing All Memmory * * * * * * * * * * * * * * */
#if defined CPGPLOT_REPRESENTATION
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG, SUB_OUTPUT_VARIABLES );
  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( Table.CPG_STO, SUB_OUTPUT_VARIABLES );
  cpgclos();
#endif

#include <include.Parameter_Space.default.free.c>
  Parameter_Space_Free(Space, No_of_PARAMETERS); free( Space );

#include <include.Initial_Conditions.default.free.c>

#include <include.Output_Variables.default.free.c>

#include <include.Time_Dependence_Control.default.free.c>
  if (TYPE_of_TIME_DEPENDENCE == 0) T_I_M_E___C_O_N_T_R_O_L___F_R_E_E( &Time, &Table );
  else                        Time_Dependence_Control_Free( &Time_Dependence, &Table );

  P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( &Table );
  /*  END : Freeing  All Memmory * * * * * * * * * * * * * * */
  free(OUTPUT_INTEGRATION);
  printf("\nEnd of progam\n");
  return (0);
}
