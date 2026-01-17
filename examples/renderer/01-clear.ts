import SDL3 from "sdl3ts";

SDL3.init({
	video: true,
});

const window = new SDL3.Window({
	name: "01 - clear",
});

// console.log(window);

const start = Date.now();

let runLoop = true;
while (runLoop) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) runLoop = false;
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
