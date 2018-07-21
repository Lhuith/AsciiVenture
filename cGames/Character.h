class Class
{

public:
  Class(std::wstring _n = L"Defualt") : className(_n){};
  inline std::wstring GetName() { return className; }

protected:
  std::wstring className;
};

class Warrior : public Class
{
public:
  Warrior() : Class(L"Warroir"){};

private:
protected:
};

class Ranger : public Class
{

public:
  Ranger() : Class(L"Ranger"){};

private:
protected:
};

class Mage : public Class
{

public:
  Mage() : Class(L"Mage"){};

private:
protected:
};

class Paladin : public Class
{

public:
  Paladin() : Class(L"Paladin"){};

private:
protected:
};

class Character : public Component
{
  int Health = 100;
  int Mana = 100;
  int Energy = 100;

  int Strength;
  int Intelligence;
  int Agility;
  int Stamina;
  int InventoryMax = 10;

  Object *Selected = nullptr;

  std::shared_ptr<Class> *ClassType;
  Gear gearslots[5];
  std::vector<Item*> Inventory;

public:
  std::wstring ClassName;
  Character(int _s = 1, int _i = 1, int _a = 1, int _st = 1, std::shared_ptr<Class> _ct = std::make_shared<Class>()) : Strength(_s), Intelligence(_i), Agility(_a), Stamina(_st), ClassType(&_ct), ClassName(_ct->GetName()){};

  Item GetInventoryAt(int i) { return *Inventory[i]; }
  std::vector<Item*> GetInventory() { return Inventory; }
  void AddToInventory(Item& i)
  {
    if (std::find(this->Inventory.begin(), this->Inventory.end(), &i) == this->Inventory.end())
    {
      Inventory.push_back(&i);
    }
  }
  //std::vector<Item> GetInventory(){return Inventory;}
  void SetSelected(Object *s) { this->Selected = s; }
  Object *GetSelected() { return Selected; }
  ~Character()
  {
    delete ClassType;
    delete Selected;
    Selected = NULL;
  }

  void Update()
  {

    if (object->GetComponent<Collider>() != nullptr)
    {

      Collider c = *object->GetComponent<Collider>();

      for (int i = 0; i < c.GetCollisions().size(); i++)
      {

        if (c.GetCollisions().at(i)->GetComponent<Collider>() != nullptr)
        {
          Collider other = *c.GetCollisions().at(i)->GetComponent<Collider>();

          if (other.object->GetTags().at(0) == "Item")
          {
            //object->GetComponent<cSprite>()->SetCol(0x0009);
            AddToInventory(*other.object->GetComponent<Item>());
            other.object->Destroy();
          }
        }
      }
    }
  }

private:
protected:
};