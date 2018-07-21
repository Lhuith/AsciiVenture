
//Behavoir Class
//Things That that do things, actions, speech and so on


class Entity : public Component {

    std::vector<std::wstring> prompts;
    int promptsindex = 0;
    bool Selected = false;
    bool Responded = false;
    
    public:
        explicit Entity(std::vector<std::wstring> _p = {L"Lets Talk Bizz Boy", L"Ok nvm", L"What now?"}) : prompts(_p){}
        std::wstring Interact(){return prompts[promptsindex++%prompts.size()];}
        void ResetPromptIndex(){promptsindex = 0;}
        void SetIfSelected(bool b){Selected = b;}
        bool IsSelected(){return Selected;}
        void SetIfResponded(bool b){this->Responded = b;}
        bool HasResponded(){return Responded;}
    private:
};
