#tic tac toe makefile

#OBJS specifies which files to compile as part of the project
OBJS = x_o.cpp Position.h Position.cpp AI.h AI.cpp Player.h Player.cpp Game.h Game.cpp Grid.h Grid.cpp Tile.cpp Tile.h Win_Case.cpp Win_Case.h

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lsqlite3

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = X_O

#This is the target that compiles our executable. for sdl2 ->$(LINKER_FLAGS)
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clean : $(OBJ_NAME)
	rm -f $(OBJ_NAME) echo "clean done"
	
