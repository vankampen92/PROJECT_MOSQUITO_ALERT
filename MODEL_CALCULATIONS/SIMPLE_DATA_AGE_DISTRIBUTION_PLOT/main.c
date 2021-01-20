/* This main function plots two scatter plots and their 
   corresponding smoothing lines on a single plot.
  
   Data are given as 1 input file (the empirical age distribution through time).    

   Compilation:
   ~$: make 
     
   Execution (if data files are read from directory, which is NOT the case in thi main code below unless you modify the program accordingly):

   ~$ ./PLOT -Fn 1 -F0 mat_ages_1.data -Y0 2378 -G0 1 -G1 1 -G2 1 -G3 0.0 -G4 2378.0 -G5 1 -G6 0.0 -G7 100.0

   It is very important to establish the axis ranks through the corresponding command line arguments as in the example. Your ranks will be active as long as you also introduce -G2 1 (x axis) and G5 1 (y axis) --- as oposed to -G2 0 and -G5 0, which will shut down your axis rank choice. In the latter case, the program calculates rank axis automatically.
 
*/

#include "main.h"

#include "global.h"

#define No_of_POINTS_MAX 10000

void Evolution_Age_Distribution_Plot_Simple (Parameter_CPGPLOT * ,
					     double * , int , 
					     double * , int ); 

int main (int argc, char **argv)
{
  int i, j, n;
  double y; 
  Parameter_CPGPLOT * CPG; 
  char ** Name_of_Rows;

#include "default.c"

 /* Command line arguments */
  if(argc>1) ArgumentControl(argc,argv);

  int No_of_COLUMNS = F_y_GRID[0]; 
  int No_of_ROWS;
  
  CPG = A_C_T_I_V_A_T_E___C_P_G_P_L_O_T (1, No_of_COLUMNS, 0,
					 CPG_DRIVER_NAME ); 
  printf(" Parameter_CPGPLOT data structure has been allocated and initiated\n");
   
  double ** Matrix_Data    = (double **)calloc( No_of_POINTS_MAX, sizeof(double *) );
  double ** Empirical_Data = (double **)calloc( No_of_POINTS_MAX, sizeof(double *) );
  double * Time           = (double  *)calloc( No_of_POINTS_MAX, sizeof(double  ) );
  double * Time_Vector    = (double  *)calloc( No_of_POINTS_MAX, sizeof(double  ) );
  double * Empirical_Age_Distribution = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
  for(i=0; i<No_of_POINTS_MAX; i++) { 
    Matrix_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
    Empirical_Data[i] = (double *)calloc( No_of_POINTS_MAX, sizeof(double) );
  }
  
  FILE * fp;
  printf("\n [Entering function Reading_Matrix_from_File(...)]:\t\n\tReading File %s...\n", 
	 Name_of_FILE[0]);
  if((fp=fopen(Name_of_FILE[0],"r")) == NULL) {
    printf("File non-existent! Cannot open file.\n");
    printf("Program aborted!!!"); exit(1);
  }

  for(j=0; j < No_of_COLUMNS; j++) {
    if( j == (No_of_COLUMNS - 1) ) fscanf(fp, "%lf\n", &y);
    else                           fscanf(fp, "%lf ", &y);
    Time[j] = y;
  }
  n=0; 
  while ( fscanf(fp, "%lf ", &y) != EOF ){
      
    Matrix_Data[n][0] = y;
      
    for(j=1; j < No_of_COLUMNS; j++) {
      if( j == (No_of_COLUMNS - 1) ) fscanf(fp, "%lf\n", &y);
      else                           fscanf(fp, "%lf " , &y);
      Matrix_Data[n][j] = y;
    }
    
    n++;
  }
  fclose(fp);
  No_of_ROWS = n;
  
  /* Reading_Standard_Data_Matrix_from_File( Name_of_FILE[0],         */
  /* 					  Matrix_Data,                */
  /* 					  &No_of_ROWS, No_of_COLUMNS, */
  /* 					  0, Name_of_Rows,            */
  /* 					  1, Time );                  */
  
  int No_of_AGES  = No_of_ROWS;
  int No_of_TIMES = No_of_COLUMNS;
  
  CPG->Title[0] = '\0'; // Effectively deleting previsously defined title
  char * p = strcat(CPG->Title, "Empirical Age Distribution over Time");

  /* char * Num = (char *)calloc( 10, sizeof(char) ); */
  /* sprintf(Num, "%7d", 5195769);                    */
  /* p = strcat(CPG->Title, Num);                     */
  /* free(Num);                                       */
 
  for( i=0; i<No_of_TIMES; i++)  Time_Vector[i] = Time[i];
  for( n=0; n<No_of_AGES;  n++)  Empirical_Data[n][0] = 0.0;
  
  for( i=1; i<No_of_TIMES; i++)
    for( n=0; n<No_of_AGES;  n++)
      Empirical_Data[n][i] = Matrix_Data[n][i-1]; 

  for( i=0; i<No_of_TIMES; i++) { 
    /* Just checking data are correctly read... */
    printf("Age distribution at time t = %g\n", Time_Vector[i]);
    for(n=0; n<No_of_AGES; n++) { 
      printf( "[n_%d = %4.3g]\t", n, Empirical_Data[n][i]);
      Empirical_Age_Distribution[n] = Empirical_Data[n][i];
    }
    printf("\n");

    printf("Please, press any key...\n"); 
    // getchar();
    
    Evolution_Age_Distribution_Plot_Simple ( CPG,
					     Time_Vector, i, 
					     Empirical_Age_Distribution, No_of_AGES );
  }

  /* Writing_Standard_Data_Matrix_to_File("Time_Evo_Empirical_Age_Dist.data",    */
  /* 				       Empirical_Data,                           */
  /* 				       No_of_ROWS, No_of_TIMES,                  */
  /* 				       0, Name_of_Rows,                          */
  /* 				       1, Time_Vector);                          */
  
  for(i=0; i<No_of_POINTS_MAX; i++) { 
    free(Matrix_Data[i]);
    free(Empirical_Data[i]); 
  }
  free(Matrix_Data);    
  free(Empirical_Data); 
  free(Time);
  free(Time_Vector);
  free(Empirical_Age_Distribution);

  P_A_R_A_M_E_T_E_R___C_P_G_P_L_O_T___F_R_E_E( CPG, 1 );
  cpgclos();
  
  printf("\nEnd of progam\n");
  return(0);
}

