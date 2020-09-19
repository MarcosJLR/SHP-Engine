
CC = g++
MODULES = Collisions Core Graphics Object Physics Input AI
SRC_DIR = $(addprefix src\, $(MODULES))
INCLUDE_PATHS = -IC:\MinGWDevLib\include\SDL2 $(addprefix -I, $(SRC_DIR))
LIBRARY_PATHS = -LC:\MinGWDevLib\lib
CFLAGS = -Wall -O2 -std=c++17
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
OBJ_FILES = vector3D.o Kinematic.o TextureManager.o Engine.o \
            CollisionHandler.o Collider.o Timer.o InputHandler.o \
            Character.o Player.o Seek.o Arrive.o Align.o Face.o \
            Pursue.o LookWhereYoureGoing.o VelocityMatch.o
OBJS = $(addprefix obj\, $(OBJ_FILES))

shp: src\Main.cpp $(OBJS)
	$(CC) $< $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) $(LFLAGS) -o $@   

obj\vector3D.o: src\Physics\vector3D.cpp src\Physics\vector3D.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@ 

obj\Kinematic.o: src\Physics\Kinematic.cpp src\Physics\Kinematic.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@ 

obj\TextureManager.o: src\Graphics\TextureManager.cpp src\Graphics\TextureManager.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Engine.o: src\Core\Engine.cpp src\Core\Engine.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Timer.o: src\Core\Timer.cpp src\Core\Timer.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Collider.o: src\Collisions\Collider.cpp src\Collisions\Collider.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\CollisionHandler.o: src\Collisions\CollisionHandler.cpp src\Collisions\CollisionHandler.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\InputHandler.o: src\Input\InputHandler.cpp src\Input\InputHandler.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Character.o: src\Object\Character.cpp src\Object\Character.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Player.o: src\Object\Player.cpp src\Object\Player.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Seek.o: src\AI\Seek.cpp src\AI\Seek.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Arrive.o: src\AI\Arrive.cpp src\AI\Arrive.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Align.o: src\AI\Align.cpp src\AI\Align.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Face.o: src\AI\Face.cpp src\AI\Face.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\LookWhereYoureGoing.o: src\AI\LookWhereYoureGoing.cpp src\AI\LookWhereYoureGoing.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\Pursue.o: src\AI\Pursue.cpp src\AI\Pursue.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

obj\VelocityMatch.o: src\AI\VelocityMatch.cpp src\AI\VelocityMatch.hpp
	$(CC) -c $< $(INCLUDE_PATHS) $(CFLAGS) -o $@

