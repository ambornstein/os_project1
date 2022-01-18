#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void main () {
 char buffer[5];
 int childnum;
 int file = open("seed.txt", O_RDONLY);
 read(file, buffer, 5);
 printf("%s", buffer);
 srand(atoi(buffer));
 for (int i = 0; i < 5; i++) {
  childnum = (rand() % (13 - 8 + 1) + 8);
  printf("%d\n", childnum);
 }
 exit(0);
}
