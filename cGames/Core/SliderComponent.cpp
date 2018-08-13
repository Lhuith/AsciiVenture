void SliderComponent::RenderSlider(RenderEngine *Renderer)
{
    SliderComponent s = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int x = 0; x < s.GetSize().x; x++)
    {
        for (int y = 0; y < s.GetSize().y; y++)
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
                if (x == 0)
                {
                    att.Char.UnicodeChar = ' ';
                    att.Attributes = 0x000C | 0x00C0;
                }
                else if (x == s.GetSize().x - 1)
                {
                    att.Char.UnicodeChar = ' ';
                    att.Attributes = 0x000A | 0x00A0;
                } else if (x == Start.x + value){
                    att.Char.UnicodeChar = ' ';
                    att.Attributes = 0x0000 | 0x0000;
                }
                else
                {
                    att.Char.UnicodeChar = '-';
                    att.Attributes = s.GetColor();
                }
            }

            Renderer->SetScreenCharAt(mIndex, att);
        }
    }
}

void SliderComponent::HoverOver(float mousex, float mousey, bool clicked, bool held)
{
    Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
    Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (this->object->t.GetWorldPosition().y + this->GetSize().y));

    if (pointInRect(mousex, mousey, p0, p1))
    {
        this->Settouching(true);

        if (held)
        {
            value = (mousex) - 2;
        }

        return;
    }

    this->Settouching(false);
}