void Evolution_Age_Distribution_Plot_Simple (Parameter_CPGPLOT * CPG,
					     double * Time_Vector,
					     int j_Time, 
					     double * Empirical_Age_Distribution,
					     int No_of_AGES )
{
   int i;
   int SAME_PLOT;
   static double Current_Time = 0.0; 
   double Last_Time;
   char * Plot_Time  = (char *)calloc( 50, sizeof(char));
   char * Time_Eraser = (char *)calloc(50, sizeof(char));
   
   /* CPG->CPG_RANGE_X_0 = 0; */
   /* CPG->CPG_RANGE_X_1 = (double)No_of_AGES; */
   /* CPG->CPG_RANGE_Y_0 = 0; */
   /* CPG->CPG_RANGE_Y_1 = CPG_RANGE_Y_1;  */

   CPG->CPG_RANGE_X_0 = CPG_RANGE_X_0;
   CPG->CPG_RANGE_X_1 = CPG_RANGE_X_1;
   CPG->CPG_RANGE_Y_0 = CPG_RANGE_Y_0;
   CPG->CPG_RANGE_Y_1 = CPG_RANGE_Y_1;

   
   double * x_Data = (double *)calloc( No_of_AGES, sizeof(double) );
   for(i=0; i<No_of_AGES; i++) x_Data[i] = (double)i;

   CPG->color_Index = 2;
   CPG->type_of_Line = 1;
   CPG->type_of_Width = 8;
   CPG->type_of_Symbol = 1;

   Last_Time     = Current_Time;
   Current_Time  = Time_Vector[j_Time];
   sprintf(Plot_Time, "Time = %5.2f", Current_Time);
   sprintf(Time_Eraser, "Time = %5.2f", Last_Time);
  
   cpgslct(CPG->DEVICE_NUMBER);      /* Selecting Device */
   SAME_PLOT = 0; 
   
   CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( CPG,
							 SAME_PLOT,
							 No_of_AGES,
							 x_Data,
							 Empirical_Age_Distribution, 
							 "Participant Age",
							 "Number of Participants",
							 CPG->Title,
							 1, 1);

   float char_Size;
   float x_Time_Position = 0.90 * (float)CPG->CPG_RANGE_X_1;
   float y_Time_Position = 1.10 * (float)CPG->CPG_RANGE_Y_1;
   
   cpgqch(&char_Size);
   cpgsch(2.0);
   cpgsci(0);
   cpgptxt(x_Time_Position, y_Time_Position, 0.0, 1.0, Time_Eraser);
   cpgsci(1);
   cpgptxt(x_Time_Position, y_Time_Position, 0.0, 1.0, Plot_Time);
   cpgsch(char_Size);
   
   free(x_Data);
   free(Plot_Time); free(Time_Eraser);
 }
