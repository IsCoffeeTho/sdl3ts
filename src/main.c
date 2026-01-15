#include "sdl3ts.h"
#include <node/js_native_api_types.h>

napi_value initSubSystem(napi_env env, napi_callback_info info) {
	napi_value retval;
	int argc = 1;
	napi_value argv[1];
	
	uint32_t flags = 0;
	
	napi_get_boolean(env, SDL_Init(flags), &retval);
	return retval;
}

napi_value export_main(napi_env env, napi_value exports) {
	
	return exports;
}