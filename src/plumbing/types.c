#include "../sdl3ts.h"
#include <node/js_native_api.h>
#include <node/js_native_api_types.h>

napi_status napi_create_pointer(napi_env env, void *ptr, napi_value *result) {
	if (!ptr)
		return napi_get_null(env, result);
	return napi_create_bigint_uint64(env, (uint64_t)ptr, result);
}

napi_status napi_get_value_pointer(napi_env env, napi_value value, void **result) {
	_Bool lossless;
	napi_status ptr_status = napi_get_value_bigint_uint64(env, value, (uint64_t *)result, &lossless);
	if (ptr_status == napi_ok)
		return ptr_status;
	*result = NULL;
	return napi_ok;
}