#include <MODEL.h>

extern double A_Rate; 

 void Evolution_Age_Distribution_Plot (Parameter_Table * Table, int j_Time)
 {
   static int DEVICE_NUMBER;
   static int No_of_CALLS = 0; 
   int i;
   int SAME_PLOT;
   static double Current_Time = 0.0; 
   double Last_Time;
   char * Plot_Time  = (char *)calloc( 50, sizeof(char));
   char * Time_Eraser = (char *)calloc(50, sizeof(char));
   
   assert(Table->No_of_AGES == Table->MODEL_STATE_VARIABLES);
   
   Table->CPG->CPG_RANGE_X_0 = 0;
   Table->CPG->CPG_RANGE_X_1 = (double)Table->No_of_AGES/4.0;
   Table->CPG->CPG_RANGE_Y_0 = 0;
   Table->CPG->CPG_RANGE_Y_1 = 0.03 * A_Rate/Table->Gamma_0;
   
   double * x_Data = (double *)calloc( Table->No_of_AGES, sizeof(double) );
   for(i=0; i<Table->No_of_AGES; i++) x_Data[i] = (double)i;

   Table->CPG->color_Index = 2;
   Table->CPG->type_of_Line = 1;
   Table->CPG->type_of_Width = 8;
   Table->CPG->type_of_Symbol = 1;

   if(No_of_CALLS == 0) {
      DEVICE_NUMBER = cpgopen( "/XSERVE" );
      cpgsubp(1, 1);
      cpgask( 0 );
   }
   
   assert( Table->T->Time_0 == 0.0 ); 
   Last_Time     = Current_Time;
   Current_Time  = Table->T->Time_Vector[j_Time];
   sprintf(Plot_Time, "Time = %5.2f", Current_Time);
   sprintf(Time_Eraser, "Time = %5.2f", Last_Time);
  
   cpgslct(DEVICE_NUMBER);      /* Selecting Device */
   SAME_PLOT = No_of_CALLS++; 
   // SAME_PLOT = 0; 
   CPGPLOT___X_Y___P_L_O_T_T_I_N_G___S_A_M_E___P_L_O_T ( Table->CPG,
   							   SAME_PLOT,
   							   Table->No_of_AGES,
   							   x_Data,
   							   Table->Vector_Model_Variables,
   							   "Participant Age",
   							   "Number of Participants",
   							   "",
   							   1, 1);
   
   /* CPGPLOT___X_Y___S_C_A_T_T_E_R_E_D___S_A_M_E___P_L_O_T ( Table->CPG, */
   /* 							   SAME_PLOT, */
   /* 							   Table->No_of_AGES,  */
   /* 							   x_Data,  */
   /* 							   Table->Vector_Model_Variables, */
   /* 							   "Participant Age",  */
   /* 							   "Number of Participants",  */
   /* 							   "",  */
   /* 							   1, 1); */

   float char_Size;
   float x_Time_Position = 0.90 * (float)Table->CPG->CPG_RANGE_X_1;
   float y_Time_Position = 0.90 * (float)Table->CPG->CPG_RANGE_Y_1;

   printf( "x_Position = %f\t y_Position = %f\n", x_Time_Position, y_Time_Position); 
   
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
