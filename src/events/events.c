#include "../sdl3ts.h"

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
			for (int32_t i = 0; i < ev.num_candidates; i++)
			{
				napi_create_uint32(env, i, &index);

				const char *candidate = ev.candidates[i];
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
	else if (SDL_EVENT_MOUSE_ADDED == event.type || SDL_EVENT_MOUSE_REMOVED == event.type)
	{
		SDL_MouseDeviceEvent ev = event.mdevice;
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
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
	else if (SDL_EVENT_JOYSTICK_AXIS_MOTION == event.type)
	{
		SDL_JoyAxisEvent ev = event.jaxis;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_uint32(env, ev.axis, &val);
		napi_set_named_property(env, retval, "axis", val);
		
		napi_create_int32(env, ev.value, &val);
		napi_set_named_property(env, retval, "value", val);
	}
	else if (SDL_EVENT_JOYSTICK_BALL_MOTION == event.type)
	{
		SDL_JoyBallEvent ev = event.jball;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_uint32(env, ev.ball, &val);
		napi_set_named_property(env, retval, "ball", val);
		
		napi_create_int32(env, ev.xrel, &val);
		napi_set_named_property(env, retval, "xrel", val);
		
		napi_create_int32(env, ev.yrel, &val);
		napi_set_named_property(env, retval, "yrel", val);
	}
	else if (SDL_EVENT_JOYSTICK_BALL_MOTION == event.type)
	{
		SDL_JoyBallEvent ev = event.jball;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_uint32(env, ev.ball, &val);
		napi_set_named_property(env, retval, "ball", val);
		
		napi_create_int32(env, ev.xrel, &val);
		napi_set_named_property(env, retval, "xrel", val);
		
		napi_create_int32(env, ev.yrel, &val);
		napi_set_named_property(env, retval, "yrel", val);
	}
	else if (SDL_EVENT_JOYSTICK_HAT_MOTION == event.type)
	{
		SDL_JoyHatEvent ev = event.jhat;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_uint32(env, ev.hat, &val);
		napi_set_named_property(env, retval, "hat", val);
		
		napi_create_uint32(env, ev.value, &val);
		napi_set_named_property(env, retval, "xrel", val);
	}
	else if (SDL_EVENT_JOYSTICK_BUTTON_DOWN == event.type || SDL_EVENT_JOYSTICK_BUTTON_UP == event.type)
	{
		SDL_JoyButtonEvent ev = event.jbutton;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_uint32(env, ev.button, &val);
		napi_set_named_property(env, retval, "button", val);
		
		napi_get_boolean(env, ev.down, &val);
		napi_set_named_property(env, retval, "down", val);
	}
	else if (SDL_EVENT_JOYSTICK_ADDED == event.type || SDL_EVENT_JOYSTICK_REMOVED == event.type || SDL_EVENT_JOYSTICK_UPDATE_COMPLETE == event.type)
	{
		SDL_JoyBatteryEvent ev = event.jbattery;
		
		napi_create_uint32(env, ev.which, &val);
		napi_set_named_property(env, retval, "which", val);
		
		napi_create_int32(env, ev.state, &val);
		napi_set_named_property(env, retval, "state", val);
		
		napi_create_int32(env, ev.percent, &val);
		napi_set_named_property(env, retval, "percent", val);
	}

	return retval;
}

napi_value export_events(napi_env env, napi_value exports)
{
	export_fn(env, exports, "SDL_PollEvent", SDL_PollEvent_wrapper);
	return exports;
}