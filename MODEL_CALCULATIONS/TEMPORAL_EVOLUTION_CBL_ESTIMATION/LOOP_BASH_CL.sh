# A shell script to send multiple job to the queue.

export TERM=xterm

/home/usuaris/m.pardo/RANDOM_SEED_FILE -N $1
echo "A random_seed.dat file containing 30 random seeds has been saved for further use"

count=0
for (( replica=1; replica<=$1; replica++ )) 
do 
	read seed

	count=`expr $count + 1`             # Increment arithmetically the counter

	qsub -N MP.$Year -m bea -M mpardo@ceab.csic.es -v SEED=$seed,LABEL=$1 ${HOME}/my_PBS_FILE.sh

	echo "Job Number: "$count "has been queued!!!"


done < random_Seeds.dat 
