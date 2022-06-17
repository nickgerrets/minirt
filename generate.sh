#!/bin/bash

FILE=scenes/random.rt

echo 'C  -10,-10,-10       1,1,1 90'     > $FILE
echo 'A  0.2               255,255,255' >> $FILE
echo                                    >> $FILE
echo 'L  0,0,0         0.5 255,255,255' >> $FILE
echo 'L  100,0,0       0.5 255,255,255' >> $FILE
echo 'L  0,100,0       0.5 255,255,255' >> $FILE
echo 'L  100,100,0     0.5 255,255,255' >> $FILE
echo 'L  0,0,100       0.5 255,255,255' >> $FILE
echo 'L  100,0,100     0.5 255,255,255' >> $FILE
echo 'L  0,100,100     0.5 255,255,255' >> $FILE
echo 'L  100,100,100   0.5 255,255,255' >> $FILE
echo                                    >> $FILE
echo 'pl 110,110,110   1,1,1 63,63,63'  >> $FILE

function randomObject
{
	case $(($RANDOM % 3)) in
		0)
			echo -n 'sp ' >> $FILE
			randomPoint
			randomDiameter
			randomColor
			randomMaterial
			echo >> $FILE
			;;
		1)
			echo -n 'cy ' >> $FILE
			randomPoint
			randomPoint
			randomDiameter
			randomDiameter
			randomColor
			randomMaterial
			echo >> $FILE
			;;
		2)
			echo -n 'co ' >> $FILE
			randomPoint
			randomPoint
			randomDiameter
			randomDiameter
			randomColor
			randomMaterial
			echo >> $FILE
			;;
	esac
}

function randomMaterial
{
	case $(($RANDOM % 4)) in
		0)
			MAT=
			;;
		1)
			MAT="mirror"
			;;
		2)
			MAT="glass"
			;;
		3)
			MAT="water"
			;;
	esac
	echo -n $MAT >> $FILE
}

function randomDiameter
{
	echo -n "$(($RANDOM % 20)).$(($RANDOM % 100)) " >> $FILE
}

function randomColor
{
	echo -n "$(($RANDOM % 256)),$(($RANDOM % 256)),$(($RANDOM % 256)) " >> $FILE
}

function randomPercentage
{
	echo -n "0.$(($RANDOM % 100)) " >> $FILE
}

function randomDouble
{
	echo -n "$(($RANDOM % 100)).$(($RANDOM % 100))" >> $FILE
}

function randomPoint
{
	randomDouble
	echo -n "," >> $FILE
	randomDouble
	echo -n "," >> $FILE
	randomDouble
	echo -n " " >> $FILE
}

for i in {1..100} ; do
	randomObject
done