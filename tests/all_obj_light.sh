if [ -e ../a.out ]
then
	EXE="$PWD"/../a.out
	echo $EXE
elif [ -e ../rt ]
then
	EXE="$PWD"/../rt
	echo $EXE
else
	echo Pas d\'exécutable.
	exit
fi
for map in obj_light/*$1*.xml
do
	echo "$PWD/$map"
	"$EXE" "$PWD/$map"
done
