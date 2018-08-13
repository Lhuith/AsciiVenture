
void InitMenu()
{
    RenderEngine *r = Engine->GetRenderer();

    Menu = new Panel(Vector2(0,0), PanelComponent(Vector2(r->GetScreenWidth(), r->GetScreenHeight()), 0x0000));
    //Vector2(0,0) , PanelComponent( , ))
    int hOffset = 2;

    Menu->AddChild(new Text(Vector2(0, r->GetScreenHeight() / 2.0 - 7 + hOffset), TextComponent( L"Paused", 0x000F)));
    //Op->ion Pointer
    Menu->AddChild(new Text(Vector2(0 - 6, (r->GetScreenHeight() / 2.0) - 5 + hOffset), TextComponent( L">>", 0x000F)));
    Menu->AddChild(new Text(Vector2(0, (r->GetScreenHeight() / 2.0) - 5 + hOffset), TextComponent( L"Continue", 0x000F)));
    Menu->AddChild(new Text(Vector2(0 + 1, (r->GetScreenHeight() / 2.0) - 4 + hOffset), TextComponent( L"Options", 0x000F)));
    Menu->AddChild(new Text(Vector2(0, (r->GetScreenHeight() / 2.0) - 3 + hOffset), TextComponent( L"Save", 0x000F)));
    Menu->AddChild(new Text(Vector2(0, (r->GetScreenHeight() / 2.0) - 2 + hOffset), TextComponent( L"Load", 0x000F)));
    Menu->AddChild(new Text(Vector2(0, (r->GetScreenHeight() / 2.0) - 1 + hOffset), TextComponent( L"Quit", 0x000F)));

    CheckBox* DebugCheckBox = new CheckBox(Vector2(2, (r->GetScreenHeight() / 2.0) - 4 + hOffset), CheckBoxComponent(0x000D|0x00F0, true));

    Menu->AddChild(new Slider(Vector2(2, (r->GetScreenHeight() / 2.0) - 2 + hOffset), SliderComponent(Vector2(0,0), Vector2(10,0), 0x000D | 0x00F0, true)));
    Menu->AddChild(DebugCheckBox);

    Menu->SetActive(false);
    Engine->GetUI()->AddUIElement(Menu);
}