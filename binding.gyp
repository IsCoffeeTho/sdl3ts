{
	"targets": [
		{
			"target_name": "sdl3ts",
			"sources": [
				"./src/sdl3ts.c",
				"./src/plumbing/instancing.c",
				"./src/plumbing/types.c",
				"./src/events/events.c",
				"./src/window/window.c",
				"./src/renderer/renderer.c"
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