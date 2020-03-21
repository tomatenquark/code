# Cube 2: Tomatenquark

First of all, welcome to Cube 2: Tomatenquark! To start off, if you are looking for help with the game itself, refer to the [Documentation](https://tomatenquark.org). Here are some places of interest on the internet, which are related to Cube / Cube 2: Tomatenquark.

## Build instructions

You can find the build instructions in [BUILD.md](./BUILD.md).

## Links

- [Cube and Cube 2 Engines](http://cubeengine.com/): Start Page for the Cube Engine series.
- [Cube 2: Sauerbraten](http://sauerbraten.org): The Sauerbraten FPS (First Person Shooter) Homepage.
- [Quadropolis](http://quadropolis.us/): Online Cube Engine community, with user made maps, mods, and scripts.
- [Cube Wiki](http://cubeengine.com/wiki/Main_Page) Cube Wiki has a lot of useful information for working with the game and engine, contributed by the community which elaborates and breaks alot of the information down into more digestable chunks

## Current Features

Cube 2: Tomatenquark is an open source project derived from Cube 2: Sauerbraten, and maintains constant development, yet it is very feature-rich and playable as a game. What follows is a list of the most prominent features.

### Game Features

- Oldskool fast & intense gameplay (read: similar to Doom 2 / Quake 1).
- Many multiplayer gameplay modes, most in teamplay variants as well: deathmatch, instagib, efficiency, tactics, capture (domination/battlefield style), CTF (capture the flag), coop edit (!).
- Masterserver & ingame server browser.
- Lag-free gameplay experience.
- Two singleplayer modes: DMSP (fight a monster invasion on any DM map), classic SP (progression driven SP like other games)
- 7 weapons tuned for maximum satisfaction: double barrelled shogun, rocket launcher, machine gun, rifle, grenade launcher, pistol, fist.

### Engine Features

- 6 directional heightfield in octree world structure allowing for instant easy in-game geometry editing (even in multiplayer, coop edit).
- Rendering engine optimized for high geometry throughput, supporting hardware occlusion culling and software precomputed conservative PVS with occluder fusion.
- Lightmap based lighting with accurate shadows from everything including mapmodels, smooth lighting for faceted geometry, and fast compiles. Soft shadowmap based shadows for dynamic entities.
- Pixel and vertex shader support, each model and world texture can have its own shader assigned. Supports normal and parallax mapping, specular and dynamic lighting with bloom and glow, environment-mapped and planar reflections/refractions, and post-process effects.
- Robust physics written specifically for this world structure.
- Loading of md2/md3/md5/obj/smd/iqm models for skeletal and vertex animated characters, weapons, items, and world objects. Supports animation blending, procedural pitch animation, and ragdoll physics for skeletally-animated characters.
- Network library designed for high speed games, client/server network system.
- Small but complete configuration/scripting language.
- Simple stereo positional sound system.
- Particle engine, supporting text particles, volumetric explosions, soft particles, and decals.
- 3d menu/gui system, for in-world representation of choices.

### Additional developer documentation

- [Notes about historical development of the Cube engine](http://svn.code.sf.net/p/sauerbraten/code/docs/dev/readme_developer.txt)
- [Notes about potential implementations](http://svn.code.sf.net/p/sauerbraten/code/docs/dev/wikistuff.html) in Cube 2: Sauerbraten
