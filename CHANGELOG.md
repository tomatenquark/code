# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2020-03-04
## Changed
- No more armor in regen capture
- Use multiple file downloads method to download map resources

## Added
- `showserverhost` which will hide IP and port of servers by default
- `mmodelfile` to indicate resources

## [0.0.23] - 2020-01-04
## Fixed
- fixed lightmaps crashing the game on windows
- fixed path issues with assetbundler on windows
- don't localconnect while the client initializes

## [0.0.22] - 2020-30-03
## Added
- Added `maxhealth` display and colored health display
- Automatically balance spectators as well
- Added WAV scaling so the sound will be improved better (experimental)
- Added `downloadmaps` and `servercontent` variables to send maps

## Changed
- Hold drop penalty has been changed from 2 to 3
- Updated Windows SDL dependency to 2.0.12

## [0.0.21] - 2020-22-03
## Added
- allow jpeg screenshots
- experimental alpha mask support for world geometry
- allow disabling pitch clamping 

## Changed
- Increase flag drop limit to 3
- Replace custom new operators with `<new>`
- Improved spawn system (still WIP)

## Fixed
- prevent hold timer from being stolen by opposing team
- Fix all the `.framework` issues on OSX in order to be able to properly notarize the app

## [0.0.20] - 2020-15-03
## Changed
- Disable `oqwait` by default on GLX 1000 and 2000 series
- Update latest changes from enet (1.3.14)

## [0.0.19] - 2020-14-03
## Added
- Added `collide` to rotation and update packages to `4751da1736fbe2d1d0745f5cbb05d9d17dc2d07e`

## [0.0.18] - 2020-12-03
## Added
- Added `luna` to rotation and update packages to `1c2261e45176e7f4ab7787e0362bd143caa608de`

## [0.0.17] - 2020-12-03
## Changed
- Fix issue where skybox warnings would appear even when a skybox was set in the `map.cfg`

## [0.0.16] - 2020-12-03
## Added
- Introduced `mapmodelwarnings` variable

## [0.0.15] - 2020-08-03
## Changed
- Rename Windows executables to `tomatenquark.exe`
- Rename window handle to `Cube 2: Tomatenquark`

## [0.0.14] - 2020-08-03
## Changed
- Rename OSX App to `tomatenquark.app`

## [0.0.13] - 2020-08-03
## Changed
- Rename unix executables to `tomatenquark_unix` and likes

## [0.0.12] - 2020-08-03
## Added
- Added the `getalltexname` command which is helpful for debugging map problems

## [0.0.11] - 2020-06-03
## Added
- Add Windows x32 binaries as well

## [0.0.10] - 2020-03-03
## Fixed
- Models that are currently not available have been disabled to fix bots spawning with unavailable models

## [0.0.9] - 2020-03-03
## Added
- Package `server-init.cfg` as well

## [0.0.8] - 2020-22-02
## Fixed
- Properly package `sauer_client` as `linux_64_client`

## [0.0.7] - 2020-22-02
## Added
- Package up media content (essential) on GitHub

## [0.0.6] - 2020-22-02
## Fixed
- Package binaries on Ubuntu correctly as well

## [0.0.5] - 2020-22-02
## Changed
- Build in release mode for Windows and OSX (omit development files)

## [0.0.4] - 2020-05-02
### Added
- Added ammobar implementation by Redon

## [0.0.3] - 2020-02-02
### Changed
- Package up `bin64` folder on Windows and more stuff using CD

## [0.0.2] - 2020-01-02
### Fixed
- Fixed issue with the CI failing continuously on Ubuntu due to `apt`

## [0.0.1] - 2020-31-01
### Added
- Import code from revision 5652
- Add continous integration for Windows, OSX and Linux using GitHub Actions
- Add continous deployment for Windows, OSX and Linux using GitHub actions

## 2020 edition

- added new MP maps by Sprite & Crap_I'm_dead (spcr2), Zoocata (asthma, colony, ruebli, zdm2), Nieb (ra), Sheik (cartel, legacy, sandstorm2), Ardelico & Doko & MasterTechCC (antel), HeWho & Nieb (rm1), Fatality (carbide, fallen, fdm6, fire_keep, frag-lab, laucin, luna, mc-lab, pandora, stronghold), 2+2=3 & Luffy & pix (croma), t-chen (duel5), Sheik & Doko (averas), FixxxerSA & Redon (collide), rabe (oldschool, sauerowalk, stahlbox), Pointblank (pariah), shuzo & Redon & Nieb (fusion), Adrelico & Doko (gothic-df), Ardelico (akimiski, asenatra), SATAN!!! (access), Kv (albatross, tectonic), miscreant (exist), Doko & pyccna (toxicity), Gangler (breakout, enigma), Suicizer (aod, lost_soul), Redon (anubis, gorge), Halbgar (hdm3), Doko (waltz), AtlasSteal (insipid), Fatum (abyss, eris, exo, ferguson, fragnostic, hektik, phrantic, regal, zavial), HeWho & nopnotme & Doom32 & Sheik (tatooine), Salatiel (memoria, ventania), Sauce (genesis), Misan & Shuzo & KI113R (turmoil), Mysterious (new_energy), fixxxer (conflict, disruption), Frosty & Nieb (purgatory), pix (bklyn), Gangler & Nieb (souls), 7YearWitch & Sauce & Xadus (clash, earthsea)
- added new SP map by Skur (skrsp1), crun (crnsp1)

## 2013_01_04_collect_edition

