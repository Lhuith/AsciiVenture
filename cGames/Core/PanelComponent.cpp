void PanelComponent::RenderPanel(RenderEngine *Renderer, float mX, float mY)
{
    PanelComponent p = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

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

    if (this->object->GetChildren().size() != 0)
    {
        for (int i = 0; i < this->object->GetChildren().size(); i++)
        {
            HandleChildElements(i, Renderer, mX, mY);
        }
    }
}

void PanelComponent::HandleChildElements(int i, RenderEngine *Renderer, float mX, float mY)
{
    if (this->object->GetChildAt(i)->GetComponent<PanelComponent>() != nullptr)
    {
        InteractWithChildElement(*this->object->GetChildAt(i)->GetComponent<PanelComponent>(), mX, mY);
        this->object->GetChildAt(i)->GetComponent<PanelComponent>()->RenderPanel(Renderer, mX, mY);
    }

    if (this->object->GetChildAt(i)->GetComponent<TextComponent>() != nullptr)
    {
        InteractWithChildElement(*this->object->GetChildAt(i)->GetComponent<TextComponent>(), mX, mY);
        this->object->GetChildAt(i)->GetComponent<TextComponent>()->RenderText(Renderer, this->GetSizeRef());
    }

    if (this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>() != nullptr)

    {
        InteractWithChildElement(*this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>(), mX, mY);
        this->object->GetChildAt(i)->GetComponent<cUISpriteComponent>()->RendercSprite(Renderer);
    }
}

//Heads Up, Rectangles are rendered from pos -> to max size
//doesnt start from centre so /2.0 work work

void PanelComponent::InteractWithChildElement(PanelComponent &p, float mX, float mY)
{
    if (HoverOver(mX, mY, p.object->t.GetWorldPosition(), p.GetSize()))
    {
        p.SetColor(0x00C0);
    }
    else
    {
        p.SetColor(p.GetStoredGetColor());
    }
}

void PanelComponent::InteractWithChildElement(TextComponent &t, float mX, float mY)
{
    if (t.Align == TextComponent::Alignment::L)
    {

        if (HoverOver(mX, mY, Vector2(t.object->t.GetWorldPosition().x, t.object->t.GetWorldPosition().y), t.GetSize()))
        {
            t.SetColor(0x00C0);
        }
        else
        {
            t.SetColor(t.GetStoredGetColor());
        }
    }
    else if (t.Align == TextComponent::Alignment::C)
    {

        if (HoverOver(mX, mY, Vector2(t.object->t.GetWorldPosition().x + this->GetSize().x / 2.0 - t.GetSize().x / 2.0 - 1, t.object->t.GetWorldPosition().y), t.GetSize()))
        {
            t.SetColor(0x00C0);
        }
        else
        {
            t.SetColor(t.GetStoredGetColor());
        }
    }
    else if ((t.Align == TextComponent::Alignment::R))
    {

        if (HoverOver(mX, mY, Vector2(t.object->t.GetWorldPosition().x + this->GetSize().x - t.GetSize().x / 2.0 - 1, t.object->t.GetWorldPosition().y), t.GetSize()))
        {
            t.SetColor(0x00C0);
        }
        else
        {
            t.SetColor(t.GetStoredGetColor());
        }
    }
    else
    {

        if (HoverOver(mX, mY, t.object->t.GetWorldPosition(), t.GetSize()))
        {
            t.SetColor(0x00C0);
        }
        else
        {
            t.SetColor(t.GetStoredGetColor());
        }
    }
}

void PanelComponent::InteractWithChildElement(cUISpriteComponent &c, float mX, float mY)
{
    if (HoverOver(mX, mY, c.object->t.GetWorldPosition(), c.GetSize()))
    {
        c.SetColor(0x00C0);
    }
    else
    {
        c.SetColor(c.GetStoredColor());
    }
}

bool PanelComponent::HoverOver(float mousex, float mousey, Vector2 pos, Vector2 size)
{
    Vector2 p0 = Vector2((pos.x), (pos.y));
    Vector2 p1 = Vector2((pos.x + size.x), (pos.y + size.y));

    if (pointInRect(mousex, mousey, p0, p1))
        return true;

    return false;
}

void PanelComponent::RenderBackGround(RenderEngine *Renderer)
{
    PanelComponent p = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int nx = 0; nx < p.GetSize().x; nx++)
        for (int ny = 0; ny < p.GetSize().y; ny++)
        {
            CHAR_INFO att;

            att.Char.UnicodeChar = ' ';
            att.Attributes = p.GetColor();
            Renderer->SetScreenCharAt((ny + pos.y) * Renderer->GetScreenWidth() + (nx + pos.x), att);
        }
}