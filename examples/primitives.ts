import { SDL3, SDLEventType } from "../src/sdl3";

SDL3.Init({
	video: true,
});

const window = new SDL3.Window();

while (true) {
	var event = SDL3.PollEvent();
	if (event) {
		if (event.type == SDLEventType.Quit)
			break;
		console.log(event);
	}
	window.renderer.setDrawColor(33,33,33);
	
	window.renderer.clear();
	window.renderer.present();
	await Bun.sleep(1);
}
