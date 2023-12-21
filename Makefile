all: build run

build: compile link

compile:
	g++ -c main.cpp -static

link:
	g++ main.o -o main -DSFML_STATIC -Lsrc/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32

run:
	main.exe