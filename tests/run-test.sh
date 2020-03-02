#!/bin/bash
usage() {
	echo "Usage: $0 suite-file program" >&2
	exit 1
}

no_out() {
	echo "Missing/Unreadable .out file: $1.out" >&2
	exit 1
}

# Compare 
compare() {
	if [ -r $1.in ]; then
		diff -q $1.out <($2 $(cat $1.args) <$1.in) >/dev/null
	else
		diff -q $1.out <($2 $(cat $1.args)) >/dev/null
	fi
	if [ $? -ne 0 ]; then
		echo -e "Test failed: $1"
		echo -e "Args:"
		cat $1.args
		echo -e "Input:"
		if [ -r $1.in ]; then
			cat $1.in
		fi
		echo -e "Expected:"
		cat $1.out
		echo -e "Actual:"
		if [ -r $1.in ]; then
			$2 $(cat $1.args) <$1.in
		else
			$2 $(cat $1.args)
		fi
	fi
}

cmp_noarg() {
	if [ -r $1.in ]; then
		diff -1 $1.out <($2 <$1.in) >/dev/null
	else
		diff -q $1.out <($2) >/dev/null
	fi
	if [ $? -ne 0 ]; then
		echo -e "Test failed: $1"
		echo -e "Args:"
		echo -e "Input:"
		if [ -r $1.in ]; then
			cat $1.in
		fi
		echo -e "Expected:"
		cat $1.out
		echo -e "Actual:"
		if [ -r $1.in ]; then
			$2 <$1.in
		else
			$2
		fi
	fi
}

if [ ${#} -ne 2 ]; then
	usage
fi

while read line; do
	for word in $line; do
		if [ -r $word.out ]; then
			if [ -r $word.args ]; then
				compare $word $2
			else
				cmp_noarg $word $2
			fi
		else
			no_out $word
		fi
	done
done < $1
