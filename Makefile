
OBJS = $(wildcard $(SCR_PATH)/*.cpp)

OBJ_NAME = game

CC = g++

SCR_PATH = scr

INCLUDE_PATHS = -I.\include

LIBRARY_PATHS = -L.\lib

FLAGS = -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wall

all : $(OBJS)
	g++ $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(FLAGS) -o $(OBJ_NAME)
