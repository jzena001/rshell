#!/bin/sh
./bin/rshell << 'EOF'
echo hello; echo goodbye
touch filename1; touch filename2
rm filename1; rm filename2;
echo hello; ls -a;
rm filename; touch filename;
rm filename|| touch filename;
rm filename&& echo howdy
rm filename&& echo howdy
touch filename|| touch filename2
rm filename&& rm filename2&& echo howdy
echo howdy&& rm filename&& echo potato
rm filename|| echo howdy&& touch potato
rm potato; echo howdy|| echo umbrella
exit
EOF
