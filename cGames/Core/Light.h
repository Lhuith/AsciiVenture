
class Light : public Component{
    float intensity;
    WORD color;

    public:
        explicit Light(float i = 0.5f, WORD c = 0x000F) : intensity(i), color(c){}
        inline void SetIntensity(float i){this->intensity = i;}
        inline float GetI()const{return intensity;}
        inline WORD GetC()const{return color;}
        inline void SetI(float i){this->intensity = i;}
        inline void AddToI(float i){this->intensity += (intensity >= 0.01) ? i : 0.01;}
        inline void SetC(WORD c){this->color = c;}
        void Update(){}
        void Init(){}
    private:


};

