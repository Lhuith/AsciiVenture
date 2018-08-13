namespace Models {
    namespace Entities{

        cSprite humanoid_00(
           L"  o  "
            " ||| "
            "  ║  ", Vector2(5, 3), Vector2(1, 1), 0x000F
        );
        cSprite humanoid_01(
            L"  ÷  "
            " ||| "
            "  ║  ", Vector2(5, 3), Vector2(1, 1), 0x000F
        );
        cSprite humanoid_02(
            L"  Θ  "
            " ||| "
            "  ║  ", Vector2(5, 3), Vector2(1, 1), 0x000F
        );
        cSprite humanoid_03(
            L"  ᵶ  "
            " ||| "
            "  ║  ", Vector2(5, 3), Vector2(1, 1), 0x000F
        );
    }
    namespace UI {
        std::wstring potion_00(
            L"   "  
             " ▄ "
             "▐█▌");
        std::wstring gloves_00_slot(L"+");
        std::wstring head_00_slot(L"+-+"
                                   "+ +");
        std::wstring chest_00_slot(L"+---+"
                                    " |-| "
                                    " +-+ ");
        std::wstring pants_00_slot(L"---"
                                    "| |"
                                    "| |");
        std::wstring boots_00_slot(L"+ "
                                    "+-");
        std::wstring boots_00_b_slot(L" +"
                                      "-+");

        std::wstring chest_00(L"▄▄▄"
                               "▐█▌"
                               "   ");

        std::wstring pants_00(L"▄▄▄"
                               "▌ ▐"
                               "   ");


        std::wstring head_00(L"   "
                              "█▀█"
                              "   ");
         std::wstring boots_00(L"   "
                                " █ "
                                "▀▀ ");

    }

    namespace Items {
        std::wstring potion_00(L"u");

        std::wstring chest_00(L"▄▄▄"
                               "▐█▌");

        std::wstring pants_00(L"▄▄"
                               "▌▐");

        std::wstring head_00(L"∩");

        std::wstring boots_00(L"╝ ╚");
    }
}