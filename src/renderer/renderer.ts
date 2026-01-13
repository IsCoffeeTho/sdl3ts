import type { Pointer } from "../native";
import type Point from "../primitives/Point";
import { Rect, sdl3_native } from "../sdl3";
import type Window from "../window/window";

export default class Renderer {
	private _ptr: Pointer = null;
	constructor(public readonly window: Window) {
		// @ts-ignore
		this._ptr = sdl3_native.SDL_CreateRenderer(window._ptr);
		if (this._ptr == null) throw sdl3_native.SDL_GetError();

		process.on("beforeExit", () => {
			this.destroy();
		});
	}

	/**
	 * Set the color used for drawing operations.
	 * Set the color for drawing or filling rectangles, lines, and points, and for `Renderer.clear()`.
	 *
	 * @param r {number} `0.0 - 1.0` the red value used to draw on the rendering target.
	 * @param g {number} `0.0 - 1.0` the green value used to draw on the rendering target.
	 * @param b {number} `0.0 - 1.0` the blue value used to draw on the rendering target.
	 * @param a {number?} `0.0 - 1.0` the alpha (opacity) value used to draw on the rendering target.
	 */
	setDrawColorNormal(r: number, g: number, b: number, a: number = 1) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_SetRenderDrawColorFloat(this._ptr, r, g, b, a);
	}

	/**
	 * Set the color used for drawing operations.
	 * Set the color for drawing or filling rectangles, lines, and points, and for `Renderer.clear()`.
	 *
	 * @param r {number} `0 - 255` the red value used to draw on the rendering target.
	 * @param g {number} `0 - 255` the green value used to draw on the rendering target.
	 * @param b {number} `0 - 255` the blue value used to draw on the rendering target.
	 * @param a {number?} `0 - 255` the alpha (opacity) value used to draw on the rendering target.
	 */
	setDrawColor(r: number, g: number, b: number, a: number = 255) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_SetRenderDrawColor(this._ptr, r, g, b, a);
	}

	fillRect(rect: Rect) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderFillRect(this._ptr, rect);
	}
	fillRects(rects: Rect[]) {
		if (this._ptr == null) new Error("Use after free");
		for (var rect of rects) sdl3_native.SDL_RenderFillRect(this._ptr, rect);
	}
	rect(rect: Rect) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderRect(this._ptr, rect);
	}
	rects(rects: Rect[]) {
		if (this._ptr == null) new Error("Use after free");
		for (var rect of rects) sdl3_native.SDL_RenderRect(this._ptr, rect);
	}

	line(x1: number, y1: number, x2: number, y2: number) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderLine(this._ptr, x1, y1, x2, y2);
	}
	/**
	 * @todo Implement native version
	 */
	lines(line_points: Point[]) {
		if (this._ptr == null) new Error("Use after free");
		var prevPoint: Point | undefined;
		for (var point of line_points) {
			if (prevPoint) sdl3_native.SDL_RenderLine(this._ptr, point.x, point.y, prevPoint.x, prevPoint.y);
			prevPoint = point;
		}
	}

	point(point: Point) {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderPoint(this._ptr, point);
	}
	/**
	 * @todo Implement native version
	 */
	points(points: Point[]) {
		if (this._ptr == null) new Error("Use after free");
		for (var point of points) sdl3_native.SDL_RenderPoint(this._ptr, point);
	}

	/**/
	clear() {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderClear(this._ptr);
	}

	present() {
		if (this._ptr == null) new Error("Use after free");
		sdl3_native.SDL_RenderPresent(this._ptr);
	}

	destroy() {
		if (this._ptr != null) {
			sdl3_native.SDL_DestroyRenderer(this._ptr);
			this._ptr = null;
		}
	}
}
