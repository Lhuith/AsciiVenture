WORD RenderEngine::RenderLight(CHAR_INFO att, int x, int y)
{
    if (lights.size() != 0)
    {
        for (int i = 0; i < this->lights.size(); i++)
        {
            if (lights.at(i)->GetComponent<Light>() != nullptr)
            {
                Light light = *lights.at(i)->GetComponent<Light>();

                float px = lights.at(i)->t.GetWorldPosition().x;
                float py = lights.at(i)->t.GetWorldPosition().y;

                //diffrence vector
                float dx = px - (float)x;
                float dy = py - (float)y;

                //mag of the diffrence
                float distance = sqrt(std::abs(dx * dx) + std::abs(dy * dy) * 3.0); // * 3.0 since ascii is longer then wider

                float norm = ((distance) / (100)) / light.GetI();

                if (norm <= .04)
                {
                    att.Attributes = 0x000F;
                }
                else if (norm <= .16 > .02)
                {
                    if (light.GetC() != 0x000F)
                        att.Attributes = light.GetC() | FOREGROUND_INTENSITY;
                    else
                        att.Attributes = att.Attributes | FOREGROUND_INTENSITY;
                }
                else if (norm <= .30 && norm >= .16)
                {
                    if (light.GetC() != 0x000F)
                        att.Attributes = light.GetC();
                    else
                        att = att;
                }
                else if (norm <= .35 && norm >= .30)
                {
                    //att.Attributes = 0x0007;
                }
                else if (norm <= .40 && norm >= .35)
                {
                    // att.Attributes = 0x0008;
                    att.Char.UnicodeChar = 0x2591;
                }
            }
        }
    }

    return att.Attributes;
}

void MixColor()
{
}

void RenderEngine::RenderScene()
{
    for (int i = 0; i < objects->size(); i++)
    {
        Object *o = objects->at(i);

        if (o->GetComponent<Item>() != nullptr)
            RenderModel(*o->GetComponent<Item>()->getWorldSprite(), o->t.GetWorldPosition());
        else if(o->GetComponent<cSprite>() != nullptr)
            RenderModel(*o->GetComponent<cSprite>(), o->t.GetWorldPosition());
    }
}

void RenderEngine::RenderSceneMap()
{
    if (this->scene != nullptr)
    {
        Vector2 WorldTransform = this->Engine->GetCamera()->t.GetPos();
        //Display Scene
        for (int nx = 0; nx < this->nScreenWidth; nx++)
            for (int ny = 0; ny < this->nScreenHeight; ny++)
            {
                CHAR_INFO att;
                int mIndexY = (ny - (int)WorldTransform.y);
                int mIndexX = (nx - (int)WorldTransform.x);
                int mIndex = (mIndexY) * this->scene->GetWidth() + mIndexX;

                //if the screen is larger then the Scene width, just mark as x
                if (mIndexX >= this->scene->GetWidth() || mIndexX < 0 || mIndexY >= this->scene->GetHeight() || mIndexY < 0)
                {
                    att.Char.UnicodeChar = 'x';
                    att.Attributes = 0x0005;
                }
                else
                {
                    att = scene->GetAttAt(mIndex);
                    att.Attributes = RenderLight(scene->GetAttAt(mIndex), mIndexX + (int)WorldTransform.x, mIndexY + (int)WorldTransform.y);
                }

                this->screenBuffer[ny * (int)this->nScreenWidth + nx] = att;
            }
    }
}

//FIX THIS!~
void RenderEngine::RenderModel(cSprite s, Vector2 p)
{
    for (int i = 0; i < s.size.x; i++)
        for (int j = 0; j < s.size.y; j++)
        {
            int mIndexY = (j + (int)p.y - std::round((int)(s.size.y / 2.0)));
            int mIndexX = (i + (int)p.x - std::round((int)(s.size.x / 2.0)));
            int mIndex = (mIndexY) * this->scene->GetWidth() + mIndexX;

            //if the screen is larger then the Scene width, just mark as x
            if (mIndexX >= this->nScreenWidth || mIndexX < 0 || mIndexY >= this->nScreenHeight || mIndexY < 0)
            {
                continue;
            }
            else
            {

                std::wstring m = s.GetM();
                //char wc = s.GetM().c_str();

                if (m[j * (int)s.size.x + i] != ' ')
                {
                    CHAR_INFO c;
                    c.Char.UnicodeChar = s.GetM()[j * (int)s.size.x + i];
                    c.Attributes = s.GetCol();
                    //scene->SetAttAt(mIndex, c);
                    c.Attributes = RenderLight(c, mIndexX, mIndexY);
                    screenBuffer[(mIndexY) * this->nScreenWidth + mIndexX] = c;
                }
                else
                {
                    //CHAR_INFO c;
                    //c.Char.UnicodeChar = scene->GetCharAtIndex(mIndex);
                    //c.Attributes = scene->GetAttAt(mIndex).Attributes;
                    //scene->SetAttAt(mIndex, c);
                }
            }
        }
}

void RenderEngine::BlitToScreen()
{
    screenBuffer[(int)(nScreenWidth) * (int)(nScreenHeight)-1].Char.UnicodeChar = '\0';
    GameInformation[(int)(nScreenHeight)-1] = '\0';

    WriteConsoleOutput(m_hConsole, screenBuffer, {(short)nScreenWidth, (short)nScreenHeight}, {0, 0}, &this->m_rectWindow);
    WriteConsoleOutputCharacter(m_hConsole, GameInformation, (short)nScreenWidth - 1, {0, 0}, &dwBytesWritten);
}