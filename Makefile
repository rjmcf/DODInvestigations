CC := g++
CFLAGS := -lmingw32 -lSDL2main -lSDL2 -Werror -Wall
INCS := -I . -I oopVersion -I sdl/include
LIBS := -L sdl/lib
TARGET := main

all:
	$(CC) $(INCS) $(LIBS) -o $(TARGET) *.cpp oopVersion/animations/*.cpp oopVersion/enemies/*.cpp oopVersion/scene/*.cpp $(CFLAGS)