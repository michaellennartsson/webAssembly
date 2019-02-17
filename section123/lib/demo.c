#include <stdio.h>
#include <string.h>

int main() {
  printf("WASM Ready!\n");
  return 1;
}

int getNum() {
  return 22;
}

int squareNum(int x) {
  return x * x;
}

char* greet(char* name) {
  char* greeting = "Hello From C ";
  strcat(greeting, name);
  return greeting;
}