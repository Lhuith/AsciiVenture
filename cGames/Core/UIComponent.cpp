void UIComponent::HoverOver(float mousex, float mousey, bool clicked, bool held)
{
    Vector2 p0 = Vector2((this->object->t.GetWorldPosition().x), (this->object->t.GetWorldPosition().y));
    Vector2 p1 = Vector2((this->object->t.GetWorldPosition().x + this->GetSize().x), (this->object->t.GetWorldPosition().y + this->GetSize().y));

    if (pointInRect(mousex, (mousey), p0, p1))
    {
        this->Settouching(true);
        return;
    }


    this->Settouching(false);
}