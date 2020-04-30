## QA
1. should we always print GET Req into standard error? Or just when failed to send data?
3. when output the header lines of response, should I output the original string? With the delimiter \r\n?
4. because this connection is one-time connection. when I extract the response body, why I have to figure out when I've finished receiving the entire body?
5. how to output the image data into standard output? what I've accomplished is that I can write them into local files and looks great. But ...

## test
./http_cli http://fac-staff.seattleu.edu

./http_cli http://fac-staff.seattleu.edu > err.txt

./http_cli http://fac-staff.seattleu.edu:80

./http_cli http://fac-staff.seattleu.edu/elarson/web/Linux/command-line.htm

./http_cli http://pages.cs.wisc.edu/~remzi/OSTEP/

./http_cli http://pages.cs.wisc.edu/~remzi/OSTEP/book-cover-two.jpg

./http_cli http://pages.cs.wisc.edu/~remzi/OSTEP/book-cover-two.jpg 2>err.txt 1>a.jpg

./http_cli http://fac-staff.seattleu.edu/elarson/web/Linux/command-line.htm 2>err.txt 1>body.html