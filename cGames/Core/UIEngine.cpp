//void UIEngine::RenderText(Vector2 pos, std::wstring text, WORD col)
//{
//    for (int i = 0; i < text.size() + 1; i++)
//    {
//        Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + ((int)pos.x + i), text[i]);
//        Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + ((int)pos.x + i), col);
//    }
//}

wchar_t UIEngine::RenderSlot(cSprite c, int x, int y, bool flipC)
{
    wchar_t wc;

    if (x >= c.GetSize().x || y >= c.GetSize().y || x < 0 || y < 0)
    {
        wc = ' ';
    }
    else
    {
        if (!flipC)
            wc = c.GetM()[y * c.GetSize().x + x];
        else
            wc = c.GetMflipped()[y * c.GetSize().x + x];
    }

    return wc;
}

void UIEngine::Inventory()
{
    //for (int nx = 0; nx < Renderer->GetScreenWidth(); nx++)
    //    for (int ny = 0; ny < Renderer->GetScreenHeight(); ny++)
    //    {
    //        CHAR_INFO att;
    //        att.Char.UnicodeChar = ' ';
    //        att.Attributes = 0x0000;
    //        Renderer->SetScreenCharAt(ny * Renderer->GetScreenWidth() + nx, att);
    //    }
    //
    //RenderText(Vector2(14, 1), L"ITEMS", 0x0000 | 0x00F0);
    //
    ////Gear UI
    //RenderPanel(Vector2(2, 2), Vector2(11, 15), 0x00F0);
    //RenderText(Vector2(2, 1), L"GEAR", 0x0000 | 0x00F0);
    ////Head Slot
    //RenderPanel(Vector2(5, 3), Vector2(5, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::head_00, Vector2(3, 2), Vector2(3, 2), 0x000F));
    //
    ////Chest Slot
    //RenderPanel(Vector2(4, 6), Vector2(7, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::chest_00, Vector2(5, 3), Vector2(3, 2), 0x000F));
    //
    ////Pants Slot
    //RenderPanel(Vector2(5, 10), Vector2(5, 4), 0x000F | 0x0000,
    //            cUISprite(Models::UI::pants_00, Vector2(3, 3), Vector2(3, 2), 0x000F));
    //
    ////Glove Slot
    ////Left Side
    //RenderPanel(Vector2(2, 9), Vector2(3, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F));
    ////Right Side
    //RenderPanel(Vector2(10, 9), Vector2(3, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::gloves_00, Vector2(1, 1), Vector2(3, 2), 0x000F));
    //
    ////Boot Slot
    ////Left Side
    //RenderPanel(Vector2(4, 14), Vector2(4, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::boots_00, Vector2(2, 2), Vector2(3, 2), 0x000F));
    ////Right Side
    //RenderPanel(Vector2(7, 14), Vector2(4, 3), 0x000F | 0x0000,
    //            cUISprite(Models::UI::boots_00_b, Vector2(2, 2), Vector2(3, 2), 0x000F));
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
void UIEngine::Menu()
{
    //for (int nx = 0; nx < Renderer->GetScreenWidth(); nx++)
    //    for (int ny = 0; ny < Renderer->GetScreenHeight(); ny++)
    //    {
    //        CHAR_INFO att;
    //
    //        att.Char.UnicodeChar = ' ';
    //        att.Attributes = 0x000F;
    //        Renderer->SetScreenCharAt(ny * Renderer->GetScreenWidth() + nx, att);
    //    }
    //
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, 4.0), L"Paused");
    //
    ////Option Pointer
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0 - 2, Renderer->GetScreenHeight() / 2.0), L">>");
    //
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, Renderer->GetScreenHeight() / 2.0), L"Continue");
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, Renderer->GetScreenHeight() / 2.0 + 1), L"Options");
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, Renderer->GetScreenHeight() / 2.0 + 2), L"Save");
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, Renderer->GetScreenHeight() / 2.0 + 3), L"Load");
    //RenderText(Vector2(Renderer->GetScreenWidth() / 2.0, Renderer->GetScreenHeight() / 2.0 + 4), L"Exit");
}

