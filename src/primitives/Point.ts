import type Rect from "./Rect";

export default class Point {
	constructor(
		public x: number = 0,
		public y: number = 0,
	) {
		 
	}
	
	inRect(rect: Rect): boolean {
		if (this.x < rect.x) return false;
		if (this.y < rect.y) return false;
		if (this.x > rect.x + rect.w) return false;
		if (this.y > rect.y + rect.h) return false;
		return true;
	}
}