- reanimated Ogro (by Geartrooper) with skeletal animation so he supports vweps and ragdolls
- added new MP maps by 4t3one & Snowy (collusion), viruz (subterra), Windecker (alithia), miscreant (turbulence), Suicizer (evilness), sinsch (catch22), flubz0r (hidden), Skur (skrdm1), SuperMan (bvdm_01), Fatum (tumwalk, snapper_rocks, bad_moon, shiva, elegy), Meister & Fatum (mill, asgard, legazzo, teahupoo, gubo), rabe (outpost), Doko & MisanthropX & Nieb (renegade), Nieb & RaZgRiZ & SirAlex & Windecker (garden), Chris_0076 & Nieb & SomeDude (hashi), t-chen (simplicity, fury, mbt4, mbt9, arbana, haste, forgotten), t-chen & RaZgRiZ (mbt12), RaZgRiZ (twinforts), cm|CubicMatter (kopenhagen), Nieb (autumn), ac & Boxx & HeWho (depot), HeWho (rm5), Sprite & Crap_I'm_Dead (spcr), Crap_I'm_Dead (dirtndust), Maycrus & AtlasSteal & HeWho & Somedude & Chris (masdm), Star (sauerstruck), b4lkLu & Chris_0076 (donya), Majikal (siberia), Ardelico & HeWho & Suicizer (force), Snowy (nucleus), Zeronic & HeWho & Cooper (eternal_valley)
- added "collect", "insta collect", and "efficiency collect" game modes
- new weapon sounds by Slawomir 'Q009' Blauciak
- added support for directional sunlight for lightmaps (controlled via "sunlight", "sunlightyaw", "sunlightpitch", and "sunlightscale" vars)
- added "savebrush" and "pastebrush" commands for saving and pasting selected geometry
- added support for up to 4 types of water, lava, and glass materials (using "water2", "lava3", etc. materials)
- added geometry filter modes for "editmat" command ("empty", "notempty", "solid", and "notsolid")
- now uses GLSL as the default rendering path when available (use "forceglsl 0" to use the old assembly shader path if necessary)
- added support for international character sets
- added support for 64-bit Windows builds
- config files and maps are now saved to the My Games directory on Windows
- added auto-update and auto-sort options to the server browser
- made server browser stay open on connect failure
- server browser now displays time remaining for the match on servers
- server now shows up as a system tray icon on Windows
- server now loads entities directly from maps if available
- server may now have multiple masters, auths, and admins at the same time
- server now controls its own map rotation
- server now supports configurable teamkill limits
- increased pistol and grenade damage, and lengthened yellow armour spawn time
- health boost and quad spawn times are no longer randomized
- shortened game times to 10 minutes in all team modes
- players now spawn with blue armour again in FFA
- teammates are now shown on minimap
- team frags are now tracked independently of player frags
- in CTF the same player that dropped a flag may now pick it back up one time, but not twice in a row without a teammate picking it up in between
- teamkilling the flag runner in CTF modes now disallows the teamkiller from picking up the flag (toggled via "ctftkpenalty" var in server-init.cfg)
- team damage no longer contributes to accuracy
- gamehud and edithud may now span multiple lines
- added "hidedead" var to control whether players disappear immediately once killed
- added "restrictpausegame" var for controlling whether need to be admin to use pausegame during multiplayer
- added "restrictdemos" var for controlling whether need to be admin to record a demo and "maxdemos"/"maxdemosize" vars for limiting the number and size of demos
- movie recorder now supports larger than 1 GB files using OpenDML/AVI 2.0
- added "ignore" and "unignore" commands to locally ignore chat from players
- added "-g" command-line option which sets which file console output is logged to
- added support for DDS DXT1/3/5 compressed skyboxes and envmaps
- added simplified IK for pitch animation
- added support for applying transforms to bone tags on skeletal models
- revised internal geometry format to support merging cube faces into convex triangle fans instead of just rectangles
- use premultiplied-alpha for grass textures to avoid darkening around grass outlines
- improved model lighting that preserves contrast on unlit side
- added cubescript recursion limits
- added "local" command to cubescript that allows you to declare local variables
- added cubescript compiler
- added snow particles (particle type 13)
- "lightthreads" and "pvsthreads" vars now default to the estimated number of CPUs when set to 0
- fixed lightmap blurring (controlled via "blurlms" var) at lightmap borders
- normals are now sampled at all t-joints for smoothing rather than speculatively subdividing edges
- improved packing of lightmaps when a cube face has more than one plane
- added "guispring" for creating springs inside a list

## 2010_07_19_justice_edition

- added new player models Inky and Captain Cannon by Geartrooper
- added new MP maps by t-chen & MisanthropX (tempest), MisanthropX & Finn & t-chen (xenon), mIscreant (mercury), Nieb & Geartrooper (justice), Blindabuser & PainKillAH (fc5), KI113R & Redon & SkiingPenguins (alloy), TomekGNO (ruine), Kretren (core_refuge), KaiserTodretter (infamy, desecration), Nieb (bt_falls), viruz (abbey, tortuga), Jonlimle & Argh! & Nieb (injustice), Jonlimle & Nieb & Razgriz (curvy_castle), Nieb & Jonlimle (authentic), t-chen (duel7, duel8, mbt1, mbt2, mbt10, caribbean), MisanthropX & t-chen & Nieb (industry), Fatum (nitro), Vincent (suburb), BlikjeBier (akaritori), Nieb & Destroyer & MisanthropX & viruz (park), KaZ (dune), Justin (pitch_black), and Meister (osiris)
- added trak5 texture set by TRaK
- added "efficiency ctf", "efficiency protect", "hold", "insta hold", and "efficiency hold" game modes
- green and yellow armour spawn delay is now partially randomized and do not spawn immediately
- can return the flag to base in protect mode by dropping the flag on top of the base
- if a player explicitly drops a flag in ctf mode, he can't pick it back up (only his teammates can)
- added numbered base blips for capture modes (toggled via "basenumbers" var, contributed by NancyWilliams)
- players are now notified of team switches, and team switches can only be done while dead (forces player to die if alive)
- teleports now preserve velocity if third attribute of teledest is set to 1
- smoothed out climbing of 1:1 stairs
- added mini-map to radar
- match time remaining is now displayed in minutes and seconds
- added crosshair selection menu
- can now change the texture configuration in-game of all textures within a selection (via "vrotate", "voffset", "vscale", "vscroll", "vlayer", "valpha", "vshaderparam", "vcolor", "vreset", and "vdelta" commands)
- added support for alpha-blended textures (controlled via "editmat alpha", "texalpha", and "valpha" commands)
- added color scaling for diffuse textures in all shaders (via "texcolor" and "vcolor" commands)
- added support for fogging skybox (controlled via "fogdomemax", "fogdomemin", and "fogdomeheight" vars)
- added support for coloring skybox (via "skyboxcolour" var)
- sky-textured geometry no longer blocks skylight (controlled via "skytexturelight" var)
- added multi-threading for "calclight" command (controlled via "lightthreads" var)
- edit clipboard is now synchronized when a new player connects to a coop-edit
- added "replacesel" command that only replaces textures within the current selection
- added "shrinkmap" command for reducing oversized maps
- cubes are now textured on all sides with the second texture slot by default
- added optional Quake-like mouse acceleration (controlled via "mouseaccel" var)
- added "reconnect" command for connecting to the last connected server
- added optional wall clock (controlled via "wallclock", "wallclock24", and "wallclocksecs" vars)
- added "conscale" var that controls the size of console text
- added teamkill filter for console
- added "screenshotdir" var that controls where screenshots are placed
- "writeobj" command now exports texture assignments
- revised vertex format to be more efficient on older/generic 3D cards
- added GLSL render path (toggled via "forceglsl" var)
- added support for uniform buffer objects to GLSL skeletal animation path
- improved skeletal animation blending quality in fixed-function mode
- added support for environment-mapped world geometry in fixed-function mode
- added rotational friction for ragdolls to make them settle more quickly
- revised collision detection to use Minkowski Portal Refinement (allows for easier extending of collision to new shapes)
- improved adaptive sampling for calclight (faster "calclight 1")
- added motion blur effect (toggled via "motionblur" var)
- "deathscore" variable controls whether scoreboard is shown on death
- scoreboard shows the server you are currently connected to (toggled via "showservinfo")
- added "guinameslider" for selecting from a list of names with a slider
- added "guialign" for creating aligned lists
- added SMD and IQM model support (see models.html)

