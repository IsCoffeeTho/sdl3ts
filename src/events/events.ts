import { sdl3_native } from "../sdl3";
import type { SDLScancode } from "./scancodes";
import { SDLKeycode, SDLKeymod } from "./keycodes";

export enum SDLEventType {
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
	Private0 = 0x4000,
	Private1,
	Private2,
	Private3,
}

export type SDLCommonEvent<T extends SDLEventType> = {
	type: T;
	timestamp: bigint;
};

export type CommonEvent = SDLCommonEvent<SDLEventType.Quit>;

export type DisplayEvent = SDLCommonEvent<
	| SDLEventType.DisplayOrientation
	| SDLEventType.DisplayAdded
	| SDLEventType.DisplayRemoved
	| SDLEventType.DisplayMoved
	| SDLEventType.DisplayDesktopModeChanged
	| SDLEventType.DisplayCurrentModeChanged
	| SDLEventType.DisplayContentScaleChanged
	| SDLEventType.DisplayUsableBoundsChanged
> & {
	displayId: number;
	data1: number;
	data2: number;
};

export type WindowEvent = SDLCommonEvent<
	| SDLEventType.WindowShown
	| SDLEventType.WindowHidden
	| SDLEventType.WindowExposed
	| SDLEventType.WindowMoved
	| SDLEventType.WindowResized
	| SDLEventType.WindowPixelSizeChanged
	| SDLEventType.WindowMetalViewResized
	| SDLEventType.WindowMinimized
	| SDLEventType.WindowMaximized
	| SDLEventType.WindowRestored
	| SDLEventType.WindowMouseEnter
	| SDLEventType.WindowMouseLeave
	| SDLEventType.WindowFocusGained
	| SDLEventType.WindowFocusLost
	| SDLEventType.WindowCloseRequested
	| SDLEventType.WindowHitTest
	| SDLEventType.WindowIccprofChanged
	| SDLEventType.WindowDisplayChanged
	| SDLEventType.WindowDisplayScaleChanged
	| SDLEventType.WindowSafeAreaChanged
	| SDLEventType.WindowOccluded
	| SDLEventType.WindowEnterFullscreen
	| SDLEventType.WindowLeaveFullscreen
	| SDLEventType.WindowDestroyed
	| SDLEventType.WindowHdrStateChanged
> & {
	windowId: number;
	data1: number;
	data2: number;
};

export type KeyboardDeviceEvent = SDLCommonEvent<SDLEventType.KeyboardAdded | SDLEventType.KeyboardRemoved> & { which: number };

export type KeyboardEvent = SDLCommonEvent<SDLEventType.KeyDown | SDLEventType.KeyUp> & {
	windowId: number;
	which: number;
	scancode: SDLScancode;
	key: number;
	mod: number;
	raw: number;
	down: boolean;
	repeat: boolean;
};

export type KboardEvent = KeyboardDeviceEvent | KeyboardEvent | TextEditingEvent | TextEditingCandidatesEvent;

export type TextEditingEvent = SDLCommonEvent<SDLEventType.TextEditing> & {
	windowId: number;
	text: string;
	start: number;
	length: number;
};

export type TextEditingCandidatesEvent = SDLCommonEvent<SDLEventType.TextEditingCandidates> & {
	windowId: number;
	candidates: string[];
	selected_candidate: number;
	horizontal: boolean;
};

export type MouseDeviceEvent = SDLCommonEvent<SDLEventType.MouseAdded | SDLEventType.MouseRemoved> & { which: number };

export type MouseMotionEvent = SDLCommonEvent<SDLEventType.MouseMotion> & {
	windowId: number;
	which: number;
	buttons: {
		left: boolean;
		middle: boolean;
		right: boolean;
		X1: boolean;
		X2: boolean;
	};
	x: number;
	y: number;
	xrel: number;
	yrel: number;
};

export type MouseButtonEvent = SDLCommonEvent<SDLEventType.MouseButtonUp | SDLEventType.MouseButtonDown> & {
	windowId: number;
	which: number;
	button: number;
	down: boolean;
	clicks: number;
	x: number;
	y: number;
};

export type MouseWheelEvent = SDLCommonEvent<SDLEventType.MouseWheel> & {
	windowId: number;
	which: number;
	x: number;
	y: number;
	inverted: boolean;
	mouse_x: number;
	mouse_y: number;
	integer_x: number;
	integer_y: number;
};

export type MouseEvent = MouseDeviceEvent | MouseMotionEvent | MouseButtonEvent | MouseWheelEvent;

export type JoyAxisEvent = SDLCommonEvent<SDLEventType.JoystickAxisMotion> & {
	which: number;
	axis: number;
	value: number;
};

export type JoyBallEvent = SDLCommonEvent<SDLEventType.JoystickBallMotion> & {
	which: number;
	ball: number;
	xrel: number;
	yrel: number;
};

export type JoyHatEvent = SDLCommonEvent<SDLEventType.JoystickHatMotion> & {
	which: number;
	hat: number;
	value: number;
};

export type JoyButtonEvent = SDLCommonEvent<SDLEventType.JoystickButtonDown | SDLEventType.JoystickButtonUp> & {
	which: number;
	button: number;
	down: boolean;
};

export type JoyDeviceEvent = SDLCommonEvent<SDLEventType.JoystickAdded | SDLEventType.JoystickRemoved | SDLEventType.JoystickUpdateComplete> & {
	which: number;
};

export enum JoyBatteryState {
	Error = -1,
	Unknown,
	OnBattery,
	NoBattery,
	Charging,
	Charged,
}

export type JoyBatteryEvent = SDLCommonEvent<SDLEventType.JoystickAdded | SDLEventType.JoystickRemoved | SDLEventType.JoystickUpdateComplete> & {
	which: number;
	state: JoyBatteryState;
	percent: number;
};

export type JoystickEvent = JoyAxisEvent | JoyBallEvent | JoyHatEvent | JoyButtonEvent | JoyDeviceEvent | JoyBatteryEvent;

export type SDLEvent = CommonEvent | DisplayEvent | WindowEvent | KboardEvent | MouseEvent | JoystickEvent;

export function PollEvent(): SDLEvent | undefined {
	var event = sdl3_native.SDL_PollEvent();
	if (event) event.name = SDLEventType[event.type];
	return event;
}
