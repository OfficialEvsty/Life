#ifndef SETTINGS_H
#define SETTINGS_H

struct Size{
    //size of interacting field
    unsigned long long int LengthX;
    unsigned long long int LengthY;
};


class Settings{
    Size m_size;

    //enviromental tick in ms
    unsigned int ui_tick;

    //width of cell
    unsigned int i_cell_width = 8;

    //singleton ctor of game settings
    Settings(unsigned int tick);

public:
    //singleton instance of class
    static Settings *Instance;

    static void Init(unsigned int tick){
        if (!Settings::Instance){
            Settings::Instance = new Settings(tick);
        }
    }
    Size GetSizeOfField();
    unsigned int GetCellWidth();
    unsigned int GetTimeOfFrame();
};

#endif // SETTINGS_H
