#include <stdio.h>
#include<emscripten.h>

EM_JS(void, jsFunc, (int n), {
  console.log("Value from jsFunc: " + n);
});

int main() {
  printf("WASM Ready!\n");

  // Call a JS function (eval)
  emscripten_run_script("console.log('Hello from C')");

  // Call a JS async function (eval)
  emscripten_async_run_script("console.log('Hello from C - async')", 2000);

  // Get a return value from JS function - INT
  int jsInt = emscripten_run_script_int("getNum()");

  // Get a return value from JS function - STR
  char* jsStr = emscripten_run_script_string("getStr()");

  printf("Value from getNum: %d\n", jsInt);
  printf("Value from getStr: %s\n", jsStr);

  jsFunc(321);

  return 1;
}

