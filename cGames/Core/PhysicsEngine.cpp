struct DistanceFunction
{

  public:
    DistanceFunction(const Object &_p, const int wX, const int wY, UIEngine *ui) : p(_p), WorldCoordX(wX), WorldCoordY(wY), UI(ui) {}

    bool operator()(const Object *l, const Object *r) const
    {

        Vector2 pl = Vector2(p.t.GetPos().x + WorldCoordX / 2.0, p.t.GetPos().y + WorldCoordY / 2.0);
        //Pretty long and convoluted and will try for a lamba later,
        //UI->Debug(l->t.GetPos());
        return p.t.GetPos().Distance(pl, l->t.GetPos()) < p.t.GetPos().Distance(pl, r->t.GetPos());
    }

  private:
    Object p;
    int WorldCoordX;
    int WorldCoordY;
    UIEngine *UI;
};

//Sort Objects in List, Manage how many times, and which ones to select for near search
void PhysicsEngine::WideSort()
{
    //Nice Big Fat sort of objects of the level
    //Will add stoppers and sleep timers as objects gets larger

    if (Engine != nullptr && this->objects != nullptr || this->objects->size() != 0)
    {
        //std::sort(
        //    (this->objects->begin()),
        //    (this->objects->end()),
        //    DistanceFunction(*Engine->GetCamera(),
        //                     Engine->GetCamera()->GetComponent<Camera>()->GetWidth(),
        //                     Engine->GetCamera()->GetComponent<Camera>()->GetHeight(), UI));
    }
}

void PhysicsEngine::NearHandle()
{
    if (objects != nullptr || objects->size() != 0)
    {
        //set limit based on wether the number of objects is less then the nearlimit
        int limit = objects->size(); //(objects->size() < this->NEARLIMIT) ? objects->size() : NEARLIMIT;
        //objects->size();//
        for (int i = 0; i < limit; i++)
        {
            for (int j = 0; j < limit; j++)
            {
                if (this->objects->at(i) != nullptr && this->objects->at(j) != nullptr)
                {
                    Object *o0 = this->objects->at(i);
                    Object *o1 = this->objects->at(j);

                    //if (o0->GetComponent<BoxCollider>() != nullptr)

                    //Changing Color Based on range to MainCamera
                    Vector2 CamWorldPos = Vector2(
                        Engine->GetCamera()->t.GetPos().x + Engine->GetCamera()->GetComponent<CameraComponent>()->GetWidth() / 2.0,
                        Engine->GetCamera()->t.GetPos().y + Engine->GetCamera()->GetComponent<CameraComponent>()->GetHeight() / 2.0);

                    //if (Vector2().Distance(o0->t.GetWorldPosition(), CamWorldPos) < 25.0)
                    //{
                    //}
//
                    if (o1 == o0)
                        continue;

                    if (o1->GetComponent<Item>() != nullptr && o0->GetComponent<Item>() != nullptr)
                        continue;

                    if (o0->GetComponent<BoxCollider>() != nullptr && o1->GetComponent<BoxCollider>() != nullptr)
                    {

                        BoxCollider leftCollider = *o0->GetComponent<BoxCollider>();
                        BoxCollider rightCollider = *o1->GetComponent<BoxCollider>();

                        if (BoxCollider().AABB(leftCollider, rightCollider))
                        {
                            leftCollider.AddCollisions(o1);
                            rightCollider.AddCollisions(o0);
                        }
                    }
                }
            }
        }

        if (objects->size() != 0)
        {
            for (int i = 0; i < objects->size(); i++)
            {
                 Object *o0 = this->objects->at(i);
                if (o0->GetComponent<BoxCollider>() != nullptr)
                {
                    o0->GetComponent<BoxCollider>()->CheckCollisions();
                    o0->GetComponent<BoxCollider>()->CleanUp();
                }
            }
        }

        //CleanUp();
    }

    //CollisionsDebug();
}

//Add to junkpile and remove any collision objects
void PhysicsEngine::CleanUp()
{
    if (CleanUpCrew.size() != 0)
    {
        for (int i = 0; i < CleanUpCrew.size(); i++)
        {
            RemoveCollisions(CleanUpCrew.at(i));
            RemoveFromCleanUp(CleanUpCrew.at(i));
        }
    }
}

