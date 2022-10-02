//running by MeowCat Game Engine
//COMPILE THIS FILE

#include <MCGE/engine.hpp>

gm::Game main_game;

//is called before first frame
void start() {

}
//is called every frame
void update() {

}

int main() {

    main_game.setFrameRate(60);
    main_game.setResolution(1280,720);



    main_game.awake();
    main_game.start(update,start);

    return 0;
}