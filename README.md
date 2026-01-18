# SDL3ts

> [!warning] Work In Progress  
> Any version prioir to `1.0.0` is going to be **unready** for production use.

SDL3 Binding library built for the Bun runtime.

```ts
// index.ts
import SDL3 from "sdl3ts";

SDL3.init({
	video: true,
});

const win = new SDL3.Window();

let done = false;
while (!done) {
	var event;
	while ((event = SDL3.pollEvent())) {
		if (event.type == SDL3.EventType.Quit) done = true;
	}

	// Do game logic, etc.
	win.renderer.present();
	await Bun.sleep(1);
}
```
