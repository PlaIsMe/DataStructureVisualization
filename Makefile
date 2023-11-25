all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp utils.cpp menu.cpp page.cpp sort.cpp linked_list.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf