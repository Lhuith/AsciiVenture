std::wstring cSprite::GetMflipped() const {
    std::wstring wc = model;
    std::reverse(wc.begin(), wc.end());
    
    return wc;
}
