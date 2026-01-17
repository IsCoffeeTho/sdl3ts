import SDL3 from "sdl3ts";

SDL3.init({
	video: true,
});

const WINDOW_WIDTH = 640;
const WINDOW_HEIGHT = 480;

const window = new SDL3.Window({
	width: 640,
	height: 480,
});
const renderer = window.renderer;

const rects: SDL3.Rect[] = [];

for (var i = 0; i < 16; i++) {
	rects[i] = new SDL3.Rect();
}

let runLoop = true;
while (runLoop) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) runLoop = false;
	}

	const now = Date.now();

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();

	const direction = now % 2000 >= 1000 ? 1.0 : -1.0;
	const scale = (((now % 1000) - 500) / 500) * direction;

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();

	let rect = <SDL3.Rect>rects[0];

	rect.x = rect.y = 100;
	rect.w = rect.h = 100 + 100 * scale;
	renderer.setDrawColor(255, 0, 0);
	renderer.drawRect(rect);

	for (i = 0; i < 3; i++) {
		const size = (i + 1) * 50.0;
		let rect = <SDL3.Rect>rects[i];
		rect.w = rect.h = size + size * scale;
		rect.x = (WINDOW_WIDTH - rect.w) / 2;
		rect.y = (WINDOW_HEIGHT - rect.h) / 2;
	}
	renderer.setDrawColor(0, 255, 0);
	renderer.drawRects(rects.slice(0, 3));

	rect.x = 400;
	rect.y = 50;
	rect.w = 100 + 100 * scale;
	rect.h = 50 + 50 * scale;
	renderer.setDrawColor(0, 0, 255);
	renderer.fillRect(rect);

	for (i = 0; i < rects.length; i++) {
		const w = WINDOW_WIDTH / rects.length;
		const h = i * 8.0;
		let rect = <SDL3.Rect>rects[i];
		rect.x = i * w;
		rect.y = WINDOW_HEIGHT - h;
		rect.w = w;
		rect.h = h;
	}
	renderer.setDrawColor(255, 255, 255);
	renderer.fillRects(rects);

	renderer.present();
	await Bun.sleep(1);
}
