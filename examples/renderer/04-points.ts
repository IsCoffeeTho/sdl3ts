import SDL3 from "sdl3ts";

SDL3.init({
	video: true,
});

const WINDOW_WIDTH = 640;
const WINDOW_HEIGHT = 480;
const MIN_PIXELS_PER_SECOND = 30;
const MAX_PIXELS_PER_SECOND = 60;

const NUM_POINTS = 500;

const window = new SDL3.Window({
	width: WINDOW_WIDTH,
	height: WINDOW_HEIGHT,
});
const renderer = window.renderer;

let points: SDL3.Point[] = [];
let point_speeds: number[] = [];

for (let i = 0; i < NUM_POINTS; i++) {
	points[i] = new SDL3.Point(Math.random() * WINDOW_WIDTH, Math.random() * WINDOW_HEIGHT);
	point_speeds[i] = MIN_PIXELS_PER_SECOND + Math.random() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND);
}

let last_time = Date.now();

let runLoop = true;
while (runLoop) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) runLoop = false;
	}

	const now = Date.now();
	const elapsed = (now - last_time) / 1000;
	for (let i = 0; i < NUM_POINTS; i++) {
		const distance = elapsed * <number>point_speeds[i];
		const point = <SDL3.Point>points[i];
		point.x += distance;
		point.y += distance;
		if (point.x >= WINDOW_WIDTH || point.y >= WINDOW_HEIGHT) {
			/* off the screen; restart it elsewhere! */
			if (Math.random() > 0.5) {
				point.x = Math.random() * WINDOW_WIDTH;
				point.y = 0;
			} else {
				point.x = 0;
				point.y = Math.random() * WINDOW_HEIGHT;
			}
			point_speeds[i] = MIN_PIXELS_PER_SECOND + Math.random() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND);
		}
	}

	last_time = now;

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();
	renderer.setDrawColor(255, 255, 255);
	renderer.drawPoints(points);

	renderer.present();
	await Bun.sleep(1);
}
