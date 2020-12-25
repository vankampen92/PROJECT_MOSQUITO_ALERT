#include <MODEL.h>

void Parameter_Space_Boundary_for_Trends(int j, double *value_0, double *value_1)
{
  switch(j)
  {
    case 0: 
    (*value_0) = 0.0;        (*value_1) = 600.0;
    break;
    case 1: 
    (*value_0) = 0.0;        (*value_1) = 1.0;
    break;
    case 2: 
    (*value_0) = 0.0;        (*value_1) = 50000.0;
    break;
    case 3: 
    (*value_0) = (1.0/70.0); (*value_1) = (1.0/20.0);
    break;
    case 4: 
    (*value_0) = (1.0/70.0); (*value_1) = (1.0/20.0);
    break;
    case 5: 
    (*value_0) = (6.0);      (*value_1) = (24.0);
    break;
    case 6: 
    (*value_0) = (1.0/20.0); (*value_1) = (1.0/5.0);
    break;
    case 7: 
    (*value_0) =  0.0;       (*value_1) =  99.0;
    break;
    case 8: 
    (*value_0) =  0.0;       (*value_1) =  600.0;
    break;
    case 9: 
    (*value_0) = 0.0;        (*value_1) = 1.0;
    break;
    case 10: 
    (*value_0) = (0.0);      (*value_1) = (1.0/2.0);
    break;
    case 11: 
    (*value_0) = (0.0);      (*value_1) = (1.0/2.0);
    break;
    case 12: 
    (*value_0) = (0.0);      (*value_1) = (9.0);
    break;
    case 13: 
    (*value_0) =   0.0;      (*value_1) = 50000.0;
    break;
    case 14: 
    (*value_0) = ( 1.0);     (*value_1) = (10.0);
    break;
    case 15: 
    (*value_0) = (0.0);      (*value_1) = (9.0);
    break;
    case 16: 
    (*value_0) = (0.0);      (*value_1) = (0.5);
    break;
    
    default:
    printf("...(in Parameter_Space_Boundary_for_Trends.c) INVALID PARAMETER KEY (key = %d)\n", j);
    printf("...(in Parameter_Space_Boundary_for_Trends.c) VALID PARAMETER KEYS (from 0 to 20)\n");
    exit(0);
  }
}
