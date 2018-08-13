
class UIComponent : public Component
{
  WORD color, stored_color;
  Vector2 size;
  bool interactive, touching = false;

public:
  explicit UIComponent(WORD c = 0x000F, Vector2 s = Vector2(1, 1), bool b = false) : color(c), size(s), stored_color(c), interactive(b) {}

  Vector2 GetSize() const { return size; }
  Vector2 *GetSizeRef() { return &size; }

  WORD GetColor() const { return color; }
  void SetColor(WORD c) { this->color = c; }
  WORD GetStoredGetColor() const { return stored_color; }

  void Setinteractive(bool b) { interactive = b; }
  bool Getinteractive() { return interactive; }

  void Settouching(bool b) { touching = b; }
  bool Gettouching() { return touching; }
  virtual void HoverOver(float mousex, float mousey, bool clicked, bool held);
  void OverrideColor(WORD c)
  {
    this->color = c;
    this->stored_color = c;
  }

  void Update()
  {
  }

};

#include "UIComponent.cpp"

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
  void SetText(std::wstring t) { text = t; }
  void AddText(std::wstring t) { text = text + t; }
  void HoverOver(float mousex, float mousey, bool clicked, bool held, UIComponent* parent = nullptr);
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
  bool interactive, touching = false;

public:
  cUISpriteComponent(std::wstring m = L"?", Vector2 s = Vector2(0, 0), Vector2 c = Vector2(0, 0), WORD col = 0x000F, bool b = false)
      : cSprite(m, s, c, col), interactive(b){};
  void RendercSprite(RenderEngine *Renderer);

  void Setinteractive(bool b) { interactive = b; }
  bool Getinteractive() { return interactive; }

  void Settouching(bool b) { touching = b; }
  bool Gettouching() { return touching; }
  void HoverOver(float mousex, float mousey, bool clicked, bool held);

  void Update()
  {
  }
};

#include "cUISpriteComponent.cpp"

class CUISprite : public Object
{
  cUISpriteComponent sprite;

public:
  explicit CUISprite(Vector2 pos, cUISpriteComponent s = cUISpriteComponent()) : Object(Transform(pos), L"Sprite", {"UI"},
                                                                                        {std::make_shared<cUISpriteComponent>(s)}),
                                                                                 sprite(s) {}
  cUISpriteComponent GetUISprite() { return sprite; }
};

class CheckBoxComponent : public UIComponent
{
  bool Checked;

public:
  CheckBoxComponent(WORD c = 0x000F | 0x0000, bool b = false)
      : Checked(false), UIComponent(c, Vector2(1, 1), b) {}
  void RenderCheckBox(RenderEngine *Renderer);
  void HoverOver(float mousex, float mousey, bool clicked, bool held);
  bool GetIfChecked(){return Checked;}
};

#include "CheckBoxComponent.cpp"

class CheckBox : public Object
{
  CheckBoxComponent checkbox;

public:
  explicit CheckBox(Vector2 pos, CheckBoxComponent cx = CheckBoxComponent()) : Object(Transform(pos), L"CheckBox", {"UI"}, {std::make_shared<CheckBoxComponent>(cx)}), checkbox(cx) {}
  CheckBoxComponent &GetCheckBox() { return checkbox; }
};

class SliderComponent : public UIComponent
{
  Vector2 Start, End;
  float value;

public:
  SliderComponent(Vector2 s = Vector2(0, 0), Vector2 e = Vector2(2, 0), WORD c = 0x000F | 0x0000, bool b = false)
      : Start(s), End(e), UIComponent(c, Vector2(distance(s, e), 1), b) {value = 4;}
  Vector2 GetEnd(){return End;}
  void RenderSlider(RenderEngine *Renderer);
  void HoverOver(float mousex, float mousey, bool clicked, bool held);
};

#include "SliderComponent.cpp"

class Slider : public Object
{
  SliderComponent slider;

public:
  explicit Slider(Vector2 pos, SliderComponent s = SliderComponent()) 
  : Object(Transform(pos), L"Slider", {"UI"}, {std::make_shared<SliderComponent>(s)}), slider(pos, s.GetEnd(), s.GetColor(), s.Getinteractive()) {}
  SliderComponent &GetSlider() { return slider; }
};

class PanelComponent : public UIComponent
{

public:
  explicit PanelComponent(Vector2 s = Vector2(1, 1), WORD c = 0x000F | 0x0000, bool b = false) : UIComponent(c, s, b) {}

  void RenderPanel(RenderEngine *Renderer);
  void RenderBackGround(RenderEngine *Renderer);
  //bool HoverOver(float mousex, float mousey, Vector2 pos, Vector2 size);
  void HandleChildInterAction(int i, RenderEngine *Renderer, float mX, float mY, bool clicked, bool held);
  void InteractWithElement(PanelComponent &p, float mX, float mY, bool clicked, bool held);
  void InteractWithElement(TextComponent &t, float mX, float mY, bool clicked, bool held);
  void InteractWithElement(cUISpriteComponent &c, float mX, float mY, bool clicked, bool held);
  void InteractWithElement(SliderComponent &sl, float mX, float mY, bool clicked, bool held);
  void InteractWithElement(CheckBoxComponent &bx, float mX, float mY, bool clicked, bool held);
  void CheckInteractions(RenderEngine *Renderer, float mX, float mY, bool clicked, bool held);

  void RenderChildren(int i, RenderEngine *Renderer);

protected:
};
#include "PanelComponent.cpp"

class Panel : public Object
{
  PanelComponent panel;
public:
  explicit Panel(Vector2 pos, PanelComponent p = PanelComponent()) : 
  Object(Transform(pos), L"Panel", {"UI"}, {std::make_shared<PanelComponent>(p)}), panel(p) {};
  PanelComponent &GetPanel() { return panel; }
};
