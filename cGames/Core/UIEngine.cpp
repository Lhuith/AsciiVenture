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
                att.Char.UnicodeChar = ' ';
                att.Attributes = p.GetColor();
            }

            Renderer->SetScreenCharAt(mIndex, att);
        }
    }
}

void UIEngine::RenderBackGround(PanelComponent c, Vector2 pos)
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


void UIEngine::RenderUIElements()
{
    if (UIElements.size() != 0)
    {
        for (int i = 0; i < UIElements.size(); i++)
        {
            if (UIElements.at(i)->isActive)
            {
                //RenderCanvas(*UIElements.at(i));
                if(UIElements.at(i)->GetComponent<PanelComponent>() != nullptr){
                   UIElements.at(i)->GetComponent<PanelComponent>()->RenderBackGround(Renderer); 
                   UIElements.at(i)->GetComponent<PanelComponent>()->RenderPanel(Renderer, m_mousePosX, m_mousePosY); 
                }
            }
        }
    }
}

bool UIEngine::HoverOver(Vector2 pos, Vector2 size){
        Vector2 p0 = Vector2((float)(pos.x), (float)(pos.y));
        Vector2 p1 = Vector2((float)(pos.x + (float)size.x), (float)(pos.y + size.y));

        if(pointInRect(m_mousePosX, m_mousePosY, p0, p1))
           return true;

        return false;
}

void UIEngine::SetUIElement()
{
    if (UIElements.size() != 0)
    {
        for (int i = 0; i < UIElements.size(); i++)
        {
            UIElements.at(i)->t.SetWorldTransform(&UIElements.at(i)->t.GetPositionRefrence());
            UIElements.at(i)->SetLocalArray(UIElements);
            UIElements.at(i)->Init();
        }
    }
}

void UIEngine::SetUIElement(Object *c)
{
    c->t.SetWorldTransform(&c->t.GetPositionRefrence());
    c->SetLocalArray(UIElements);
    c->Init();
}

void UIEngine::UpdateUIElemnts()
{
    if (UIElements.size() != 0)
    {
        for (int i = 0; i < UIElements.size(); i++)
        {
            if (UIElements.at(i)->isActive)
            {
                UIElements.at(i)->Update();
            }
        }
    }
}