## 2009_05_04_trooper_edition

- added new player model Snout X10000 by Geartrooper
- added new hudguns and vweps by Geartrooper
- added new logo and loading screens by Blindabuser
- added new soundtrack "Odious" by Fanatic
- added new MP maps by Nieb (flagstone, turbine), Meister & Com3t4 (valhalla), Blikje Bier (konkuri-to), KaiserTodretter (redemption), Blindabuser (fc4), THEtarget (l_ctf), Halleck (neondevastation), mIscreant (refuge, forge), MX (sdm1), viruz (dust2), schmutzwurst (campo), KI113R & Redon (killcore3), Majikal (damnation, torment), Hero (europium), Kal & Halleck (kffa), Meister (shinmei1), Destroyer (dock), Hero & viruz (cwcastle), Redon (memento, frozen, recovery), Drakker (sacrifice, powerplant), Kretren (core_transfer), and MisanthropX (arabic)
- added new SP map by Redon (lost)
- added new stained glass texture set by PainKillAH and snow texture set by TomekGNO
- backported bots from Blood Frontier by Quin
- new announcer voice by Blindabuser
- added "protect" and "insta protect" game modes
- added layer blending for world geometry
- added flame particles (particle types 0 and 11) and smoke particles (particle type 12)
- all map vars (skybox, fog, watercolour, etc.) now save inside maps and sync during coop-edit
- ambient light can now be colored (with "ambient R G B")
- "fogcolour" variable can now be set with the form "fogcolour R G B"
- renamed "aiclip" material to "gameclip" and allowed it to be used to prevent flag dropping in areas in CTF/protect modes or base capturing in capture modes
- "editmat" command can now specify an optional filter material which limits the cubes it modifies
- added "gotosel" command to go to the current selection's position in edit mode
- simplified "calclight"/"patchlight" quality levels to 1: high, -1: low, and 0: determined by "lmshadows" and "lmaa" vars
- particles now show in edit mode (controlled by "showparticles" var)
- pickups now show up immediately when added in edit mode
- added support for optional hit sound (toggle with "hitsound" var)
- added configurable mini-console for chat (configurable via "miniconsize", "miniconwidth", "miniconfilter", and "miniconfade" vars)
- made key-binding menu easier to use
- extended damage compass to 8 directions (from 4)
- added ammo inventory display to HUD
- made "sensitivity" variable floating-point (no more "sensitivityscale" needed)
- added "dropflag" command for CTF modes to drop the flag
- main menu is now shown instead of dumping to local map when game starts up or when disconnected from multiplayer
- players can now un-spectator themselves if mastermode is less than 2 (locked)
- can now keep servers in the server browser with the "keepserver" command and also specify passwords for it to use
- demo recording now works for local MP modes
- re-enabled listen server functionality (via "-d1" command-line option or "startlistenserver" command)
- can now setup server parameters with "server-init.cfg" instead of using command-line options
- can now specify different ports for servers to use (via "-j" command-line option)
- included source code for new master/auth server
- added optional master authentication system instead of old "approve" command
- added support for locking servers with passwords (via "-y" command-line option)
- server admins can now pause matches with the "pausegame" command
- collision boxes for mapmodels now support yaw
- smoothed out player collisions against stairways
- added optional ragdoll physics for skeletally-animated models
- added movie recording in uncompressed AVI YUV format (via "movie" command)
- screenshots now save as PNG images instead of BMP
- added support for loading files directly out of ZIP archives
- added support for DDS DXT1/3/5 compressed textures
- removed dependency on libGLU
- added view frustum/PVS culling for particle entities
- deferred loading of world shaders until they are used
- replaced "setpixelparam"/"setvertexparam" with easier "setshaderparam" command
- rewrote grass rendering to support blending and better batching
- made "mdltrans"/"mdlscale" use matrix transforms instead of preprocessing vertexes
- added cheap blob shadows fallback for player shadows
- removed old/inefficient stencil shadows fallback
- added support for shadow mapping in fixed-function mode
- added support for dynamic lights in fixed-function mode
- rewrote post-processing shaders to allow stacking

## 2008_06_17_ctf_edition

