class Item : public Component {
    int index;
    cUISpriteComponent *UISprite;
    protected:
        int power;
    enum ITEMTYPE{
        DEFUALT,
        GEAR,
        WEAPON,
        CONSUMABLE,
        QUEST,
    } Type;
    
    enum ITEMRARITY{
        MISC,
        UNCOMMON,
        COMMON,
        RARE,
        UBER,
        LEGENDARY
    } Quality;

    
    public:
        Item(int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent(), ITEMTYPE t = ITEMTYPE::DEFUALT, ITEMRARITY r = ITEMRARITY::MISC) 
        : index(_i), UISprite(_gUIS), Quality(r), Type(t){}
        
        inline cUISpriteComponent* getUISprite() const {return UISprite;}
        ~Item(){delete UISprite;}
};

class Consumable : public Item {

    public:
        Consumable(int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent()) 
        : Item(_i, _gUIS, _gWS, Item::CONSUMABLE){}
        //int Use(){return power;}
};

class Gear : public Item {

    int Armour;
    protected:

    public:
    enum GEARTYPE {
        CLOTH,
        LEATHER,
        MAIL,
        PLATE,
        SHIELD
    } GearType;

    enum GEARSLOT {
        CHEST,
        PANTS,
        GLOVES,
        HEAD,
        BOOTS,
        OFFHAND
    } GearSlot;


    Gear(GEARTYPE _gt = GEARTYPE::CLOTH, GEARSLOT _gs = GEARSLOT::CHEST, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : GearType(_gt), GearSlot(_gs), Armour(_a), Item(_i, _gUIS, _gWS, Item::GEAR){}
        //int Use(){return power;}
};

class Chest: public Gear{

    public:
      Chest(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::CHEST,_a, _i, _gUIS, _gWS){}

};

class Pants: public Gear{

    public:
     Pants(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::PANTS,_a, _i, _gUIS, _gWS){}

};

class Gloves: public Gear{

    public:
        Gloves(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::GLOVES,_a, _i, _gUIS, _gWS){}

};

class Head: public Gear{

    public:
        Head(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::HEAD,_a, _i, _gUIS, _gWS){}

};

class Boots: public Gear{

    public:
        Boots(Gear::GEARTYPE _gt = GEARTYPE::CLOTH, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::BOOTS,_a, _i, _gUIS, _gWS){}

};

class Shield: public Gear{

    public:
        Shield(Gear::GEARTYPE _gt = GEARTYPE::SHIELD, int _a = 1, int _i = 999, cUISpriteComponent* _gUIS = new cUISpriteComponent(), cUISpriteComponent* _gWS = new cUISpriteComponent())
         : Gear(_gt, GEARSLOT::OFFHAND,_a, _i, _gUIS, _gWS){}
}; 

class Weapon : public Item {

    enum WEAPONTYPE{
        AXE,
        SWORD,
        BOW,
        STAFF,
    } WeaponType;

    public:
        //int Use(){return power;}
        //void Equip(){}
};