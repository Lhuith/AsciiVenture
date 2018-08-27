class Item : public Component
{
    int index;
    cUISpriteComponent *UISprite;
    std::wstring name;

  protected:
    int power;

  public:
    enum ITEMTYPE
    {
        DEFUALT,
        GEAR,
        WEAPON,
        CONSUMABLE,
        QUEST,
        EMPTY,
    } Type;

    enum ITEMRARITY
    {
        ZILCH,
        MISC,
        UNCOMMON,
        COMMON,
        RARE,
        UBER,
        LEGENDARY,
        ARTIFACT,
    } Quality;

    explicit Item(int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), ITEMTYPE t = ITEMTYPE::EMPTY, ITEMRARITY r = ITEMRARITY::ZILCH, std::wstring n = L"Empty")
        : index(_i), UISprite(_gUIS), Quality(r), Type(t), name(n) {}

    inline cUISpriteComponent *getUISprite() const { return UISprite; }
    ~Item() { delete UISprite; }

    std::wstring GetName() { return name; }
    ITEMRARITY GetRarity() { return Quality; }
    ITEMTYPE GetType() { return Type; }


    bool operator==(const Item& right){
        return this->name == right.name && 
               this->index == right.index && 
               this->Type == right.Type && 
               this->Quality == right.Quality;}
};

class Consumable : public Item
{

  public:
    explicit Consumable(int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Item(_i, _gUIS, Item::CONSUMABLE, Item::ITEMRARITY::MISC, n) {}
    //int Use(){return power;}
};

class Gear : public Item
{

    int Armour;

  protected:
  public:
    enum GEARTYPE
    {
        CLOTH,
        LEATHER,
        MAIL,
        PLATE,
        SHIELD
    } GearType;

    enum GEARSLOT
    {
        CHEST,
        PANTS,
        GLOVES,
        HEAD,
        BOOTS,
        OFFHAND
    } GearSlot;

    explicit Gear(GEARTYPE _gt = GEARTYPE::CLOTH, GEARSLOT _gs = GEARSLOT::CHEST, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : GearType(_gt), GearSlot(_gs), Armour(_a), Item(_i, _gUIS, Item::GEAR, rare, n) {}
    //int Use(){return power;}
};

class Chest : public Gear
{

  public:
    explicit Chest(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::CHEST, rare, _a, _i, _gUIS, n) {}
};

class Pants : public Gear
{

  public:
    explicit Pants(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::PANTS, rare, _a, _i, _gUIS, n) {}
};

class Gloves : public Gear
{

  public:
    explicit Gloves(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::GLOVES, rare, _a, _i, _gUIS, n) {}
};

class Head : public Gear
{

  public:
    explicit Head(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::HEAD, rare, _a, _i, _gUIS, n) {}
};

class Boots : public Gear
{

  public:
    explicit Boots(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::BOOTS, rare, _a, _i, _gUIS, n) {}
};

class Shield : public Gear
{

  public:
   explicit Shield(Gear::GEARTYPE _gt = GEARTYPE::SHIELD, Item::ITEMRARITY rare = Item::ITEMRARITY::COMMON, int _a = 1, int _i = 999, cUISpriteComponent *_gUIS = new cUISpriteComponent(), std::wstring n = L"Empty")
        : Gear(_gt, GEARSLOT::OFFHAND, rare, _a, _i, _gUIS, n) {}
};

class Weapon : public Item
{

    enum WEAPONTYPE
    {
        AXE,
        SWORD,
        BOW,
        STAFF,
    } WeaponType;

  public:
    //int Use(){return power;}
    //void Equip(){}
};