#include <stdio.h>
#include <stdlib.h>

int main() {
FILE* in, *out;

char c;

in = fopen("file.in", "r");
out = fopen("file.out", "a+");

while((c = fgetc(in)) != EOF)
fputc(c, out);

exit(0);
}
