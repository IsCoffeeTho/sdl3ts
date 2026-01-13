#include "../sdl3ts.h"
#include <node/js_native_api.h>

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

napi_value SDL_RenderFillRect_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 2;
	napi_value argv[2];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}
	SDL_FRect rect;
	napi_get_value_rect(env, argv[1], &rect);
	
	SDL_RenderFillRect(renderer, &rect);
	
	return retval;
}

napi_value SDL_RenderRect_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 2;
	napi_value argv[2];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}
	SDL_FRect rect;
	napi_get_value_rect(env, argv[1], &rect);
	
	SDL_RenderRect(renderer, &rect);
	
	return retval;
}

napi_value SDL_RenderPoint_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 2;
	napi_value argv[2];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}
	SDL_Point point;
	napi_get_value_point(env, argv[1], &point);
	
	SDL_RenderPoint(renderer, point.x, point.y);
	
	return retval;
}

napi_value SDL_RenderLine_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;
	size_t argc = 5;
	napi_value argv[5];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	SDL_Renderer *renderer;
	napi_get_value_pointer(env, argv[0], (void *)&renderer);
	if (!renderer)
	{
		napi_throw_error(env, "Error", "Renderer: Use after free");
		return retval;
	}
	double x1;
	napi_get_value_double(env, argv[1], &x1);
	double y1;
	napi_get_value_double(env, argv[2], &y1);
	double x2;
	napi_get_value_double(env, argv[3], &x2);
	double y2;
	napi_get_value_double(env, argv[4], &y2);
	
	SDL_RenderLine(renderer, x1, y1, x2, y2);
	
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
	
	export_fn(env, exports, "SDL_RenderFillRect", SDL_RenderFillRect_wrapper);
	export_fn(env, exports, "SDL_RenderRect", SDL_RenderRect_wrapper);
	
	export_fn(env, exports, "SDL_RenderPoint", SDL_RenderPoint_wrapper);
	
	export_fn(env, exports, "SDL_RenderLine", SDL_RenderLine_wrapper);

	return exports;
}