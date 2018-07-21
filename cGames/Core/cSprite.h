struct cSprite : public Component{
    Vector2 size;
    Vector2 centre;
    std::wstring model;
    WORD color, storedCol;

    public:
        cSprite(std::wstring m = L"?",Vector2 s = Vector2(0,0), Vector2 c = Vector2(0,0), WORD col = 0x000F) 
        : model(m), size(s), centre(c), color(col), storedCol(col){};

    
        inline std::wstring GetM() const {return model;}
        inline WORD GetCol() const {return color;}
        inline WORD GetStoredCol() const {return storedCol;}
        inline Vector2 GetSize() const {return size;}

        inline void SetM(std::wstring c){this->model = c;}
        inline void SetCol(WORD col){this->color = col;}
        inline void SetSize(Vector2 s){this->size = Vector2(s);}
        inline std::wstring GetMflipped() const;

};

std::wstring cSprite::GetMflipped() const {
    std::wstring wc = model;
    std::reverse(wc.begin(), wc.end());
    
    return wc;
}