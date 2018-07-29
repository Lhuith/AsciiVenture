bool TextBox::HoverOver(float x, float y){
        Vector2 p0 = Vector2((float)(this->posX - (float)this->width - 1), (float)(this->posY + Renderer->GetScreenHeight() - this->height/2.0) + 1);
        Vector2 p1 = Vector2((float)(this->posX + (float)this->width - 1), (float)(this->posY + Renderer->GetScreenHeight()/2.0 + this->height/2.0) + 1);

        if(pointInRect(x, y, p0, p1)){
            this->color = 0x0080;
           return true;
        } else {
            this->color = 0x00F0;
        }

        return false;
}

void TextBox::HightLight(int& m_mouseScroll, int& old_mouseScroll, float m_mousePosX, float m_mousePosY){

    if (HoverOver(m_mousePosX, m_mousePosY))
        {
            if (old_mouseScroll != m_mouseScroll)
            {
                if (m_mouseScroll < 0)
                    AddToScroll(+1);
                else if (m_mouseScroll > 1)
                    AddToScroll(-1);
                old_mouseScroll = m_mouseScroll;
                m_mouseScroll = 0;
            }
        }
}

void TextBox::DisplayTextBox()
{
    for (int x = 0; x < this->width; x++)
        for (int y = 0; y < this->height; y++)
        {
            //The Whole TextBox
            int screenBufferIndex =
                (y + (this->Renderer->GetScreenHeight() - (this->height + 1))) * this->Renderer->GetScreenWidth() +
                (x + ((int)(this->width / 2.0 + this->posX) - ((this->width / 2) - 1)));

            int tIndex = (y + this->ScrollY) * (this->width) + x;

            std::wstring message;

            for (int z = 0; z < this->logs.size(); z++)
            {
                std::wstring occ = s2ws(std::to_string(this->logs.at(z).occurance));
                if(this->logs.at(z).occurance < 998){
                std::wstring occ = s2ws(std::to_string(this->logs.at(z).occurance));
                } else {
                    occ = L"999+";
                }

                message += this->logs.at(z).log + AddSpace(std::abs((this->width) - this->logs.at(z).log.size() - occ.size()))
                 + occ;
            }

            if (tIndex < message.size())
            {
                char txt = message[tIndex];
                CHAR_INFO att;
                att.Attributes = this->color;
                att.Char.UnicodeChar = txt;

                Renderer->SetScreenCharAt(screenBufferIndex, att);
                Renderer->SetScreenAttributeAt(screenBufferIndex, this->color);
            }
            else
            {
                Renderer->SetScreenAt(screenBufferIndex, ' ');
                Renderer->SetScreenAttributeAt(screenBufferIndex, this->color);
            }
        }
}

//void TextBox::AddToTextBox(std::wstring msg){
//    if (find(this->messages.begin(), this->messages.end(), msg) == this->messages.end())
//    {
//        this->messages.push_back(msg);
//    }
//}

void TextBox::Log(std::wstring msg){
    
    std::vector<LogInfo>::iterator size = (std::find(this->logs.begin(), this->logs.end(), (LogInfo(msg, 0))));

    int index = std::distance(this->logs.begin(), (std::find(this->logs.begin(), this->logs.end(), (LogInfo(msg, 0)))));

    if (index == logs.size())
    {
        //No Occurence of log
        this->logs.push_back(LogInfo(msg, index));
    } else {
        this->logs.at(index).AddOccarance(index);
    }
}

std::wstring TextBox::AddSpace(int size)
{
    std::wstring space;
    for (int i = 0; i < size; i++)
        space += L" ";

    return space;
}
