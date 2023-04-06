all : main

main : 
	g++ server.cpp -o server -pthread
	g++ main.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -pthread -o main
	
clean:
	rm -rf main server
