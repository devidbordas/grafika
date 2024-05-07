all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/fire.c src/ice_element.c src/iceball.c src/trophy.c src/skybox.c src/map.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o iceball.exe -Wall -Wextra -Wpedantic 

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/fire.c src/ice_element.c src/iceball.c src/trophy.c src/skybox.c src/map.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o iceball -Wall -Wextra -Wpedantic 