void PhysicsEngine::RemoveFromCleanUp(Object *o)
{
    // erase-remove idiom.
    if (o->GetComponent<cSprite>() != nullptr)
        o->GetComponent<cSprite>()->SetCol(o->GetComponent<cSprite>()->GetStoredCol());
    else if (o->GetComponent<Item>() != nullptr)
        o->GetComponent<Item>()->getWorldSprite()->SetCol(o->GetComponent<Item>()->getWorldSprite()->GetStoredCol());

    CleanUpCrew.erase(std::remove(CleanUpCrew.begin(), CleanUpCrew.end(), o), CleanUpCrew.end());
}

void PhysicsEngine::AddToCleanUpCrew(Object *o)
{
    if (std::find(CleanUpCrew.begin(), CleanUpCrew.end(), o) == this->CleanUpCrew.end())
    {
        if (o->GetComponent<cSprite>() != nullptr)
            o->GetComponent<cSprite>()->SetCol(0x0004);
        else if (o->GetComponent<Item>() != nullptr)
            o->GetComponent<Item>()->getWorldSprite()->SetCol(0x0004);

        CleanUpCrew.push_back(o);
    }
}

//void PhysicsEngine::AddCollisions(Object *o)
//{
//    if (std::find(collisions.begin(), collisions.end(), o) == this->collisions.end())
//    {
//        if (o->GetComponent<cSprite>() != nullptr)
//            o->GetComponent<cSprite>()->SetCol(0x0004);
//        else if (o->GetComponent<Item>() != nullptr)
//            o->GetComponent<Item>()->getWorldSprite()->SetCol(0x0004);
//
//        collisions.push_back(o);
//    }
//}

void PhysicsEngine::RemoveCollisions(Object *o)
{
    // erase-remove idiom.
    if (o->GetComponent<cSprite>() != nullptr)
        o->GetComponent<cSprite>()->SetCol(o->GetComponent<cSprite>()->GetStoredCol());
    else if (o->GetComponent<Item>() != nullptr)
        o->GetComponent<Item>()->getWorldSprite()->SetCol(o->GetComponent<Item>()->getWorldSprite()->GetStoredCol());

    collisions.erase(std::remove(collisions.begin(), collisions.end(), o), collisions.end());
}

void PhysicsEngine::CollisionsDebug()
{
    if (collisions.size() != 0)
    {
        for (int i = 0; i < collisions.size(); i++)
        {
            Object *o = collisions.at(i);
            //UI->Debug(o->t.GetPos());

            //if (o->GetComponent<cSprite>() != nullptr)
            //    o->GetComponent<cSprite>()->SetCol(0x0004);
            //else if (o->GetComponent<Item>() != nullptr)
            //    o->GetComponent<Item>()->getWorldSprite()->SetCol(0x0004);
        }
    }
}

void PhysicsEngine::PhysicsDebug(Object *o, bool condition)
{
    if (Debug)
    {
        Vector2 CamWorldPos = Vector2(
            (int)Engine->GetCamera()->t.GetPos().x + (int)Engine->GetCamera()->GetComponent<CameraComponent>()->GetWidth() / 2.0,
            (int)Engine->GetCamera()->t.GetPos().y + (int)Engine->GetCamera()->GetComponent<CameraComponent>()->GetHeight() / 2.0);

        if (Engine != nullptr || o != nullptr)
        {

            if (condition)
            {
                if (o->GetComponent<cSprite>() != nullptr)
                    o->GetComponent<cSprite>()->SetCol(0x0004);
                else if (o->GetComponent<Item>() != nullptr)
                    o->GetComponent<Item>()->getWorldSprite()->SetCol(0x0004);
            }
            else
            {
                if (o->GetComponent<cSprite>() != nullptr)
                    o->GetComponent<cSprite>()->SetCol(o->GetComponent<cSprite>()->GetStoredCol());
                else if (o->GetComponent<Item>() != nullptr)
                    o->GetComponent<Item>()->getWorldSprite()->SetCol(o->GetComponent<Item>()->getWorldSprite()->GetStoredCol());
            }
        }
    }
}
