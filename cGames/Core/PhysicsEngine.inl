
inline bool PhysicsEngine::RangeCheck(Object *l, Object *r, float max)
{
    Vector2 WorldTransform = this->Engine->GetCamera()->t.GetPos();

    Vector2 wPos = Vector2(l->t.GetX() - (int)WorldTransform.getX(), l->t.GetY() - (int)WorldTransform.getY());

    //if (wPos.Distance(r->t.GetPos()) < max)
    //{
    //    return true;
    //}
//
    return false;
}