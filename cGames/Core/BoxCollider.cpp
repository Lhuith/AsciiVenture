bool BoxCollider::AABB(const BoxCollider &left, const BoxCollider &right)
{
    if (left.object != nullptr && right.object != nullptr)
    {
        Vector2 min0 = Vector2((float)(left.object->t.GetPos().x - (left.GetSize().x / 2.0)),
                               (float)(left.object->t.GetPos().y - (left.GetSize().y / 2.0)));

        Vector2 max0 = Vector2((float)(left.object->t.GetPos().x + (left.GetSize().x / 2.0)),
                               (float)(left.object->t.GetPos().y + (left.GetSize().y / 2.0)));

        Vector2 min1 = Vector2((float)(right.object->t.GetPos().x - (right.GetSize().x / 2.0)),
                               (float)(right.object->t.GetPos().y - (right.GetSize().y / 2.0)));

        Vector2 max1 = Vector2((float)(right.object->t.GetPos().x + (right.GetSize().x / 2.0)),
                               (float)(right.object->t.GetPos().y + (right.GetSize().y / 2.0)));

        if (rectInterest(min0, max0, min1, max1))
            return true;
    }

    return false;
}

void BoxCollider::CheckCollisions()
{
    if (collisions->size() != 0)
    {
        for (int i = 0; i < collisions->size(); i++)
        {
           Object* o0 = collisions->at(i);

            if (collisions->at(i) != nullptr)
            {
                if (o0->GetComponent<BoxCollider>() != nullptr)
                {
                    BoxCollider leftCollider = *this;
                    BoxCollider rightCollider = *o0->GetComponent<BoxCollider>();

                    if (!BoxCollider().AABB(leftCollider, rightCollider))
                    {
                        AddToCleanUpCrew(o0);
                    }
                }
            }
        }
    }
}
