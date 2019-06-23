files="$(find test_tools/error/ -type f)"

for f in $files;
do
	echo "$f"
	valgrind --leak-check=full ./lem-in < "$f"
	sleep 2
done
