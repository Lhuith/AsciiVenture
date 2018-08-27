struct cSprite : public Component
{
    Vector2 size;
    Vector2 centre;
    std::wstring model;
    WORD color, stored_color;

  public:
    explicit cSprite(std::wstring m = L"???"
                                       "???"
                                       "???", Vector2 s = Vector2(3, 3), Vector2 c = Vector2(0, 0), WORD col = 0x000F | 0x0000)
        : model(m), size(s), centre(c), color(col), stored_color(col){};

    inline std::wstring GetM() const { return model; }
    inline WORD GetColor() const { return color; }
    inline WORD GetStoredColor() const { return stored_color; }

    inline Vector2 GetSize() const { return size; }
    Vector2 *GetSizeRef() { return &size; }

    inline void SetM(std::wstring c) { this->model = c; }
    inline void SetColor(WORD col) { this->color = col; }
    inline void SetSize(Vector2 s) { this->size = Vector2(s); }
    inline std::wstring GetMflipped() const;
    void OverrideColor(WORD c)
    {
        this->color = c;
        this->stored_color = c;
    }
};

#include "cSprite.cpp"
