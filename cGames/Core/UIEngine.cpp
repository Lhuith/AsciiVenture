//void UIEngine::RenderText(Vector2 pos, std::wstring text, WORD col)
//{
//    for (int i = 0; i < text.size() + 1; i++)
//    {
//        Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + ((int)pos.x + i), text[i]);
//        Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + ((int)pos.x + i), col);
//    }
//}

wchar_t UIEngine::RenderIcon(cSprite c, int x, int y, bool flipC)
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
}
void UIEngine::Menu()
{
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
                
                if(p.GetUISprite().GetM() != L"?")
                    att.Char.UnicodeChar = RenderIcon(p.GetUISprite(), x, y);
                else
                    att.Char.UnicodeChar = ' ';

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
            if (CanvasList.at(i)->isActive)
            {
                RenderCanvas(*CanvasList.at(i));
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
            if (CanvasList.at(i)->isActive)
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
            if (CanvasList.at(i)->isActive)
            {
                CanvasList.at(i)->Update();
            }
        }
    }
}
