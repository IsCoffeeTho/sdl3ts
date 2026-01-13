#ifndef SDL3TS_H
#define SDL3TS_H

#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <node/node_api.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>

napi_status napi_create_pointer(napi_env env, void *ptr, napi_value *result);
napi_status napi_get_value_pointer(napi_env env, napi_value value, void **result);

napi_status napi_create_rect(napi_env env, SDL_FRect *rect, napi_value *result);
napi_status napi_get_value_rect(napi_env env, napi_value value, SDL_FRect *result);

napi_status napi_create_point(napi_env env, SDL_Point *point, napi_value *result);
napi_status napi_get_value_point(napi_env env, napi_value value, SDL_Point *result);

#define export_fn(env, exports, name, fn)                                                                              \
	{                                                                                                                  \
		napi_value val;                                                                                                \
		napi_create_function(env, NULL, 0, fn, NULL, &val);                                                            \
		napi_set_named_property(env, exports, name, val);                                                              \
	}

napi_value export_plumbing(napi_env env, napi_value exports);
napi_value export_window(napi_env env, napi_value exports);
napi_value export_renderer(napi_env env, napi_value exports);
napi_value export_events(napi_env env, napi_value exports);

#endif