CXXFLAGS= -Os
override CXXFLAGS+= -Wall -fsigned-char -fno-exceptions -fno-rtti

PLATFORM= $(shell uname -s)
PLATFORM_PREFIX= native

INCLUDES= -I../shared -I../engine -I../rpggame -I../enet/include

STRIP=
ifeq (,$(findstring -g,$(CXXFLAGS)))
ifeq (,$(findstring -pg,$(CXXFLAGS)))
  STRIP=strip
endif
endif

MV=mv

ifneq (,$(findstring MINGW,$(PLATFORM)))
WINDRES= windres
ifneq (,$(findstring 64,$(PLATFORM)))
ifneq (,$(findstring CROSS,$(PLATFORM)))
  CXX=x86_64-w64-mingw32-g++
  WINDRES=x86_64-w64-mingw32-windres
ifneq (,$(STRIP))
  STRIP=x86_64-w64-mingw32-strip
endif
endif
WINLIB=lib64
WINBIN=../bin64
override CXX+= -m64
override WINDRES+= -F pe-x86-64
else
ifneq (,$(findstring CROSS,$(PLATFORM)))
  CXX=i686-w64-mingw32-g++
  WINDRES=i686-w64-mingw32-windres
ifneq (,$(STRIP))
  STRIP=i686-w64-mingw32-strip
endif
endif
WINLIB=lib
WINBIN=../bin
override CXX+= -m32
override WINDRES+= -F pe-i386
endif
CLIENT_INCLUDES= $(INCLUDES) -I../include
STD_LIBS= -static-libgcc -static-libstdc++
CLIENT_LIBS= -mwindows $(STD_LIBS) -L../$(WINBIN) -L../$(WINLIB) -lSDL2 -lSDL2_image -lSDL2_mixer -lzlib1 -lopengl32 -lenet -lws2_32 -lwinmm
else	
CLIENT_INCLUDES= $(INCLUDES) -I/usr/X11R6/include `sdl2-config --cflags`
CLIENT_LIBS= -L../enet -lenet -L/usr/X11R6/lib -lX11 `sdl2-config --libs` -lSDL2_image -lSDL2_mixer -lz -lGL
endif
ifeq ($(PLATFORM),Linux)
CLIENT_LIBS+= -lrt
endif
CLIENT_OBJS= \
	../shared/crypto.o \
	../shared/geom.o \
	../shared/glemu.o \
	../shared/stream.o \
	../shared/tools.o \
	../shared/zip.o \
	../engine/3dgui.o \
	../engine/bih.o \
	../engine/blend.o \
	../engine/blob.o \
	../engine/client.o	\
	../engine/command.o \
	../engine/console.o \
	../engine/cubeloader.o \
	../engine/decal.o \
	../engine/dynlight.o \
	../engine/glare.o \
	../engine/grass.o \
	../engine/lightmap.o \
	../engine/main.o \
	../engine/material.o \
	../engine/menus.o \
	../engine/movie.o \
	../engine/normal.o	\
	../engine/octa.o \
	../engine/octaedit.o \
	../engine/octarender.o \
	../engine/physics.o \
	../engine/pvs.o \
	../engine/rendergl.o \
	../engine/rendermodel.o \
	../engine/renderparticles.o \
	../engine/rendersky.o \
	../engine/rendertext.o \
	../engine/renderva.o \
	../engine/server.o	\
	../engine/serverbrowser.o \
	../engine/shader.o \
	../engine/shadowmap.o \
	../engine/sound.o \
	../engine/texture.o \
	../engine/water.o \
	../engine/world.o \
	../engine/worldio.o \
	../rpggame/ent.o \
	../rpggame/entities.o \
	../rpggame/objset.o \
	../rpggame/rpg.o

CLIENT_PCH= ../shared/cube.h.gch ../engine.h.gch ../rpggame/rpg.h.gch

default: all

all: client

enet/libenet.a:
	$(MAKE)	-C ../enet/
libenet: enet/libenet.a

clean:
	-$(RM) $(CLIENT_PCH) $(CLIENT_OBJS) rpg_client

$(filter-out shared/%,$(CLIENT_PCH)): $(filter shared/%,$(CLIENT_PCH))

