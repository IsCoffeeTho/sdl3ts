#ifndef SDL3TS_H
#define SDL3TS_H

#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <node/node_api.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>

void export_main(napi_env env, napi_value exports);
void export_point(napi_env env, napi_value exports);
void export_rect(napi_env env, napi_value exports);
void export_events(napi_env env, napi_value exports);
void export_window(napi_env env, napi_value exports);

#define export_function(env, exports, name, fn)                                                                        \
	{                                                                                                                  \
		napi_value val;                                                                                                \
		napi_create_function(env, NULL, 0, fn, NULL, &val);                                                            \
		napi_set_named_property(env, exports, name, val);                                                              \
	}

napi_status sdl3ts_pull_point(napi_env env, napi_value val, SDL_Point *point);
napi_status sdl3ts_pull_rect(napi_env env, napi_value val, SDL_FRect *rect);

void dbg_print_val(napi_env env, napi_value val, const char *name);

#endif