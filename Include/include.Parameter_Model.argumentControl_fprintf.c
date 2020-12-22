/* Human Parameters */

	    case 'z': 
              if(argv[argcount][2]=='0')        fprintf(fp, "-u0 %g",
						       Table->Mu_0);                 /* 0 */

              else if(argv[argcount][2]=='1')   fprintf(fp, "-u1 %g",
						       Table->Mu_1);                 /* 3 */

	      else if(argv[argcount][2]=='2')   fprintf(fp, "-u2 %g",
						       Table->Mu_2);                 /* 6 */

	      else if(argv[argcount][2]=='3')   fprintf(fp, "-u3 %g",
						       Table->Mu_3);                 /* 9 */

	      else if(argv[argcount][2]=='4')   fprintf(fp, "-u4 %g",
						       Table->Mu_4);                 /* 12 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

            case 'g': 
              if(argv[argcount][2]=='0')        fprintf(fp, "-g0 %g  ",
						       Table->Gamma_0);                 /* 1 */

              else if(argv[argcount][2]=='1')   fprintf(fp, "-g1 %g  ",
						       Table->Gamma_1);                 /* 4 */

	      else if(argv[argcount][2]=='2')   fprintf(fp, "-g2 %g  ",
						       Table->Gamma_2);                 /* 7 */

	      else if(argv[argcount][2]=='3')   fprintf(fp, "-g3 %g  ",
						       Table->Gamma_3);                 /* 10 */

	      else if(argv[argcount][2]=='4')   fprintf(fp, "-g4 %g  ",
						       Table->Gamma_4);                 /* 13 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;


            case 'k': 
              if(argv[argcount][2]=='0')        fprintf(fp, "-k0 %d  ",
						       Table->k_0);                 /* 2 */

              else if(argv[argcount][2]=='1')   fprintf(fp, "-k1 %d  ",
						       Table->k_1);                 /* 5 */

	      else if(argv[argcount][2]=='2')   fprintf(fp, "-k2 %d  ",
						       Table->k_2);                 /* 8 */

	      else if(argv[argcount][2]=='3')   fprintf(fp, "-k3 %d  ",
						       Table->k_3);                 /* 11 */

	      else if(argv[argcount][2]=='4')   fprintf(fp, "-k4 %d  ",
						       Table->k_4);                 /* 14 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

           case 'K': 
              if(argv[argcount][2]=='K')        fprintf(fp, "-KK  %d  ",
						       Table->No_of_GROUPS);      /* 15 */
              
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

           case 'r': 
              if(argv[argcount][2]=='A')        fprintf(fp, "-rA %g  ",
						       Table->A_Rate);            /* 16 */
              
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

 
              #include <include.Type_of_Model.argumentControl_fprintf.c>




              
