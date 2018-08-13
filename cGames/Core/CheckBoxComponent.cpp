void CheckBoxComponent::RenderCheckBox(RenderEngine *Renderer)
{
    CheckBoxComponent bx = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int x = 0; x < bx.GetSize().x; x++)
    {
        for (int y = 0; y < bx.GetSize().y; y++)
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
                if (this->Checked)
                {
                    att.Char.UnicodeChar = 'X';
                    att.Attributes = bx.GetColor();
                }
                else
                {
                    att.Char.UnicodeChar = ' ';
                    att.Attributes = bx.GetColor();
                }
            }

            Renderer->SetScreenCharAt(mIndex, att);
        }
    }
}

void CheckBoxComponent::HoverOver(float mousex, float mousey, bool clicked, bool held)
{
    Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
    Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (this->object->t.GetWorldPosition().y + this->GetSize().y));

    if (pointInRect(mousex, mousey, p0, p1))
    {
        this->Settouching(true);
        if (clicked && !Checked)
        {
            this->Checked = true;
        }
        else if (clicked && Checked)
        {
            this->Checked = false;
        }
        return;
    }

    this->Settouching(false);
}