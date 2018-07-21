
struct Vector2
{
    float x;
    float y;

    explicit Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y){}
    inline Vector2& operator+=(const Vector2& right);
    inline Vector2& operator-=(const Vector2& right);

    public:
    inline float getX()const{return x;}
    inline float getY()const{return y;}
    inline float setX(float x){this->x = x;}
    inline float setY(float y){this->y = y;}
    inline float Distance(const Vector2& l, const Vector2& r) const;
    inline float Length() const;
    //inline bool operator() ( Vector2& l,  Vector2& r) const {return (l.Length() < r.Length());}
};

inline Vector2 operator+(const Vector2& left, const Vector2& right);
inline Vector2 operator-(const Vector2& left, const Vector2& right);
inline Vector2 operator*(float scalar, const Vector2& vector);
inline Vector2 operator*(const Vector2& vector, float scalar);
inline bool operator< (const Vector2& l, const Vector2& r){return (l.Length() < r.Length());}
inline bool operator> (const Vector2& l, const Vector2& r){return  operator< (r,l);}


#include "Vector2.inl"

