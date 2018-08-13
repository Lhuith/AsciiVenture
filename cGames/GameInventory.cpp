
void InitInventory()
{
    RenderEngine *r = Engine->GetRenderer();

    Inventory = new Panel(Vector2(0, 0), PanelComponent(Vector2(r->GetScreenWidth(), r->GetScreenHeight()), 0x0000, false));

    InventoryPanels = vector<ItemUIPanel *>();
    SetInventoryPanels();
    //Title
    Inventory->AddChild(new Text(Vector2(0, 1), TextComponent(L"ITEMS", 0x0000 | 0x00F0)));

    //MainPanel
    Inventory->AddChild(new Panel(Vector2(2, 2), PanelComponent(Vector2(11, 15), 0x00F0)));
    Inventory->AddChild(new Text(Vector2(2, 1), TextComponent(L"GEAR", 0x0000 | 0x00F0, TextComponent::Alignment::L)));

    Inventory->AddChild(new Panel(Vector2(6, 3), PanelComponent(Vector2(3, 2), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(5, 6), PanelComponent(Vector2(5, 3), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(6, 10), PanelComponent(Vector2(3, 3), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(3, 9), PanelComponent(Vector2(1, 1), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(11, 9), PanelComponent(Vector2(1, 1), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(5, 14), PanelComponent(Vector2(2, 2), 0x000F | 0x0000, true)));
    Inventory->AddChild(new Panel(Vector2(8, 14), PanelComponent(Vector2(2, 2), 0x000F | 0x0000, true)));

    StatPanel = new Panel(Vector2(r->GetScreenWidth() - 15, 2), PanelComponent(Vector2(13, 15), 0x00F0, false));
    Inventory->AddChild(StatPanel);

    wstring staminaTitle = L"Stamina: ";
    wstring stamina = L"222"; //s2ws(std::to_string(PlayerInformation.GetStamina()));

    wstring strengthTitle = L"Strength: ";
    wstring strength = s2ws(std::to_string(PlayerInformation.GetStrength()));

    wstring intellectTitle = L"Intellect: ";
    wstring intellect = s2ws(std::to_string(PlayerInformation.GetIntellect()));

    wstring agilityTitle = L"Agility: ";
    wstring agility = s2ws(std::to_string(PlayerInformation.GetAgility()));

    wstring armourTitle = L"Armour: ";
    wstring armour = s2ws(std::to_string(PlayerInformation.GetArmour()));

    wstring healthTitle = L"Health: ";
    wstring health = s2ws(std::to_string(PlayerInformation.GetHealth()));

    wstring manaTitle = L"Mana: ";
    wstring mana = s2ws(std::to_string(PlayerInformation.GetMana()));

    wstring energyTitle = L"Energy: ";
    wstring energy = s2ws(std::to_string(PlayerInformation.GetEnergy()));

    StatPanel->AddChild(new Text(Vector2(0, -1), TextComponent(L"STATS", 0x0000 | 0x00F0, TextComponent::Alignment::L)));

    StatPanel->AddChild(new Text(Vector2(0, 1), TextComponent(Player->GetName(), 0x000D | 0x00F0, TextComponent::Alignment::C)));

    StatPanel->AddChild(new Text(Vector2(0, 2), TextComponent(staminaTitle, 0x0000 | 0x00F0, TextComponent::Alignment::C)));
    StatPanel->AddChild(new Text(Vector2(0, 2), TextComponent(stamina, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 3), TextComponent(strengthTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 3), TextComponent(strength, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 4), TextComponent(intellectTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 4), TextComponent(intellect, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 5), TextComponent(agilityTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 5), TextComponent(agility, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 6), TextComponent(armourTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 6), TextComponent(armour, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 7), TextComponent(healthTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 6), TextComponent(health, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 8), TextComponent(manaTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 6), TextComponent(mana, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    StatPanel->AddChild(new Text(Vector2(0, 9), TextComponent(energyTitle, 0x0000 | 0x00F0, TextComponent::Alignment::L)));
    StatPanel->AddChild(new Text(Vector2(0, 6), TextComponent(energy, 0x0000 | 0x00F0, TextComponent::Alignment::R)));

    Inventory->SetActive(false);
    Engine->GetUI()->AddUIElement(Inventory);

    ToolTip = new Panel(Vector2(0, 0), PanelComponent(Vector2(12, 5), 0x00F0));
    ToolTip->t.SetWorldTransform(new Vector2(Engine->GetCoreEngine()->m_mousePosX + ToolTip->GetPanel().GetSize().x / 2.0,
                                             Engine->GetCoreEngine()->m_mousePosY - ToolTip->GetPanel().GetSize().y));
    ToolTip->SetActive(false);
    ToolTip->AddChild(new Text(Vector2(0, 0), TextComponent(L"Name", 0x000F, TextComponent::Alignment::L, false)));
    ToolTip->AddChild(new Text(Vector2(0, 1), TextComponent(L"Information", 0x000F, TextComponent::Alignment::L, false)));
    Engine->GetUI()->AddUIElement(ToolTip);
}

void SetInventoryPanels()
{

    int w = 9;
    int h = 4;
    int max = w * h;

    for (int j = 0; j < h; j++)
        for (int i = 0; i < w; i++)
        {

            int sizeX = 3;
            int sizeY = 3;

            Vector2 v = Vector2(i * (sizeX + 1) + 14, j * (sizeY + 1) + 2);

            ItemUIPanel *p = new ItemUIPanel(v, Vector2(sizeX, sizeY), new Item());

            InventoryPanels.push_back(p);
            Inventory->AddChild(p);
            p->SetActive(false);
        }
}

void UpdateInventoryPanels()
{

    int w = 9;
    int h = 4;
    int max = w * h;

    for (int j = 0; j < h; j++)
        for (int i = 0; i < w; i++)
        {
            int index = i * h + j;

            if ((int)Player->GetComponent<Character>()->GetInventory().size() != 0)
            {
                if (index < (int)Player->GetComponent<Character>()->GetInventory().size())
                {
                    Item *item = Player->GetComponent<Character>()->GetInventoryAt(index);

                    InventoryPanels.at(index)->SetActive(true);

                    InventoryPanels.at(index)->SetItem(item);
                    InventoryPanels.at(index)->SetSprite(*item->getUISprite());
                    InventoryPanels.at(index)->GetSprite().Setinteractive(true);
                }
            }

            if (InventoryPanels.at(0)->isActive)
            {
                if (InventoryPanels.at(index)->GetComponent<ItemUIComponent>() != nullptr)
                {
                    if (InventoryPanels.at(index)->GetComponent<PanelComponent>()->Gettouching())
                    {
                        if (Engine->GetCoreEngine()->GetMouse(1).bPressed)
                        {
                            //InventoryPanels.erase(remove(InventoryPanels.begin(), InventoryPanels.end(), InventoryPanels.at(0)), InventoryPanels.end());
                            break;
                        }
                    }
                }
            }
        }
}

void HandleToolTip()
{
    ToolTip->SetActive(false);
    bool isTouching = false;
    wstring text = L"poopoo";
    WORD color = 0x000F;

    for (int i = 0; i < Engine->GetUI()->GetUIElements().size(); i++)
    {
        if (Engine->GetUI()->GetUIElements().at(i)->isActive)
        {
            if (Engine->GetUI()->GetUIElements().at(i)->GetComponent<PanelComponent>() != nullptr)
            {
                isTouching = IsUITouching(Engine->GetUI()->GetUIElements().at(i), *ToolTip);
                if (isTouching)
                    break;
            }
        }
    }

    if (isTouching)
    {
        ToolTip->SetActive(true);
    }
    else
    {
        ToolTip->SetActive(false);
    }
}

WORD RareToColor(Item::ITEMRARITY r)
{

    if (r == Item::ITEMRARITY::COMMON || r == Item::ITEMRARITY::ZILCH || r == Item::ITEMRARITY::MISC)
    {
        return 0x000F | 0x0000;
    }
    else if (r == Item::ITEMRARITY::UNCOMMON)
    {
        return 0x000A | 0x0000;
    }
    else if (r == Item::ITEMRARITY::RARE)
    {
        return 0x000B | 0x0000;
    }
    else if (r == Item::ITEMRARITY::LEGENDARY)
    {
        return 0x000D | 0x0000;
    }
    else if (r == Item::ITEMRARITY::UBER)
    {
        return 0x000E | 0x0000;
    }
    else if (r == Item::ITEMRARITY::ARTIFACT)
    {
        return 0x000C | 0x0000;
    }

    return 0x000F | 0x0000;
}

bool IsUITouching(Object *o, Panel &toolTip)
{
    if (o->GetComponent<PanelComponent>() != nullptr)
    {
        if (o->GetComponent<PanelComponent>()->Gettouching())
        {
            if (o->GetComponent<ItemUIComponent>() != nullptr)
            {
                //Set Name and color to rarity
                toolTip.GetChildAt(0)->GetComponent<TextComponent>()->SetText(o->GetComponent<ItemUIComponent>()->GetItem().GetName());
                toolTip.GetChildAt(0)->GetComponent<TextComponent>()->SetColor(RareToColor((o->GetComponent<ItemUIComponent>()->GetItem().GetRarity())));

                return true;
            }
        }
    }

    if (o->GetChildren().size() != 0)
    {
        for (int j = 0; j < o->GetChildren().size(); j++)
        {
            if (o->GetChildAt(j)->isActive)
            {
                if (o->GetChildAt(j)->GetComponent<PanelComponent>() != nullptr)
                {
                    if (IsUITouching(o->GetChildAt(j), toolTip))
                        return true;
                }

                if (o->GetChildAt(j)->GetComponent<TextComponent>() != nullptr)
                {
                    if (o->GetChildAt(j)->GetComponent<TextComponent>()->Gettouching())
                    {
                        toolTip.GetChildAt(0)->GetComponent<TextComponent>()->SetText(o->GetChildAt(j)->GetComponent<TextComponent>()->GetText());
                        return true;
                    }
                }

                if (o->GetChildAt(j)->GetComponent<cUISpriteComponent>() != nullptr)
                {
                    if (o->GetChildAt(j)->GetComponent<cUISpriteComponent>()->Gettouching())
                    {
                        toolTip.GetChildAt(0)->GetComponent<TextComponent>()->SetText(o->GetChildAt(j)->GetComponent<cUISpriteComponent>()->object->GetName());
                        return true;
                    }
                }

                if (o->GetChildAt(j)->GetComponent<cUISpriteComponent>() != nullptr)
                {
                    if (o->GetChildAt(j)->GetComponent<cUISpriteComponent>()->Gettouching())
                    {
                        toolTip.GetChildAt(0)->GetComponent<TextComponent>()->SetText(o->GetChildAt(j)->GetComponent<cUISpriteComponent>()->object->GetName());
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }

    return false;
}