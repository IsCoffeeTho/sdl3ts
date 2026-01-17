#include "sdl3ts.h"

uint32_t readInitFlagsObject(napi_env env, napi_value flags)
{
	uint32_t retval = 0;

#define appendInitFlag(name, flag_bit)                                                                                 \
	{                                                                                                                  \
		napi_value val;                                                                                                \
		_Bool flagPresent;                                                                                             \
		napi_has_named_property(env, flags, name, &flagPresent);                                                       \
		if (flagPresent)                                                                                               \
		{                                                                                                              \
			_Bool flag;                                                                                                \
			napi_get_named_property(env, flags, name, &val);                                                           \
			napi_get_value_bool(env, val, &flag);                                                                      \
			if (flag)                                                                                                  \
				retval |= flag_bit;                                                                                    \
		}                                                                                                              \
	}

	appendInitFlag("audio", SDL_INIT_AUDIO);
	appendInitFlag("video", SDL_INIT_VIDEO);
	appendInitFlag("joystick", SDL_INIT_JOYSTICK);
	appendInitFlag("haptic", SDL_INIT_HAPTIC);
	appendInitFlag("gamepad", SDL_INIT_GAMEPAD);
	appendInitFlag("events", SDL_INIT_EVENTS);
	appendInitFlag("sensor", SDL_INIT_SENSOR);
	appendInitFlag("camera", SDL_INIT_CAMERA);

#undef appendInitFlag

	return retval;
}

napi_value sdl3ts_initSubSystem(napi_env env, napi_callback_info info)
{
	napi_value retval;
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	uint32_t flags = readInitFlagsObject(env, argv[0]);

	napi_get_boolean(env, SDL_InitSubSystem(flags), &retval);
	return retval;
}

napi_value sdl3ts_quitSubSystem(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	uint32_t flags = readInitFlagsObject(env, argv[0]);
	SDL_QuitSubSystem(flags);
	return NULL;
}

napi_value sdl3ts_quit(napi_env env, napi_callback_info info)
{
	SDL_Quit();
	return NULL;
}

void export_main(napi_env env, napi_value exports)
{
	export_function(env, exports, "init", sdl3ts_initSubSystem);
	export_function(env, exports, "initSubSystem", sdl3ts_initSubSystem);
	export_function(env, exports, "quit", sdl3ts_quit);
	export_function(env, exports, "quitSubSystem", sdl3ts_quitSubSystem);
}