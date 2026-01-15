# SDL3ts

> [!warning] Work In Progress  
> Any version prioir to `1.0.0` is going to be **unready** for production use.

SDL3 Binding library built for the Bun runtime.

```ts
// index.ts
import { SDL3 } from "sdl3ts";

SDL3.Init({
	video: true,
});

const win = new SDL3.Window();
const rndr = win.renderer;

while (true) {
	var event = SDL3.PollEvent();
	if (event && event.type == SDL3.EventType.Quit) break;

	window.renderer.setDrawColor(0, 0, 0);
	window.renderer.clear();

	window.renderer.present();
	await Bun.sleep(1);
}
```
