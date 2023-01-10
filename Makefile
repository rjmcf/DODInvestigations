CC := g++
CFLAGS := -lmingw32 -lSDL2main -lSDL2 -Werror -Wall
INCS := -I . -I oopVersion -I sdl/include
LIBS := -L sdl/lib
TARGET := main
SRCS := *.cpp oopVersion/animations/*.cpp oopVersion/enemies/*.cpp oopVersion/scene/*.cpp oopVersion/events/*.cpp 

all:
	$(CC) $(INCS) $(LIBS) -o $(TARGET) $(SRCS) $(CFLAGS)

asm:
	$(CC) $(INCS) $(LIBS) -S -fverbose-asm -O2 $(SRCS) $(CFLAGS)