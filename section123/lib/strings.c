#include <stdio.h>
#include<emscripten.h>

char * str = "My fantastic String";

char * getStr() {
  return str;
}

int getNumber() {
  int num = 123;

  // Starts debugger in browser
  if(1 == 2) emscripten_debugger();

  if(num < 500) emscripten_log(EM_LOG_WARN, "'num' less then 500!");
  
  return num;
}

int main() {
  printf("WASM Ready!\n");

  

  return 1;
}

