#ifndef SDL3TS_H
#define SDL3TS_H

#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <node/node_api.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>

napi_value export_main(napi_env env, napi_value exports);

#endif