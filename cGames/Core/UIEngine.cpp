
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
            UIElements.at(i)->Update();
        }
    }
}
