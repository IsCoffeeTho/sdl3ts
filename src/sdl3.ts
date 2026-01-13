import { PollEvent, SDLEventType, type SDLEvent } from "./events/events";
import Window from "./window/window";
import Rect from "./primitives/Rect";
import Point from "./primitives/Point";

export const sdl3_native = (() => require("../build/Release/sdl3ts.node"))();

export { SDLEventType, type SDLEvent, Rect, Point};

export const SDL3 = {
	Init(options?: {
		timer?: boolean;
		audio?: boolean;
		/** video implies events */
		video?: boolean;
		/** joystick implies events */
		joystick?: boolean;
		haptic?: boolean;
		/** gameController implies events */
		gameController?: boolean;
		events?: boolean;
		sensor?: boolean;
	}) {
		let init_flag: number = 0;

		init_flag |= options?.timer ? 0x01 : 0;
		init_flag |= options?.audio ? 0x10 : 0;
		init_flag |= options?.video ? 0x20 : 0;
		init_flag |= options?.joystick ? 0x200 : 0;
		init_flag |= options?.haptic ? 0x1000 : 0;
		init_flag |= options?.gameController ? 0x2000 : 0;
		init_flag |= options?.events ? 0x4000 : 0;
		init_flag |= options?.sensor ? 0x8000 : 0;

		if (!sdl3_native.SDL_Init(init_flag)) throw sdl3_native.SDL_GetError();

		process.on("beforeExit", () => {
			sdl3_native.SDL_Quit();
		});
	},
	PollEvent,
	Window,
};
