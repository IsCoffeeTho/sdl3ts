#include "../sdl3ts.h"
#include <SDL3/SDL_video.h>
#include <node/js_native_api.h>
#include <stdint.h>
#include <stdlib.h>

napi_value SDL_CreateWindow_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 4;
	napi_value argv[4];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	char name[129];
	name[128] = 0;
	size_t name_length = 0;
	napi_get_value_string_utf8(env, argv[0], name, 128, &name_length);

	int w, h;
	napi_get_value_int32(env, argv[1], &w);
	napi_get_value_int32(env, argv[2], &h);

	uint64_t flags = 0;
	napi_get_value_uint32(env, argv[3], (uint32_t *)&flags);

	SDL_Window *win = SDL_CreateWindow(name, w, h, flags);
	napi_create_pointer(env, win, &retval);

	return retval;
}

napi_value SDL_DestroyWindow_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Window *win;
	napi_get_value_pointer(env, argv[0], (void *)&win);

	if (!win)
	{
		napi_throw_error(env, "Error", "Attempting to destroy a NULL pointer");
		return retval;
	}

	SDL_DestroyWindow(win);
	return retval;
}

napi_value export_window(napi_env env, napi_value exports)
{
	export_fn(env, exports, "SDL_CreateWindow", SDL_CreateWindow_wrapper);
	export_fn(env, exports, "SDL_DestroyWindow", SDL_DestroyWindow_wrapper);
	return exports;
}