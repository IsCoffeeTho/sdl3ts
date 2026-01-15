/// <reference path="sdl3.d.ts" />

const sdl3ts = (() => require(`${__dirname}/build/Release/sdl3ts.node`))();	

export { sdl3ts as "SDL3" };