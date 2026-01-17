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

var texture_width: number = 0;
var texture_height: number = 0;
var texture: SDL3.Texture;

{
	let surface = SDL3.Surface.loadPNG(`${__dirname}/resources/sample.png`);
	texture_width = surface.w;
	texture_height = surface.h;
	texture = surface.toTexture();
	// surface should drop
}

const dst_rect = new SDL3.Rect();

let runLoop = true;
while (runLoop) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) runLoop = false;
	}
	const now = Date.now();

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();

	const direction = now % 2000 >= 1000 ? 1 : -1;
	const scale = (((now % 1000) - 500) / 500) * direction;

	dst_rect.x = 100 * scale;
	dst_rect.y = 0;
	dst_rect.w = texture_width;
	dst_rect.h = texture_height;
	renderer.drawTexture(texture, null, dst_rect);

	renderer.present();
	await Bun.sleep(1);
}
