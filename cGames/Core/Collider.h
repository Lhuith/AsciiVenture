
class Collider : public Component{
    
        std::string Tag = "Defualt";
    public:
        std::vector<Object*> *collisions; //refrence to collisions;
        std::vector<Object*> *OnExit;

        Collider(std::vector<Object*> *c = new std::vector<Object*>, std::vector<Object*> *e = new std::vector<Object*>)
        : collisions(c), OnExit(e){};
        bool isColliding, isTriggered, Trigger; //if is trigger, dont apply forces and shit
        //bool SetColliding(bool c){isColliding = c;};
        

        inline int GetCollisionsSize(){return (int)this->collisions->size();}
        inline std::vector<Object *> GetCollisions(){return *collisions;}
        inline std::vector<Object *> GetOnExit(){return *OnExit;}
        void AddCollisions(Object *o);
        void RemoveCollisions(Object *o);
        //inline void CollisionCheck();
        virtual void OnCollision(){};

        void CleanUp();
        void RemoveFromCleanUp(Object *o);
        void AddToCleanUpCrew(Object *o);

    protected:

    private:

};

#include "Collider.cpp"