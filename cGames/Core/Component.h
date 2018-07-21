class Object;

class Component {
        public:
            Object *object;
            Component(){}
            virtual void Start(){}
            virtual void Update(){}
            void SetObject(Object& p){this->object = &p;}
};
