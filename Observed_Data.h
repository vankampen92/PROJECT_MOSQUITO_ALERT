void Observed_Data_Alloc( Observed_Data * Data, int N, int No_of_TIMES);

void Observed_Data_Initialization( Observed_Data * Data, int N, int No_of_TIMES,
				   double ** Data_Matrix, const char * Name );

void Observed_Data_Free( Observed_Data * Data);
void Observed_Data_Initialization_Fil( Observed_Data * Data, int No_of_OBSERVED_VARIABLES,
                                   int No_of_TIMES, double ** Data_Matrix, int * Index_Output_Var,
                                   const char * Name );