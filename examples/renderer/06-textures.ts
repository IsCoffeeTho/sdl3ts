import * as SDL3 from "../../sdl3";

SDL3.Init({
	video: true,
});

const WINDOW_WIDTH = 640;
const WINDOW_HEIGHT = 480;

const window = new SDL3.Window({
	width: 640,
	height: 480,
});
const renderer = window.renderer;

let texture_width: number = 0;
let texture_height: number = 0;
let texture: SDL3.Texture;

function begin() {
	let surface = SDL3.Surface.loadPNG(`${__dirname}/resources/sample.png`);
	texture_width = surface.w;
	texture_height = surface.h;
	texture = surface.toTexture();
}
begin();

const dst_rect = new SDL3.Rect();

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDL3.EventType.Quit) break;
	}
	const now = Date.now();

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();

	const direction = ((now % 2000) >= 1000) ? 1 : -1;
    const scale = ((((now % 1000)) - 500) / 500) * direction;
    
    dst_rect.x = (100 * scale);
    dst_rect.y = 0;
    dst_rect.w = texture_width;
    dst_rect.h = texture_height;
    renderer.texture(texture, null, dst_rect);

	renderer.present();
	await Bun.sleep(1);
}
