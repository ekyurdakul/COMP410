CFLAGS = -std=c++14 -O3 -Wall -lGL -lGLU -lglut
OBJECTS = main.o lodepng.o Vector3D.o Point.o OrbitalBody.o SkyBox.o Camera.o FPSMeter.o Textures.o
EXEC = main

%.o: %.cpp
	g++ -c -o $@ $^ $(CFLAGS)

$(EXEC): $(OBJECTS)
	g++ -o $@ $^ $(CFLAGS)

all: $(EXEC)

run:
	-./$(EXEC)

clean:
	-rm *.o $(EXEC)

.PHONY: all run clean