- added new MP maps by Nieb (hallo, shipwreck), schmutzwurst (akroseum, berlin_wall), KillHour (hog2), KaiserTodretter (paradiselost), Mayhem & mIscreant (duomo), Mayhem (tejen), Hero & WahnFred (mach2), TUX (capture_night), SATAN!!! (reissen), Redon (c_egypt), and Kal & DairyKing (kalking1)
- added MitaMAN's new SP campaign: "Private Stan Sauer"
- added Fanatic's new 10 song soundtrack "Spontaneous Failure"
- added geartrooper's new MD5 character model: Mr. Fixit
- added ctf and insta ctf game modes
- added support for cloud boxes and cloud layers over sky box
- added in-game text editor for editing cfg files
- texture browser now displays glow, rotation, and offsets
- added console message filter (controlled via "confilter" and "fullconfilter" vars)
- "follow" command now works in first-person (can spectate in third-person via "thirdperson" var or 9 key)
- added support for Cube Server Lister extended information
- added support for Mumble positional audio (contributed by The Conquerors clan)
- added "apply changes now?" dialog using "resetgl" command (toggled via "applydialog" var)
- made clip material coexist with other materials (so water/lava can clip)
- added "death" material for forcing player suicide
- added "fullconsize" var for controlling the percent of the screen the full console occupies
- undo now works with heightmap editing mode
- now automatically pick up ammo boxes when touching a base in normal capture mode (toggled via "autorepammo" var)
- lowered the minimum gridpower to 0
- added "texoffset", "texrotate", and "texscale" commands for more easily specifying texture slot parameters
- texture rotation is now done via texture coordinate generation (instead of making copies/wasting memory)
- added "sayteam" command for chatting to teammates (bound to Y key by default)
- added optional t-joint removal to fix world sparklies (toggled via "filltjoints" var)
- made hit crosshair show when successfully hit enemy (duration set via "hitcrosshair" var)
- made teammate crosshair show when aiming at a teammate (toggled via "teamcrosshair" var)
- player is now dumped to an empty map if he does not have the particular map in multiplayer
- added support for soft particles/explosions (toggled via "depthfx" var)
- added support for "pulseglow" shaders in fixed-function mode
- added "texscroll" command for scrolling texture slots
- added cheaper/more-controlled glow/specular bloom (controlled via "glare" var)
- added "texgui2d" var for toggling whether the texture palette uses a 2D or 3D gui
- scoreboard now always defaults to 2D, regardless of GUI settings (controlled via "scoreboard2d" var)
- added "waterfallcolour" command to control coloring of waterfalls separately from water
- optimized water reflection/refraction with scissoring and tighter frustum culling
- added refractive waterfalls (controlled via "waterfallrefract" var, disabled by default due to cost)
- added environment-mapped waterfalls (controlled via "waterfallenv" var)
- added tethers that show who is capturing a base (controlled via "capturetether" var)
- rewrote particle renderer to make it more extensible
- rewrote world renderer to more efficiently batch draw calls
- made lightmaps use a texture atlas to enable better batching of draw calls
- locked physics at fixed rate of 200 Hz (no more variable rate)
- revised handling of slopes in physics to reduce sticking problems
- made underwater fog/caustics fade in instead of turn on immediately at the surface
- added "resetgl" command to restart the renderer while running
- added builtin zoom (toggled via G key or "zoom" var)
- added directional damage indicator to the HUD (toggled via "damagecompass" var)
- smoothed out the shadow boundary caused by the shadowmap depth peeling
- softened water edges now work when under water
- players can now reconnect to private games when disconnected, so long as their IP matches
- added precomputed visibility/PVS system for occlusion culling on 3D cards that don't support OQ (see editref.html)
- added support for environment-mapped water reflections as a cheap fallback (used if "waterreflect" is off)
- added movement smoothing for other players in multiplayer (reduces jumpiness from packet loss)
- added "fullbrightmodels" var for controlling fullbright-ness of player models
- added MD5 model support with new skeletal animation system (see models.html)
- added OBJ model support (see models.html)
- added new decal system for bullet holes, scorch marks, etc.

## 2007_12_22_assassin_edition

- added new "slowmo" sp and dmsp modes (-5 and -4 respectively), see sp modes description
- added lots of functionality to the rpg game
- capture meters now decay instead of reset if you leave their radius
- added assassin, insta assassin, and regen capture game modes
- models (hudguns, characters, etc.) are now preloaded to reduce load pauses during play
- switched the quick-edit menu key from TAB to F3
- air speed bonus now works when moving backwards
- added geartrooper's new hudguns and vweps
- improved remip
- added dtrace probes for cube script
- added "aiclip" material for clipping monsters in SP
- added exploding barrels, movable boxes, platforms, and elevators for SP (via "barrel", "box", "platform", and "elevator" entities)
- added support for anisotropic texture filtering (via "aniso" var)
- re-enabled occlusion query on Linux ATI/fglrx drivers due to some massive improvements in version 8.42
- cut capture/spawn times in half for insta capture
- added support for depth-fogged water in fixed-function mode
- softened up water edges when using refractive water with shaders
- master status must now be approved by one other person (via "approve" command) when using the "-o1" public server option
- rewrote heightmap. Hold LCTRL or press H to activate.
- added workaround for broken demo recording on Windows
- added normalmapping support for models (via "md3bumpmap" command)
- taunting now causes player to stop moving
- fixed bug with explosions not doing damage
- made client and server sync their clocks as often as possible to compensate for inaccurate clocks on some hardware
- replaced the display list fallback for models with vertex arrays instead (allows better reuse of model animation on older 3D cards)
- player animation is now cached so its only done once per frame despite multipass rendering (reflections, shadows, etc.)
- player models now use occlusion queries so only visible players are animated (huge SP speedup with lots of monsters)
- environment map textures are now automatically scaled so that all sides have matching resolution
- added lightning particles
- added experimental soft shadow system based on shadowmapping and depth peeling
- Cube map importer can now handle AssaultCube maps
- added spectator follow camera (via "follow" command)
- added "loadcrosshair" command
- improved scoreboard for team modes
- miscellaneous crash/bug fixes

## 2007_08_19_summer_edition

