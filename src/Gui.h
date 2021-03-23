#ifndef GUI_H
#define GUI_H  1

#include <stdio.h>
#include <iostream>

#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define DEBUG_GUI 1

class Gui {
public:
    Gui();

    bool showMainGuiWindow;
    bool showRunningGuiWindow;

    //Ventanas Gui
    int initialWindow(void);
    int mainWindow(void);
    static void helpMarker(const char* desc);
    
    int initialGraph(void); //Debe recibir sym creo
    int mainGraph(void);

    int loadBitmaps(void);

    //Configuracion Gui
    int init(void);
    int configureEvents(void);
    int configureImGui(void);

    int parseData(void);

    int drawBlobs(void);
    int drawFood(void);

    bool getClose(void);

private:

    //Simulacion
    int mode;
    int initialBlobCount;
    float relativeSpeed;
    int maxSpeed;
    int smellRadius;
    float jiggleLimit;
    float deathProbability[3];
    int foodCount;
    
    //ImGui

    int guiWindowSizeX;


    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMER* simTimer;
    ALLEGRO_TIMER* flipTimer;

    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* babyBlob;
    ALLEGRO_BITMAP* food;
    ALLEGRO_BITMAP* grownBlob;
    ALLEGRO_BITMAP* goodOldBlob;

    int displaySizeX;
    int displaySizeY;

    bool runningInitial;
    bool runningMain; 
    bool closeWindow;

    double simTpS;
    double fps; 

    int prueba;
};

#endif /* ! GUI_H */

