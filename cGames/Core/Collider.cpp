
void Collider::RemoveCollisions(Object *o)
{
    // erase-remove idiom.
    if (o->GetComponent<cSprite>() != nullptr)
        o->GetComponent<cSprite>()->SetCol(o->GetComponent<cSprite>()->GetStoredCol());
    else if (o->GetComponent<Item>() != nullptr)
        o->GetComponent<Item>()->getWorldSprite()->SetCol(o->GetComponent<Item>()->getWorldSprite()->GetStoredCol());

    collisions->erase(std::remove(collisions->begin(), collisions->end(), o), collisions->end());
}

void Collider::AddCollisions(Object *o)
{
    if (std::find(this->collisions->begin(), this->collisions->end(), o) == this->collisions->end())
    {
        //if (o->GetComponent<cSprite>() != nullptr)
        //    o->GetComponent<cSprite>()->SetCol(0x000D);
        //else if (o->GetComponent<Item>() != nullptr)
        //    o->GetComponent<Item>()->getWorldSprite()->SetCol(0x000D);
//
        this->collisions->push_back(o);
    }
}

//Add to junkpile and remove any collision objects
void Collider::CleanUp()
{
    if (OnExit->size() != 0)
    {
        for (int i = 0; i < OnExit->size(); i++)
        {
            RemoveCollisions(OnExit->at(i));
            RemoveFromCleanUp(OnExit->at(i));
        }
    }
}

void Collider::RemoveFromCleanUp(Object *o)
{
    // erase-remove idiom.
    if (o->GetComponent<cSprite>() != nullptr)
        o->GetComponent<cSprite>()->SetCol(o->GetComponent<cSprite>()->GetStoredCol());
    else if (o->GetComponent<Item>() != nullptr)
        o->GetComponent<Item>()->getWorldSprite()->SetCol(o->GetComponent<Item>()->getWorldSprite()->GetStoredCol());

    OnExit->erase(std::remove(OnExit->begin(), OnExit->end(), o), OnExit->end());
}

void Collider::AddToCleanUpCrew(Object *o)
{
    if (std::find(OnExit->begin(), OnExit->end(), o) == this->OnExit->end())
    {
        if (o->GetComponent<cSprite>() != nullptr)
            o->GetComponent<cSprite>()->SetCol(0x0004);
        else if (o->GetComponent<Item>() != nullptr)
            o->GetComponent<Item>()->getWorldSprite()->SetCol(0x0004);

        OnExit->push_back(o);
    }
}
