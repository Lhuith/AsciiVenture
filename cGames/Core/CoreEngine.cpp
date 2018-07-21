void CoreEngine::ProcessInput()
{
    //// Handle Keyboard Input
    for (int i = 0; i < 256; i++)
    {
        m_keyNewState[i] = GetAsyncKeyState(i);

        m_keys[i].bPressed = false;
        m_keys[i].bReleased = false;

        if (m_keyNewState[i] != m_keyOldState[i])
        {
            if (m_keyNewState[i] & 0x8000)
            {
                m_keys[i].bPressed = !m_keys[i].bHeld;
                m_keys[i].bHeld = true;
            }
            else
            {
                m_keys[i].bReleased = true;
                m_keys[i].bHeld = false;
            }
        }

        m_keyOldState[i] = m_keyNewState[i];
    }

    // Handle Mouse Input - Check for window events
    INPUT_RECORD inBuf[32];
    DWORD events = 0;
    GetNumberOfConsoleInputEvents(m_hConsoleInPTR, &events);
    if (events > 0)
        ReadConsoleInput(m_hConsoleInPTR, inBuf, events, &events);

    // Handle events - we only care about mouse clicks and movement
    // for now
    for (DWORD i = 0; i < events; i++)
    {
        switch (inBuf[i].EventType)
        {
        case FOCUS_EVENT:
        {
            m_bConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
        }
        break;

        case MOUSE_EVENT:
        {
            switch (inBuf[i].Event.MouseEvent.dwEventFlags)
            {
            case MOUSE_MOVED:
            {
                m_mousePosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
                m_mousePosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
                //Debug(s2ws(to_string(m_mousePosX)));
            }
            break;

            case MOUSE_WHEELED:
            {
                m_mouseScroll += inBuf[i].Event.MouseEvent.dwButtonState;
            }
            break;

            case 0:
            {
                for (int m = 0; m < 5; m++)
                    m_mouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
            }
            break;

            default:
                break;
            }
        }
        break;

        default:

            break;
            // We don't care just at the moment
        }
    }

    for (int m = 0; m < 5; m++)
    {
        m_mouse[m].bPressed = false;
        m_mouse[m].bReleased = false;

        if (m_mouseNewState[m] != m_mouseOldState[m])
        {
            if (m_mouseNewState[m])
            {
                m_mouse[m].bPressed = true;
                m_mouse[m].bHeld = true;
            }
            else
            {
                m_mouse[m].bReleased = true;
                m_mouse[m].bHeld = false;
            }
        }

        m_mouseOldState[m] = m_mouseNewState[m];
    }
}