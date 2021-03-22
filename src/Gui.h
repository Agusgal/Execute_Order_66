#ifndef GUI_H
#define GUI_H  1

#include <stdio.h>

#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>



class Gui {
public:
    Gui();

    bool showMainGuiWindow;
    bool showRunningGuiWindow;


    int MainWindow(void);
    void RunningGui(void);
    static void HelpMarker(const char* desc);
    
    int Graph(void); //Debe recibir sym creo


    int Init(void);
    int ConfigureEvents(void);
    int ConfigureImGui(void);

private:

    //Simulacion
    int mode;
    int initialBlobCount;
    float relSpeed;
    int maxSpedd;
    int smellRadius;
    float jiggleLimit;
    float deathProbability[3];
    int foodCount;
    
    //ImGui

    int guiWindowSizeX;


    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT ev;

    int displaySizeX;
    int displaySizeY;

    bool running;

};

#endif /* ! GUI_H */

