buffer=0

for i in `seq 1 $1`
do
	buffer=$((buffer + i))
done

echo $buffer