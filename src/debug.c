#include "sdl3ts.h"
#include <stdio.h>

void dbg_print_val(napi_env env, napi_value val, const char *name)
{
	napi_valuetype type;
	napi_typeof(env, val, &type);

	napi_value toString;
	if (type != napi_object)
		napi_coerce_to_string(env, val, &toString);
	else {
		napi_value G;
		napi_get_global(env, &G);
		napi_value JSON;
		napi_get_named_property(env, G, "JSON", &JSON);
		napi_value JSONStringify;
		napi_get_named_property(env, JSON, "stringify", &JSONStringify);
		napi_value args[3];
		args[0] = val;
		napi_get_null(env, &args[1]);
		napi_create_string_utf8(env, "  ", 2, &args[2]);
		napi_call_function(env, JSON, JSONStringify, 3, args, &toString);
	}
	char toStringVal[2048];
	size_t toStringValLen = 2048;
	napi_get_value_string_utf8(env, toString, toStringVal, toStringValLen, &toStringValLen);
	toStringVal[toStringValLen] = 0;
	
	if (name)
		printf("%s ", name);
	printf("%s\n", toStringVal);
}