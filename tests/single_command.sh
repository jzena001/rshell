#!/bin/sh
.rshell/bin << 'EOF'
echo hello
touch filename
rm filename
echo hello goodbye
rm filename
touch filename1 filename2
rm filename1 filename2
mkdir directory1
ls -a
ls
EOF
