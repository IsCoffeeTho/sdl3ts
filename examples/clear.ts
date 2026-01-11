import { SDL3, SDLEventType } from "../src/sdl3";

SDL3.Init({
	video: true,
});

const window = new SDL3.Window();
const start = Date.now();

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDLEventType.Quit)
			break;
	}
	const now = (Date.now() - start) / 1000;

	const red = 0.5 + 0.5 * Math.sin(now);
	const green = 0.5 + 0.5 * Math.sin(now + (Math.PI * 2) / 3);
	const blue = 0.5 + 0.5 * Math.sin(now + (Math.PI * 2) / 4);
	
	window.renderer.setDrawColorNormal(red, green, blue);
	window.renderer.clear();
	window.renderer.present();
	await Bun.sleep(1);
}
