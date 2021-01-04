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
   .~$ ./MADMODEL -y0 0  -n 1 -v0 2 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 30.0 -t4 0 -tR 1 -xn 0 -xN 0.0-KK 3 -z0 0.5 -g0 0.01 -k0 100 -z1 0.1 -g1 0.01 -k1 100 -z2 0.25 -g2 0.01 -k2 100 -rA 100.0

   .~$ ./MADMODEL -y0 0  -n 1 -v0 1 -G0 1 -G1 1 -tn 20 -t0 0.0 -t1 5.0 -t4 0 -tR 1 -xn 0 -xN 0.0  -KK 3 -z0 0.5 -g0 0.01 -k0 100 -z1 0.1 -g1 0.001 -k1 100 -z2 0.25 -g2 0.01 -k2 100 -rA 100.0

   4 groups example:  
   .~$ ./MADMODEL -y0 0 -n 1 -v0 0 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 30.0 -t4 0 -tR 1 -xn 0 -xN 0.0 -KK 3 -z0 0.5 -g0 0.01 -k0 100 -z1 0.1 -g1 0.01 -k1 100 -z2 0.25 -g2 0.01 -k2 100 -z3 0.5 -g3 0.01 -k3 100 -rA 100.0

   (See denition_OutPut_Variables.c to understand the difference between Genuine Output Variable and plain model variables):
   
   Execution (with time-dependence -t4 1):

   .~$ ./MADMODEL -y0 0 -n 1 -v0 4 -G0 1 -G1 1 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tR 1 -xn 0 -xN 0.0  -KK 1 -z0 0.5 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0

   (with generation of 4 output variables: A, P[0], P[1], P[2] )
   .~$ ./MADMODEL -y0 0 -n 4 -v0 3 -v1 4 -v2 5 -v3 6 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tR 1 -xn 0 -xN 0.0  -KK 1 -z0 0.5 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0 

   (with generation of 4 output variables: P[0], P[1], P[2], P[3] that will become psedodata with
   additional Gaussian noise in Psedo_Data_File)
   .~$ ./MADMODEL -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 10.0 -t4 1 -tR 1 -xn 0 -xN 0.0  -KK 1 -z0 0.5 -g0 0.01 -k0 100 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 0 

   (with generation of 4 output variables: P[0], P[1], P[2], P[3] that will become psedodata with
   additional Gaussian noise in Psedo_Data_File, but now 3 different age groups and 150 ages classe)
   .~$ ./MADMODEL -y0 0 -n 4 -v0 4 -v1 5 -v2 6 -v3 7 -G0 2 -G1 2 -tn 100 -t0 0.0 -t1 24.0 -t4 1 -tR 1 -xn 0 -xN 0.0 -xR 0 -KK 3 -z0 5.0 -g0 0.1 -k0 50 -z1 5.0 -g1 0.01 -k1 50 -z2 5.0 -g2 0.05 -k2 50 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 1 -F0 Time_Dependent_Downloading_Rate_25P.dat -Y0 25

   (with the real downloading data file and generation of 6 output variables: A(t), P[0], P[2], P[3], P[100], and P[101] 
   that may become psedodata with additional Gaussian noise in Psedo_Data_File.dat, but now 3 different age groups  
   and 2001 (20 + 1500 + 480) ages classes in total)
   .~$ ./MADMODEL -y0 0 -n 6 -v0 3 -v1 4 -v2 5 -v3 6 -v4 104 -v5 105 -G0 3 -G1 2 -tn 2354 -t0 0.0 -t1 2385.0 -t4 1 -tR 1 -xn 0 -xN 0.0 -xR 0 -KK 3 -z0 5.0 -g0 0.1 -k0 20 -z1 5.0 -g1 0.01 -k1 1500 -z2 5.0 -g2 0.05 -k2 480 -rA 100.0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 1 -F0 Downloads_Transposed.data -Y0 2354
*/

int main(int argc, char **argv)
{
  int i;
  Parameter_Table Table;
  Time_Control Time;
  Time_Dependence_Control Time_Dependence;
  int No_of_EMPIRICAL_TIMES;
  
  P_ARG = &Table;

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
    printf(" Time_Control structure has been correctly allocated and set up\n");
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

  printf("\nEnd of progam\n");
  return (0);
}
