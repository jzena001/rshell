#!/bin/sh
./bin/rshell << 'EOF'
echo howdy #this is a comment
; # this is a comment
#comment
exit
EOF
