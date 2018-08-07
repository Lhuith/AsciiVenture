
void cUISpriteComponent::RendercSprite(RenderEngine *Renderer)
{
    cUISpriteComponent s = *this;
    Vector2 p = this->object->t.GetWorldPosition();

    for (int i = 0; i < s.size.x; i++)
        for (int j = 0; j < s.size.y; j++)
        {
            int mIndexY = (j + (int)p.y);
            int mIndexX = (i + (int)p.x);
            int mIndex = (mIndexY)*Renderer->GetScreenWidth() + mIndexX;

            //if the screen is larger then the Scene width, just mark as x
            if (mIndexX >= Renderer->GetScreenWidth() || mIndexX < 0 || mIndexY >= Renderer->GetScreenHeight() || mIndexY < 0)
            {
                continue;
            }
            else
            {
                CHAR_INFO c;
                c.Char.UnicodeChar = s.GetM()[j * (int)s.size.x + i];
                c.Attributes = s.GetColor();
                Renderer->SetScreenCharAt(mIndex, c);
            }
        }
}

void cUISpriteComponent::HoverOver(float mousex, float mousey, bool clicked)
{
    Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
    Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (this->object->t.GetWorldPosition().y + this->GetSize().y));

    if (pointInRect(mousex, mousey, p0, p1))
    {
        this->Settouching(true);
        this->SetColor(0x000F | 0x00D0);
        return;
    }


    this->Settouching(false);
    this->SetColor(GetStoredColor());
}