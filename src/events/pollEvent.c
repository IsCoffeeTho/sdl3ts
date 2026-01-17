#include "../sdl3ts.h"
#include <stdio.h>

napi_value sdl3ts_pollEvent(napi_env env, napi_callback_info info)
{
	napi_value event;
	napi_get_undefined(env, &event);

	SDL_Event sdlevent;
	SDL_PollEvent(&sdlevent);

	if (sdlevent.type == SDL_EVENT_POLL_SENTINEL)
		return event;

	napi_create_object(env, &event);
	napi_value val;
	napi_create_bigint_uint64(env, sdlevent.common.timestamp, &val);
	napi_set_named_property(env, event, "timestamp", val);

	napi_create_uint32(env, sdlevent.type, &val);
	napi_set_named_property(env, event, "type", val);
	
	

	return event;
}

void export_events(napi_env env, napi_value exports)
{
	export_function(env, exports, "pollEvent", sdl3ts_pollEvent);
}