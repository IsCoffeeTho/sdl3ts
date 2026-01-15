{
	"targets": [
		{
			"target_name": "sdl3ts",
			"sources": [
				"./src/sdl3ts.c",
				"./src/main.c"
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