void UIEngine::RenderPanel(PanelComponent p, Vector2 pos)
{
    for (int x = 0; x < p.GetSize().x; x++)
    {
        for (int y = 0; y < p.GetSize().y; y++)
        {
            CHAR_INFO att;
            int mIndexY = (y + (int)pos.y);
            int mIndexX = (x + (int)pos.x);
            int mIndex = (mIndexY)*Renderer->GetScreenWidth() + mIndexX;

            if (mIndexX >= Renderer->GetScreenWidth() || mIndexX < 0 || mIndexY >= Renderer->GetScreenWidth() || mIndexY < 0)
            {
                continue;
            }
            else
            {

                att.Char.UnicodeChar = RenderSlot(p.GetUISprite(), x - 1, y);

                if (att.Char.UnicodeChar != ' ')
                    att.Attributes = p.GetColor();
                else
                    att.Attributes = 0x00F0;
            }

            Renderer->SetScreenCharAt(mIndex, att);
        }
    }
}

void UIEngine::RenderCanvas(Canvas c)
{
    //RenderBackground
    if (c.GetComponent<CanvasComponent>() != nullptr)
        RenderCanvasBackGround(*c.GetComponent<CanvasComponent>(), c.t.GetPos());

    if (c.GetChildren().size() != 0)
    {
        for (int i = 0; i < c.GetChildren().size(); i++)
        {
            //Render Panels
            if (c.GetChildAt(i)->GetComponent<PanelComponent>() != nullptr)
            {
                RenderPanel(*c.GetChildAt(i)->GetComponent<PanelComponent>(), c.GetChildAt(i)->t.GetPos());
            }

            //Render Text
            if (c.GetChildAt(i)->GetComponent<TextComponent>() != nullptr)
            {
                RenderText(*c.GetChildAt(i)->GetComponent<TextComponent>(), c.GetChildAt(i)->t.GetPos());
            }
        }
    }
}

void UIEngine::RenderCanvasBackGround(CanvasComponent c, Vector2 pos)
{
    for (int nx = 0; nx < c.GetSize().x; nx++)
        for (int ny = 0; ny < c.GetSize().y; ny++)
        {
            CHAR_INFO att;

            att.Char.UnicodeChar = ' ';
            att.Attributes = c.GetColor();
            Renderer->SetScreenCharAt((ny + pos.y) * Renderer->GetScreenWidth() + (nx + pos.x), att);
        }
}

void UIEngine::RenderText(TextComponent t, Vector2 pos)
{
    for (int i = 0; i < t.GetText().size() + 1; i++)
    {
        Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x - t.GetText().size()/2.0) + i), t.GetText()[i]);
        Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x - t.GetText().size()/2.0) + i), t.GetColor());
    }
}

void UIEngine::RenderCanvasElements()
{
    if (CanvasList.size() != 0)
    {
        for (int i = 0; i < CanvasList.size(); i++)
        {
            if (CanvasList.at(0)->isActive)
            {
                RenderCanvas(*CanvasList.at(0));
            }
        }
    }
}

void UIEngine::SetCanvas()
{
    if (CanvasList.size() != 0)
    {
        for (int i = 0; i < CanvasList.size(); i++)
        {
            if (CanvasList.at(0)->isActive)
            {
                CanvasList.at(i)->t.SetWorldTransform(new Vector2(0,0));
		        //CanvasList.at(i)->SetLocalArray(*CanvasList);
                CanvasList.at(i)->Init();
            }
        }
    }
}


void UIEngine::UpdateCanvas()
{
    if (CanvasList.size() != 0)
    {
        for (int i = 0; i < CanvasList.size(); i++)
        {
            if (CanvasList.at(0)->isActive)
            {
                CanvasList.at(i)->Update();
            }
        }
    }
}
