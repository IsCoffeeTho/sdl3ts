#include "../sdl3ts.h"
#include <stdio.h>

napi_value windowClass;
extern napi_value rendererClass;

void sdl3ts_window_free(napi_env env, void *finalize_data, void *hint)
{
	if (finalize_data)
		SDL_DestroyWindow(finalize_data);
}

uint32_t readWindowFlagsObject(napi_env env, napi_value flags)
{
	uint32_t retval = 0;
	napi_value val;
	napi_valuetype type;
	_Bool flag;
#define appendWindowFlag(name, flag_bit)                                                                               \
	{                                                                                                                  \
		napi_get_named_property(env, flags, name, &val);                                                               \
		napi_typeof(env, val, &type);                                                                                  \
		if (type == napi_boolean)                                                                                      \
		{                                                                                                              \
			napi_get_value_bool(env, val, &flag);                                                                      \
			if (flag)                                                                                                  \
				retval |= flag_bit;                                                                                    \
		}                                                                                                              \
	}
	appendWindowFlag("fullscreen", SDL_WINDOW_FULLSCREEN);
	appendWindowFlag("opengl", SDL_WINDOW_OPENGL);
	appendWindowFlag("occluded", SDL_WINDOW_OCCLUDED);
	appendWindowFlag("hidden", SDL_WINDOW_HIDDEN);
	appendWindowFlag("borderless", SDL_WINDOW_BORDERLESS);
	appendWindowFlag("resizable", SDL_WINDOW_RESIZABLE);
	appendWindowFlag("minimized", SDL_WINDOW_MINIMIZED);
	appendWindowFlag("maximized", SDL_WINDOW_MAXIMIZED);
	appendWindowFlag("mouseGrabbed", SDL_WINDOW_MOUSE_GRABBED);
	appendWindowFlag("inputFocus", SDL_WINDOW_INPUT_FOCUS);
	appendWindowFlag("mouseFocus", SDL_WINDOW_MOUSE_FOCUS);
	appendWindowFlag("external", SDL_WINDOW_EXTERNAL);
	appendWindowFlag("modal", SDL_WINDOW_MODAL);
	appendWindowFlag("highPixelDensity", SDL_WINDOW_HIGH_PIXEL_DENSITY);
	appendWindowFlag("mouseCapture", SDL_WINDOW_MOUSE_CAPTURE);
	appendWindowFlag("mouseRelativeMode", SDL_WINDOW_MOUSE_RELATIVE_MODE);
	appendWindowFlag("alwaysOnTop", SDL_WINDOW_ALWAYS_ON_TOP);
	appendWindowFlag("utility", SDL_WINDOW_UTILITY);
	appendWindowFlag("tooltip", SDL_WINDOW_TOOLTIP);
	appendWindowFlag("popupMenu", SDL_WINDOW_POPUP_MENU);
	appendWindowFlag("keyboardGrabbed", SDL_WINDOW_KEYBOARD_GRABBED);
	appendWindowFlag("fillDocument", SDL_WINDOW_FILL_DOCUMENT);
	appendWindowFlag("vulkan", SDL_WINDOW_VULKAN);
	appendWindowFlag("metal", SDL_WINDOW_METAL);
	appendWindowFlag("transparent", SDL_WINDOW_TRANSPARENT);
	appendWindowFlag("notFocusable", SDL_WINDOW_NOT_FOCUSABLE);
#undef appendWindowFlag
	return retval;
}

napi_value sdl3ts_window_init(napi_env env, napi_callback_info info)
{
	size_t argc = 1;
	napi_value argv[1];
	napi_value window;
	napi_get_cb_info(env, info, &argc, argv, &window, NULL);

	napi_valuetype argumentType;
	napi_typeof(env, argv[0], &argumentType);

	char windowName[2048] = "sdl3ts";
	int windowWidth = 640;
	int windowHeight = 480;
	SDL_WindowFlags windowFlags = 0;
	if (argumentType == napi_object)
	{
		napi_value val;
		napi_get_named_property(env, argv[0], "name", &val);
		napi_typeof(env, val, &argumentType);
		if (argumentType == napi_string)
		{
			size_t windowNameLength = 0;
			napi_get_value_string_utf8(env, val, windowName, 2048, &windowNameLength);
			windowName[windowNameLength] = '\0';
		}
		napi_get_named_property(env, argv[0], "width", &val);
		napi_typeof(env, val, &argumentType);
		if (argumentType == napi_number)
			napi_get_value_int32(env, val, &windowWidth);
		napi_get_named_property(env, argv[0], "height", &val);
		napi_typeof(env, val, &argumentType);
		if (argumentType == napi_number)
			napi_get_value_int32(env, val, &windowHeight);

		windowFlags = readWindowFlagsObject(env, argv[0]);
	}

	SDL_Window *sdlwindow = SDL_CreateWindow(windowName, windowWidth, windowHeight, windowFlags);
	if (!sdlwindow)
	{
		napi_throw_error(env, "SDL3.Error", SDL_GetError());
		return NULL;
	}

	napi_wrap(env, window, sdlwindow, sdl3ts_window_free, NULL, NULL);

	napi_value val;
	argc = 1;
	argv[0] = window;
	napi_new_instance(env, rendererClass, argc, argv, &val);
	napi_set_named_property(env, window, "renderer", val);

	return window;
}

void export_renderer(napi_env env, napi_value exports);

void export_window(napi_env env, napi_value exports)
{
	napi_define_class(env, "Window", 0, &sdl3ts_window_init, NULL, 0, NULL, &windowClass);
	napi_set_named_property(env, exports, "Window", windowClass);
	export_renderer(env, exports);
}