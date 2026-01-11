#include "../sdl3ts.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <node/js_native_api.h>
#include <stdint.h>
#include <stdlib.h>

napi_value SDL_CreateRenderer_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 2;
	napi_value argv[2];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Window *win;
	napi_get_value_pointer(env, argv[0], (void *)&win);

	char name_buffer[129];
	name_buffer[128] = 0;
	size_t name_length = 0;
	char *name = name_buffer;
	if (napi_get_value_string_utf8(env, argv[1], name_buffer, 128, &name_length) != napi_ok)
		name = NULL;

	SDL_Renderer *renderer = SDL_CreateRenderer(win, name);
	napi_create_pointer(env, renderer, &retval);

	return retval;
}

napi_value SDL_DestroyRenderer_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);

	if (!renderer)
	{
		napi_throw_error(env, "Error", "Attempting to destroy a NULL pointer");
		return retval;
	}

	SDL_DestroyRenderer(renderer);
	return retval;
}

napi_value SDL_RenderClear_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);

	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}

	SDL_RenderClear(renderer);
	return retval;
}

napi_value SDL_RenderPresent_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);

	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}

	SDL_RenderPresent(renderer);
	return retval;
}

napi_value SDL_SetRenderDrawColorFloat_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 5;
	napi_value argv[5];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: User after free");
		return retval;
	}

	double r, g, b, a;
	napi_get_value_double(env, argv[1], (double *)&r);
	napi_get_value_double(env, argv[2], (double *)&g);
	napi_get_value_double(env, argv[3], (double *)&b);
	napi_get_value_double(env, argv[4], (double *)&a);

	SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
	return retval;
}

napi_value SDL_SetRenderDrawColor_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 5;
	napi_value argv[5];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: User after free");
		return retval;
	}

	uint32_t r, g, b, a;
	napi_get_value_uint32(env, argv[1], (uint32_t *)&r);
	napi_get_value_uint32(env, argv[2], (uint32_t *)&g);
	napi_get_value_uint32(env, argv[3], (uint32_t *)&b);
	napi_get_value_uint32(env, argv[4], (uint32_t *)&a);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	return retval;
}

napi_value export_renderer(napi_env env, napi_value exports)
{
	export_fn(env, exports, "SDL_CreateRenderer", SDL_CreateRenderer_wrapper);
	export_fn(env, exports, "SDL_DestroyRenderer", SDL_DestroyRenderer_wrapper);

	export_fn(env, exports, "SDL_SetRenderDrawColorFloat", SDL_SetRenderDrawColorFloat_wrapper);
	export_fn(env, exports, "SDL_SetRenderDrawColor", SDL_SetRenderDrawColor_wrapper);

	export_fn(env, exports, "SDL_RenderClear", SDL_RenderClear_wrapper);
	export_fn(env, exports, "SDL_RenderPresent", SDL_RenderPresent_wrapper);

	return exports;
}