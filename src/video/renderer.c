#include "../sdl3ts.h"
#include <SDL3/SDL_oldnames.h>
#include <node/js_native_api.h>
#include <node/js_native_api_types.h>

napi_value rendererClass;
extern napi_value windowClass;

void sdl3ts_renderer_free(napi_env env, void *finalize_data, void *hint)
{
	if (finalize_data)
		SDL_DestroyRenderer(finalize_data);
}

napi_value sdl3ts_renderer_setDrawColorNormal(napi_env env, napi_callback_info info)
{
	size_t argc = 4;
	napi_value argv[4];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	double r = 0.0, g = 0.0, b = 0.0, a = 1.0;

	napi_get_value_double(env, argv[0], &r);
	napi_get_value_double(env, argv[1], &g);
	napi_get_value_double(env, argv[2], &b);

	napi_valuetype type;
	napi_typeof(env, argv[3], &type);
	if (type == napi_number)
	{
		napi_get_value_double(env, argv[3], &a);
	}

	SDL_SetRenderDrawColorFloat(sdlrenderer, r, g, b, a);
	return NULL;
}

napi_value sdl3ts_renderer_setDrawColor(napi_env env, napi_callback_info info)
{
	size_t argc = 4;
	napi_value argv[4];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	uint32_t r = 0, g = 0, b = 0, a = SDL_ALPHA_OPAQUE;

	napi_get_value_uint32(env, argv[0], &r);
	napi_get_value_uint32(env, argv[1], &g);
	napi_get_value_uint32(env, argv[2], &b);

	napi_valuetype type;
	napi_typeof(env, argv[3], &type);
	if (type == napi_number)
	{
		napi_get_value_uint32(env, argv[3], &a);
	}

	SDL_SetRenderDrawColor(sdlrenderer, r, g, b, a);
	return NULL;
}

napi_value sdl3ts_renderer_drawRect(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	SDL_FRect sdlrect;
	if (sdl3ts_pull_rect(env, argv[0], &sdlrect) != napi_ok)
		return NULL;

	SDL_RenderRect(sdlrenderer, &sdlrect);
	return NULL;
}

napi_value sdl3ts_renderer_fillRect(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	SDL_FRect sdlrect;
	if (sdl3ts_pull_rect(env, argv[0], &sdlrect) != napi_ok)
		return NULL;

	SDL_RenderFillRect(sdlrenderer, &sdlrect);
	return NULL;
}

napi_value sdl3ts_renderer_drawPoint(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	SDL_Point sdlpoint;
	if (sdl3ts_pull_point(env, argv[0], &sdlpoint) != napi_ok)
		return NULL;

	SDL_RenderPoint(sdlrenderer, sdlpoint.x, sdlpoint.y);
	return NULL;
}

napi_value sdl3ts_renderer_drawPoints(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	uint32_t n_points = 0;
	napi_get_array_length(env, argv[0], &n_points);

	for (uint32_t i = 0; i < n_points; i++)
	{
		SDL_Point sdlpoint;
		napi_value point;
		napi_get_element(env, argv[0], i, &point);
		if (sdl3ts_pull_point(env, point, &sdlpoint) != napi_ok)
			return NULL;
		SDL_RenderPoint(sdlrenderer, sdlpoint.x, sdlpoint.y);
	}
	return NULL;
}

napi_value sdl3ts_renderer_line(napi_env env, napi_callback_info info)
{
	size_t argc = 4;
	napi_value argv[4];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	double x1, y1, x2, y2;
	napi_get_value_double(env, argv[0], &x1);
	napi_get_value_double(env, argv[1], &y1);
	napi_get_value_double(env, argv[2], &x2);
	napi_get_value_double(env, argv[3], &y2);

	SDL_RenderLine(sdlrenderer, x1, y1, x2, y2);
	return NULL;
}

napi_value sdl3ts_renderer_clear(napi_env env, napi_callback_info info)
{
	size_t argc = 0;
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, NULL, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	SDL_RenderClear(sdlrenderer);
	return NULL;
}

napi_value sdl3ts_renderer_present(napi_env env, napi_callback_info info)
{
	size_t argc = 0;
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, NULL, &renderer, NULL);
	SDL_Renderer *sdlrenderer;
	napi_unwrap(env, renderer, (void **)&sdlrenderer);

	SDL_RenderPresent(sdlrenderer);
	return NULL;
}

napi_value sdl3ts_renderer_init(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value renderer;
	napi_get_cb_info(env, info, &argc, argv, &renderer, NULL);

	_Bool argumentType;
	napi_instanceof(env, argv[0], windowClass, &argumentType);
	if (!argumentType)
	{
		napi_throw_type_error(env, "InternalError", "Value passed to renderer is not a SDL3.Window");
		return NULL;
	}

	SDL_Window *sdlwindow;
	napi_unwrap(env, argv[0], (void **)&sdlwindow);

	SDL_Renderer *sdlrenderer = SDL_CreateRenderer(sdlwindow, NULL);
	if (!sdlrenderer)
	{
		napi_throw_error(env, "Error", "Could not ");
		return NULL;
	}
	napi_wrap(env, renderer, sdlrenderer, sdl3ts_renderer_free, NULL, NULL);

	napi_set_named_property(env, renderer, "window", argv[0]);
	napi_value val;

#define export_fn(name, fn)                                                                                            \
	{                                                                                                                  \
		napi_create_function(env, #fn, sizeof(#fn) - 1, &fn, NULL, &val);                                              \
		napi_set_named_property(env, renderer, name, val);                                                             \
	}

	export_fn("present", sdl3ts_renderer_present);
	export_fn("clear", sdl3ts_renderer_clear);

	export_fn("setDrawColor", sdl3ts_renderer_setDrawColor);
	export_fn("setDrawColorNormal", sdl3ts_renderer_setDrawColorNormal);

	export_fn("drawRect", sdl3ts_renderer_drawRect);
	export_fn("fillRect", sdl3ts_renderer_fillRect);

	export_fn("drawPoint", sdl3ts_renderer_drawPoint);
	export_fn("drawPoints", sdl3ts_renderer_drawPoints);
	
	export_fn("line", sdl3ts_renderer_line);
#undef export_fn

	return renderer;
}

void export_renderer(napi_env env, napi_value exports)
{
	napi_define_class(env, "Renderer", 0, &sdl3ts_renderer_init, NULL, 0, NULL, &rendererClass);
	napi_set_named_property(env, exports, "Renderer", rendererClass);
}