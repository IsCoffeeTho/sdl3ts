/**
 * Simple DirectMedia Layer 3 API
 * ```ts
 * // index.ts
 * import SDL3 from "sdl3ts";
 *
 * SDL3.init({
 *   video: true
 * });
 *
 * const win = new SDL3.Window();
 *
 * let done = false;
 * while (!done) {
 *   var event;
 *   while ((event = SDL3.pollEvent())) {
 *     if (event.type == SDL3.EventType.Quit)
 *       done = true;
 *   }
 *
 *   // Do game logic, etc.
 *
 *   win.renderer.present();
 *   await Bun.sleep(1);
 * }
 * ```
 */
declare module "sdl3ts" {
	/**
	 * Initialization flags for
	 * {@linkcode init}`(options: InitFlags)` and/or
	 * {@linkcode initSubSystem}`(options: InitFlags)`
	 */
	type InitFlags = {
		audio?: boolean;

		video?: boolean;

		joystick?: boolean;
		haptic?: boolean;

		gamepad?: boolean;
		events?: boolean;

		sensor?: boolean;

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

	class Rect {
		constructor(x?: number, y?: number, w?: number, h?: number);
		x: number;
		y: number;
		w: number;
		h: number;
	}

	class Point {
		constructor(x?: number, y?: number);
		x: number;
		y: number;
	}

	/**
	 * Create a window with the specified dimensions and settings.
	 */
	class Window {
		constructor(options?: {
			name?: string;
			width?: number;
			height?: number;
			fullscreen?: boolean;
			opengl?: boolean;
			occluded?: boolean;
			hidden?: boolean;
			borderless?: boolean;
			resizable?: boolean;
			minimized?: boolean;
			maximised?: boolean;
			mouseGrabbed?: boolean;
			inputFocus?: boolean;
			mouseFocus?: boolean;
			external?: boolean;
			modal?: boolean;
			highPixelDensity?: boolean;
			mouseCaptured?: boolean;
			mouseRelativeMode?: boolean;
			alwaysOnTop?: boolean;
			utility?: boolean;
			tooltip?: boolean;
			popupMenu?: boolean;
			keyboardGrabbed?: boolean;
			fillDocument?: boolean;
			vulkan?: boolean;
			metal?: boolean;
			transparent?: boolean;
			notFocusable?: boolean;
		});
		readonly renderer: Renderer;
	}

	/**
	 *
	 */
	interface Renderer {
		readonly window: Window;

		setDrawColor(r: number, g: number, b: number, a?: number);
		setDrawColorNormal(r: number, g: number, b: number, a?: number);

		drawRect(rect: Rect);
		drawRects(rects: Rect[]);
		
		fillRect(rect: Rect);
		fillRects(rects: Rect[]);

		drawPoint(point: Point);
		drawPoints(points: Point[]);

		line(x1: number, y1: number, x2: number, y2: number);
		lines(path: Point[]);

		clear();
		present();
	}
	
	class Texture {
		
	}
	
	class Surface {
		static loadPNG(path: string): Surface;
		w: number;
		h: number;
		toTexture(): Texture;
	}

	enum EventType {
		Quit = 0x100,
		Terminating,
		LowMemory,
		WillEnterBackground,
		DidEnterBackground,
		WillEnterForeground,
		DidEnterForeground,
		LocaleChanged,
		SystemThemeChanged,
		DisplayOrientation = 0x151,
		DisplayAdded,
		DisplayRemoved,
		DisplayMoved,
		DisplayDesktopModeChanged,
		DisplayCurrentModeChanged,
		DisplayContentScaleChanged,
		DisplayUsableBoundsChanged,
		DisplayFirst = DisplayOrientation,
		DisplayLast = DisplayUsableBoundsChanged,

		WindowShown = 0x202,
		WindowHidden,
		WindowExposed,
		WindowMoved,
		WindowResized,
		WindowPixelSizeChanged,
		WindowMetalViewResized,
		WindowMinimized,
		WindowMaximized,
		WindowRestored,
		WindowMouseEnter,
		WindowMouseLeave,
		WindowFocusGained,
		WindowFocusLost,
		WindowCloseRequested,
		WindowHitTest,
		WindowIccprofChanged,
		WindowDisplayChanged,
		WindowDisplayScaleChanged,
		WindowSafeAreaChanged,
		WindowOccluded,
		WindowEnterFullscreen,
		WindowLeaveFullscreen,
		WindowDestroyed,
		WindowHdrStateChanged,
		WindowFirst = WindowShown,
		WindowLast = WindowHdrStateChanged,

		KeyDown = 0x300,
		KeyUp,
		TextEditing,
		TextInput,
		KeymapChanged,
		KeyboardAdded,
		KeyboardRemoved,
		TextEditingCandidates,
		ScreenKeyboardShown,
		ScreenKeyboardHidden,

		MouseMotion = 0x400,
		MouseButtonDown,
		MouseButtonUp,
		MouseWheel,
		MouseAdded,
		MouseRemoved,

		JoystickAxisMotion = 0x600,
		JoystickBallMotion,
		JoystickHatMotion,
		JoystickButtonDown,
		JoystickButtonUp,
		JoystickAdded,
		JoystickRemoved,
		JoystickBatteryUpdated,
		JoystickUpdateComplete,

		GamepadAxisMotion = 0x650,
		GamepadButtonDown,
		GamepadButtonUp,
		GamepadAdded,
		GamepadRemoved,
		GamepadRemapped,
		GamepadTouchpadDown,
		GamepadTouchpadMotion,
		GamepadTouchpadUp,
		GamepadSensorUpdate,
		GamepadUpdateComplete,
		GamepadSteamHandleUpdated,

		FingerDown = 0x700,
		FingerUp,
		FingerMotion,
		FingerCanceled,

		PinchBegin = 0x710,
		PinchUpdate,
		PinchEnd,

		ClipboardUpdate = 0x900,

		DropFile = 0x1000,
		DropText,
		DropBegin,
		DropComplete,
		DropPosition,

		AudioDeviceAdded = 0x1100,
		AudioDeviceRemoved,
		AudioDeviceFormatChanged,

		SensorUpdate = 0x1200,

		PenProximityIn = 0x1300,
		PenProximityOut,
		PenDown,
		PenUp,
		PenButtonDown,
		PenButtonUp,
		PenMotion,
		PenAxis,

		CameraDeviceAdded = 0x1400,
		CameraDeviceRemoved,
		CameraDeviceApproved,
		CameraDeviceDenied,

		RenderTargetsReset = 0x2000,
		RenderDeviceReset,
		RenderDeviceLost,

		User = 0x8000,
		UserLast = 0xffff,
	}

	type CommonEvent<T extends EventType> = {
		type: T;
		timestamp: bigint;
	};

	type QuitEvent = CommonEvent<EventType.Quit>;

	type Event = QuitEvent;

	function pollEvent(): Event | undefined;
}
export module "sdl3ts";
