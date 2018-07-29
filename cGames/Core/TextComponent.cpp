
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