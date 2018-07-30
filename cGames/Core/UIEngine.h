#include "TextBox.h"

class UIEngine
{

    RenderEngine *Renderer;
    CoreEngine *Core;

    int m_mousePosX;
    int m_mousePosY;

    std::vector<Object *> UIElements;

  public:
    explicit UIEngine(TextBox *gtb = new TextBox(), RenderEngine *r = new RenderEngine()) : GameTextBox(gtb), Renderer(r)
    {
        //will define debug  textbox internally
        DebugTextBox = new TextBox(1, 1, 20, 5, {L"Debug"}, 0x0000 | 0x00F0);

        DebugTextBox->SetRenderer(r);
        GameTextBox->SetRenderer(r);
    };


    void UpdateUIInput()
    {
        m_mousePosX = Core->m_mousePosX;
        m_mousePosY = Core->m_mousePosY;
    }

    bool HoverOver(Vector2 pos, Vector2 size);

    //---------------------------------UPDATE---------------------------------///////
    void Update()
    {
        UpdateUIElemnts();
        UpdateUIInput();

        GameTextBox->RenderTextBox(Renderer);

        RenderUIElements();

        DebugTextBox->RenderTextBox(Renderer);
    }
    //---------------------------------UPDATE---------------------------------///////

    void Debug(std::wstring msg) { DebugTextBox->Log(msg); }
    void Debug(float d) { DebugTextBox->Log(s2ws(std::to_string(d))); }
    void Debug(int d) { DebugTextBox->Log(s2ws(std::to_string(d))); }
    void Debug(std::string s) { DebugTextBox->Log(s2ws(s)); }
    void Debug(Vector2 v) { DebugTextBox->Log(s2ws(std::to_string((int)round(v.x)) + " " + std::to_string((int)round(v.y)))); }

    //-------------------------------UI ELEMENTS-------------------------------------/////
    std::vector<Object *> GetUIElements() { return UIElements; }
    Object *GetCanvasAt(int i) { return UIElements.at(0); }
    void AddUIElement(Object *c)
    {
        UIElements.push_back(c);
        SetUIElement(c);
    }
    void RenderUIElements();
    void UpdateUIElemnts();
    void SetUIElement();
    void SetUIElement(Object *c);
    //-------------------------------UI ELEMENTS-------------------------------------/////

    void ScrollDebugWindow(int i) { DebugTextBox->AddToScroll(i); }
    TextBox *GetDebugWindow() const { return DebugTextBox; }
    CoreEngine *GetEngine() { return Core; }
    void SetEngine(CoreEngine *e) { this->Core = e; }

    void Init() { SetUIElement(); };

  protected:
    TextBox *DebugTextBox;
    TextBox *GameTextBox;
  private:
};

#include "UIEngine.cpp"