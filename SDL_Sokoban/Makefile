TARGET:= game
CSRCS:= $(wildcard *.c)
HDRS:= $(wildcard *.h)

SDL_FLAGS:=`pkg-config --libs sdl2`
SDL_IMAGE_FLAGS:=`pkg-config --libs sdl2_image`
CC:= gcc

${TARGET} : $(CSRCS) $(HDRS)
	@$(CC) -o $@ $< $(SDL_FLAGS) $(SDL_IMAGE_FLAGS)

clean: 
	rm -f *.o