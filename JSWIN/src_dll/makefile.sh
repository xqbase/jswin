gcc -DNDEBUG -O4 -Wall -shared -olibcallproc.so -fPIC callproc.c
gcc -DNDEBUG -O4 -Wall -shared -olibcallwindowproc.so -fPIC callwindowproc.c
gcc -DNDEBUG -O4 -Wall -ldl -otest test.c callproc.c
