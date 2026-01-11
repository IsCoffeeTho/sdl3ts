#include "../sdl3ts.h"
#include <SDL3/SDL_error.h>
#include <node/js_native_api.h>

napi_value SDL_Init_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	uint32_t flags;
	napi_get_value_uint32(env, argv[0], &flags);

	napi_get_boolean(env, SDL_Init(flags), &retval);

	return retval;
}

napi_value SDL_Quit_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	SDL_Quit();
	return retval;
}

napi_value SDL_GetError_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;

	napi_value code;
	napi_create_string_utf8(env, "SDL3tsError", 11, &code);

	const char *msg_string = SDL_GetError();
	napi_value msg;
	napi_create_string_utf8(env, msg_string, strlen(msg_string), &msg);

	napi_create_error(env, code, msg, &retval);

	return retval;
}

napi_value export_plumbing(napi_env env, napi_value exports)
{
	export_fn(env, exports, "SDL_Init", SDL_Init_wrapper);
	export_fn(env, exports, "SDL_Quit", SDL_Quit_wrapper);
	export_fn(env, exports, "SDL_GetError", SDL_GetError_wrapper);
	return exports;
}