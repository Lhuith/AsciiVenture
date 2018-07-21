
void InitMenu()
{
    RenderEngine *r = Engine->GetRenderer();

    Menu = new Canvas(Vector2(0,0) , CanvasComponent(0x0000 , Vector2(r->GetScreenWidth(), r->GetScreenHeight())));

    int hOffset = 2;

    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0, r->GetScreenHeight() / 2.0 - 7 + hOffset), TextComponent( L"Paused", 0x000F)));
    //Op->ion Pointer
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0 - 6, (r->GetScreenHeight() / 2.0) - 5 + hOffset), TextComponent( L">>", 0x000F)));
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0, (r->GetScreenHeight() / 2.0) - 5 + hOffset), TextComponent( L"Continue", 0x000F)));
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0 + 1, (r->GetScreenHeight() / 2.0) - 4 + hOffset), TextComponent( L"Options", 0x000F)));
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0, (r->GetScreenHeight() / 2.0) - 3 + hOffset), TextComponent( L"Save", 0x000F)));
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0, (r->GetScreenHeight() / 2.0) - 2 + hOffset), TextComponent( L"Load", 0x000F)));
    Menu->AddChild(new Text(Vector2(r->GetScreenWidth() / 2.0, (r->GetScreenHeight() / 2.0) - 1 + hOffset), TextComponent( L"Quit", 0x000F)));
    Menu->SetActive(false);
    Engine->GetUI()->AddCanvas(Menu);
}