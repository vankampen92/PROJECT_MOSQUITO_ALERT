/* Human Parameters */

	    case 'z': 
              if(argv[argcount][2]=='0')        sscanf(argv[argcount+1],"%lf",
						       &Mu_0);                 /* 0 */

              else if(argv[argcount][2]=='1')   sscanf(argv[argcount+1],"%lf",
						       &Mu_1);                 /* 3 */

	      else if(argv[argcount][2]=='2')   sscanf(argv[argcount+1],"%lf",
						       &Mu_2);                 /* 6 */

	      else if(argv[argcount][2]=='3')   sscanf(argv[argcount+1],"%lf",
						       &Mu_3);                 /* 9 */

	      else if(argv[argcount][2]=='4')   sscanf(argv[argcount+1],"%lf",
						       &Mu_4);                 /* 12 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;


            case 'g': 
              if(argv[argcount][2]=='0')        sscanf(argv[argcount+1],"%lf",
						       &Gamma_0);                 /* 1 */

              else if(argv[argcount][2]=='1')   sscanf(argv[argcount+1],"%lf",
						       &Gamma_1);                 /* 4 */

	      else if(argv[argcount][2]=='2')   sscanf(argv[argcount+1],"%lf",
						       &Gamma_2);                 /* 7 */

	      else if(argv[argcount][2]=='3')   sscanf(argv[argcount+1],"%lf",
						       &Gamma_3);                 /* 10 */

	      else if(argv[argcount][2]=='4')   sscanf(argv[argcount+1],"%lf",
						       &Gamma_4);                 /* 13 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;


            case 'k': 
              if(argv[argcount][2]=='0')        sscanf(argv[argcount+1],"%d",
						       &k_0);                 /* 2 */

              else if(argv[argcount][2]=='1')   sscanf(argv[argcount+1],"%d",
						       &k_1);                 /* 5 */

	      else if(argv[argcount][2]=='2')   sscanf(argv[argcount+1],"%d",
						       &k_2);                 /* 8 */

	      else if(argv[argcount][2]=='3')   sscanf(argv[argcount+1],"%d",
						       &k_3);                 /* 11 */

	      else if(argv[argcount][2]=='4')   sscanf(argv[argcount+1],"%d",
						       &k_4);                 /* 14 */

	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;


            case 'K': 
              if(argv[argcount][2]=='K')        sscanf(argv[argcount+1],"%d",
						       &No_of_GROUPS);          /* 15 */
              
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;

           case 'r': 
              if(argv[argcount][2]=='A')        sscanf(argv[argcount+1],"%lf",
						       &A_Rate);          /* 16 */
              
	      else {
		printf(" Error at reading input arguments: -  %s  \n", argv[argcount]);
		exit(0);
	      }
	      skip++;
	      break;



              #include <include.Type_of_Model.argumentControl.c>
