class Transform : public Component {
    Vector2 position;
    Vector2 Origin;
    Vector2 rotation;
    Vector2 WorldPosition;
    Vector2 *WorldTransform;
    public:
        explicit Transform(Vector2 p = Vector2(0,0), Vector2 r = Vector2(0,0), Vector2* wT = nullptr)
         : position(p), rotation(r), Origin(p), WorldPosition(p){}

        inline void SetPos(Vector2 _p){this->position = _p;}
        inline Vector2 GetPos()const{return this->position;}
        inline Vector2& GetPositionRefrence() {return this->position;}


        inline Vector2 GetOPos()const{return this->Origin;} //Position set at the beginning
        //inline void UpdateTransform(){}

        void Update(){this->WorldPosition = this->position + *WorldTransform;}
        inline Vector2 GetTranslatedPosition(){return this->Origin - this->position;}

        inline Vector2 GetWorldPosition(){return WorldPosition;}
        inline Vector2& GetWorldPositionRef(){return WorldPosition;}

        inline void SetWorldTransform(Vector2* _t){WorldTransform = _t;}
        inline Vector2 *GetWorldTransform(){return WorldTransform;}

        inline void SetRot(Vector2 _r){this->rotation = _r;}
        inline Vector2 GetRot()const{return this->rotation;} 

        inline float GetX()const{return position.x;}
        inline float GetY()const{return position.y;}

        inline void setX(float x){this->position.x = x;}
        inline void setY(float y){this->position.y = y;}

        inline void AddToX(float x){this->position.x += x;}
        inline void AddToY(float y){this->position.y += y;}

        inline Transform& operator+=(const Vector2& right);
        inline Transform& operator-=(const Vector2& right);
};


Transform& Transform::operator+=(const Vector2& right){
    this->position += right;
    return *this;
}

Transform& Transform::operator-=(const Vector2& right){
    this->position -= right;
    return *this;
}