SUB_OUTPUT_VARIABLES = 60; // OUTPUT_VARIABLES_MAXIMUM;
// First Age group.
  variable_0 = 0;//2; Date:14-06-2014
  variable_1 = 1; //16; 
  variable_2 = 2; //4;
  variable_3 = 3; //5;
  variable_4 = 4; //6;
  variable_5 = 5; //8;

  variable_6  = 6;//2;
  variable_7  = 7; //16;
  variable_8  = 8; //4;
  variable_9  = 9; //5;
  variable_10 = 10; //6;
  variable_11 = 11; //8;

  variable_12 = 12;//2;

  variable_13 = 13; //16;
  variable_14 = 14; //4;
  variable_15 = 15; //5;
  variable_16 = 16; //6;
  variable_17 = 17; //8;

  variable_18 = 18;
  variable_19 = 19;
  variable_20 = 20;
  variable_21 = 21;
  variable_22 = 22;
  variable_23 = 23;
  variable_24 = 24;
  variable_25 = 25;
  variable_26 = 26;
  variable_27 = 27;
  variable_28 = 28;
  variable_29 = 29;
// Second Age group.
  variable_30 = 30; //Date: 14-07-2014
  
  variable_31 = 80;
  variable_32 = 130;
  variable_33 = 180;
  variable_34 = 230;
  variable_35 = 280;
  variable_36 = 330;
  variable_37 = 380;
  variable_38 = 430;
  variable_39 = 480;

  variable_40 = 530;
  variable_41 = 580;
  variable_42 = 630;
  variable_43 = 680;
  variable_44 = 730;
  variable_45 = 780;
  variable_46 = 830;
  variable_47 = 880;
  variable_48 = 930;
  variable_49 = 980;
// Third Age group.
  variable_50 = 1205; //Date: 01-10-2017

  variable_51 = 1315;
  variable_52 = 1425;
  variable_53 = 1535;
  variable_54 = 1645;
  variable_55 = 1755;
  variable_56 = 1865;
  variable_57 = 1975;
  variable_58 = 2085;
  variable_59 = 2195;

Index_Output_Variables = (int *)calloc(OUTPUT_VARIABLES_MAXIMUM, sizeof(int));

// We have reserved 60 int space because this is what it is
// used in include.Output_Variables.default.aux.c !!!

// Index_Output_Variables = (int *)calloc(60, sizeof(int));

#include <include.Output_Variables.default.aux.c>
