{
	"targets": [
		{
			"target_name": "sdl3ts",
			"sources": [
				"./src/sdl3ts.c",
				"./src/plumbing/instancing.c",
				"./src/plumbing/pointer.c",
				"./src/events/events.c",
				"./src/window/window.c",
				"./src/renderer/renderer.c",
				"./src/primitives/Rect.c",
				"./src/primitives/Point.c"
			],
			"cflags": [
				"-Wall",
				"-Werror",
				"-Wextra"
			],
			"libraries": [
				"-lSDL3"
			]
		}
	]
}