- local server now respects "gamespeed" and "paused" vars
- added toggles for trilinear and bilinear filtering (via "trilinear" and "bilinear" vars)
- added "consize" var for controlling the size of the default/overlayed console
- server browser now sorts servers by number of players (empty servers still sorted by ping)
- directions and radiuses of entities now display in edit mode (toggled via "showentradius" var)
- added support for FBO depth+stencil format so dynamic shadows can render properly in water refractions
- "remip" now synchronized with all clients in coop-edit
- added "clearbans" command so masters can clear all bans
- added "floatspeed" var for controlling spectator/editmode movement speed
- added "outlinemeters" var for outlining capture meters
- added "teamskins" var for toggling usage of red/blue skins in FFA modes
- added "ogro" var for toggling use of Ogro
- models now use a bounding interval hierarchy for ray tracing/lightmapping instead of sphere trees (better memory/cache usage)
- added workaround for crashes with Linux ATI/fglrx drivers
- fixed collision bug that let players walk inside sloped geometry
- added blood decals (toggled via the "blood" var)
- added "insta capture" game mode
- tweaked capture gameplay timings
- added calclight visualization of lightmaps
- added "-v" command-line option for controlling vsync
- added "-k" command-line option for adding mod directories
- added "-q" command-line option to set per-user home directories
- added "-r" command-line option to load "init.cfg" on startup
- added "init.cfg" so init settings can be changed from in-game and take effect on restart without needing command-line
- added "guilistslider" command for selecting from a list of specific integer values
- added support for hardware-accelerated mipmap generation (via "hwmipmap" var)
- added "gui2d" var for making all menus/scoreboard 2D
- added "texreduce" var for scaling texture quality down
- added dynamic lighting system
- new "gridlookup" var controls whether cursor grid size is looked up from cube under cursor
- refactored gameplay and moved some of it (damage, ammo, health) server-side
- autoteam now only selects good/evil regardless of number of teams in play
- experimental server-side demo recording
- added "admin" privileges via "setmaster password"
- added support for translucent models
- made yaw/pitch of playermodels interpolated in multiplayer
- VBOs now supported on animated models
- added support for custom fonts
- added "lava" material
- added "goto" command for spectators
- made models share meshes/rendering data if same md2/md3 file is loaded for better memory usage
- connection to masterserver can now be aborted in case the http socket connect locks up
- fixed bug that caused some unnecessary sparklies in indoor maps
- glowmapped models/geometry now work in fixed-function mode
- models now support environment mapping (via custom envmaps or envmap entities)
- added (ugly) fallback for old cards with no multitexture support (rather than spitting out error and quitting)
- revised texture combiner support to more easily add fixed-function effects
- fixed particles and materials not fogging properly
- duplicate player names are now distinguished by client number
- optimized model rendering to batch similar models and reduce state changing as much as possible
- capture bases can now be named via "base_N" aliases
- animation now supports multi-part md3 characters
- added support for OGG sounds
- added "spotlight" entities
- added texture slot "e" for loading custom envmaps with envmapped shaders
- added support for post-pass blurring of lightmaps (via "blurlms" and "blurskylight" vars)
- added ambient occlusion for lightmaps (via "skylight" command)
- added softened explosions via shaders (spheres) or fixed-function mode (hemispheres)
- added workaround for explosions crashing on some Intel integrated graphics
- added vertex animation to water

## 2007_04_13_spring_edition

- added hudgun sway (toggled via "hugunsway" variable)
- "crosshairfx" variable now works again
- servers now report correct IP to masterserver with the -i command-line option
- scoreboard now displays mode, map, and time remaining
- bases now produce ammo in capture mode (take ammo with R key or "repammo" command)
- added reflective water in fixed-function mode
- added reflective glass in fixed-function mode
- made waterfall top/bottom correctly align with water surface
- player vs. player collisions now use ellipses instead of bounding boxes
- added new functionality to the rpg prototype (WiP)
- added planar shadows for most dynamic entities
- added -o option for servers to disable "locked" and "private" mastermodes
- dead players now colored gray on scoreboard
- changed experimental movement speedup code to include both jumping & forward independently (see game.html)
- added F key support to heightmap editing.
- improved "fastshader" system to support more than 2 performance levels
- added environment-mapped geometry shaders (via "bumpenv*world" shaders)
- added ambient sound entities (via "mapsound" and "newent sound")
- added alpha-masked shadows for mapmodels with alpha-channel skins (via "calclight 3")
- added animated caustics effect to underwater geometry
- added experimental animated grass system
- added support for GLSL shaders
- added entautoview, entitysurf and selectionsurf
- added Marc's latest 8 tracks, for a total of 31 now!
- added visual entity box handle. allows easy choice of orientation. hovering over an ent now replaces closest ent as implicit ent selection.
- added smoothmap command for heightmaps. (default press H when already in hmap mode) executes a moving avg filter over hmap
- added context sensitive entity menu (default TAB)
- added a scale parameter to the "texture" command, for changing the apparent size
- texture combining now scales combined texture to match size of base texture
- command "showtexgui" (default F2) allows for comfortable texture browsing
- made gui stick to player's Z
- fixed server lockup (in patch)

## 2006_12_04_gui_edition

- added 'particletext' var for toggling particle text
- alias arguments now set by 'push' on execution, and restored by 'pop' after
- added 'push' and 'pop' commands for saving and restoring aliases
- glass reflection using environment maps
- added environment map entities (created by "newent envmap") for reflecting geometry
- added S3 texture compression support (controlled by "mintexcompresssize" var)
- added Gregor's new texture set and map, and many other new maps/media
- added heightmaps for most existing normalmapped textures, so we can have parallax on everything
- added scripting documentation for the rpg
- model rendering code now automatically generates triangle strips for both md2s and md3s
- added workaround for garbage in skybox on ATI cards (must be enabled explicitly by "/ati_skybox_bug 1" if necessary)
- fixed lighting bug in fixed-function mode that caused textures to saturate
- made selections solid. you can still use 'passthrough' to suppress it
- changed some default editing key bindings. right mouse is now the 'editextend' command, B is now change brush, Alt is now passthrough
- added multiple entity selection.
- added boolean operators to cubescript: &&(and), ||(or), ^(xor), !(not)
- exposed selecting to cube script. see "entselect, moving, dragging, entmoving" and related commands. ex: KP_Enter selects entity's within selection, etc.
- added a bunch of new editing commands to seperate much of the entity and cube commands in engine. overloading behaviours is now left to scripts. see data/stdedit.cfg
- new gui/menu system
- added surface merging that drastically reduces world geometry (done on remip/calclight)
- teams now automatically selected on any team mode by server
- added support for md3 vweps
- default enemy ogro skin is now always red (teammates always blue)
- added progress meters for base captures
- server will now pick map with most pending votes (if possible) at the end of a match
- reflections now use occlusion queries instead of distance check
- changed geometry rendering to use triangles instead of quads (consistent subdivision on all platforms)
- "newmap" is now synchronized across all clients in coopedit
- revised networking code to better utilize enet (less lag and bandwidth usage)

