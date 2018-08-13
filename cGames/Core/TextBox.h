class LogInfo {
    public:
        LogInfo(std::wstring l, int i) : log(l), occurance(i){};
        std::wstring log;
        int occurance;
        void SetOccarance(int i){occurance = i;}
        void AddOccarance(int i){occurance += i;}
};

inline bool operator==(const LogInfo& left, const LogInfo& right){return left.log == right.log;}
    

struct TextBox {
    int width, posX;
    int height, posY;
    int ScrollY = 0;
    bool isScrollable;

    public:
        explicit TextBox(int x = 1, int y = 1, int w = 1, int h = 1, std::vector<std::wstring> m = {L"poop", L"Dong"}, WORD c = 0x0000 | 0x000F, bool scroll = true) : 
        posX(x), posY(y), width(w), height(h), messages(m), color(c), isScrollable(scroll){}

        WORD color;
        void RenderTextBox(RenderEngine* Renderer);
        void AddToTextBox(std::wstring msg);
        void Log(std::wstring msg);
        void SetRenderer(RenderEngine *re){Renderer = re;}
        std::wstring AddSpace(int size);
        inline void AddToScroll(int i){ if(ScrollY < 1) ScrollY = 1;  ScrollY += i;}
        inline void SetCol(WORD c){color = c;}

        inline int GetWidth() const {return width;}
        inline int GetHeight() const {return height;}

        inline void SetPosX(float x){this->posX = x;}
        inline void SetPosY(float y){this->posY = y;}

        inline int GetPosX() const {return posX;}
        inline int GetPosY() const {return posY;}

        inline void HightLight(int& m_mouseScroll, int& old_mouseScroll, float m_mousePosX, float m_mousePosY);
        inline int GetScreenPosX() const {return posX;}
        inline int GetScreenPosY() const {return posY + Renderer->GetScreenHeight();}

        bool HoverOver(float x, float y);
        
        ~TextBox(){
            delete Renderer;
        }
    protected:
        RenderEngine *Renderer;
        std::vector<LogInfo> logs;
        std::vector<std::wstring> messages;
};

#include "TextBox.cpp"
