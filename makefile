#tic tac toe makefile

#OBJS specifies which files to compile as part of the project
OBJS = x_o.cpp

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
