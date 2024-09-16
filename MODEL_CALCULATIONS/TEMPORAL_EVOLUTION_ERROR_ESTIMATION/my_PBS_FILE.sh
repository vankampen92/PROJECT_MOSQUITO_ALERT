#!/bin/sh

export TERM=xterm



GSL_RND_SEED=${SEED} /home/usuaris/m.pardo/PROJECT_MOSQUITO_ALERT/MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_CBL_ESTIMATION/MADMODELNW -y0 0 -n 90 -sT 1.0E-04 -sN 300 -sP 3 -KK 3 -k0 30 -k1 1700 -k2 648 -I0 0 -m0 0.0 -M0 1.0 -A0 0.1 -I1 2 -m1 0.0 -M1 1.0 -A1 0.01 -I2 4 -m2 0.0 -M2 1.0 -A2 0.5 -iP 0 -en 0 -eV 100.0 -tn 2301 -t0 0.0 -t1 2300 -t4 1 -tE 2.0 -tR 300 -xn 0 -xN 0.0 -xR 0 -DP 1 -DC 0 -D0 0 -D1 1 -D2 0 -P0 16 -a0 0 -Fn 2 -F0 /home/usuaris/m.pardo/PROJECT_MOSQUITO_ALERT/MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_CBL_ESTIMATION/Observed_data_2300.data -Y0 2301 -F1 /home/usuaris/m.pardo/PROJECT_MOSQUITO_ALERT/MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_CBL_ESTIMATION/Downloads_full_2300.data -Y1 2301


cp Full_Parameter_Set.dat /home/usuaris/m.pardo/RESULTS_ESTIMATION/Full_Parameter_Set_${GROUP}_${CLASS}.dat

