/* Human Parameters */

	      break;

            case 'g': 
              if(argv[argcount][2]=='0')        fprintf(fp, "-g0 %g  ",
						       Table->Gamma_0);                 /* 0 */

              else if(argv[argcount][2]=='1')   fprintf(fp, "-g1 %g  ",
						       Table->Gamma_1);                 /* 2 */

	      	  else if(argv[argcount][2]=='2')   fprintf(fp, "-g2 %g  ",
						       Table->Gamma_2);                 /* 4 */

	      	  else if(argv[argcount][2]=='3')   fprintf(fp, "-g3 %g  ",
						       Table->Gamma_3);                 /* 6 */

	      	  else if(argv[argcount][2]=='4')   fprintf(fp, "-g4 %g  ",
						       Table->Gamma_4);   /* 8 */

		  	  else if(argv[argcount][2]=='5')   fprintf(fp, "-g5 %g  ",
						       Table->Gamma_5);   /* 10 */

		  	  else if(argv[argcount][2]=='6')   fprintf(fp, "-g6 %g  ",
						       Table->Gamma_6); /* 12 */
							   
		  	  else if(argv[argcount][2]=='7')   fprintf(fp, "-g7 %g  ",
						       Table->Gamma_7);                 /* 14 */
							   

	      	  else {
		        printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
				exit(0);
	      		}
	         skip++;
	         break;


            case 'k': 
              if(argv[argcount][2]=='0')        fprintf(fp, "-k0 %d  ",
						       Table->k_0);                 /* 1 */

              else if(argv[argcount][2]=='1')   fprintf(fp, "-k1 %d  ",
						       Table->k_1);                /* 3*/

	      	  else if(argv[argcount][2]=='2')   fprintf(fp, "-k2 %d  ",
						       Table->k_2);                 /* 5*/

	      	  else if(argv[argcount][2]=='3')   fprintf(fp, "-k3 %d  ",
						       Table->k_3);                 /* 7 */

	      	  else if(argv[argcount][2]=='4')   fprintf(fp, "-k4 %d  ",
						       Table->k_4);                 /* 9 */

		  	  else if(argv[argcount][2]=='5')   fprintf(fp, "-k5 %d  ",
						       Table->k_5);                 /* 11 */

	      	  else if(argv[argcount][2]=='6')   fprintf(fp, "-k6 %d  ",
						       Table->k_6);                 /* 13 */

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

           case 'o': 
              if(argv[argcount][2]=='rho')        fprintf(fp, "-rho %g  ",
						       Table->rho);            /* 17 */
              
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

 
              #include <include.Type_of_Model.argumentControl_fprintf.c>




              
