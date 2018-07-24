void InitInventory()
{
    RenderEngine *r = Engine->GetRenderer();

    Inventory = new Canvas(Vector2(0, 0), CanvasComponent(0x0000, Vector2(r->GetScreenWidth(), r->GetScreenHeight())));

    //Title
    Inventory->AddChild(new Text(Vector2(15, 1), TextComponent(L"ITEMS", 0x0000 | 0x00F0)));

    //MainPanel
    Inventory->AddChild(new Panel(Vector2(2, 2), PanelComponent(Vector2(11, 15), 0x00F0)));
    Inventory->AddChild(new Text(Vector2(2, 1), TextComponent(L"GEAR", 0x0000 | 0x00F0)));

    Inventory->AddChild(new Panel(Vector2(6, 3), PanelComponent(Vector2(5, 3), 0x000F | 0x0000,
                                                                cUISprite(Models::UI::head_00, Vector2(3, 2), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(5, 6), PanelComponent(Vector2(7, 3), 0x000F | 0x0000,
                                                                cUISprite(Models::UI::chest_00, Vector2(5, 3), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(6, 10), PanelComponent(Vector2(5, 4), 0x000F | 0x0000,
                                                                 cUISprite(Models::UI::pants_00, Vector2(3, 3), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(3, 9), PanelComponent(Vector2(3, 3), 0x000F | 0x0000,
                                                                cUISprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(11, 9), PanelComponent(Vector2(3, 3), 0x000F | 0x0000,
                                                                 cUISprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(5, 14), PanelComponent(Vector2(4, 3), 0x000F | 0x0000,
                                                                 cUISprite(Models::UI::boots_00_b, Vector2(2, 2), Vector2(3, 2), 0x000F))));

    Inventory->AddChild(new Panel(Vector2(8, 14), PanelComponent(Vector2(4, 3), 0x000F | 0x0000,
                                                                 cUISprite(Models::UI::boots_00, Vector2(2, 2), Vector2(3, 2), 0x000F))));

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 4; j++)
        {
            int sizeX = 3;
            int sizeY = 3;
            Item item = Item();

            if (Player->GetComponent<Character>() != nullptr)
            {
                if (Player->GetComponent<Character>()->GetInventoryAt(j * 9 + i) != nullptr)
                {
                    item = *Player->GetComponent<Character>()->GetInventoryAt(i);
                    Debug(item.object->GetName());
                    Inventory->AddChild(new Panel(Vector2(((i * (sizeX + 1))) + 14, (j * (sizeY + 1)) + 2),
                                                  PanelComponent(Vector2(sizeX, sizeY), 0x00F0,
                                                                 cUISprite(
                                                                     item.getUISprite()->GetM(), item.getUISprite()->GetSize(), Vector2(1, 1), item.getUISprite()->GetCol()))));
                }
                else
                {
                    //Inventory->AddChild(new Panel(Vector2(((i * (sizeX + 1))) + 14, (j * (sizeY + 1)) + 2),
                    //                              PanelComponent(Vector2(sizeX, sizeY), 0x00F0,
                    //                                             cUISprite(Models::UI::potion_00, Vector2(3, 3), Vector2(1, 1), 0x000F))));
                }//
            }
        }
    //
    ////Inventory Description
    //RenderText(Vector2(Renderer->GetScreenWidth() - 15, 1), L"DESCRIPTION", 0x0000 | 0x00F0);
    //RenderPanel(Vector2(Renderer->GetScreenWidth() - 15, 2), Vector2(13, 15), 0x00F0);

    Inventory->AddChild(new Text(Vector2(r->GetScreenWidth() - 9, 1), TextComponent(L"DESCRIPTION", 0x0000 | 0x00F0)));
    Inventory->AddChild(new Panel(Vector2(r->GetScreenWidth() - 15, 2), PanelComponent(Vector2(13, 15), 0x00F0)));

    Inventory->SetActive(false);
    Engine->GetUI()->AddCanvas(Inventory);
}
