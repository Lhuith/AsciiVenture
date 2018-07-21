void InitInventory()
{
     RenderEngine *r = Engine->GetRenderer();

    Inventory = new Canvas(Vector2(0,0), CanvasComponent(0x0000 , Vector2(r->GetScreenWidth(), r->GetScreenHeight())));
    
    //RenderText(Vector2(14, 1), L"ITEMS", 0x0000 | 0x00F0);
//
    ////Gear UI
    //RenderPanel(Vector2(2, 2), Vector2(11, 15), 0x00F0);
    //RenderText(Vector2(2, 1), L"GEAR", 0x0000 | 0x00F0);
    ////Head Slot
    //RenderPanel(Vector2(5, 3), Vector2(5, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::head_00, Vector2(3, 2), Vector2(3, 2), 0x000F));
//
    ////Chest Slot
    //RenderPanel(Vector2(4, 6), Vector2(7, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::chest_00, Vector2(5, 3), Vector2(3, 2), 0x000F));
//
    ////Pants Slot
    //RenderPanel(Vector2(5, 10), Vector2(5, 4), 0x000F | 0x0000,
    //            cSprite(Models::UI::pants_00, Vector2(3, 3), Vector2(3, 2), 0x000F));
//
    ////Glove Slot
    ////Left Side
    //RenderPanel(Vector2(2, 9), Vector2(3, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F));
    ////Right Side
    //RenderPanel(Vector2(10, 9), Vector2(3, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F));
//
    ////Boot Slot
    ////Left Side
    //RenderPanel(Vector2(4, 14), Vector2(4, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::boots_00, Vector2(2, 2), Vector2(3, 2), 0x000F));
    ////Right Side
    //RenderPanel(Vector2(7, 14), Vector2(4, 3), 0x000F | 0x0000,
    //            cSprite(Models::UI::boots_00_b, Vector2(2, 2), Vector2(3, 2), 0x000F));
//
    ////Render Inventory
    ////if(Core->GetSceneAt(0)->objects
    ////Charcter Player;
    ////for(int i = 0; i < )
//
    //for (int i = 0; i < 9; i++)
    //    for (int j = 0; j < 4; j++)
    //    {
    //        int sizeX = 3;
    //        int sizeY = 3;
    //        RenderPanel(Vector2(((i * (sizeX + 1))) + 14, (j * (sizeY + 1)) + 2), Vector2(sizeX, sizeY), 0x00F0);
    //    }
//
    ////Inventory Description
    //RenderText(Vector2(Renderer->GetScreenWidth() - 15, 1), L"DESCRIPTION", 0x0000 | 0x00F0);
    //RenderPanel(Vector2(Renderer->GetScreenWidth() - 15, 2), Vector2(13, 15), 0x00F0);
}

