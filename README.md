Run file C:\Users\milen1\Visual_Studio_Code_Pjojects\emsdk\emsdk_env.bat fefore start working

https://emscripten.org/

Build commands:
emcc lib/demo.c -s WASM=1 -o public/demo.js
emcc lib/demo.c -s WASM=1 -o public/demo.html
emcc lib/demo.c -s WASM=1 -O2 -o public/demo.js
emcc lib/demo.c -s WASM=1 -O2 -o public/demo.js --closure
emcc lib/demo.c -s WASM=1 -O2 --post-js public/ready.js -o public/demo.js
emcc lib/demo.c -s WASM=1 -O2 --pre-js public/ready.js -o public/demo.js
emcc lib/demo.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_getNum','_main']" -o public/demo.js

Wrap functions from C in JS:
const greet = cwrap('greet', 'string', ['string']);