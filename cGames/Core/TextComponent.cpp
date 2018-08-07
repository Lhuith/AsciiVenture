
void TextComponent::RenderText(RenderEngine *Renderer, Vector2 *PanelSize)
{
    TextComponent t = *this;
    Vector2 pos = this->object->t.GetWorldPosition();

    for (int i = 0; i < t.GetText().size() + 1; i++)
    {
        if (PanelSize != nullptr)
        {
            if (t.GetAlignment() == TextComponent::Alignment::C)
            {
                Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x + PanelSize->x / 2.0 - round((int)t.GetText().size() / 2.0)) + i), t.GetText()[i]);
                Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x + PanelSize->x / 2.0 - round((int)t.GetText().size() / 2.0)) + i), t.GetColor());
            }
            else if (t.GetAlignment() == TextComponent::Alignment::L)
            {
                Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x) + i), t.GetText()[i]);
                Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x) + i), t.GetColor());
            }
            else if (t.GetAlignment() == TextComponent::Alignment::R)
            {
                Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x + PanelSize->x - round((int)t.GetText().size())) + i), t.GetText()[i]);
                Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x) + i), t.GetColor());
            }
        }
        else
        {

            Renderer->SetScreenAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x - t.GetText().size() / 2.0) + i), t.GetText()[i]);
            Renderer->SetScreenAttributeAt(((int)pos.y) * Renderer->GetScreenWidth() + (((int)pos.x - t.GetText().size() / 2.0) + i), t.GetColor());
        }
    }
}

void TextComponent::HoverOver(float mousex, float mousey, bool clicked, UIComponent *parent)
{
    if (parent == nullptr)
    {
        Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
        Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (int)(this->object->t.GetWorldPosition().y + this->GetSize().y));

        if (pointInRect(mousex, round((int)mousey), p0, p1))
        {
            this->Settouching(true);
            return;
        }

        this->Settouching(false);
    }
    else
    {
        if (this->Align == Alignment::C)
        {

            Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x + (int)(parent->GetSize().x / 2.0 - (int)this->GetSize().x / 2.0)), (int)(this->object->t.GetWorldPosition().y));
            Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + (int)(parent->GetSize().x / 2.0 - (int)this->GetSize().x / 2.0) + (int)this->GetSize().x), (int)(this->object->t.GetWorldPosition().y + this->GetSize().y));

            if (pointInRect(mousex, round((int)mousey), p0, p1))
            {
                this->Settouching(true);
                return;
            }

            this->Settouching(false);
        }
        else if (this->Align == Alignment::L)
        {
            Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
            Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (int)(this->object->t.GetWorldPosition().y + this->GetSize().y));

            if (pointInRect(mousex, round((int)mousey), p0, p1))
            {
                this->Settouching(true);
                return;
            }

            this->Settouching(false);
        }
        else if (this->Align == Alignment::R)
        {
            Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x + (int)(parent->GetSize().x - (int)this->GetSize().x)), (int)(this->object->t.GetWorldPosition().y));
            Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + (int)(parent->GetSize().x - (int)this->GetSize().x) + (int)this->GetSize().x), (int)(this->object->t.GetWorldPosition().y + this->GetSize().y));

            if (pointInRect(mousex, round((int)mousey), p0, p1))
            {
                this->Settouching(true);
                return;
            }

            this->Settouching(false);
        }
    }
}