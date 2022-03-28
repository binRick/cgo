reset
nodemon -I -V --delay .1 -e c,h,sh --signal SIGKILL -w foo.c -w foo.go -x sh -- -c "clear;./test.sh||true"
