#!/bin/sh
./bin/rshell << 'EOF'
(echo a)
(echo a && echo b)
(echo b || echo c)
(echo a && echo c) && echo d
(echo a || echo c) || echo e
(blarg || echo a) || echo f
(blarg && blarg) && echo a
(blarg && blarg) || (echo a || echo b)
((echo b || echo c) && (echo c || echo d)) && echo c


exit
EOF
