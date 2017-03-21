#!/bin/sh
./bin/rshell << 'EOF'
echo hello > filename.txt
rm filename.txt
echo hello >> filename.
echo goodbye >> filename.txt
cat < filename.txt
rm filename.txt < filename.txt
rm filename.txt > filename.txt2
cat < filename.txt
echo hello >> filename.txt && echo goodbye 
rm filename.txt && echo hello >> filename.txt
echo hello again >> filename.txt && echo goodbye >> filename.txt
rm filename.txt
echo hello >> filename.txt && echo goodbye > filename.txt
echo hello > filename.txt && echo hello > filename2.txt
rm filename.txt filename.txt2; cat < filename.txt
echo hello > filename.txt; cat < filename.txt
echo hello > filename.txt; echo goodbye >> filename.txt; cat < filename.txt
touch filename2.txt > filename3.txt
echo hello | echo goodbye
echo hello | echo howdy | echo goodbye
echo hello > filename1.txt | echo goodbye > filename2.txt
cat < filename1.txt | cat < filename2.txt
cat < filename1.txt | filename2.txt
echo howdy | cat < filename1.txt
cat < filename1.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2


EOF