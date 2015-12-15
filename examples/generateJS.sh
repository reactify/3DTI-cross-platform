#!/bin/sh

python ~/emsdk/emscripten/1.35.0/tools/webidl_binder.py ./example-js/StereoSpread.idl ./example-js/glue

~/emsdk/emscripten/1.35.0//emcc ../StereoSpread.cpp ./example-js/include.cpp --post-js ./example-js/glue.js -o ./example-js/StereoSpread.js


#~/emsdk/emscripten/1.35.0/emcc --bind ../StereoSpread.cpp -o ./example-js/StereoSpread.js #-s EXPORTED_FUNCTIONS="['_setWidth']"
