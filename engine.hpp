#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>

#include <chrono>
#include <thread>
#include <unistd.h>
#include <functional>

#include <MCGE/objects.hpp>


using namespace std::chrono;
using namespace std;



sf::VideoMode video_mode(800,600);

namespace gm {

    ///             GAME


    class Game {
    private:
        int scr_width;
        int scr_height;
        string game_name;
        bool full_scr;
        bool is_running;
        int frame_rate;
        float delta;
        int frames;
        float time;
        vector<string> tags;
    public:
	//Path to textures folder
        string textures_path;
        string fonts_path;
        string sounds_path;
        sf::RenderWindow *window_ptr;
        vector<GameObject> objects;
        vector<vector<sf::Sprite>> layers;
        Game();
        ~Game();
	//Returns true if game is running.
        bool isRunning();
	//Returns true if game is in fullscreen.
        bool isFullScreen();

	//Returns screen width. 
        int getScreenWidth();
	//Returns screen height.
        int getScreenHeight();
	//Returns number of current frame.
        int getFrameNo();

	//Returns time between frames.
        float getDelta();

	//Sets resolution as x-width, y-height.
        void setResolution(int x, int y);
	//Sets fullscreen mode if b == true.
        void setFullScreen(bool b);
	//Sets framerate as f.
        void setFrameRate(float f);
	//Sets name of game instance.
        void setName(string name);

	//Put this before start().
        void awake();
	//Starts program.
        void start(function<void ()> upd,function<void ()> str);
        //Runs every frame.
	void update();

    };
    //constructors / destructors




    Game::Game() {
        this -> scr_width = 800;
        this -> scr_height = 600;
        this -> frames = 0;
        this -> full_scr = false;
        this -> is_running = false;
        this -> frame_rate = 60;
        this -> textures_path = "assets/sprites/";
        this -> fonts_path = "assets/fonts/";
        this -> sounds_path = "assets/sounds/";
    }
    Game::~Game() {
        this -> is_running = false;
        cout<<"Wygenerowano " << frames << " klatek.\n";
        cout<<"Chodzilo przez "<<(float) (delta * frames) / 1000000<<" sekund.\n";
        cout<<"Ending"<<endl;
    }


    //global functions




    void Game::awake() {
        cout<<"Starting..."<<endl;
        this -> delta = 1000000 / frame_rate;
        this -> is_running = true;
    }
    void Game::start(function<void ()> upd, function<void ()> str) {
        sf::RenderWindow win(video_mode, game_name, isFullScreen() ? sf::Style::Fullscreen : sf::Style::Default);
        str();
        this -> window_ptr = &win;
        while (isRunning()) {
            while (win.isOpen())
            {
            sf::Event event;
                while (win.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        win.close();
                }
                win.clear();
                auto start = high_resolution_clock::now();
                update();
                upd();
                win.display();
                auto stop = high_resolution_clock::now();
                auto dur = duration_cast<microseconds>(stop - start);
                //if (frames < 10) {
                //    cout<<delta<<endl;
                //    cout<<dur.count()<<endl;
                //}
                if (dur.count() < delta) {
                    usleep(delta-dur.count());
                }
            }
            this -> is_running = false;
        }
    }
    void Game::update() {
        frames++;
        //cout<<"update "<<frames<<endl;
        //for (int i = 0; i < objects.size();i++) {
        //    this -> objects[i].update();
        //}
    }

    //setters



    void Game::setResolution(int x, int y) {
        this -> scr_width = x;
        this -> scr_height = y;

        video_mode = sf::VideoMode(x,y);
    }
    void Game::setFullScreen(bool b) {
        this -> full_scr = b;
    }
    void Game::setFrameRate(float f) {
        this -> frame_rate = f;
    }
    void Game::setName(string name) {
        this -> game_name = name;
    }


    //getters



    bool Game::isFullScreen() {
        return this -> full_scr;
    }
    bool Game::isRunning() {
        return this -> is_running;
    }

    int Game::getScreenHeight() {
        return this -> scr_height;
    }
    int Game::getScreenWidth() {
        return this -> scr_width;
    }
    int Game::getFrameNo() {
        return this -> frames;
    }
    
    float Game::getDelta() {
        return this->delta/1000000;
    }

    sf::Vector2f vec_to_sf(gm::Vector2 vec) {
        return sf::Vector2f{vec.x,vec.y};
    }



}
