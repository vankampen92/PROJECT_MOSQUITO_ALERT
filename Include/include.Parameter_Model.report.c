/* Initial Conditions parameters */

fprintf(fp, "\n");
fprintf(fp, " M O D E L   ( C O R E )   P A R A M E T E R S :\n");
fprintf(fp, " App Downloading Rate                   ...> -rA [value], i.e.,  -rA %g\n", A_Rate); 
fprintf(fp, " Number of Groups (of ages)             ...> -KK [value], i.e.,  -KK %d\n", No_of_GROUPS);
fprintf(fp, " Transition rate between classes        ...> -z[n] [value], i.e.,  -z0 %g\n", Mu_0);  
fprintf(fp, " Constannt loss rate (for each n group) ...> -g[n] [value], i.e.,  -g0 %g\n", Gamma_0);
fprintf(fp, " Nunber of age classes in each group    ...> -k[n] [value], i.e.,  -k0 %d\n", k_0);
fprintf(fp, " ( [n] is the label of the group sharing Mu and Gamma parameters )\n");


