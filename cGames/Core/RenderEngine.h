class RenderEngine
{
    std::vector<Object *> *objects; //pointer to scene objects to render
    std::vector<Object *> lights;   //points to objects with lights component

    Scene *scene; //Current Scene

    HANDLE m_hConsole, m_hConsoleIn;
    SMALL_RECT m_rectWindow;
    DWORD dwBytesWritten, prev_mode;
    HANDLE m_hOriginalConsole;

    COORD coord;

  public:
    void ScreenInit();
    //will auto add lights when they are created
    explicit RenderEngine(int screenwidth = 65, int screenheight = 20, std::vector<Object *> *_o = {nullptr}, Scene *s = new Scene())
        : nScreenWidth(screenwidth), nScreenHeight(screenheight), objects(_o), scene(s)
    {
        SHORT WIDTH = (short)this->nScreenWidth;
        SHORT HEIGHT = (short)this->nScreenHeight;

        m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

        COORD coord = {(SHORT)nScreenWidth, (SHORT)nScreenHeight};

        //Set the size of the screen buffer
        SetConsoleScreenBufferSize(m_hConsole, coord);
        SetConsoleActiveScreenBuffer(m_hConsole);

        //Set Physical Console Window size    
        m_rectWindow = {0, 1, WIDTH, HEIGHT};
        SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

        //Set Flags to allow mouse input
        SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
        screenBuffer = new CHAR_INFO[nScreenWidth * nScreenHeight];
        memset(screenBuffer, 0, sizeof(CHAR_INFO) * screenwidth * screenheight);

        GameInformation = new wchar_t[nScreenWidth * screenheight - 1];
        memset(GameInformation, 0, sizeof(wchar_t) * screenwidth * screenheight - 1);

        SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
    }
    //void ()

    //Draw ScreenBuffer to Screen
    void BlitToScreen();

    static BOOL CloseHandler(DWORD evt)
	{
		// Note this gets called in a seperate OS thread, so it must
		// only exit when the game has finished cleaning up, or else
		// the process will be killed before OnUserDestroy() has finished
		if (evt == CTRL_CLOSE_EVENT)
		{
			//m_bAtomActive = false;

			//// Wait for thread to be exited
			//unique_lock<mutex> ul(m_muxGame);
			//m_cvGameFinished.wait(ul);
		}
		return true;
	}

    ~RenderEngine(){ 
        delete objects; 
        delete[] screenBuffer; 
        delete[] GameInformation; 
        delete Engine;

        delete scene;

        if(lights.size() != 0){
            for(int i = 0; i < lights.size(); i++){
                delete lights.at(i);
            }
        }

        SetConsoleActiveScreenBuffer(m_hOriginalConsole);
        }
    
    WORD RenderLight(CHAR_INFO att, int x, int y);
    void AddLight(Object *l) { lights.push_back(l); }
    std::vector<Object *> GetLights() { return lights; }

    void RenderScene();
    void RenderModel(cSprite s, Vector2 p);
    void RenderSceneMap();

    void Update() { RenderScene(); }
    void ResetConsoleMode() { SetConsoleMode(m_hConsoleIn, prev_mode | ENABLE_EXTENDED_FLAGS); }
    inline void PrintGameInformation() {swprintf(GameInformation, L"X=%d, Y=%d, Type=%d, World: %s", (int)this->Engine->GetCamera()->t.GetPos().x, (int)this->Engine->GetCamera()->t.GetPos().y, lights.size(), (scene->GetName().c_str())); }
    inline void SetScene(Scene* s){scene = s;}
    inline HANDLE GetSTDHConsole() { return m_hConsoleIn; }

    inline int GetScreenWidth() const { return nScreenWidth; }
    inline int GetScreenHeight() const { return nScreenHeight; }
    
    inline void SetScreenAttributeAt(int i, WORD w) { screenBuffer[i].Attributes = w; }
    inline void SetScreenCharAt(int i, CHAR_INFO c) { screenBuffer[i] = c; }
    inline void SetScreenAt(int i, char c) { screenBuffer[i].Char.UnicodeChar = c; }
    CoreEngine* GetEngine(){return Engine;}
    void SetEngine(CoreEngine* e){this->Engine = e;}
  private:
  protected:
    _CHAR_INFO *screenBuffer;
    wchar_t *GameInformation;
    int nScreenWidth;
    int nScreenHeight;
    CoreEngine* Engine;
};

#include "RenderEngine.cpp"