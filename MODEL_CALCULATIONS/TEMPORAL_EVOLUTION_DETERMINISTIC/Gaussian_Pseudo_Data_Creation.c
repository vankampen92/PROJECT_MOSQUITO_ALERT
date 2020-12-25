#include <MODEL.h>

#define EPSILON 1.0E-06

extern gsl_rng * r;

#if defined CPGPLOT_REPRESENTATION
extern double CPG_RANGE_X_0;
extern double CPG_RANGE_X_1;
extern double CPG_RANGE_Y_0;
extern double CPG_RANGE_Y_1;
extern double A_Rate;       /* Participate in the defintion Y Axis Range */
#endif

int Gaussian_Pseudo_Data_Creation( Parameter_Table * Table )
{
  double x;
  int i,j, k, kk, n;

  /* Parameter_Model * P = (Parameter_Model *)malloc( 1 * sizeof(Parameter_Model) );    */
  /* P_A_R_A_M_E_T_E_R___I_N_I_T_I_A_L_I_Z_A_T_I_O_N (Table, P);                        */
  /* Table->P  = P;                                                                     */
  /* printf(" Parameter_Model structure has been correctly allocated and initiated\n"); */

  Time_Control * Time = Table->T;
  
  double Sigma_Heuristics;
  double Sigma_Factor     = 0.01;
  
  if(Time->TYPE_of_TIME_DEPENDENCE == 1) {
    assert( Table->TDC->TYPE_1_PARAMETERS == 1); 
    assert( Table->TDC->Index_Dependent_Parameters[0] == 16 ); 
    Sigma_Heuristics = Sigma_Factor *  Average_double_Vector(Table->TDC->Dependent_Parameter[0],
							     Table->TDC->No_of_EMPIRICAL_TIMES);
  }
  else { 
    Sigma_Heuristics = 10.0;
  }

  for(j=0; j < Time->I_Time; j++) { 
    for(k=0; k < Table->SUB_OUTPUT_VARIABLES; k++){
      
      Table->Matrix_Output_Variables[k][j] = Table->Matrix_Output_Variables[k][j] + Sigma_Heuristics * gsl_ran_gaussian(r, 1.0) ;
      
      if ( Table->Matrix_Output_Variables[k][j] < 0.0 ) Table->Matrix_Output_Variables[k][j] = 0.0; 
    }
  }
  /* B E G I N : Saving Pseudo-Data File: */
  char ** Name_of_Rows; 
  Writing_Standard_Data_Matrix_to_File("Pseudo_Data_File.dat",
				       Table->Matrix_Output_Variables,
				       Table->SUB_OUTPUT_VARIABLES, Time->I_Time, 
				       0, Name_of_Rows, // 0: not in use
				                         // 1: Names should be provided!!! 
				       1, Time->Time_Vector);
  /*     E N D : Saving Pseudo-Data File: */
#if defined CPGPLOT_REPRESENTATION
  /* Parameter Table dependent costumized plotting is defined
     in ~/CPGPLOT/CPGPLOT_Parameter_Table/CPGPLOT___X_Y___Parameter_Table.c 
  */
  int TIMES           = Table->T->I_Time;
  int Input_Parameter = 0; /* The value of this model parameter appears in the title */

  Table->CPG->CPG_SCALE_X = 1;
  Table->CPG->CPG_RANGE_X_0 = Table->T->Time_0;
  Table->CPG->CPG_RANGE_X_1 = Table->T->Time_1;
  Table->CPG->CPG_SCALE_Y = 1;
  Table->CPG->CPG_RANGE_Y_0 = 0.0;
  Table->CPG->CPG_RANGE_Y_1 = 0.03 * A_Rate/Table->Gamma_0;

  printf("X Axis Range: [%g, %g]\n", Table->CPG->CPG_RANGE_X_0, Table->CPG->CPG_RANGE_X_1);
  printf("Y Axis Range: [%g, %g]\n", Table->CPG->CPG_RANGE_Y_0, Table->CPG->CPG_RANGE_Y_1);

  /* Directly controlled through input arguments (see extern double CPG_RANGE_X_0; above!!) */
  /* Table->CPG->CPG_RANGE_X_0 = CPG_RANGE_X_0; */
  /* Table->CPG->CPG_RANGE_X_1 = CPG_RANGE_X_1; */
  /* Table->CPG->CPG_RANGE_Y_0 = CPG_RANGE_Y_0; */
  /* Table->CPG->CPG_RANGE_Y_1 = CPG_RANGE_Y_1; */
  
  Table->CPG->color_Index = 5;
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 8;
  Table->CPG->type_of_Symbol = 1; 
  
  C_P_G___S_U_B___P_L_O_T_T_I_N_G___C_U_S_T_O_M_I_Z_E_D___T_I_T_L_E ( Table,
   								      TIMES,
   								      Table->CPG->x_Time,
   								      Table->CPG->y_Time,
   								      Input_Parameter );
  Table->CPG->color_Index = 1;
  Table->CPG->type_of_Line = 1;
  Table->CPG->type_of_Width = 3;
  Table->CPG->type_of_Symbol = 2; 
  C_P_G___S_U_B___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T (1, Table, 
						       TIMES,
						       Time->Time_Vector,
						       Table->Matrix_Output_Variables ); 
#endif
  
  // free ( P );

  printf(" Gaussian Pseudo Data Generation successfully completed!!!\n");
  return(0);
}
