#include "../sdl3ts.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <node/js_native_api.h>
#include <stdint.h>
#include <stdlib.h>

napi_value SDL_PollEvent_wrapper(napi_env env, napi_callback_info info)
{
	napi_value retval = NULL;

	SDL_Event event;
	if (!SDL_PollEvent(&event))
		return retval;

	napi_create_object(env, &retval);
	napi_value val;
	napi_create_uint32(env, event.type, &val);
	napi_set_named_property(env, retval, "type", val);
	napi_create_bigint_uint64(env, event.common.timestamp, &val);
	napi_set_named_property(env, retval, "timestamp", val);

	if (SDL_EVENT_DISPLAY_FIRST < event.type && event.type <= SDL_EVENT_DISPLAY_LAST)
	{
		SDL_DisplayEvent ev = event.display;

		napi_create_uint32(env, ev.displayID, &val);
		napi_set_named_property(env, retval, "displayId", val);
		
		napi_create_int32(env, ev.data1, &val);
		napi_set_named_property(env, retval, "data1", val);
		
		napi_create_int32(env, ev.data2, &val);
		napi_set_named_property(env, retval, "data2", val);
	}
	else if (SDL_EVENT_WINDOW_FIRST < event.type && event.type <= SDL_EVENT_WINDOW_LAST)
	{
		SDL_WindowEvent ev = event.window;

		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);
		
		napi_create_int32(env, ev.data1, &val);
		napi_set_named_property(env, retval, "data1", val);
		
		napi_create_int32(env, ev.data2, &val);
		napi_set_named_property(env, retval, "data2", val);
	}
	else if (SDL_EVENT_TEXT_EDITING == event.type)
	{
		SDL_TextEditingEvent ev = event.edit;
		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);
		
		napi_create_string_utf8(env, ev.text, strlen(ev.text), &val);
		napi_set_named_property(env, retval, "text", val);
		
		napi_create_int32(env, ev.start, &val);
		napi_set_named_property(env, retval, "start", val);
		
		napi_create_int32(env, ev.length, &val);
		napi_set_named_property(env, retval, "length", val);
	}
	else if (SDL_EVENT_TEXT_EDITING_CANDIDATES == event.type)
	{
		SDL_TextEditingCandidatesEvent ev = event.edit_candidates;
		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);
		{
			napi_value candidates;
			napi_create_array(env, &candidates);
			napi_set_named_property(env, retval, "candidates", candidates);
			
			napi_value index;
			for (uint32_t i = 0; i < ev.num_candidates; i++) {
				napi_create_uint32(env, i, &index);
				
				const char * candidate = ev.candidates[i];
				napi_create_string_utf8(env, candidate, strlen(candidate), &val);
				
				napi_set_property(env, candidates, index, val);
			}
		}
		napi_create_int32(env, ev.selected_candidate, &val);
		napi_set_named_property(env, retval, "selected_candidate", val);
		
		
		napi_get_boolean(env, ev.horizontal, &val);
		napi_set_named_property(env, retval, "horizontal", val);
	}
	else if (SDL_EVENT_KEYBOARD_ADDED == event.type || SDL_EVENT_KEYBOARD_ADDED == event.type)
	{
		SDL_KeyboardDeviceEvent ev = event.kdevice;
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
	}
	else if (SDL_EVENT_KEY_DOWN == event.type || SDL_EVENT_KEY_UP == event.type)
	{
		SDL_KeyboardEvent ev = event.key;

		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);

		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);

		napi_create_uint32(env, ev.scancode, &val);
		napi_set_named_property(env, retval, "scancode", val);

		napi_create_uint32(env, ev.key, &val);
		napi_set_named_property(env, retval, "key", val);

		napi_create_uint32(env, ev.mod, &val);
		napi_set_named_property(env, retval, "mod", val);

		napi_create_uint32(env, ev.raw, &val);
		napi_set_named_property(env, retval, "raw", val);

		napi_get_boolean(env, ev.down, &val);
		napi_set_named_property(env, retval, "down", val);

		napi_get_boolean(env, ev.repeat, &val);
		napi_set_named_property(env, retval, "repeat", val);
	}
	else if (SDL_EVENT_MOUSE_MOTION == event.type)
	{
		SDL_MouseMotionEvent ev = event.motion;
		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);

		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		{
			napi_value buttons;
			napi_create_object(env, &buttons);

			napi_get_boolean(env, ev.state & SDL_BUTTON_MASK(SDL_BUTTON_LEFT), &val);
			napi_set_named_property(env, buttons, "left", val);

			napi_get_boolean(env, ev.state & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE), &val);
			napi_set_named_property(env, buttons, "middle", val);

			napi_get_boolean(env, ev.state & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT), &val);
			napi_set_named_property(env, buttons, "right", val);

			napi_get_boolean(env, ev.state & SDL_BUTTON_MASK(SDL_BUTTON_X1), &val);
			napi_set_named_property(env, buttons, "X1", val);

			napi_get_boolean(env, ev.state & SDL_BUTTON_MASK(SDL_BUTTON_X2), &val);
			napi_set_named_property(env, buttons, "X2", val);

			napi_set_named_property(env, retval, "buttons", buttons);
		}
		napi_create_double(env, ev.x, &val);
		napi_set_named_property(env, retval, "x", val);

		napi_create_double(env, ev.y, &val);
		napi_set_named_property(env, retval, "y", val);

		napi_create_double(env, ev.xrel, &val);
		napi_set_named_property(env, retval, "xrel", val);

		napi_create_double(env, ev.yrel, &val);
		napi_set_named_property(env, retval, "yrel", val);
	}
	else if (SDL_EVENT_MOUSE_BUTTON_DOWN == event.type || SDL_EVENT_MOUSE_BUTTON_UP == event.type)
	{
		SDL_MouseButtonEvent ev = event.button;
		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);

		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);

		napi_create_uint32(env, ev.button, &val);
		napi_set_named_property(env, retval, "button", val);

		napi_get_boolean(env, ev.down, &val);
		napi_set_named_property(env, retval, "down", val);

		napi_create_uint32(env, ev.clicks, &val);
		napi_set_named_property(env, retval, "clicks", val);

		napi_create_double(env, ev.x, &val);
		napi_set_named_property(env, retval, "x", val);

		napi_create_double(env, ev.y, &val);
		napi_set_named_property(env, retval, "y", val);
	}
	else if (SDL_EVENT_MOUSE_WHEEL == event.type)
	{
		SDL_MouseWheelEvent ev = event.wheel;
		napi_create_uint32(env, ev.windowID, &val);
		napi_set_named_property(env, retval, "windowId", val);

		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);

		napi_create_double(env, ev.x, &val);
		napi_set_named_property(env, retval, "x", val);

		napi_create_double(env, ev.y, &val);
		napi_set_named_property(env, retval, "y", val);

		napi_get_boolean(env, ev.direction == SDL_MOUSEWHEEL_FLIPPED, &val);
		napi_set_named_property(env, retval, "inverted", val);

		napi_create_double(env, ev.mouse_x, &val);
		napi_set_named_property(env, retval, "mouse_x", val);

		napi_create_double(env, ev.mouse_y, &val);
		napi_set_named_property(env, retval, "mouse_y", val);

		napi_create_int32(env, ev.integer_x, &val);
		napi_set_named_property(env, retval, "integer_x", val);

		napi_create_int32(env, ev.integer_y, &val);
		napi_set_named_property(env, retval, "integer_y", val);
	}
	else if (SDL_EVENT_MOUSE_ADDED == event.type || SDL_EVENT_MOUSE_REMOVED == event.type)
	{
		SDL_MouseDeviceEvent ev = event.mdevice;
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
	}
	else if (SDL_EVENT_USER >= event.type && event.type <= SDL_EVENT_LAST)
	{
		
	}

	return retval;
}

napi_value export_events(napi_env env, napi_value exports)
{
	export_fn(env, exports, "SDL_PollEvent", SDL_PollEvent_wrapper);
	return exports;
}