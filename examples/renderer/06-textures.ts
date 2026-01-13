import {  SDL3, SDLEventType } from "../../src/sdl3";

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

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDLEventType.Quit) break;
	}

	const now = Date.now();

	renderer.setDrawColor(0, 0, 0);
	renderer.clear();

	

	renderer.present();
	await Bun.sleep(1);
}
