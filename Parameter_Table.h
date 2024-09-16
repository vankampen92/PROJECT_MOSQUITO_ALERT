void P_A_R_A_M_E_T_E_R___T_A_B_L_E___A_L_L_O_C( Parameter_Table * );

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___U_P_L_O_A_D( Parameter_Table *, int * );

void P_A_R_A_M_E_T_E_R___T_A_B_L_E___F_R_E_E( Parameter_Table * );

void Parameter_Table_Index_Update(int * , int , Parameter_Table * );

void Parameter_Values_into_Parameter_Table(Parameter_Table * ); 

void Resetting_Mu_Gamma_K_Vectors (Parameter_Table * ); 

void rand_index_OutputVar(int * , int );

void Uploading_Demographic_Parameters_into_Parameter_Table(Parameter_Table * Table, double ** Data,
							   int k, int * Index,
							   int No_of_PARAMETERS );

void Uploading_Model_Parameters_into_Parameter_Table(Parameter_Table * Table, double ** Data,
						     int k);

void upload_extra_vec_to_ParameterTable(char * File_Name,
                              double * vec,
                              int No_of_Row,
                              Parameter_Table * Table);