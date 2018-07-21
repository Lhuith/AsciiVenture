//class Scene;

class Object
{
    std::wstring name;
    Object *Parent;
    std::vector<Object *> *local;
    std::vector<Object *> children;

  public:
    Transform t;
    std::vector<std::string> tags;
    bool isActive = true;

    explicit Object(Transform _t = Transform(Vector2(0, 0)), std::wstring n = L"Fart", std::vector<std::string> _ta = {"Defualt"},
                    std::vector<std::shared_ptr<Component>> _c = {std::make_shared<Component>()})
        : t(_t), name(n), components(_c), tags(_ta) {}

    inline std::wstring GetName() const { return name; }
    void SetComponents();
    void SetLocalArray(std::vector<Object *> &l) { this->local = &l; }
    template <typename T>
    std::shared_ptr<T> AddComponent();
    template <typename T>
    std::shared_ptr<T> GetComponent();
    inline void SetTag(std::string str)
    {
        if (find(this->tags.begin(), this->tags.end(), str) == this->tags.end())
        {
            tags.push_back(str);
        }
    };
    inline std::vector<std::string> GetTags() { return tags; }

    //----------------------- CHILDREN --------------------------//
    void UpdateChildren();
    void SetChildren();
    void SetChild(int i);
    void SetChild(Object *o);
    std::vector<Object *> GetChildren() { return children; }
    Object *GetChildAt(int i) { return children.at(i); }
    
    void AddChild(Object *o)
    {
        if (std::find(this->children.begin(), this->children.end(), o) == this->children.end())
        {
            children.push_back(o);
            SetChild(o);
            SetComponents();
        }
    }

    //----------------------- CHILDREN --------------------------//

    void UpdateComponents();
    virtual void Init()
    {
        SetComponents();
        SetChildren();
    }
    virtual void Update()
    {
        t.Update();
        UpdateComponents();
        UpdateChildren();
    }
    void Remove(Object *o);
    virtual void Destroy() { Remove(this); }

    void SetActive(bool b) { isActive = b; }
    ~Object()
    {
        delete Parent;
        delete local;
    }

  private:
  protected:
    //Collection of Components
    std::vector<std::shared_ptr<Component>> components;
};

template <typename T>
std::shared_ptr<T> Object::GetComponent()
{

    //Check that we dont already have a component of this type.
    for (std::shared_ptr<Component> existingComponent : components)
    {
        if (std::dynamic_pointer_cast<T>(existingComponent))
        {
            return std::dynamic_pointer_cast<T>(existingComponent);
        }
    }

    return nullptr;
}

template <typename T>
std::shared_ptr<T> Object::AddComponent()
{
    //first well create the component
    std::shared_ptr<T> newComponent = std::make_shared<T>();

    //Check that we dont already have component of this type.
    //std::dynamic_pointer_cast<T>(exist)
    for (std::shared_ptr<Component> &existingComponent : components)
    {
        if (std::dynamic_pointer_cast<T>(existingComponent))
        {
            //If we do replace it.
            existingComponent = newComponent;
            return newComponent;
        }
    }

    // The component is the first of its type so add it.
    components.push_back(newComponent);

    return newComponent;
}

#include "Object.cpp"
