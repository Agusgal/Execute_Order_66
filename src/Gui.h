#ifndef GUI_H
#define GUI_H  1

#include <stdio.h>
#include <iostream>
#include <string>

#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "World.h"

#include <cmath>

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
    int showMainWindow(void);

    int loadBitmaps(void);

    //Configuracion Gui
    int init(void);
    int configureEvents(void);
    int configureImGui(void);

    int checkData(void);

    int drawBlobs(void);
    int drawFood(void);
    int drawBackground(void);

    bool getClose(void);

    int getMode(void);
    int getBlobNum(void);
    int getFoodCount(void);
    float getMaxSpeed(void);
    float getRelativeSpeed(void);
    float getDead(int type);
    float getSmellRadius(void);
    float getJiggle(void);

    //void setData(World& sim);

    bool initWorld(void);
    void destroyWorld(void);
    void updateData(void);

private:

    //Simulacion
    int mode;
    int initialBlobCount;
    float relativeSpeed;
    float maxSpeed;
    float smellRadius[NBLOBS];
    float jiggleLimit;
    float deathProbability[NBLOBS];
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

    double displaySizeX;
    double displaySizeY;

    bool runningInitial;
    bool runningMain;
    bool closeWindow;

    double simTpS;
    double fps; 

    int backgroundSize;

    World* sim;
};

#endif /* ! GUI_H */

