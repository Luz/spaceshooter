GCC     = gcc
GPP	= g++
LIBS    = sdl
#LIBS   += SDL_image
FLAGS   = `pkg-config  --cflags --libs $(LIBS) ` -lSDL_image -Wall
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

$(TARGET): $(TARGETS)
	$(GPP) $(FLAGS) -o $(TARGET) $(TARGETS)

%.o: src/%.cpp
	$(GPP) -g $(FLAGS) -o $@ -c $<


%.out: src/%.c
	$(GCC) -Wall -g $(FLAGS) -o $@  -c $<

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
