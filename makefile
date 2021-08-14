all: compile link

compile:
	g++ -I src/include -c main.cpp 

link:
	g++ main.o -o "Castle Attack" -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -mwindows