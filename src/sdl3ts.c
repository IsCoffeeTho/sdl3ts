#include "sdl3ts.h"

napi_value export_sdl3ts(napi_env env, napi_value exports) {
	export_main(env, exports);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, export_sdl3ts);