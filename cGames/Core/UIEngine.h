#include "TextBox.h"

class UIEngine {

    RenderEngine *Renderer;
    CoreEngine *Core;
    
    float m_mousePosX; 
    float m_mousePosY;

    bool ShowInventory, ShowPause;
    std::vector<Object*> UIElements;

    public:
        explicit UIEngine(TextBox* db = new TextBox(), TextBox* gtb = new TextBox(), RenderEngine *r = new RenderEngine()) :
        DebugTextBox(db), GameTextBox(gtb), Renderer(r){DebugTextBox->SetRenderer(r); GameTextBox->SetRenderer(r);};

        void RenderTextBoxes(){DebugTextBox->DisplayTextBox(); GameTextBox->DisplayTextBox();}

    

        void UpdateUIInput(){m_mousePosX = Core->m_mousePosX; m_mousePosY = Core->m_mousePosY;}

        void SetShowMenu(bool b){ShowInventory = b; if(b == true)ShowPause = false;}
        void SetShowPause(bool b){ShowPause = b; if(b == true)ShowInventory = false;}
        bool GetShowMenuBool(){return ShowInventory;}
        bool HoverOver(Vector2 pos, Vector2 size);

        //---------------------------------UPDATE---------------------------------///////
        void Update(){
            RenderTextBoxes(); 
            UpdateUIInput();
            RenderUIElements();
            UpdateUIElemnts();
            }
        //---------------------------------UPDATE---------------------------------///////

        void Debug(std::wstring msg){DebugTextBox->Log(msg);}

        void Debug(float d){DebugTextBox->Log(s2ws(std::to_string(d)));}

        void Debug(int d){DebugTextBox->Log(s2ws(std::to_string(d)));}

        void Debug(std::string s){DebugTextBox->Log(s2ws(s));}

        void Debug(Vector2 v){DebugTextBox->Log(s2ws(std::to_string((int)round(v.x)) + " " + std::to_string((int)round(v.y))));}
        
        //-------------------------------UI ELEMENTS-------------------------------------/////
        std::vector<Object*> GetUIElements(){return UIElements;}
        Object* GetCanvasAt(int i){return UIElements.at(0);}
        wchar_t RenderIcon(cSprite, int x, int y, bool flipC = false);
        void RenderPanel(PanelComponent p, Vector2 pos); //Render Panels inside Canvas
        void RenderText(TextComponent t, Vector2 pos, Vector2 *PanelSize = nullptr);
        void RenderBackGround(PanelComponent c, Vector2 pos);
        void AddUIElement(Object* c){UIElements.push_back(c); SetUIElement(c);}
        void RenderUIElements();
        void UpdateUIElemnts();
        void SetUIElement();
        void SetUIElement(Object *c);
        //-------------------------------UI ELEMENTS-------------------------------------/////
  
        void ScrollDebugWindow(int i){DebugTextBox->AddToScroll(i);}
        TextBox* GetDebugWindow() const {return DebugTextBox;}
        CoreEngine* GetEngine(){return Core;}
        void SetEngine(CoreEngine* e){this->Core = e;}

        void Init(){SetUIElement();};
        
    protected:
    TextBox *DebugTextBox;
    TextBox *GameTextBox;

    private:
};

#include "UIEngine.cpp"