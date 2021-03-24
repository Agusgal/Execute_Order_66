#ifndef GUI_H
#define GUI_H  1

#include <stdio.h>
#include <iostream>
#include <string>

#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "World.h"

//#define DEBUG_GUI 

class Gui {
public:
    Gui();

   

    //Ventanas Gui
    int initialWindow(void);
    int mainWindow(void);
    void helpMarker(const char* desc);
    void popup(const char* msg);

    int showInitialWindow(void); //Debe recibir sym creo
    int showMainWindow(World &sim);

    int loadBitmaps(void);

    //Configuracion Gui
    int init(void);
    int configureEvents(void);
    int configureImGui(void);

    int checkData(void);
    int parseData(void);

    int drawBlobs(World &sim);
    int drawFood(World &sim);
    int drawBackground(World& sim);

    bool getClose(void);

    int getMode(void);
    int getBlobNum(void);
    int getFoodCount(void);
    float getMaxSpeed(void);
    float getRelativeSpeed(void);
    float getDead(int type);
    float getSmellRadius(void);
    float getJiggle(void);


    void setInitialData(World &sim);
    void setData(World& sim);

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
    
    std::string errorType;
    bool noError;
    bool popupOpen;
    
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

