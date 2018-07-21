
class cUISprite : public cSprite{

    public:
        cUISprite(std::wstring m = L"?", Vector2 s = Vector2(0,0), Vector2 c = Vector2(0,0), WORD col = 0x000F) 
        : cSprite(m, s, c, col){};
};