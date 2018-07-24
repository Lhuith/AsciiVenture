//RenderText(Vector2(14, 1), L"ITEMS", 0x0000 | 0x00F0);
//RenderPanel(Vector2(5, 10), Vector2(5, 4), 0x000F | 0x0000, cUISprite(Models::UI::pants_00, Vector2(3, 3), Vector2(3, 2), 0x000F));
class TextComponent : public Component {
    std::wstring text;
    WORD color;

    public:
        explicit TextComponent(std::wstring txt = L"BlaBla", WORD c = 0x000F) : text(txt), color(c){}
          WORD GetColor()const{return color;}
          std::wstring GetText()const{return text;}
};

class Text : public Object {
    TextComponent text;

    public:
        explicit Text(Vector2 pos, TextComponent t = TextComponent()) : Object(Transform(pos), L"Text", {"UI"}, {std::make_shared<TextComponent>(t)}), text(t){}
        TextComponent GetText(){return text;}
};

class PanelComponent : public Component {
    Vector2 size;
    WORD color;
    cUISprite UISprite;

    public:
        explicit PanelComponent(Vector2 s = Vector2(1,1), WORD c = 0x000F | 0x0000, cUISprite ui =  cUISprite(L"?", Vector2(3,3), Vector2 (3, 2), 0x000F)):
            size(s), color(c), UISprite(ui){}

        Vector2 GetSize()const{return size;}
        cUISprite GetUISprite()const{return UISprite;}
        WORD GetColor()const{return color;}
};

class Panel : public Object {
    PanelComponent panel;

    public:
        explicit Panel(Vector2 pos, PanelComponent t = PanelComponent()) : 
        Object(Transform(pos), L"Panel", {"UI"}, {std::make_shared<PanelComponent>(t)}), panel(t){}
        PanelComponent GetPanel(){return panel;}
};

class CanvasComponent : public Component {
    WORD color;
    Vector2 size;
    public:
        explicit CanvasComponent(WORD c = 0x0000, Vector2 s = Vector2(1,1)) : color(c), size(s){}
        Vector2 GetSize()const{return size;}
        WORD GetColor()const{return color;}
};

#include "CanvasComponent.cpp"

class Canvas : public Object {
    CanvasComponent canvas;

    public:
        explicit Canvas(Vector2 pos, CanvasComponent t = CanvasComponent()) : 
        Object(Transform(pos), L"Canvas", {"UI"}, {std::make_shared<CanvasComponent>(t)}), canvas(t){}
        CanvasComponent GetCanvas(){return canvas;}
};