%.h.gch: %.h
	$(CXX) $(CXXFLAGS) -x c++-header -o $@.tmp $<
	$(MV) $@.tmp $@

$(CLIENT_OBJS): CXXFLAGS += $(CLIENT_INCLUDES)
$(filter ../shared/%,$(CLIENT_OBJS)): $(filter ../shared/%,$(CLIENT_PCH))
$(filter ../engine/%,$(CLIENT_OBJS)): $(filter ../engine/%,$(CLIENT_PCH))
$(filter ../rpggame/%,$(CLIENT_OBJS)): $(filter ../rpggame/%,$(CLIENT_PCH))

ifneq (,$(findstring MINGW,$(PLATFORM)))
client: $(CLIENT_OBJS)
	$(WINDRES) -I ../vcpp -i ../vcpp/mingw.rc -J rc -o ../vcpp/mingw.res -O coff 
	$(CXX) $(CXXFLAGS) -o ../$(WINBIN)/rpg.exe ../vcpp/mingw.res $(CLIENT_OBJS) $(CLIENT_LIBS)
ifneq (,$(STRIP))
	$(STRIP) ../../bin/rpg.exe
endif
else
client:	libenet $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o rpg_client $(CLIENT_OBJS) $(CLIENT_LIBS)
endif

depend:
	makedepend -Y -I../shared -I../engine -I../rpggame $(CLIENT_OBJS:.o=.cpp)
	makedepend -a -o.h.gch -Y -I../shared -I../engine -I../rpggame $(CLIENT_PCH:.h.gch=.h)

# DO NOT DELETE

