{
	"targets": [
		{
			"target_name": "sdl3ts",
			"sources": [
				"./src/sdl3ts.c",
				"./src/main.c",
				"./src/debug.c",
				"./src/events/pollEvent.c",
				"./src/primitives/Point.c",
				"./src/primitives/Rect.c",
				"./src/video/window.c",
				"./src/video/renderer.c"
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