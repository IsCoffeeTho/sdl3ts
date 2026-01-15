/**
 * Simple DirectMedia Layer 3 API
 * ```ts
 * // index.ts
 * import {SDL3} from "sdl3ts";
 *
 * SDL3.Init({
 *   video: true
 * });
 *
 * const win = new SDL3.Window();
 * const rndr = win.renderer;
 *
 * while (true) {
 *   var event = SDL3.PollEvent();
 *   if (event) {
 *     if (event.type == SDL3.EventType.Quit)
 *       break;
 *   }
 *
 *   window.renderer.setDrawColor(0, 0, 0);
 *   window.renderer.clear();
 *
 *   window.renderer.present();
 *   await Bun.sleep(1);
 * }
 * ```
 */
declare module "SDL3" {
	/**
	 * Initialization flags for
	 * {@linkcode init}`(options: InitFlags)` and/or
	 * {@linkcode initSubSystem}`(options: InitFlags)`
	 */
	type InitFlags = {
		/** `audio` implies `events` */
		audio?: boolean;
		/** `video` implies `events`, should be initialized on the main thread. */
		video?: boolean;
		/** `joystick` implies `events` */
		joystick?: boolean;
		haptic?: boolean;
		/** `gamepad` implies `joystick` */
		gamepad?: boolean;
		events?: boolean;
		/** `sensor` implies `events` */
		sensor?: boolean;
		/** `camera` implies `events` */
		camera?: boolean;
	};
	/**
	 * Compatibility function to initialize the SDL Library.
	 *
	 * @see {@linkcode InitFlags}
	 */
	function initSubSystem(options: InitFlags): void;
	/**
	 * Initialize the SDL Library.
	 *
	 * @see {@linkcode InitFlags}
	 */
	function init(options: InitFlags): void;
	/**
	 * Clean up all initialized subsystems.
	 * > This gets called under the hood before an application closes
	 */
	function quit(): void;
	/**
	 * Shut down specific SDL subsystems.
	 * > System calls `SDL3.`{@linkcode quit}`()` before application closes
	 *
	 * @see {@linkcode InitFlags}
	 */
	function quitSubSystem(options: InitFlags): void;
	
	enum EventType {
		
	}
	
	type CommonEvent<T extends EventType> = {
		type: T,
		name: EventType[T],
		timestamp: bigint,
	};
	
	type Event = ;
	
	/**
	 * Poll for currently pending events.
	 */
	function PollEvent(): Event;
}