../shared/crypto.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/crypto.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/crypto.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../shared/geom.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/geom.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/geom.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../shared/glemu.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/glemu.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/glemu.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../shared/stream.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/stream.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/stream.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../shared/tools.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/tools.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/tools.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../shared/zip.o: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../shared/zip.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../shared/zip.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../engine/3dgui.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/3dgui.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/3dgui.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/3dgui.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/3dgui.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/3dgui.o: ../engine/model.h ../engine/textedit.h
../engine/bih.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/bih.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/bih.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/bih.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/bih.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/bih.o: ../engine/model.h
../engine/blend.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/blend.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/blend.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/blend.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/blend.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/blend.o: ../engine/model.h
../engine/blob.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/blob.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/blob.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/blob.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/blob.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/blob.o: ../engine/model.h
../engine/client.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/client.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/client.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/client.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/client.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/client.o: ../engine/model.h
../engine/command.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/command.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/command.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/command.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/command.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/command.o: ../engine/model.h
../engine/console.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/console.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/console.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/console.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/console.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/console.o: ../engine/model.h
../engine/cubeloader.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/cubeloader.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/cubeloader.o: ../shared/glexts.h ../shared/glemu.h
../engine/cubeloader.o: ../shared/iengine.h ../shared/igame.h
../engine/cubeloader.o: ../engine/world.h ../engine/octa.h
../engine/cubeloader.o: ../engine/lightmap.h ../engine/bih.h
../engine/cubeloader.o: ../engine/texture.h ../engine/model.h
../engine/decal.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/decal.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/decal.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/decal.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/decal.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/decal.o: ../engine/model.h
../engine/dynlight.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/dynlight.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/dynlight.o: ../shared/glexts.h ../shared/glemu.h
../engine/dynlight.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/dynlight.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/dynlight.o: ../engine/texture.h ../engine/model.h
../engine/glare.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/glare.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/glare.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/glare.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/glare.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/glare.o: ../engine/model.h ../engine/rendertarget.h
../engine/grass.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/grass.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/grass.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/grass.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/grass.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/grass.o: ../engine/model.h
../engine/lightmap.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/lightmap.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/lightmap.o: ../shared/glexts.h ../shared/glemu.h
../engine/lightmap.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/lightmap.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/lightmap.o: ../engine/texture.h ../engine/model.h
../engine/main.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/main.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/main.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/main.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/main.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/main.o: ../engine/model.h
../engine/material.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/material.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/material.o: ../shared/glexts.h ../shared/glemu.h
../engine/material.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/material.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/material.o: ../engine/texture.h ../engine/model.h
../engine/menus.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/menus.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/menus.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/menus.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/menus.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/menus.o: ../engine/model.h
../engine/movie.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/movie.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/movie.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/movie.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/movie.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/movie.o: ../engine/model.h
../engine/normal.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/normal.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/normal.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/normal.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/normal.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/normal.o: ../engine/model.h
../engine/octa.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/octa.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/octa.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/octa.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/octa.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/octa.o: ../engine/model.h
../engine/octaedit.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/octaedit.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/octaedit.o: ../shared/glexts.h ../shared/glemu.h
../engine/octaedit.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/octaedit.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/octaedit.o: ../engine/texture.h ../engine/model.h
../engine/octarender.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/octarender.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/octarender.o: ../shared/glexts.h ../shared/glemu.h
../engine/octarender.o: ../shared/iengine.h ../shared/igame.h
../engine/octarender.o: ../engine/world.h ../engine/octa.h
../engine/octarender.o: ../engine/lightmap.h ../engine/bih.h
../engine/octarender.o: ../engine/texture.h ../engine/model.h
../engine/physics.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/physics.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/physics.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/physics.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/physics.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/physics.o: ../engine/model.h ../engine/mpr.h
../engine/pvs.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/pvs.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/pvs.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/pvs.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/pvs.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/pvs.o: ../engine/model.h
../engine/rendergl.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/rendergl.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/rendergl.o: ../shared/glexts.h ../shared/glemu.h
../engine/rendergl.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/rendergl.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/rendergl.o: ../engine/texture.h ../engine/model.h
../engine/rendermodel.o: ../engine/engine.h ../shared/cube.h
../engine/rendermodel.o: ../shared/tools.h ../shared/geom.h ../shared/ents.h
../engine/rendermodel.o: ../shared/command.h ../shared/glexts.h
../engine/rendermodel.o: ../shared/glemu.h ../shared/iengine.h
../engine/rendermodel.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/rendermodel.o: ../engine/lightmap.h ../engine/bih.h
../engine/rendermodel.o: ../engine/texture.h ../engine/model.h
../engine/rendermodel.o: ../engine/ragdoll.h ../engine/animmodel.h
../engine/rendermodel.o: ../engine/vertmodel.h ../engine/skelmodel.h
../engine/rendermodel.o: ../engine/md2.h ../engine/md3.h ../engine/md5.h
../engine/rendermodel.o: ../engine/obj.h ../engine/smd.h ../engine/iqm.h
../engine/renderparticles.o: ../engine/engine.h ../shared/cube.h
../engine/renderparticles.o: ../shared/tools.h ../shared/geom.h
../engine/renderparticles.o: ../shared/ents.h ../shared/command.h
../engine/renderparticles.o: ../shared/glexts.h ../shared/glemu.h
../engine/renderparticles.o: ../shared/iengine.h ../shared/igame.h
../engine/renderparticles.o: ../engine/world.h ../engine/octa.h
../engine/renderparticles.o: ../engine/lightmap.h ../engine/bih.h
../engine/renderparticles.o: ../engine/texture.h ../engine/model.h
../engine/renderparticles.o: ../engine/rendertarget.h ../engine/depthfx.h
../engine/renderparticles.o: ../engine/explosion.h ../engine/lensflare.h
../engine/renderparticles.o: ../engine/lightning.h
../engine/rendersky.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/rendersky.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/rendersky.o: ../shared/glexts.h ../shared/glemu.h
../engine/rendersky.o: ../shared/iengine.h ../shared/igame.h
../engine/rendersky.o: ../engine/world.h ../engine/octa.h
../engine/rendersky.o: ../engine/lightmap.h ../engine/bih.h
../engine/rendersky.o: ../engine/texture.h ../engine/model.h
../engine/rendertext.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/rendertext.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/rendertext.o: ../shared/glexts.h ../shared/glemu.h
../engine/rendertext.o: ../shared/iengine.h ../shared/igame.h
../engine/rendertext.o: ../engine/world.h ../engine/octa.h
../engine/rendertext.o: ../engine/lightmap.h ../engine/bih.h
../engine/rendertext.o: ../engine/texture.h ../engine/model.h
../engine/renderva.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/renderva.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/renderva.o: ../shared/glexts.h ../shared/glemu.h
../engine/renderva.o: ../shared/iengine.h ../shared/igame.h ../engine/world.h
../engine/renderva.o: ../engine/octa.h ../engine/lightmap.h ../engine/bih.h
../engine/renderva.o: ../engine/texture.h ../engine/model.h
../engine/server.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/server.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/server.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/server.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/server.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/server.o: ../engine/model.h
../engine/serverbrowser.o: ../engine/engine.h ../shared/cube.h
../engine/serverbrowser.o: ../shared/tools.h ../shared/geom.h
../engine/serverbrowser.o: ../shared/ents.h ../shared/command.h
../engine/serverbrowser.o: ../shared/glexts.h ../shared/glemu.h
../engine/serverbrowser.o: ../shared/iengine.h ../shared/igame.h
../engine/serverbrowser.o: ../engine/world.h ../engine/octa.h
../engine/serverbrowser.o: ../engine/lightmap.h ../engine/bih.h
../engine/serverbrowser.o: ../engine/texture.h ../engine/model.h
../engine/shader.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/shader.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/shader.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/shader.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/shader.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/shader.o: ../engine/model.h
../engine/shadowmap.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/shadowmap.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/shadowmap.o: ../shared/glexts.h ../shared/glemu.h
../engine/shadowmap.o: ../shared/iengine.h ../shared/igame.h
../engine/shadowmap.o: ../engine/world.h ../engine/octa.h
../engine/shadowmap.o: ../engine/lightmap.h ../engine/bih.h
../engine/shadowmap.o: ../engine/texture.h ../engine/model.h
../engine/shadowmap.o: ../engine/rendertarget.h
../engine/sound.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/sound.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/sound.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/sound.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/sound.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/sound.o: ../engine/model.h
../engine/texture.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/texture.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/texture.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/texture.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/texture.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/texture.o: ../engine/model.h
../engine/water.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/water.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/water.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/water.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/water.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/water.o: ../engine/model.h
../engine/world.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/world.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/world.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/world.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/world.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/world.o: ../engine/model.h
../engine/worldio.o: ../engine/engine.h ../shared/cube.h ../shared/tools.h
../engine/worldio.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../engine/worldio.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../engine/worldio.o: ../shared/igame.h ../engine/world.h ../engine/octa.h
../engine/worldio.o: ../engine/lightmap.h ../engine/bih.h ../engine/texture.h
../engine/worldio.o: ../engine/model.h
../rpggame/ent.o: rpg.h ../shared/cube.h ../shared/tools.h ../shared/geom.h
../rpggame/ent.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../rpggame/ent.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../rpggame/ent.o: stats.h rpgent.h rpgobj.h
../rpggame/entities.o: rpg.h ../shared/cube.h ../shared/tools.h
../rpggame/entities.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../rpggame/entities.o: ../shared/glexts.h ../shared/glemu.h
../rpggame/entities.o: ../shared/iengine.h ../shared/igame.h stats.h rpgent.h
../rpggame/entities.o: rpgobj.h
../rpggame/objset.o: rpg.h ../shared/cube.h ../shared/tools.h
../rpggame/objset.o: ../shared/geom.h ../shared/ents.h ../shared/command.h
../rpggame/objset.o: ../shared/glexts.h ../shared/glemu.h ../shared/iengine.h
../rpggame/objset.o: ../shared/igame.h stats.h rpgent.h rpgobj.h
../rpggame/rpg.o: rpg.h ../shared/cube.h ../shared/tools.h ../shared/geom.h
../rpggame/rpg.o: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../rpggame/rpg.o: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../rpggame/rpg.o: stats.h rpgent.h rpgobj.h

../shared/cube.h.gch: ../shared/tools.h ../shared/geom.h ../shared/ents.h
../shared/cube.h.gch: ../shared/command.h ../shared/glexts.h
../shared/cube.h.gch: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../rpggame/rpg.h.gch: ../shared/cube.h ../shared/tools.h ../shared/geom.h
../rpggame/rpg.h.gch: ../shared/ents.h ../shared/command.h ../shared/glexts.h
../rpggame/rpg.h.gch: ../shared/glemu.h ../shared/iengine.h ../shared/igame.h
../rpggame/rpg.h.gch: stats.h rpgent.h rpgobj.h
