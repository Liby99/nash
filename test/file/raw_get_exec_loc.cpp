#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("%s\n", argv[0]);
  char buffer[100];
  getcwd(buffer, 100);
  printf("%s\n", buffer);
}
