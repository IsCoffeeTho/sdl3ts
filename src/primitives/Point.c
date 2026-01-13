#include "../sdl3ts.h"
#include <node/js_native_api.h>

napi_status napi_create_point(napi_env env, SDL_Point *point, napi_value *result)
{
	napi_status retval;
	if (!point)
		return napi_get_null(env, result);
	
	if ((retval = napi_create_object(env, result)) != napi_ok) return retval;
	napi_value val;
	
	napi_create_double(env, point->x, &val);
	napi_set_named_property(env, *result, "x", val);
	
	napi_create_double(env, point->y, &val);
	napi_set_named_property(env, *result, "y", val);
	
	return napi_ok;
}

napi_status napi_get_value_point(napi_env env, napi_value value, SDL_Point *result)
{
	double num;
	napi_value val;
	
	napi_get_named_property(env, value, "x", &val);
	napi_get_value_double(env, val, &num);
	result->x = num;
	
	napi_get_named_property(env, value, "y", &val);
	napi_get_value_double(env, val, &num);
	result->y = num;
	
	return napi_ok;
}