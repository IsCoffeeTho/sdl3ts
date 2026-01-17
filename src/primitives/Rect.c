#include "../sdl3ts.h"
#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <stdio.h>
#include <stdlib.h>

napi_value rectClass;

napi_status sdl3ts_pull_rect(napi_env env, napi_value val, SDL_FRect *rect)
{
	_Bool argumentType;
	napi_instanceof(env, val, rectClass, &argumentType);
	if (!argumentType) {
		napi_throw_type_error(env, "SDL.Error", "Rect is not of type SDL.Rect");
		return napi_pending_exception;
	}
	
	napi_value property;
	double n;
	napi_get_named_property(env, val, "x", &property);
	napi_get_value_double(env, property, &n);
	rect->x = n;
	napi_get_named_property(env, val, "y", &property);
	napi_get_value_double(env, property, &n);
	rect->y = n;
	napi_get_named_property(env, val, "w", &property);
	napi_get_value_double(env, property, &n);
	rect->w = n;
	napi_get_named_property(env, val, "h", &property);
	napi_get_value_double(env, property, &n);
	rect->h = n;
	
	return napi_ok;
}

napi_value sdl3ts_rect_init(napi_env env, napi_callback_info info)
{
	size_t argc = 4;
	napi_value argv[4];
	napi_value rect;
	napi_get_cb_info(env, info, &argc, argv, &rect, NULL);

	napi_valuetype arg_type;

	napi_typeof(env, argv[0], &arg_type);
	if (arg_type != napi_number)
		napi_create_double(env, 0.0, &argv[0]);
	napi_set_named_property(env, rect, "x", argv[0]);

	napi_typeof(env, argv[1], &arg_type);
	if (arg_type != napi_number)
		napi_create_double(env, 0.0, &argv[1]);
	napi_set_named_property(env, rect, "y", argv[1]);

	napi_typeof(env, argv[2], &arg_type);
	if (arg_type != napi_number)
		napi_create_double(env, 0.0, &argv[2]);
	napi_set_named_property(env, rect, "w", argv[2]);

	napi_typeof(env, argv[3], &arg_type);
	if (arg_type != napi_number)
		napi_create_double(env, 0.0, &argv[3]);
	napi_set_named_property(env, rect, "h", argv[3]);

	return rect;
}

void export_rect(napi_env env, napi_value exports)
{
	napi_define_class(env, "Rect", 0, &sdl3ts_rect_init, NULL, 0, NULL, &rectClass);
	napi_set_named_property(env, exports, "Rect", rectClass);
}