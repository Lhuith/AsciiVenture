
#define UNICODE

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

#include <Windows.h>
#include <cmath>

#include <cstdio>
#include <cwchar>
#include <stdio.h>
#include <wchar.h>

#define swprintf_s swprintf 

using namespace std;

short nScreenWidth = 120;
short nScreenHeight = 40;
const short WIDTH = nScreenWidth;
const short HEIGHT = nScreenHeight;
float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 64;
int nMapWidth = 64;

float fFov = 3.14159 / 4.0;
float fDepth = 16.0f;
float fSpeed = 1.0f;

//void Loop(int i, wstring map, wchar_t* screen);

int main()
{

    //Crate Screen Buffer
    wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
    _CHAR_INFO *chars = new _CHAR_INFO[nScreenWidth * nScreenHeight];

    SMALL_RECT window_size = {0,1, WIDTH,HEIGHT};

    COORD coord = { WIDTH, HEIGHT};

    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    SetConsoleTitle(L"Pussy BItch");
    WORD attribute = FOREGROUND_RED | FOREGROUND_INTENSITY;
    
    wstring map;

    map += L"################";
    map += L"#..............#";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"################";

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();
    int count = 0;
    
    while (1)
    {   
        // We'll need time differential per frame to calculate modification
		// to movement speeds, to ensure consistant movement, as ray-tracing
		// is non-deterministic
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
        float fElepsedTime = elapsedTime.count();

        //Controls
        //Handle CCW Rotation

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
            fPlayerA -= (0.8f) * fElepsedTime;

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
            fPlayerA += (0.8f) * fElepsedTime;

        if(GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
            fPlayerX += sinf(fPlayerA) * 5.0f * fElepsedTime;
            fPlayerY += cosf(fPlayerA) * 5.0f * fElepsedTime;

            if(map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
            {
                fPlayerX -= sinf(fPlayerA) * 5.0f * fElepsedTime;
                fPlayerY -= cosf(fPlayerA) * 5.0f * fElepsedTime;
            }
        }

           if(GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            fPlayerX -= sinf(fPlayerA) * 5.0f * fElepsedTime;
            fPlayerY -= cosf(fPlayerA) * 5.0f * fElepsedTime;

            if(map[(int)fPlayerY * nMapWidth + (int)fPlayerX]  == '#')
            {
                fPlayerX += sinf(fPlayerA) * 5.0f * fElepsedTime;
                fPlayerY += cosf(fPlayerA) * 5.0f * fElepsedTime;
            }
        }

        for (int x = 0; x < nScreenWidth; x++)
        {
            float fRayAngle = (fPlayerA - fFov / 2.0f) + ((float)x / (float)nScreenWidth) * fFov;

            float fDistanceToWall = 0;
            bool bHitWall = false;
            bool bBoundary = false;


            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < fDepth)
            {

                fDistanceToWall += 0.1f;

                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                //Test if ray is out of bounds
                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
                {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                }
                else
                {
                    //Ray is InBounds so test to see if the ray cell is a wall block
                    if (map[nTestY * nMapWidth + nTestX] == '#')
                    {
                        bHitWall = true;

                        vector<pair<float, float>> p; //distance, dot

                        for(int tx = 0; tx < 2; tx++)
                            for(int ty = 0; ty < 2; ty++){
                                float vy = (float)nTestY + ty - fPlayerY;
                                float vx = (float)nTestX + tx - fPlayerX;
                                float d = sqrt(vx*vx + vy*vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                p.push_back(make_pair(d, dot));
                            }

                        //Sort Pairs from closes to farthest
                        sort(p.begin(), p.end(), [](const pair <float, float> &left, const pair<float, float> &right) {return left.first < right.first;});

                        float fBound = 0.01;
                        if(acos(p.at(0).second) < fBound) bBoundary = true;
                        if(acos(p.at(1).second) < fBound) bBoundary = true;
                        //if(acos(p.at(2).second) < fBound) bBoundary = true;
                    }
                }
            }

            //Calculate the distance to the ceiling and floor
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            short nShade = ' ';

            if(fDistanceToWall <= fDepth / 4.0f)        nShade = 0x2588; //Very Close
            else if (fDistanceToWall < fDepth / 3.0f)   nShade = 0x2593;
            else if (fDistanceToWall < fDepth / 2.0f)   nShade = 0x2592;
            else if (fDistanceToWall < fDepth)          nShade = 0x2591;
            else nShade = ' ';                                           //To Far Away

            if(bBoundary) nShade = ' ';                                 //Black it Out

            for (int y = 0; y < nScreenHeight; y++)
            {
                if (y <= nCeiling)
                {
                    //screen[y * nScreenWidth + x] = ' ';
                    chars[y * nScreenWidth + x].Char.UnicodeChar = '-';
                    chars[y * nScreenWidth + x].Attributes = 0x0007;
                }

                else if (y > nCeiling && y <= nFloor)
                {
                    //screen[y * nScreenWidth + x] = nShade;
                    chars[y * nScreenWidth + x].Char.UnicodeChar = nShade;
                    chars[y * nScreenWidth + x].Attributes = 0x0007;
                }

                else
                {   
                    //shade floor based on distance
                    float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f ));
                    if(b < 0.25) nShade = '#';
                    else if(b < 0.5) nShade = 'x';
                    else if(b < 0.75) nShade = '.';
                    else if(b < 0.9) nShade = '-';
                    else nShade = ' ';
                    //screen[y * nScreenWidth + x] = nShade;
                    chars[y * nScreenWidth + x].Attributes = 0x0007;
                    chars[y * nScreenWidth + x].Char.UnicodeChar = nShade;
                }
            }
        }

		//Display Stats
		swprintf(screen, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElepsedTime);

		//Display Map
		for(int nx = 0; nx < nMapWidth; nx++)
			for (int ny = 0; ny < nMapWidth; ny++)
			{
				//screen[(ny + 1)*nScreenWidth + nx] = map[ny * nMapWidth + nx];
                chars[(ny + 1)*nScreenWidth + nx].Char.UnicodeChar = map[ny * nMapWidth + nx];
                chars[(ny + 1)*nScreenWidth + nx].Attributes = 0x0007;
			}
        //screen[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX] = '0';
        chars[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX].Char.UnicodeChar = 0x25A0;
        chars[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX].Attributes = 0x0002;

		//screen[nScreenWidth * nScreenHeight - 1] = '\0';
        chars[nScreenWidth * nScreenHeight - 1].Char.UnicodeChar = '\0';

        WriteConsoleOutput (hConsole, chars, coord, { 0,0 }, &window_size);
        WriteConsoleOutputCharacter(hConsole, screen, nScreenHeight, {0,0}, &dwBytesWritten);
    }

    
    return 0;
}

void Loop(int i, wstring map, wchar_t *screen)
{
}

void WriteToScreen()
{
}
void CreateScreen()
{
}