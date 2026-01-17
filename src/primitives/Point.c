#include "../sdl3ts.h"
#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <stdio.h>
#include <stdlib.h>

napi_value pointClass;

napi_status sdl3ts_pull_point(napi_env env, napi_value val, SDL_Point *point)
{
	_Bool argumentType;
	napi_instanceof(env, val, pointClass, &argumentType);
	if (!argumentType)
	{
		napi_throw_type_error(env, "SDL.Error", "Point is not of type SDL.Point");
		return napi_pending_exception;
	}
	napi_value property;
	double n;
	napi_get_named_property(env, val, "x", &property);
	napi_get_value_double(env, property, &n);
	point->x = n;
	napi_get_named_property(env, val, "y", &property);
	napi_get_value_double(env, property, &n);
	point->y = n;

	return napi_ok;
}

napi_value sdl3ts_point_init(napi_env env, napi_callback_info info)
{
	size_t argc = 2;
	napi_value argv[2];
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

	return rect;
}

void export_point(napi_env env, napi_value exports)
{
	napi_define_class(env, "Point", 0, &sdl3ts_point_init, NULL, 0, NULL, &pointClass);
	napi_set_named_property(env, exports, "Point", pointClass);
}