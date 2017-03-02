#!/bin/sh
./bin/rshell << 'EOF'
exit
echo howdy; exit
echo howdy && exit;
echo alrighty || exit;
exit;
EOF
