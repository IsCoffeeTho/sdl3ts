import type Point from "./Points";

export default class Rect {
	constructor(
		public x: number = 0,
		public y: number = 0,
		public w: number = 0,
		public h: number = 0,
	) {}

	enclosePoints(points: Point[]) {
		var maximal = { x: -Infinity, y: -Infinity };
		var minimal = { x: Infinity, y: Infinity };
		for (var point of points) {
			if (point.x < minimal.x) minimal.x = point.x;
			if (point.y < minimal.y) minimal.y = point.y;
			if (point.x > maximal.x) maximal.x = point.x;
			if (point.y > maximal.y) maximal.y = point.y;
		}
		this.x = minimal.x;
		this.y = minimal.y;
		this.w = maximal.x - minimal.x;
		this.h = maximal.y - minimal.y;
	}

	empty() {
		return this.w == 0 || this.h == 0;
	}
}
