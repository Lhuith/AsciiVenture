void Object::SetComponents()
{
    if (components.size() != 0)
    {
        for (int i = 0; i < components.size(); i++)
        {
            components.at(i)->SetObject(*this);
        }
    }
}

void Object::SetChildren()
{
    if (children.size() != 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            SetChild(i);
        }
    }
}

void Object::SetChild(int i)
{
    if (i <= children.size())
    {
        children.at(i)->Init();
        children.at(i)->SetLocalArray(*local);
        children.at(i)->Parent = this;
        children.at(i)->t.SetWorldTransform(&t.GetWorldPositionRef());
    }
}

void Object::SetChild(Object *o)
{
    if (o != nullptr)
    {
        if (std::find(this->children.begin(), this->children.end(), o) != this->children.end())
        {
            o->Init();
            o->SetLocalArray(*local);
            o->Parent = this;
            o->t.SetWorldTransform(&t.GetWorldPositionRef());
        }
    }
}

void Object::SetChildActive(bool b)
{
    if (children.size() != 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            children.at(i)->SetActive(b);
        }
    }
}
void Object::UpdateComponents()
{
    if (components.size() != 0)
    {
        for (int i = 0; i < components.size(); i++)
        {
            components.at(i)->Update();
        }
    }
}

void Object::UpdateChildren()
{
    // t.UpdateTransform();
    if (children.size() != 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            children.at(i)->Update();
        }
    }
}

void Object::Remove(Object *o)
{
    this->local->erase(std::remove(this->local->begin(), this->local->end(), o), this->local->end());
}