class BoxCollider : public Collider {
    Vector2 size;
    public:
        BoxCollider(Vector2 s = Vector2(1,1)): size(s), Collider(){};
        inline Vector2 GetSize()const{return size;}
        bool AABB(const BoxCollider &left, const BoxCollider &right);
        void CheckCollisions();
};

#include "BoxCollider.cpp"