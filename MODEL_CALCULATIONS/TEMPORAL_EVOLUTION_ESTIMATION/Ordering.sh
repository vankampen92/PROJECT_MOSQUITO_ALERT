# Bash Ordering Script

# Stringency Criterion:

## Stringency = "$1"

for f in Full_Par*_Set.dat;
do
    head -n 1 $f > Title_Row.txt
#   sort -k 7 $f | awk 'NR==1 { temp=$7; ((temp+=Stringency)) } NR>=1 { if ($7 <= temp) { print } }' > ${f/%.dat/_Ord.dat}; 
    sort -n -r -k 7 $f | awk 'NR==1 { temp=$7; ((temp+=10)) } NR>=1 { if ($7 <= temp) { print } }' > ${f/%.dat/_Ord.dat}; 
done

for f in Full_Par*_Ord.dat;
do
    cat Title_Row.txt $f > ${f/%.dat/ered.dat}
done

rm *Ord.dat
