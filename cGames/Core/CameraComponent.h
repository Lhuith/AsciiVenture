class CameraComponent : public Component{

    int nScreenWidth;
    int nScreenHeight;

    public:
        explicit CameraComponent(int w = 1, int h = 1) : nScreenWidth(w), nScreenHeight(h){}  
        inline int GetWidth(){return nScreenWidth;}
        inline int GetHeight(){return nScreenHeight;}
};

#include "CameraComponent.cpp"
