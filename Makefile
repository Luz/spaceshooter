GCC     = gcc
GPP	= g++
LIBS    = sdl
LIBS   += SDL_image
#LIBS   += SDL_ttf
INCLUDE = /usr/include/SDL/
FLAGS   = `pkg-config  --cflags --libs $(LIBS) ` 
SOURCE  = src/main.cpp
#SOURCE += src/SDL_rotozoom.c
SOURCE += src/Asteroid.cpp
SOURCE += src/Engine.cpp
SOURCE += src/ObjectHandler.cpp
SOURCE += src/Rakete.cpp
SOURCE += src/Schuss.cpp
SOURCE += src/Spieler.cpp
SOURCE += src/CollisionHandler.cpp
SOURCE += src/global.cpp
SOURCE += src/Object.cpp
SOURCE += src/PlayerHandler.cpp
SOURCE += src/SaveLoadSchuss.cpp
SOURCE += src/SchussHandler.cpp
SOURCE += src/timer.cpp
TARGETS  = main.o
TARGETS += SDL_rotozoom.out
TARGETS += Asteroid.o
TARGETS += Engine.o
TARGETS += ObjectHandler.o
TARGETS += Rakete.o
TARGETS += Schuss.o
TARGETS += Spieler.o
TARGETS += CollisionHandler.o
TARGETS += global.o
TARGETS += Object.o
TARGETS += PlayerHandler.o
TARGETS += SaveLoadSchuss.o
TARGETS += SchussHandler.o
TARGETS += timer.o
TARGET  = spaceshooter
PREFIX  = /usr/local

all: $(TARGET)

#hintingmode.h: input_hinting_mode.js
#	perl ./js-merge-helper.pl

#SDL_rotozoom: src/SDL_rotozoom.c src/SDL_rotozoom.h
#	$(GCC) $(FLAGS) -I $(INCLUDE) -o SDL_rotozoom src/SDL_rotozoom.c

$(TARGET): $(TARGETS)
	$(GPP) $(FLAGS) -I $(INCLUDE) -Wall -o $(TARGET) $(TARGETS)

%.o: src/%.cpp
	$(GPP) -Wall -g -I $(INCLUDE) -o $@ -c $<


%.out: src/%.c
	$(GCC) -Wall -g -I $(INCLUDE) -o $@  -c $<

clean:
	rm -f $(TARGET) $(TARGETS)

run:
	./$(TARGET)

install: all uninstall
	cp $(TARGET) $(PREFIX)/bin && chmod 755 $(PREFIX)/bin/$(TARGET)
	cp vimprobable.1 $(PREFIX)/man/man1 && chmod 644 $(PREFIX)/man/man1/vimprobable.1

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	rm -f $(PREFIX)/man/man1/vimprobable.1
