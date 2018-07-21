
class Camera : public Object{

    CameraComponent cameraComponent;

    public:
        Camera(CameraComponent c = CameraComponent()) 
        : cameraComponent(c), Object(Transform(Vector2(0,0)), L"MainCamera", {"Camera"}, {std::make_shared<CameraComponent>(c)}) {
        }
};