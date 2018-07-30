#define UNICODE
#define swprintf_s swprintf

#include <iostream>
#include <chrono>
#include <vector>

#include <algorithm>
#include <Windows.h>
#include <cmath>
#include <stdio.h>
#include <memory>

#include "Core/ToiEngine.h"

using namespace std;

struct Direction
{
    bool LEFT;
    bool RIGHT;
    bool UP;
    bool DOWN;

  public:
    void GoLeft()
    {
        this->LEFT = true;
        this->RIGHT = false, this->UP = false, this->DOWN = false;
    }
    void GoRight()
    {
        this->RIGHT = true;
        this->LEFT = false, this->UP = false, this->DOWN = false;
    }
    void GoUp()
    {
        this->UP = true;
        this->RIGHT = false, this->LEFT = false, this->DOWN = false;
    }
    void GoDown()
    {
        this->DOWN = true;
        this->RIGHT = false, this->UP, this->LEFT = false;
    }
} direction;

Panel *Menu;
Panel *Inventory;
Panel *StatPanel;
Panel* ToolTip;
std::vector<Panel*> InventoryPanels;

float fPlayerX = 32;
float fPlayerY = 9;
float fPlayerA = 0.0f;

Object *testLight;
Object *testLight2;

bool Interacting, l_mButton, ShowText, ShowDebug;

Scene *currentLevel;

Object *Player;
Character PlayerInformation;

enum GameStates
{
    PAUSED,
    PLAY,
    INVENTORY,
};

GameStates CurrentState;
void Input();

void AssignLevel(Scene *Scene);

void Debug(wstring msg);
void Debug(float d);
void Debug(int d);
void Debug(string s);
void Debug(Vector2 v);
void InitMenu();
void InitInventory();
void UpdateInventoryPanels();
void SetInventoryPanels();

float OldTime, currentTime, duration = 1.0;

//CoreEngine* Engine;
ToiEngine *Engine;
//Object* CameraWorldPos;
int main()
{
    CurrentState = PLAY;
    currentLevel = &OverWorld;

    Engine = new ToiEngine(new CoreEngine({&OverWorld}));

    Player = new Object(Transform(Vector2(Engine->GetRenderer()->GetScreenWidth() / 2.0, Engine->GetRenderer()->GetScreenHeight() / 2.0)), L"Gene", {"Player"},
                        {std::make_shared<cSprite>(Models::Entities::humanoid_00),
                         std::make_shared<Character>(1, 1, 1, 1, std::make_shared<Warrior>()),
                         std::make_shared<BoxCollider>(Vector2(3, 3))});

    currentLevel->AddObject(Player);

    float screenWH = Engine->GetRenderer()->GetScreenWidth() / 2.0;
    float screenHH = Engine->GetRenderer()->GetScreenHeight() / 2.0;

    testLight = new Object(Transform(Vector2(0, 5)), L"Light1", {"Light"}, {std::make_shared<Light>(0.1f, 0x0003)});
    testLight2 = new Object(Transform(Vector2(8, 5)), L"Light2", {"Light"}, {std::make_shared<Light>(0.1f, 0x0004)});

    Engine->GetRenderer()->AddLight(testLight2);
    Engine->GetRenderer()->AddLight(testLight);

    PlayerInformation = *Player->GetComponent<Character>();

    currentLevel->AddObject(testLight2);
    testLight2->AddChild(testLight);

    Engine->Init();

    InitInventory();
    InitMenu();

    while (1)
    {
        ToolTip->t.SetWorldTransform(new Vector2(Engine->GetCoreEngine()->m_mousePosX + ToolTip->GetPanel().GetSize().x/2.0,
         Engine->GetCoreEngine()->m_mousePosY - ToolTip->GetPanel().GetSize().y));

        currentTime = Engine->GetCoreEngine()->Time - OldTime;
        int size = 0;

        //if(Player->GetComponent<Collider>() != nullptr)
        //size = (int)();

        //Debug(Player->GetTags().at(0));

        Engine->EngineUpdate();
        Input();

        //Debug(Engine->GetUI()->GetCanvasAt(0)->GetChildAt(4)->GetComponent<TextComponent>()->GetText());
        //Debug(Player->GetChildAt(0)->GetChildAt(0)->GetName());
        //if(Player->GetComponent<Character>()->GetInventory().size() > 1)

        Engine->GetCoreEngine()->GetCamera()->t.SetPos((Player->t.GetTranslatedPosition()));
        //Debug(StatPanel->GetChildAt(0)->t.GetPos());
        //if (Player->GetComponent<Character>()->GetInventory().size() != 0)
        //{
        //    for (int i = 0; i < Player->GetComponent<Character>()->GetInventory().size(); i++)
        //    {
        //        //Debug(Player->GetComponent<Character>()->GetInventoryAt(i)->object->GetName());
        //    }
        //}

        if (!Engine->GetCoreEngine()->IsFocused() && CurrentState == PLAY || !Engine->GetCoreEngine()->IsFocused() && CurrentState == INVENTORY)
        {
            CurrentState = PAUSED;
        }
        //If !Paused or !Focused, Show the game
        if (CurrentState == PLAY)
        {
            Engine->SetRenderWorldBool(true);

            //Engine->SetRenderWorldBool(false);

            if (currentTime >= duration)
            {
                currentTime = 0;
                OldTime = Engine->GetCoreEngine()->Time;
            }

            Menu->SetActive(false);
            Inventory->SetActive(false);
        }

        if (CurrentState == INVENTORY)
        {
            UpdateInventoryPanels();
            Engine->SetRenderWorldBool(false);
            Menu->SetActive(false);
            Inventory->SetActive(true);
        }

        if (CurrentState == PAUSED)
        {
            Engine->SetRenderWorldBool(false);
            Menu->SetActive(true);
            Inventory->SetActive(false);
        }
    }

    Engine->GetRenderer()->ResetConsoleMode();

    delete currentLevel;
    delete Player;
    delete testLight2;
    delete testLight;
    delete Menu;
    delete Inventory;
    delete Engine;
    return 0;
}

