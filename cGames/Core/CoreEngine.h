class CoreEngine
{
    struct sKeyState
    {
        bool bPressed;
        bool bReleased;
        bool bHeld;
    } m_keys[256], m_mouse[5];

    Camera *MainCamera;
    std::vector<Scene *> Scenes;

        HANDLE m_hConsoleInPTR;
        
  public:
    std::vector<std::string> FLAGS{
        "Player",
        "UI",
        "Camera",
    }; //Handlers for Renderer and Physics to skip certain objects and class's

    int m_mousePosX;
    int m_mousePosY;

    int m_mouseScroll = 0;
    int old_mouseScroll = 0;

    float Time;
    float DeltaTime;
    std::chrono::_V2::system_clock::time_point tp1, tp2;

    CoreEngine(std::vector<Scene *> s = {new Scene()}, Camera *c = new Camera(CameraComponent(1, 1)), HANDLE CinPTR = nullptr)
        : MainCamera(c),
          m_hConsoleInPTR(CinPTR),
          Scenes(s)
    {

        //Set World and Set Camera are Both the same thing

        //Physics->SetWorldTransform(c->t.GetPositionRefrence());
        //Renderer->SetWorldTransform(c->t.GetPositionRefrence());
        //Physics->SetCamera(c);

        //Will need to do something about this
        Scenes.at(0)->SetWorldTransform(c->t.GetPositionRefrence());

        memset(m_keyNewState, 0, 256 * sizeof(short));
        memset(m_keyOldState, 0, 256 * sizeof(short));
        memset(m_keys, 0, 256 * sizeof(sKeyState));
    }

    void Update()
    {
        // We'll need Time differential per frame to calculate modification
        // to movement speeds, to ensure consistant movement, as ray-tracing
        // is non-deterministic

        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        DeltaTime = elapsedTime.count();
        Time += DeltaTime;

        ProcessInput();

        if (Scenes.size() != 0)
        {
            for (int i = 0; i < Scenes.size(); i++)
            {
                Scenes.at(i)->Update();
            }
        }
    }
    void Init()
    {
        tp1 = std::chrono::system_clock::now();
        tp2 = std::chrono::system_clock::now();

        if (Scenes.size() != 0)
        {
            for (int i = 0; i < Scenes.size(); i++)
            {
                Scenes.at(i)->Init();
            }
        }
    };
    void ProcessInput();

    inline Scene *GetSceneAt(int i) const { return Scenes.at(i); }
    //inline Scene GetSceneRefenceAt(int i) {return Scenes.at(i);}
    bool IsFocused() { return m_bConsoleInFocus; }
    inline Object *GetCamera() { return (Object *)MainCamera; }
    sKeyState GetKey(int nKeyID) { return m_keys[nKeyID]; }
    sKeyState GetMouse(int nMouseButtonID) { return m_mouse[nMouseButtonID]; }
    inline std::vector<Scene *> GetScenes() { return Scenes; }

    ~CoreEngine()
    {
        delete MainCamera;

        if (Scenes.size() != 0)
        {
            for (int i = 0; i < Scenes.size(); i++)
            {
                delete Scenes.at(i);
            }
        }
    }

  protected:
    short m_keyOldState[256] = {0};
    short m_keyNewState[256] = {0};
    bool m_mouseOldState[5] = {0};
    bool m_mouseNewState[5] = {0};

    bool m_bConsoleInFocus = true;
};

#include "CoreEngine.cpp"