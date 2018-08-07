
void UIEngine::RenderUIElements()
{
    if (UIElements.size() != 0)
    {
        for (int i = 0; i < UIElements.size(); i++)
        {
            if (UIElements.at(i)->isActive)
            {
                if (UIElements.at(i)->GetComponent<PanelComponent>() != nullptr)
                {
                    UIElements.at(i)->GetComponent<PanelComponent>()->RenderBackGround(Renderer);
                    UIElements.at(i)->GetComponent<PanelComponent>()->RenderPanel(Renderer);
                }
            }
        }
    }
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
            //Normal Object Update
            UIElements.at(i)->Update();

            if (UIElements.at(i)->GetComponent<PanelComponent>() != nullptr)
            {
                UIElements.at(i)->GetComponent<PanelComponent>()->CheckInteractions(Renderer, round(m_mousePosX), round(m_mousePosY), m_click_0);
            }
        }
    }
}
