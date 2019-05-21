touch ope.naz;
touch unixcase.naz;
touch files.naz;

# Add void to prototypes
# Check if include are at the top
# All rules present in the Makefile

if [ "$1" == "-f" ] ; then
	find $2 -name "*[A-Z]*" >> files.naz
	cat files.naz
else
	while [ "$1" != "" ] ; do
		grep $1 /dev/null -ne "[^*/]\*$" >> ope.naz
		grep $1 /dev/null -ne "+$" >> ope.naz
		grep $1 /dev/null -ne "[^-]-$" >> ope.naz
		grep $1 /dev/null -ne "=$" >> ope.naz
		grep $1 /dev/null -ne "?$" >> ope.naz
		grep $1 /dev/null -ne "<$" >> ope.naz
		grep $1 /dev/null -ne "[^h]>$" >> ope.naz
		grep $1 /dev/null -ne "&$" >> ope.naz
		grep $1 /dev/null -ne "|$" >> ope.naz
		grep $1 /dev/null -ne "[^*]/$" >> ope.naz
		grep $1 /dev/null -ne "^\(\t\| \)*[a-z\|_]\+\(\t\| \)\+\([a-z]*_*[a-z]*[A-Z]\+[a-z]*_*\)\+\([a-z]*_*\)*;$" >> unixcase.naz
		grep $1 /dev/null -ne "^\(\t\| \)*[a-z\|_]\+\(\t\| \)\+\([a-z]*_*[a-z]*[A-Z]\+[a-z]*_*\)\+\([a-z]*_*\)*(" >> unixcase.naz
		shift
	done ;
	if [ -s ope.naz ]
	then
		echo "\x1B[1m\x1B[33mEndline operators:\x1B[0m"
		cat ope.naz;
	else
		echo "\x1B[32m\x1B[1mNo endline operators\x1B[0m"
	fi
	if [ -s unixcase.naz ]
	then
		echo "\x1B[1m\x1B[33mNon-unix_case function names and variables:\x1B[0m"
		cat unixcase.naz;
	else
		echo "\x1B[1m\x1B[32mEvery variables and function names are unix_case\x1B[0m"
	fi
fi
rm files.naz;
rm ope.naz;
rm unixcase.naz;
