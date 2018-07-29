
class UIComponent : public Component
{
  WORD color, stored_color;
  Vector2 size;
  bool hover;

public:
  explicit UIComponent(WORD c = 0x000F, Vector2 s = Vector2(1, 1), bool b = false) : color(c), size(s), stored_color(c), hover(b) {}

  Vector2 GetSize() const { return size; }
  Vector2 *GetSizeRef() { return &size; }

  WORD GetColor() const { return color; }
  void SetColor(WORD c) { this->color = c; }
  WORD GetStoredGetColor() const { return stored_color; }
  void Sethover(bool b) { hover = b; }
  void OverrideColor(WORD c)
  {
    this->color = c;
    this->stored_color = c;
  }
};

class TextComponent : public UIComponent
{
  std::wstring text;

public:
  enum Alignment
  {
    C,
    L,
    R
  } Align;

  explicit TextComponent(std::wstring txt = L"BlaBla", WORD c = 0x000F, Alignment a = C, bool b = false) : text(txt), Align(a), UIComponent(c, Vector2(txt.size(), 1), b) {}
  std::wstring GetText() const { return text; }
  Alignment GetAlignment() const { return Align; }
  void RenderText(RenderEngine *Renderer, Vector2 *PanelSize = nullptr);
};
#include "TextComponent.cpp"

class Text : public Object
{
  TextComponent text;

public:
  explicit Text(Vector2 pos, TextComponent t = TextComponent()) : Object(Transform(pos), L"Text", {"UI"}, {std::make_shared<TextComponent>(t)}), text(t) {}
  TextComponent GetText() { return text; }
};

class cUISpriteComponent : public cSprite
{
  bool hover;
public:
  cUISpriteComponent(std::wstring m = L"?", Vector2 s = Vector2(0, 0), Vector2 c = Vector2(0, 0), WORD col = 0x000F, bool b = false)
      : cSprite(m, s, c, col), hover(b){};
  void RendercSprite(RenderEngine *Renderer);
    void Sethover(bool b) { hover = b; }
};

#include "cUISpriteComponent.cpp"

class CUISprite : public Object
{
  cUISpriteComponent sprite;

public:
  explicit CUISprite(Vector2 pos, cUISpriteComponent s = cUISpriteComponent()) : Object(Transform(pos), L"Sprite", {"UI"},
      {std::make_shared<cUISpriteComponent>(s)}), sprite(s) {}
  cUISpriteComponent GetUISprite() { return sprite; }

};

class PanelComponent : public UIComponent
{

public:
  explicit PanelComponent(Vector2 s = Vector2(1, 1), WORD c = 0x000F | 0x0000, bool b = false) : UIComponent(c, s, b) {}

  void RenderPanel(RenderEngine *Renderer, float mX, float mY);
  void RenderBackGround(RenderEngine *Renderer);
  bool HoverOver(float mousex, float mousey, Vector2 pos, Vector2 size);
  void HandleChildElements(int i, RenderEngine* Renderer, float mX, float mY);
  void InteractWithChildElement(PanelComponent& p, float mX, float mY);
  void InteractWithChildElement(TextComponent& t, float mX, float mY);
  void InteractWithChildElement(cUISpriteComponent& c, float mX, float mY);
  
protected:
};
#include "PanelComponent.cpp"

class Panel : public Object
{
  PanelComponent panel;

public:
  explicit Panel(Vector2 pos, PanelComponent t = PanelComponent()) : Object(Transform(pos), L"Panel", {"UI"}, {std::make_shared<PanelComponent>(t)}), panel(t) {}
  PanelComponent &GetPanel() { return panel; }
};
