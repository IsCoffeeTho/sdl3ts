import type { Pointer } from "../native";
import { sdl3_native } from "../sdl3";
import Renderer from "../renderer/renderer";

(global as any).sdl_windows = <Window[]>[];

const WindowFlags = {
	fullscreen: 0x1,
	opengl: 0x2,
	occluded: 0x4,
	hidden: 0x8,
	borderless: 0x10,
	resizable: 0x20,
	minimized: 0x40,
	maximized: 0x80,
	mouse_grabbed: 0x100,
	input_focus: 0x200,
	mouse_focus: 0x400,
	external: 0x800,
	modal: 0x1000,
	high_pixel_density: 0x2000,
	mouse_capture: 0x4000,
	mouse_relative_mode: 0x8000,
	always_on_top: 0x10000,
	utility: 0x20000,
	tooltip: 0x40000,
	popup_menu: 0x80000,
	keyboard_grabbed: 0x100000,
	fill_document: 0x200000,
	vulkan: 0x400000,
	metal: 0x800000,
	transparent: 0x1000000,
	not_focusable: 0x2000000,
};

type WindowFlagOptions = { [K in keyof typeof WindowFlags]?: boolean };

export default class Window {
	private _ptr: Pointer<Window> = null;
	public readonly renderer: Renderer;
	constructor(options?: {
		name?: string;
		width?: number;
		height?: number;
	} & WindowFlagOptions) {
		let window_flag: number = 0;

		if (options)
			for (var flag in WindowFlags) {
				if ((<any>options)[flag]) window_flag |= WindowFlags[<keyof typeof WindowFlags>flag];
			}

		this._ptr = sdl3_native.SDL_CreateWindow(options?.name ?? "sdl3ts window", options?.width ?? 800, options?.height ?? 600, window_flag);
		if (this._ptr == null)
			throw sdl3_native.SDL_GetError();
		
		this.renderer = new Renderer(this);

		process.on("beforeExit", () => {
			this.close();
		});
		
		((global as any).sdl_windows as Window[]).push(this);
	}
	
	close() {
		if (this._ptr != null) {
			sdl3_native.SDL_DestroyWindow(this._ptr);
			this._ptr = null;
		}
		this.renderer.destroy();
		var globalIndex = ((global as any).sdl_windows as Window[]).findIndex(v => v == this);
		if (globalIndex != -1)
			((global as any).sdl_windows as Window[]).splice(globalIndex, 1);
	}
}