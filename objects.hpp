#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;


namespace gm {

    //          Color

    class Color {
        private:
        public:
            int r;
            int g;
            int b;
            int a;
            Color() {
                r,g,b,a = 1;
            }
            Color(int gray) {
                r,g,b = gray;
                a = 1;
            }
    };

    //          Position

    class Vector2
    {
    private:
    public:
        float x;
        float y;







        void lookAt(Vector2 destination) {
                //6             10
            if (x > destination.x) {
                x = -x - abs(destination.x);//-4
            } else {
                x = -x + destination.x;//4
            }
            if (y > destination.y) {
                y = -y - abs(destination.y);
            } else {
                y = -y + destination.y;
            }
        }

        void normalize() {
            float __len = len(Vector2(x,y));
            x = x/__len;
            y = y/__len;
        }

        float len(Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
        }

        float distanceTo(Vector2 b) {
        return (float) abs(x - b.x) + abs(y - b.y);
        }

        void multiplyBy(float __val) {
            x,y *= __val;
        }



        Vector2() {
            x,y = 0;
        }
        Vector2(int n, int m) {
            x = n;
            y = m;
        }
        Vector2(float n, float m) {
            x = n;
            y = m;
        }
        ~Vector2();
    };

    Vector2::~Vector2()
    {
    }
    

    class Vector3
    {
    private:
    public:
        float x;
        float y;
        float z;

        Vector3() {
            x,y,z = 0;
        }
        Vector3(int n, int m, int o) {
            x = n;
            y = m;
            z = o;
        }
        Vector3(float n, float m, float o) {
            x = n;
            y = m;
            z = o;
        }
        ~Vector3();
    };

    Vector3::~Vector3()
    {
    }


    ///             Component

    class Component {
        public:
            bool enabled = true;
    };



    ///             Transform

    class Transform {
        public:
            Transform();
            Transform(Vector2 vec);

            Vector2 position = {0,0};
            void setPosition(Vector2 __vec);
            void setPosition(float x, float y);
            void setPosition(int x, int y);
            void addPosition(Vector2 __vec);
            Vector2 getPosition();
    };

    Transform::Transform() {
        position = Vector2(0,0);
    }

    Transform::Transform(Vector2 __vec) {
        this->setPosition(__vec);
    }
    void Transform::setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }
    void Transform::setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }

    void Transform::setPosition(Vector2 vec) {
        this -> position.x = vec.x;
        this -> position.y = vec.y;
    }

    Vector2 Transform::getPosition() {
        return this->position;
    }

    void Transform::addPosition(Vector2 __vec) {
        position.x += __vec.x;
        position.y += __vec.y;
    }



    ///             Renderer

    class Renderer : Component {
        public:
            Renderer();
            ~Renderer();
            Color color();
    };
    Renderer::Renderer() {

    }

    class Animator : Component {
        private:
        public:
            bool is_running;
            float delta;
            float timer;


            Animator(float d) {
                delta = d;
            }
            ~Animator() {

            }
            void start() {
                is_running = true;
            }
            void stop() {
                is_running = false;
                timer = 0;
            }
            void update() {
                if (is_running) {
                    timer += delta;
                }
            }

    };



    ///             GAMEOBJECT


    class GameObject {
        private:
            string name;
            bool active;
            string tag;
        public:
            Transform transform;
            GameObject();
            GameObject(string n);
            ~GameObject();
            void setActive(bool b);
            void update();
            vector<Component> components;
    };

    GameObject::GameObject() {
        this -> name = "Game Object";
        this -> active = true;
    }
    GameObject::GameObject(string n) {
        this -> name = n;
        this -> active = true;
    }
    GameObject::~GameObject() {

    }
    void GameObject::setActive(bool b) {
        this -> active = b;
    }
    void GameObject::update() {
        
    }

    class Grid
    {
    private:
    public:
        int width;
        int height;
        vector<vector<Transform>> columns;
        Vector2 offset = {0,0};

        Transform transform;

        int cell_size;
        int spacing;
        bool centered;
        bool isometric;

        Grid();
        Grid(int x);
        Grid(int x, int y);
        ~Grid();
        void setSize(int x, int y);
        void genGrid();
    };
    
    Grid::Grid()
    {
    }

    Grid::Grid(int x)
    {
        this->setSize(x,x);
    }
    Grid::Grid(int x, int y)
    {
        this->setSize(x,y);
    }
    
    Grid::~Grid()
    {
    }

    void Grid::setSize(int x, int y) {
        this->width=x;
        this->height=y;
    }

    void Grid::genGrid() {
        Vector2 off = this->offset;
        if (this->centered) {
            off = Vector2{(float)this->width / 2, (float)this->height /2};
        }
        if (!this->isometric) {
            for (int c = 0; c < this->width; c++) {
                columns.push_back(vector<Transform>{});
                for (int r = 0; r < this->height; r++) {
                this->columns[c].push_back(Transform(Vector2{(float)c * this->cell_size + this->spacing * c + this->transform.position.x - off.x * (this->cell_size + this->spacing), (float)r * this->cell_size + this->spacing * r + this->transform.position.y - off.y * (this->cell_size + this->spacing)}));
                }
            }
        }
    }

    void print(string __msg) {
        cout<<__msg<<endl;
    }
    void print(Vector2 __msg) {
        for (int i = 0; i<2; i++) {
            std::cout<<'['<<__msg.x<<", "<<__msg.y<<']'<<std::endl;
        }
    }

    float distance(Vector2 a, Vector2 b) {
        return (float) abs(a.x - b.x) + abs(a.y - b.y);
    }


    float vector_len(Vector2 __vec) {
        return sqrt(pow(__vec.x,2) + pow(__vec.y,2));
    }

    Vector2 normalize(Vector2 __vec) {

        return Vector2(__vec.x/vector_len(__vec), __vec.y/vector_len(__vec));
        
    }



}
