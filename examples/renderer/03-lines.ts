import { Point, SDL3, SDLEventType } from "../../src/sdl3";

SDL3.Init({
	video: true,
});

const window = new SDL3.Window({
	width: 640,
	height: 480,
});
const renderer = window.renderer;

const line_points: Point[] = [
	new Point(100, 354),
	new Point(220, 230),
	new Point(140, 230),
	new Point(320, 100),
	new Point(500, 230),
	new Point(420, 230),
	new Point(540, 354),
	new Point(400, 354),
	new Point(100, 354),
];

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDLEventType.Quit) break;
	}

	renderer.setDrawColor(100, 100, 100);
	renderer.clear();

	renderer.setDrawColor(127, 49, 32);
	renderer.line(240, 450, 400, 450);
	renderer.line(240, 356, 400, 356);
	renderer.line(240, 356, 240, 450);
	renderer.line(400, 356, 400, 450);

	renderer.setDrawColor(0, 255, 0);
	renderer.lines(line_points);

	for (let i = 0; i < 360; i++) {
		const size = 30;
		const x = 320;
		const y = 95 - size / 2;
		const r = i * (Math.PI / 180);
		renderer.setDrawColor(Math.random() * 256, Math.random() * 256, Math.random() * 256);
		renderer.line(x, y, x + Math.cos(r) * size, y + Math.sin(r) * size);
	}

	renderer.present();
	await Bun.sleep(1);
}
