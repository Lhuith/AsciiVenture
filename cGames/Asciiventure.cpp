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

class ItemUIComponent : public Component
{

    Item *item;

  public:
    ItemUIComponent(Item *i) : item(i) {}

    Item GetItem() { return *item; }
    Item* GetItemRef() { return item; }
    void SetItem(Item *i) { this->item = i; };
};

class ItemUIPanel : public Object
{

  public:
    explicit ItemUIPanel(Vector2 pos, Vector2 s, Item *i = new Item()) : Object(Transform(pos), L"UIPanel", {"UI"}, {
            std::make_shared<PanelComponent>(PanelComponent(s, 0x000F | 0x0000, true)),
            std::make_shared<cUISpriteComponent>(cUISpriteComponent()),
            std::make_shared<ItemUIComponent>(ItemUIComponent(i)),
                                                                                                                    }){};

    cUISpriteComponent &GetSprite() { return *this->GetComponent<cUISpriteComponent>(); }
    
    void SetSprite(cSprite s)
    {
        this->GetComponent<cUISpriteComponent>()->SetM(s.GetM());
        this->GetComponent<cUISpriteComponent>()->SetSize(s.GetSize());
        this->GetComponent<cUISpriteComponent>()->SetColor(s.GetColor());
    };

    Item GetItem() { return this->GetComponent<ItemUIComponent>()->GetItem(); }
    Item* GetItemRef() { return this->GetComponent<ItemUIComponent>()->GetItemRef(); }

    void SetItem(Item *i)
    {
        this->GetComponent<ItemUIComponent>()->SetItem(i);
        SetSprite(*i->getUISprite());
    };

    PanelComponent &GetPanel() { return *this->GetComponentAt<PanelComponent>(0); }
    void SetPanel(PanelComponent p) { GetPanel() = p; }
};

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
Panel *ToolTip;

std::vector<ItemUIPanel *> InventoryPanels;
std::vector<ItemUIPanel *> InventoryPanelsCleanUp;
std::vector<ItemUIPanel *> InventoryPanelsOnExit;

float fPlayerX = 32;
float fPlayerY = 9;
float fPlayerA = 0.0f;

Object *testLight;
Object *testLight2;

Scene *currentLevel;

Object *Player;
Character PlayerInformation;
Vector2 *tPos;

enum GameStates
{
    PAUSED,
    PLAY,
    INVENTORY,
};

GameStates CurrentState;
int InventoryListLog = 0;

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
void HandleToolTip();
bool IsUITouching(Object *o, Panel &toolTip);
void ManageToolTip();
WORD RareToColor(Item::ITEMRARITY r);
void HandleInventoryInteraction();

float OldTime, currentTime, duration = 1.0;

ToiEngine *Engine;

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
        currentTime = Engine->GetCoreEngine()->Time - OldTime;
        int size = 0;

        ManageToolTip();
        UpdateInventoryPanels();
        HandleInventoryInteraction();
        Engine->EngineUpdate();
        Input();

        Engine->GetCoreEngine()->GetCamera()->t.SetPos((Player->t.GetTranslatedPosition()));

        if (!Engine->GetCoreEngine()->IsFocused() && CurrentState == PLAY || !Engine->GetCoreEngine()->IsFocused() && CurrentState == INVENTORY)
        {
            CurrentState = PAUSED;
        }
        //If !Paused or !Focused, Show the game
        if (CurrentState == PLAY)
        {
            Engine->SetRenderWorldBool(true);

            if (currentTime >= duration)
            {
                currentTime = 0;
                OldTime = Engine->GetCoreEngine()->Time;
            }

            Menu->SetActive(false);
            Inventory->SetActive(false);

            Debug((int)InventoryPanels.size());
        }

        if (CurrentState == INVENTORY)
        {

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

        HandleToolTip();
    }

    Engine->GetRenderer()->ResetConsoleMode();

    delete currentLevel;
    delete Player;
    delete testLight2;
    delete testLight;
    delete Menu;
    delete Inventory;
    delete Engine;
    delete ToolTip;
    delete tPos;

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

void ManageToolTip()
{
    tPos = new Vector2(Engine->GetCoreEngine()->m_mousePosX + 3, Engine->GetCoreEngine()->m_mousePosY);

    if (tPos->x + ToolTip->GetPanel().GetSize().x > Engine->GetRenderer()->GetScreenWidth())
    {
        tPos = new Vector2(Engine->GetRenderer()->GetScreenWidth() - ToolTip->GetPanel().GetSize().x, tPos->y);
    }

    if (tPos->y + ToolTip->GetPanel().GetSize().y + 1 > Engine->GetRenderer()->GetScreenHeight())
    {
        tPos = new Vector2(tPos->x, Engine->GetRenderer()->GetScreenHeight() - ToolTip->GetPanel().GetSize().y - 1);
    }

    ToolTip->t.SetWorldTransform(tPos);
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
