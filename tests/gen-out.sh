#!/bin/bash
usage() {
	echo "usage: $0 suite-file program" >&2
	exit 1
}
# Given a stem and a program, runs its respective test and stores output
runtest() {
	$2 $(cat $1.args) < $1.in > $1.out
}

if [ ${#} -ne 2 ]; then
	usage
fi
while read line; do
	for word in $line; do
		if [ -r $word.args ]; then
			if [ -r $word.in ]; then
				runtest $word $2
			else
				$2 $(cat $word.args) > $word.out
			fi
		elif [ -r $word.in ]; then
			$2 <$word.in > $word.out
		else
			$2 > $word.out
		fi
	done
done < $1
