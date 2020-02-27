deg="debug"
rel="release"

if [ $# -ne 1 ]
then
	echo "bad arguments"
else
	if [ $1 = $rel ]
	then
		gcc -o prog/mystery-code prog/mystery-code.c
		prog/mystery-code
	elif [ $1 = $deg ]
	then
		gcc -g -o prog/mystery-code prog/mystery-code.c
		gdb ./prog/mystery-code
	fi
fi