#include "../Math/Vector2.h"
#include "../Math/Utils.h"
#include "Component.h"

#include "../Math/Transform.h"

#include "../Entity.h"

#include "cSprite.h"

#include "Object.h"
#include "CameraComponent.h"
#include "Camera.h"
//#include "Primitives/Humonoid.h"
#include "../AsciiArt.h"



#include "Light.h"
#include "Scene.h"


//#include "Primitives/TestHouse.h"

#include "CoreEngine.h"
#include "RenderEngine.h"

#include "UIElements.h"

#include "UIEngine.h"
#include "../Item.h"

#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "../Character.h"
#include "PhysicsEngine.h"

#include "../OverWorld.h"

class ToiEngine
{

    PhysicsEngine *Physics;
    RenderEngine *Renderer;
    CoreEngine *Engine;
    UIEngine *UI;
    bool RenderWorld = false;

  public:
    ToiEngine(CoreEngine *ce = new CoreEngine(),
              RenderEngine *r = new RenderEngine(65, 20)) : Engine(new CoreEngine(ce->GetScenes(), new Camera(CameraComponent(r->GetScreenWidth(), r->GetScreenHeight())), r->GetSTDHConsole())),
                                                            Renderer(new RenderEngine(r->GetScreenWidth(), r->GetScreenHeight(), &ce->GetSceneAt(0)->objects, ce->GetSceneAt(0))),
                                                            Physics(new PhysicsEngine(&ce->GetSceneAt(0)->objects)),
                                                            UI(new UIEngine(new TextBox(24, 1, 20, 5, {L"Game Text"}, 0x0000 | 0x000F), Renderer))
    {
        Physics->SetEngine(Engine);
        Physics->SetUI(UI);
        Renderer->SetEngine(Engine);
        UI->SetEngine(Engine);
    }

    void Init()
    {
        Engine->Init();
        UI->Init();

        Physics->SetDebug(true);
    }
    void EngineUpdate()
    {
        Engine->Update();
        
        if (RenderWorld)
        {
            Renderer->RenderSceneMap();
            Renderer->RenderScene();
        }

        UI->Update();
        Physics->Update();
        UI->GetDebugWindow()->HightLight(Engine->m_mouseScroll, Engine->old_mouseScroll, Engine->m_mousePosX, Engine->m_mousePosY);
        Renderer->PrintGameInformation();
        Renderer->BlitToScreen();
    }

    void LateUpate();
    void FixedUpdate();
    void SetRenderWorldBool(bool b) { RenderWorld = b; }
    inline RenderEngine *GetRenderer() { return Renderer; }
    inline UIEngine *GetUI() { return UI; }
    inline PhysicsEngine *GetPhysics() { return Physics; }
    inline CoreEngine *GetCoreEngine() { return Engine; }
};

enum COLOUR
{
    FG_BLACK = 0x0000,
    FG_DARK_BLUE = 0x0001,
    FG_DARK_GREEN = 0x0002,
    FG_DARK_CYAN = 0x0003,
    FG_DARK_RED = 0x0004,
    FG_DARK_MAGENTA = 0x0005,
    FG_DARK_YELLOW = 0x0006,
    FG_GREY = 0x0007, //iThanksiMSi:-/
    FG_DARK_GREY = 0x0008,
    FG_BLUE = 0x0009,
    FG_GREEN = 0x000A,
    FG_CYAN = 0x000B,
    FG_RED = 0x000C,
    FG_MAGENTA = 0x000D,
    FG_YELLOW = 0x000E,
    FG_WHITE = 0x000F,
    BG_BLACK = 0x0000,
    BG_DARK_BLUE = 0x0010,
    BG_DARK_GREEN = 0x0020,
    BG_DARK_CYAN = 0x0030,
    BG_DARK_RED = 0x0040,
    BG_DARK_MAGENTA = 0x0050,
    BG_DARK_YELLOW = 0x0060,
    BG_GREY = 0x0070,
    BG_DARK_GREY = 0x0080,
    BG_BLUE = 0x0090,
    BG_GREEN = 0x00A0,
    BG_CYAN = 0x00B0,
    BG_RED = 0x00C0,
    BG_MAGENTA = 0x00D0,
    BG_YELLOW = 0x00E0,
    BG_WHITE = 0x00F0,
};