#include "GameMenu.cpp"
#include "GameInventory.cpp"

void Debug(wstring msg)
{
    Engine->GetUI()->Debug(msg);
}

void Debug(float d)
{
    Engine->GetUI()->Debug(s2ws(to_string(d)));
}

void Debug(int d)
{
    Engine->GetUI()->Debug(s2ws(to_string(d)));
}

void Debug(string s)
{
    Engine->GetUI()->Debug(s2ws(s));
}

void Debug(Vector2 v)
{
    Engine->GetUI()->Debug(s2ws(to_string((int)round(v.x)) + " " + to_string((int)round(v.y))));
}

//// upcast - implicit type cast allowed
//  Parent *pParent = &child;
//
//  // downcast - explicit type case required
//  Child *pChild =  (Child *) &parent;

void AssignLevel(Scene *Scene)
{
    currentLevel = Scene;
}

void Input()
{
    if (CurrentState == PLAY)
    {
        float speed = 21.2f * Engine->GetCoreEngine()->DeltaTime;
        Object *TestObject = Engine->GetCoreEngine()->GetSceneAt(0)->GetObjectAt(2);
        //Mouse has new scroll value

        if (Engine->GetCoreEngine()->GetKey((unsigned short)'F').bHeld)
        {
            testLight2->t.AddToX(-speed);
            //TestObject->t.AddToX(-speed);
        }

        if (Engine->GetCoreEngine()->GetKey((unsigned short)'G').bHeld)
        {
            testLight2->t.AddToX(speed);
            //TestObject->t.AddToX(speed);
        }

        if (Engine->GetCoreEngine()->GetKey((unsigned short)'A').bHeld)
        {
            direction.GoLeft();
            //Engine->GetCoreEngine()->GetCamera()->t.AddToX(speed);
            Player->t.AddToX(-speed);
        }
        if (Engine->GetCoreEngine()->GetKey((unsigned short)'D').bHeld)
        {
            direction.GoRight();
            //Engine->GetCoreEngine()->GetCamera()->t.AddToX(-speed);
            Player->t.AddToX(speed);
        }
        if (Engine->GetCoreEngine()->GetKey((unsigned short)'W').bHeld)
        {
            direction.GoUp();
            //Engine->GetCoreEngine()->GetCamera()->t.AddToY(speed);
            Player->t.AddToY(-speed);
        }

        if (Engine->GetCoreEngine()->GetKey((unsigned short)'S').bHeld)
        {
            direction.GoDown();
            //Engine->GetCoreEngine()->GetCamera()->t.AddToY(-speed);
            Player->t.AddToY(speed);
        }

        if ((Engine->GetCoreEngine()->GetKey((unsigned short)'I').bPressed))
        {
            CurrentState = INVENTORY;
        }

        if ((Engine->GetCoreEngine()->GetKey(VK_ESCAPE).bPressed))
        {
            CurrentState = PAUSED;
        }
    }
    else if (CurrentState == INVENTORY)
    {
        if ((Engine->GetCoreEngine()->GetKey(VK_ESCAPE).bPressed) || (Engine->GetCoreEngine()->GetKey((unsigned short)'I').bPressed))
        {
            CurrentState = PLAY;
        }
    }
    else if (CurrentState == PAUSED)
    {
        if (Engine->GetCoreEngine()->GetKey(VK_ESCAPE).bPressed)
        {
            CurrentState = PLAY;
        }
    }
}
