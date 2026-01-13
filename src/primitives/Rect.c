#include "../sdl3ts.h"
#include <node/js_native_api.h>

napi_status napi_create_rect(napi_env env, SDL_FRect *rect, napi_value *result)
{
	napi_status retval;
	if (!rect)
		return napi_get_null(env, result);
	
	if ((retval = napi_create_object(env, result)) != napi_ok) return retval;
	napi_value val;
	
	napi_create_double(env, rect->x, &val);
	napi_set_named_property(env, *result, "x", val);
	
	napi_create_double(env, rect->y, &val);
	napi_set_named_property(env, *result, "y", val);
	
	napi_create_double(env, rect->w, &val);
	napi_set_named_property(env, *result, "w", val);
	
	napi_create_double(env, rect->h, &val);
	napi_set_named_property(env, *result, "h", val);
	
	return napi_ok;
}

napi_status napi_get_value_rect(napi_env env, napi_value value, SDL_FRect *result)
{
	double num;
	napi_value val;
	
	napi_get_named_property(env, value, "x", &val);
	napi_get_value_double(env, val, &num);
	result->x = num;
	
	napi_get_named_property(env, value, "y", &val);
	napi_get_value_double(env, val, &num);
	result->y = num;
	
	napi_get_named_property(env, value, "w", &val);
	napi_get_value_double(env, val, &num);
	result->w = num;
	
	napi_get_named_property(env, value, "h", &val);
	napi_get_value_double(env, val, &num);
	result->h = num;
	
	return napi_ok;
}