## 2006_09_12_water_edition

- added "setteam" command for forcing teams via mastermode
- added support for material texture slots
- added "shaderdetail" var that can turn off some expensive shaders
- new water rendering supporting reflection & refraction
- monsters wake up if monsters close to them get shot by a visible player
- dying while using a menu doesn't pop up the scoreboard anymore
- added a static version of the wiki to the documentation
- uniformly scaled down the spec factor in all maps from 8 to 6 (as used in metl4)
- deaths now spawn a number gibs depending on the amount of excess damage, if that is a lot then no corpse is rendered
- increased the minimum ambient light factor for opponents in multiplayer a lot (can't hide in the dark anymore)
- added simple keybinding options to the menus
- added damageblendfactor & damagespherefactor var
- starting grenades reduced to just 1
- added support for md2 vweps
- added optional flipping over X and Y axes to "texture" command
- added makke's new ammo/health models
- added models for rocket/grenade launcher projectiles
- fixed broken world-specular on ATI cards
- changed rendering architecture to do seperate Z pass to get more accurate occlusion culling and reduced pixelshader load

## 2006_07_22_normalmap_edition

- added support for "dot3 lightmap / radiosity lightmap" mode that works well with normalmaps & per pixel light, various shaders supporting bump/parallax mapping, glow/specmaps etc.
- added lots of normalmapped textures
- many new maps using normalmapping
- extended Fanatic's amazing soundtrack with 8 new tracks!
- added dbghelp.dll to the bin folder that win98 users need to rename...
- clearer color coding in the console: green: player talk, blue: "echo" command, yellow: gameplay messages, red: important errors, white: everything else
- added -z (z-buffer precision), -b (bits per pixel), -a (FSAA), and -f (shader precision) command-line settings (see config.html)
- added "trigger" command for opening/closing doors
- added entity selection by left mouse button.
- added entity copy and paste
- added entity undo / redo support
- added entity support to flip and rotate
- added editmove command
- added replaceents command
- made sure that textures of 'new cubes' are appropriate. Maps need to be remipped for this to fully work.
- added outline mode for showing geom boundaries (toggled by "outline" var)
- added -p (admin password) and -c (maxclients, default 4) command-line options for servers
- added setmaster command
- added voice announcer for certain gameplay events
- quad & boost powerups are now randomized in spawn times, but their spawn is announced 10 seconds before (so everyone will have to fight for it :)
- added showcharacterboundingbox var (useful when creating new models)
- increased rhino bounding box size

## 2006_06_11_sp_edition

- scripting language: every command/block/exp can now return string values (no more use of variable "s", much cleaner code)
- scripting language: reduced allocations a great deal, should execute faster now
- scripting language: can now write X = Y instead of alias X Y for more readable code
- If sauer crashes on a non-programmer machine on Windows, it will now output a stacktrace (both in a popup and the console window) which can be copy-pasted and sent to the developers (do this before you press "OK" to close the program, from the console windows menu).
- added provisional "sendmap"/"getmap" commands for coopedit mode
- explicit sky polies are now outlined in editmode (toggled by "showsky" var)
- now shows names of entities floating in edit mode (in green, closest = red)
- any non-multiplayer games can now be paused (variable "paused", default key F1)
- fixed rockets exploding mid-air if they were aimed at a moving target
- copy/paste now work in coop-edit
- moved all mapmodels into the menus
- new SP respawning system! read "SP Respawning" in game.html
- console language macros now allow code generation (see config.html)
- added customizable file completion (via "complete" command)
- aliases and vars set in map cfgs are now sandboxed (don't persist)
- world shaders can now work with any number of textures (see "texture" command).
- support for specularity maps and glow maps on md2/md3 models (see md2.txt/md3_sauer_howto.txt)
- new "editbind" works like "bind", only the key is only available in edit mode. cleaned up keymap/default cfg files (no more bindings in keymap)
- added triggerable mapmodels (see editref.html for more info)
- removed the z-offset attribute from mapmodel info and ents and moved mapmodel ent skin attribute to mapmodel info (see editref.html)
- added support for full screen pixel shader effects (see setfullscreenshader, and the "option" menu)
- removed obsolete editheight command
- added powerful new heightmap mode! use getheightmap command [default H key] when there is a selection box to activate (see editref.html for more info)
- added selectbrush modifier [default J key] that switches between brushes defined in data/brush.cfg
- added copybrush [default K key] to use current heightmap as brush. see data/brush.cfg for more info.
- editable brushes for heightmap mode. see data/brush.cfg for more info.
- capture gameplay mode fixes
- ip address lookups now use the concurrent resolver
- added redo command [default I key]
- made importcube remip while importing to save memory
- removed some lighting/physics bottlenecks in SP mode
- removed 256 textures per map limit (is now 64k)
- fixed incorrect mapmodel shadows on Windows
- fixed invincibility bug

## 2006_04_26_occlusion_edition

- tweaks & fixes to the capture gameplay mode
- added high resolution skyboxes, and some of the g_pack textures to the standard set
- fixed newent sending invalid attributes in coopedit mode
- models with a specularity of 0 now have a specialized shader ("nospecpvmodel") for faster drawing (mainly for vegetation)
- grenadelauncher damage increased to max 75
- multiplayer players & flag models will not be culled no matter how far away they are
- added waterfall effect for water material sides
- added pistol ammo (ent type "cartridges")
- added linearly-interpolated normals for lighting (controlled by "lerpangle", "lerpsubdiv", and "lerpsubdivsize" vars)
- added HW occlusion culling support (requires NV GeForce3-class hardware or better)
- reduced overdraw dramatically
- reduced size of vertex data by using short instead of float
- removed ZYX order inconistency from math classes
- fixed lights placed outside the world not casting shadows
- fixed grenades being stopped by clip material and being stuck in walls
- made networking protocol use less bandwidth
- calclight now uses multi-sampling and adaptive sampling
- faster mapmodel ray intersects with spheretrees instead of bsp
- shorter fuse on grenades (2 seconds)
- fixed hudgun light computation related crash

## 2006_03_20_shader_edition

- registersound now allows individual sound volume adjustment
- can now render md2s without back face culling (good for vegetation models), custom specularity, custom shader.
- console now supports line-editing
- calclight now forces a map remip automatically, and has 4 quality settings you can pass (see ref)
- added workaround for texgen bug in nvidia drivers
- added goal-oriented team player mode (mode 12, "capture", see game.html, try playing it on face-capture map)
- added initial version of the grenade launcher
- added macros to the scripting language
- everything in the engine is now rendered using shaders
- converted the engine's use of OpenGL from xzy to xyz (don't ask)
- added phong lighting for models
- added shader system, each world surface can now have its own shader, and maps can have their own shaders. Look at the shader and setshader commands.
- reorganized directory structure
- can now specify custom animations and other properties for md2s (see docs/dev/md2.txt)
- clip material no longer stops bullets (only the glass material does)
- added spectator mode (toggled by "spectator" command, or mastermode 2)
- many mastermode bug fixes
- fixed line wrapping to depend on screen resolution
- added map model shadows for md2s (available in maximum quality mode of "calclight", see ref)
- added Cube-like "replace" command that will repeat a texture edit across matching parts of a selection
- maxhealth now persists across disconnects

## 2006_02_27_physics_edition

- added Fanatic's new soundtrack! 15 2 minute tracks, played at random in sequence (they were meant to "connect"), an endlessly varying song! :)
- experimental gameplay feature: the health boost / megahealth now only gives you +10, except it is permanent to your maxhealth for this game, as opposed to just health.
- experimental forward push on jump. Let me know if this is cool..
- text particles can now be any size, and now show the player's name permanently in 3d as well as any chat
- made T default key for multiplayer chat again, Y is now default for texture edits.
- frags now persist across disconnects
- fixed hellpig bounding sphere
- added menu page scrolling
- "sleep" command now supports multiple timers
- "music" command can now execute commands when a song is done playing
- optimized material rendering by grouping into larger surfaces (toggled by "optmats" var)
- many tiny tweaks to the multiplayer gameplay
- "maxfps" var for limiting fps
- "showmat" var for rendering invisible materials and selecting materials in edit mode
- edited cubes default to fullbright until calclight/patchlight
- added coopedit support back in | no map uploading yet...
- rewrote physics to be closer to the original Cube physics

## 2006_01_31_mp_edition

- disconnection messages now show why you were disconnected
- multiplayer enemies show firing/pain animations
- weapon pushback (esp for rockets) now works over the network, and for monsters
- reduced ammo you can carry from 5 to 3 boxes each, and increased ammo respawn times by 33%.
- machinegun now has mild inaccuracy at distance
- fixed shotgun (all rays are now individual so you can hit multiple targets optimally, better spread pattern, slightly wider)
- fixed all hitscan weapons not stopping at first target
- fixed RL splash damage, now does more damage in radius and rocket jumps work better
- masterserver functionality restored
- added flare particles to help emphasize hitscan weapons
- interpretation of cubes edges switched from 'edgepan' to 'vector'
- passthrough command. normally cubes of equal size to the grid are given priority when selecting; passthrough removes this priority while held down. (default key: LCTRL)
- fixed ghost/disconnection problems in multiplayer
- "allfaces" var for texturing all faces at once
- "writeobj" command writes a sauer level out as .obj file for potential use in other apps.
- added "text particles": small bits of text that can float in 3d space. Currently used for damage numbers (red) and other gameplay events (green).
- gameplay changes: pistol damage 40 -> 25
- "mastermode" for having easy, cheater-free multiplayer games with the people you want. Read the section "Cheating & Multiplayer" in game.html to learn how to use it.
- gettex command
- fixed sky HOM when fog was closer than size of world

## 2005_11_07_agc_edition

- warning will appear if player cannot see most of selection when trying to edit
- selecting now ignores the cube the player is currently in
- "importcube" command for converting old cube maps
- fixed animation blending
- fixed being at the surface of water generating many sound events
- did an endless amount of more refactoring to seperate the game code out more. Multiple "games" can now coexist in the same exe
- "lanconnect" command for broadcasting connection requests over a LAN
- "maxparticledistance" variable culls all particle splashes at distance
- "maxmodelradiusdistance" variable calls models at distance, relative to their size. One day we will render models as sprites in the distance, but for now this is a cheap way to significantly reduce the rendering load on large maps
- "loddistance" sets the distance at which vertex array blocks of world geometry use a lower LOD approximation. Significantly reduces amount of small detail rendered at distance. Useful on larger maps only.
- "lodsize" must be set to 32 to turn lod on for a map (use only for really large maps), 0 turns it off. saved with the map.

## 2005_08_15_quakecon_edition

- animation blending... makes 3rd person view, other players and monsters look much better
- now saves to config.cfg automatically so you can change settings persistently in game
- first attempt at factoring out all gameplay code, results may be buggy

## May 22 2005

- 101 small changes to bring all the old cube functionality back up and running, mostly affecting gameplay & rendering. Singleplayer and Multiplayer mostlty work again.

## May 21 2005

- lots of updates to lightmaps, and related stuff
- prune micro cubes in editing
- limit texture selection

## May 17 2005

- raycube changed to support lightmaps better

## May 16 2005

- inital lightmap code added

## May 15 2005

- added a cube validator that's called after a map is loaded.
- added a ray casting function in preperation for lighting. Using it to get editing cursor for now.
- added some collision detection / response against entities. they still get stuck...

## May 8 2005

- collision detection / response is now functionally done.
- cleaned up editing a bit.

## May 6 2005

- remip functionally done. will want to clean it up a bit though.

## Apr 24 2005

- more tweaks to remip

## Apr 23 2005

- remip. still need to integrate it with editing commands.

## Apr 22 2005

- added reorient command.
- changed collision detection. Now player treated as rectangle. Much simpler and faster. still need to find proper floorheight
- Collision clipping planes added to cube structure. Are generated at same time as vertexes are. (currently static arrays, though will probably allocate dynamically in future to save mem)
- also a few other minor changes to subdivision etc, since no need for gentris().

## Feb 2 2005

- fixed dropped geometries in octarender (#58)

## Jan 24 2005

- simplifyied the rendering and partial update code
- rearranged the hud map numbers abit, added allocated vertex array counter "va"

## Jan 18 2005

- fixed crash due to failed to clear va pointer

## Jan 9 2005

- changed cvec into ivec (integers instead of uchar)
- changed most integer points into ivec
- fixed cursor position depth for small gridsizes
- added error msg to newmap when not in editmode
- started to clean up some stuff 

## Jan 4 2005

- make _DEBUG gcc friendly

## Jan 3 2005

- fixed memory leak (vertex array not destroyed)
- force all children in selection area to update

## Dec 31 2004

- fixed GL_ARB_vertex_buffer_object function pointer dereference when extension not present

## Dec 19 2004

- revision 1.12 of the exe has a new command "fixmap", that can be entered through the console. this will convert older maps that had problems because of recent updates. it acts as a toggle. "fixmap" will not be a part of future exe s, and I haven't bothered putting it in the source code.

## Dec 18 2004

- fixed partial update bug, now calls addchanged() after octree is changed
- perfoemance improvement for partial updates
- added partial updates

## Dec 13 2004

- more work on ramp collision and response (very smooth now)
- fixed bug #15

## Dec 12 2004

- rework vertex array code to better fit model
- GNU g++ compatibility in physics.cpp
- add framework for partial map updates

## Dec 11 2004

- fixed up ramp collision

## Dec 8 2004

- added VBO support
- fixed possible memory leak
- removed VAR code

## Dec 6 2004

- make tools.h more compatible with gcc
- comment out VAR code
- improved hidden face rejection
- added hierarchial vertex arrays
- added view frustrum culling
- updated included glext.h to latest from SGI

## Dec 4 2004

- fixed edgeinv creating invalid cubes
- fixed grid being changable while dragging
- fixed #2, #3
- added selection support to cube hud counter
- misc cleanup in octaedit
- made tools.h more compatible with gnu c++, based on somebody's (D.plomat?, Thailon?) mingw cube source.
- added subdivision special cases. still need to add slightly stronger condition for 'peeling'

## Nov 30 2004

- tiny bug fixes, like #8 and selgrid init
- selection support for rotation
- changed edge configuration. simplifies flip and rotate, while everything else should be unaffected.

## Nov 28 2004

- real gravity (but too much air friction)

## Nov 27 2004

- starting to refactor some things like subdivision (but need to fix special cases), RCD, loopsel, gentris etc
- made bounding box react more elliptical... though still need to fix physics/collision stuff with z dimension like changing gravity to a velocity.

## Sept 8 2004

- added stairs support
- added jumping

## July 29 2004

- fixed player starting inside the ground when newmap
- took out the newworld function
- cubes are now always convex (well except for some very rare special cases)
- added collision detection for ellipsoid players. step response is only partial finished.

## May 21 2004

- added red 0 reference box
- added selection support to copy and paste
- added selection support to undo
- added selection support to flip

## May 19 2004

- tweaked cursor depth
- added 3D selection
- added selection support to fill command
- added selection support to edittex
- made undo more conservative

## May 15 2004

- fixed subdivision happening in cursorupdate, cube stat
- fixed subdivisions 'peeling' and 'cracking' to a decent degree
- changed fill command to no longer fill cube when scrolling down
- added selection functionality to fill command
- added ad-hoc vertex lighting editing
- more rearrangement of faceverts.
- added fixfaces to fix old maps that are displayed differently because of faceverts changes (remove after next release)
- finished empty_world / newmap
- updated menu.cfg, autoexec

## May 09 2004
- added cube stat to hud

## May 06 2004

- added geomip (though not inverse)
- added cubic copy and paste
- added cubic flip and 90 degree rotate
- added undo (doesn't work with selections fully )
- added texture edit
- changed pitch/yaw derived selection to cubic boundary face selection
- cleaned up octaedit
- hacked a fix for a culling error in touchingfaces

[Unreleased]: https://github.com/tomatenquark/code/compare/v0.0.23...HEAD
[0.0.23]: https://github.com/tomatenquark/code/compare/v0.0.22...v0.0.23
[0.0.22]: https://github.com/tomatenquark/code/compare/v0.0.21...v0.0.22
[0.0.21]: https://github.com/tomatenquark/code/compare/v0.0.20...v0.0.21
[0.0.20]: https://github.com/tomatenquark/code/compare/v0.0.19...v0.0.20
[0.0.19]: https://github.com/tomatenquark/code/compare/v0.0.18...v0.0.19
[0.0.18]: https://github.com/tomatenquark/code/compare/v0.0.17...v0.0.18
[0.0.17]: https://github.com/tomatenquark/code/compare/v0.0.16...v0.0.17
[0.0.16]: https://github.com/tomatenquark/code/compare/v0.0.15...v0.0.16
[0.0.15]: https://github.com/tomatenquark/code/compare/v0.0.14...v0.0.15
[0.0.14]: https://github.com/tomatenquark/code/compare/v0.0.13...v0.0.14
[0.0.13]: https://github.com/tomatenquark/code/compare/v0.0.12...v0.0.13
[0.0.12]: https://github.com/tomatenquark/code/compare/v0.0.11...v0.0.12
[0.0.11]: https://github.com/tomatenquark/code/compare/v0.0.10...v0.0.11
[0.0.10]: https://github.com/tomatenquark/code/compare/v0.0.9...v0.0.10
[0.0.9]: https://github.com/tomatenquark/code/compare/v0.0.8...v0.0.9
[0.0.8]: https://github.com/tomatenquark/code/compare/v0.0.7...v0.0.8
[0.0.7]: https://github.com/tomatenquark/code/compare/v0.0.6...v0.0.7
[0.0.6]: https://github.com/tomatenquark/code/compare/v0.0.5...v0.0.6
[0.0.5]: https://github.com/tomatenquark/code/compare/v0.0.4...v0.0.5
[0.0.4]: https://github.com/tomatenquark/code/compare/v0.0.3...v0.0.4
[0.0.3]: https://github.com/tomatenquark/code/compare/v0.0.2...v0.0.3
[0.0.2]: https://github.com/tomatenquark/code/compare/v0.0.1...v0.0.2
[0.0.1]: https://github.com/tomatenquark/code/releases/tag/v0.0.1
