
class Scene {
	std::wstring name;
	std::wstring map;
	int width;
	int height;
	Vector2 spawn;
	int index;
	CHAR_INFO* attributes;
	//RenderEngine* Renderer;
	Vector2* WorldTransform;
	public:
		std::vector<Object*> objects;
		explicit Scene(std::wstring _n = L" ", std::wstring _m = L"?", 
		int _i = 1, int w = 1, int h = 1, Vector2 s = Vector2(0,0), std::vector<Object*> _o = {new Object()}, 
		std::vector<Object*> _p = {new Object()}) 
		: name(_n), map(_m), index(_i), width(w), height(h), 
		spawn(s), objects(_o){attributes = new CHAR_INFO[w * h]; AssignAttribute();};

		~Scene()
		{
			delete[] attributes;
			// Free the memory from all the pointers
			for (int i = 0; i < objects.size(); i++)
			{
				Object *o = objects[i];
				delete o;
			}
		}

		void Init(){InitObjects();}
		virtual void Update(){UpdateObjects();}

		void InitObjects();
		void InitObjectAt(int i);
		void InitObjectAt(Object* o);

		void UpdateObjects();
		void RemoveObject(Object* o);
		
		inline void SetWorldTransform(Vector2& v) {WorldTransform = &v;}
		inline Vector2 GetWorldTransform(){return *WorldTransform;}
		inline std::vector<Object*> GetObjects()const{return objects;}
		inline Object* GetObjectAt(int i)const{return objects[i];}
		
		inline void SetObjectAt(int i, Object e){objects[i] = &e;}
		inline void SetObjects(std::vector<Object*> e){objects = e;}
	
		inline void AddObject(Object* o){objects.push_back(o); InitObjectAt(o);}
		inline std::vector<Object*>& GetObjects(){return objects;}
		std::wstring GetMap()const{return map;}
		inline int GetWidth()const{return width;}
		inline int GetHeight()const{return height;}
		inline int GetIndex()const{return index;}
		inline int GetSpawnX()const{return spawn.x;}
		inline int GetSpawnY()const{return spawn.y;}
		inline char GetCharAtIndex(int i)const{return map[i];}
		inline CHAR_INFO GetAttAt(int i)const{return attributes[i];}
		inline void SetAttAt(int i, CHAR_INFO c)const{attributes[i] = c;}
		inline void SetCharAtIndex(int i, char c){map[i] = c ;} 
		inline std::wstring GetName()const{return name;}

	private:
		void AssignAttribute();
		WORD SortAttrbute(char c);
};

#include "Scene.cpp"



