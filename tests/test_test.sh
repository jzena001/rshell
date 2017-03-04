#!/bin/sh
./bin/rshell << 'EOF'
test -e rshell
test -f rshell
test -d rshell
test -e filename
test rshell
[ -e rshell ]
test -e rshell && echo path exists
[ rshell ]
[ rshell ] && echo path exists
exit
EOF
