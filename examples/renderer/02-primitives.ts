import { Point, Rect, SDL3, SDLEventType } from "../../src/sdl3";

SDL3.Init({
	video: true,
});

const window = new SDL3.Window({
	width: 640,
	height: 480
});
const renderer = window.renderer;

let rect = new Rect();

let points: Point[] = [];

for (let i = 0; i < 500; i++) {
	points[i] = new Point((Math.random() * 440) + 100, (Math.random() * 280) + 100);
}

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDLEventType.Quit) break;
	}

	renderer.setDrawColor(33, 33, 33);
	renderer.clear();
	
	renderer.setDrawColor(0, 0, 255);
	rect.x = rect.y = 100;
    rect.w = 440;
	rect.h = 280;
	renderer.fillRect(rect);
	
	renderer.setDrawColor(255, 0, 0);
	renderer.points(points);
	
	renderer.setDrawColor(0, 255, 0);
	rect.x += 30;
    rect.y += 30;
    rect.w -= 60;
    rect.h -= 60;
	renderer.rect(rect);
	
	renderer.setDrawColor(255, 255, 0);
	renderer.line(0, 0, 640, 480);
	renderer.line(0, 480, 640, 0);

	renderer.present();
	await Bun.sleep(1);
}
