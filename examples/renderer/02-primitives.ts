import SDL3 from "sdl3ts";

SDL3.init({
	video: true,
});

const window = new SDL3.Window({
	name: "02 - primitives",
	width: 640,
	height: 480,
});

let rect = new SDL3.Rect();

let points: SDL3.Point[] = [];

for (let i = 0; i < 500; i++) {
	points[i] = new SDL3.Point(Math.random() * 440 + 100, Math.random() * 280 + 100);
}

let runLoop = true;
while (runLoop) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) runLoop = false;
	}

	window.renderer.setDrawColor(33, 33, 33);
	window.renderer.clear();

	window.renderer.setDrawColor(0, 0, 255);
	rect.x = rect.y = 100;
	rect.w = 440;
	rect.h = 280;
	window.renderer.fillRect(rect);

	window.renderer.setDrawColor(255, 0, 0);
	window.renderer.drawPoints(points);

	window.renderer.setDrawColor(0, 255, 0);
	rect.x += 30;
	rect.y += 30;
	rect.w -= 60;
	rect.h -= 60;
	window.renderer.drawRect(rect);

	window.renderer.setDrawColor(255, 255, 0);
	window.renderer.line(0, 0, 640, 480);
	window.renderer.line(0, 480, 640, 0);

	window.renderer.present();
	await Bun.sleep(1);
}
