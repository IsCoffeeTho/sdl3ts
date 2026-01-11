#include "sdl3ts.h"

napi_value export_sdl3ts(napi_env env, napi_value exports) {
	export_plumbing(env, exports);
	export_events(env, exports);
	export_window(env, exports);
	export_renderer(env, exports);
	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, export_sdl3ts);