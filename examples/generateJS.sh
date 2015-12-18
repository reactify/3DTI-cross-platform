#!/bin/sh

~/emsdk/emscripten/1.35.0/emcc ./example-js/StereoSpreadWrapper.cpp -o ./example-js/StereoSpreadLib.js -s EXPORTED_FUNCTIONS="['_stereospread_new', '_stereospread_set_width', '_stereospread_process_inline', '_stereospread_free']"
