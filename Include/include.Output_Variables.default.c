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
  
  variable_31 = 44;
  variable_32 = 54;
  variable_33 = 64;
  variable_34 = 74;
  variable_35 = 84;
  variable_36 = 94;
  variable_37 = 104;
  variable_38 = 114;
  variable_39 = 124;

  variable_40 = 134;
  variable_41 = 144;
  variable_42 = 154;
  variable_43 = 164;
  variable_44 = 174;
  variable_45 = 184;
  variable_46 = 194;
  variable_47 = 204;
  variable_48 = 214;
  variable_49 = 224;
// Third Age group.
  variable_50 = 234; //Date: 01-10-2017

  variable_51 = 244;
  variable_52 = 254;
  variable_53 = 264;
  variable_54 = 274;
  variable_55 = 284;
  variable_56 = 294;
  variable_57 = 304;
  variable_58 = 314;
  variable_59 = 324;

Index_Output_Variables = (int *)calloc(OUTPUT_VARIABLES_MAXIMUM, sizeof(int));

// We have reserved 60 int space because this is what it is
// used in include.Output_Variables.default.aux.c !!!

// Index_Output_Variables = (int *)calloc(60, sizeof(int));

#include <include.Output_Variables.default.aux.c>
