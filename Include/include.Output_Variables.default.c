SUB_OUTPUT_VARIABLES = 60; // OUTPUT_VARIABLES_MAXIMUM;
// First Age group.
  variable_0 = 4;//2; Date:14-06-2014
  variable_1 = 5; //16; 
  variable_2 = 6; //4;
  variable_3 = 7; //5;
  variable_4 = 8; //6;
  variable_5 = 9; //8;

  variable_6  = 10;//2;
  variable_7  = 11; //16;
  variable_8  = 12; //4;
  variable_9  = 13; //5;
  variable_10 = 14; //6;
  variable_11 = 15; //8;

  variable_12 = 16;//2;

  variable_13 = 17; //16;
  variable_14 = 18; //4;
  variable_15 = 19; //5;
  variable_16 = 20; //6;
  variable_17 = 21; //8;

  variable_18 = 22;
  variable_19 = 23;
  variable_20 = 24;
  variable_21 = 25;
  variable_22 = 26;
  variable_23 = 27;
  variable_24 = 28;
  variable_25 = 29;
  variable_26 = 30;
  variable_27 = 31;
  variable_28 = 32;
  variable_29 = 33;
// Second Age group.
  variable_30 = 34; //Date: 14-07-2014
  
  variable_31 = 84;
  variable_32 = 134;
  variable_33 = 184;
  variable_34 = 234;
  variable_35 = 284;
  variable_36 = 334;
  variable_37 = 384;
  variable_38 = 434;
  variable_39 = 484;

  variable_40 = 534;
  variable_41 = 584;
  variable_42 = 634;
  variable_43 = 684;
  variable_44 = 734;
  variable_45 = 784;
  variable_46 = 834;
  variable_47 = 884;
  variable_48 = 934;
  variable_49 = 984;
// Third Age group.
  variable_50 = 1209; //Date: 01-10-2017

  variable_51 = 1319;
  variable_52 = 1429;
  variable_53 = 1539;
  variable_54 = 1649;
  variable_55 = 1759;
  variable_56 = 1869;
  variable_57 = 1979;
  variable_58 = 2089;
  variable_59 = 2199;

Index_Output_Variables = (int *)calloc(OUTPUT_VARIABLES_MAXIMUM, sizeof(int));

// We have reserved 60 int space because this is what it is
// used in include.Output_Variables.default.aux.c !!!

// Index_Output_Variables = (int *)calloc(60, sizeof(int));

#include <include.Output_Variables.default.aux.c>
