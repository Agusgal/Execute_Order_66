#include "Gui.h"


Gui::Gui() {
    showMainGuiWindow = true;
    showRunningGuiWindow = false;

    runningInitial = true;

    noError = true;

    display = NULL;
    queue = NULL;
    simTimer = NULL;
    flipTimer = NULL;
    fps = 120;
    simTpS = 2;
    displaySizeX = 1280;
    displaySizeY = 720;

    guiWindowSizeX = 500;


    mode = -1;
    initialBlobCount = 0;
    relativeSpeed = 0;
    maxSpeed = 0;
    smellRadius = 0;
    jiggleLimit = 0;
    deathProbability[0] = 0;
    deathProbability[1] = 0;
    deathProbability[2] = 0;

    foodCount = 0;
    prueba = 0;

}


int Gui::showInitialWindow(void) {

    init();

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(displaySizeX, displaySizeY);
    if (!display){
        
        fprintf(stderr, "Failed to create display !\n");
        return -1;
    }

    al_set_window_title(display, "Blob Simulation");

    simTimer = al_create_timer(1 / simTpS);
    flipTimer = al_create_timer(1 / fps);


    if (configureEvents() == -1) {
        return -1;
    }

    if (configureImGui() == -1) {
        return -1; 
    }

    al_start_timer(simTimer);
    al_start_timer(flipTimer);

    //MainLoop
    while (runningInitial) {

        while (al_get_next_event(queue, &ev)) {

            ImGui_ImplAllegro5_ProcessEvent(&ev);	// Mandar el evento a Dear ImGui para que lo procese

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                runningInitial = false;
                //falta limpiar()
                return -1;
            }
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }

            if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == flipTimer){
                
                ImGui_ImplAllegro5_NewFrame();
                ImGui::NewFrame();
                ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);


                if (initialWindow()) {
                    runningInitial = false;
                }

                ImGui::Render();	

                al_clear_to_color(al_map_rgba_f(1, 1, 0.8, 1));	

                //Todo lo que dibuje aca va a quedar por detr�s de las ventanas de DearImGui

                ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	

                //Todo lo que dibuje aca va a quedar por encima de las ventanas de DearImGui

                al_flip_display(); 

            }
        }
    }

    // Cleanup final
    //ImGui_ImplAllegro5_Shutdown();
    //ImGui::DestroyContext();
    
    //al_destroy_event_queue(queue);
    //al_destroy_display(display);
    //al_shutdown_primitives_addon();
   
    return 0;
}

int Gui::showMainWindow(World& sim) {//end esarrollo

    while (runningMain) {

        while (al_get_next_event(queue, &ev)) {

            ImGui_ImplAllegro5_ProcessEvent(&ev);	

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                runningMain = false;
                //falta limpiar()
                return -1;
            }
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
            if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == simTimer) {
                prueba++;
                //aca simulo un tick 
                //simulate()
                //draw()
                drawBackground(sim);
            }
            if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == flipTimer) {
            
                ImGui_ImplAllegro5_NewFrame();
                ImGui::NewFrame();
                ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);


                if (mainWindow()) {
                    runningMain = false;
                }

                ImGui::Render();	

                al_clear_to_color(al_map_rgba_f(1, 1, 0.8, 1));	

                //Todo lo que dibuje aca va a quedar por detr�s de las ventanas de DearImGui

                ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	

                //Todo lo que dibuje aca va a quedar por encima de las ventanas de DearImGui

                al_flip_display(); 
            }
        }

        // Cleanup final
        ImGui_ImplAllegro5_Shutdown();
        ImGui::DestroyContext();

        al_destroy_event_queue(queue);
        al_destroy_display(display);
        al_shutdown_primitives_addon();

        return 0;
    }
}


int Gui::initialWindow(void) {

    int out = 0;//esto se retorna

    static bool NoTitlebar = true;
    static bool NoMenu = true;
    static bool NoCollapse = true;
    static bool NoResize = true;
    static bool NoMove = true;
    static bool NoClose = true;
    static bool NoBackground = true;
    static bool NoScrollbar = true;
    static bool no_bring_to_front = false;

    ImGuiWindowFlags window_flags = 0;
    if (NoTitlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (NoScrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!NoMenu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (NoMove)            window_flags |= ImGuiWindowFlags_NoMove;
    if (NoResize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (NoCollapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (NoBackground)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;


    ImGui::SetNextWindowSize(ImVec2(guiWindowSizeX, displaySizeY), ImGuiCond_Always); //Aca pongo tama�o de la pantalla

    ImGui::Begin("Configure Simulation", NULL, window_flags);


    const char* items[] = { "Mode 1", "Mode 2" };
    ImGui::Combo("Mode", &mode, items, IM_ARRAYSIZE(items)); //chequear modo simulacion 

    ImGui::InputInt("Blob number", &initialBlobCount);
    ImGui::SameLine(); helpMarker("Enter values between 0 and 50");

    ImGui::SliderFloat("Relative speed", &relativeSpeed, 0.0f, 1.0f, "speed ratio = %.3f");

    ImGui::SliderInt("Max blob speed", &maxSpeed, 1, 30);
    ImGui::SameLine(); helpMarker("contrl + click to enter value, must not exceed 50 pixels per tick");

    ImGui::InputInt("Smell Radius", &smellRadius);
    ImGui::SameLine(); helpMarker("Enter values between 0 and 50");

    ImGui::SliderAngle("Jiggle Limit", &jiggleLimit, 0.0f, 360.0f);

    ImGui::SliderFloat("BabyBlob", &deathProbability[0], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::SliderFloat("GrownBlob", &deathProbability[1], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::SliderFloat("GoodOldBlob", &deathProbability[2], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::InputInt("Food count", &foodCount);
    ImGui::SameLine(); helpMarker("Enter values between 0 and 50");

    if (ImGui::Button("Start Simulation", ImVec2(guiWindowSizeX, 50))){
        
        if (checkData()) {
            noError = false;
        }  
    }
    else {
        noError = true;
        //Puedo seguir al programa principal
    }
    
    if (!noError) {
        ImGui::OpenPopup("error");
        popupOpen = true;
    }
    if (popupOpen) {
        popup(errorType.c_str());
    }
    
    
    
    
    

    //popup(errorType.c_str());
    //if(!noError){
     //   popup(errorType.c_str());
    //}

#ifdef DEBUG_GUI
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
#endif

    ImGui::End();
    return out;
}

int Gui::mainWindow(void) {

    int out = 0;//esto se retorna

    static bool NoTitlebar = true;
    static bool NoMenu = true;
    static bool NoCollapse = true;
    static bool NoResize = true;
    static bool NoMove = true;
    static bool NoClose = true;
    static bool NoBackground = true;
    static bool NoScrollbar = true;
    static bool no_bring_to_front = false;

    ImGuiWindowFlags window_flags = 0;
    if (NoTitlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (NoScrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!NoMenu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (NoMove)            window_flags |= ImGuiWindowFlags_NoMove;
    if (NoResize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (NoCollapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (NoBackground)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;


    ImGui::SetNextWindowSize(ImVec2(guiWindowSizeX, displaySizeY), ImGuiCond_Always); //Aca pongo tama�o de la pantalla

    ImGui::Begin("Configure Simulation", NULL, window_flags);

    ImGui::SliderFloat("Relative speed", &relativeSpeed, 0.0f, 1.0f, "speed ratio = %.3f");

    ImGui::SliderInt("Max blob speed", &maxSpeed, 1, 30);
    ImGui::SameLine(); helpMarker("contrl + click to enter value, must not exceed 50 pixels per tick");

    ImGui::InputInt("Smell Radius", &smellRadius);
    ImGui::SameLine(); helpMarker("Enter values between 0 and 50");

    ImGui::SliderAngle("Jiggle Limit", &jiggleLimit, 0.0f, 360.0f);

    ImGui::SliderFloat("BabyBlob", &deathProbability[0], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::SliderFloat("GrownBlob", &deathProbability[1], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::SliderFloat("GoodOldBlob", &deathProbability[2], 0.01f, 0.99f, "P.death = %.3f");

    ImGui::InputInt("Food count", &foodCount); 
    ImGui::SameLine(); helpMarker("Enter values between 0 and 50");



    if (!noError) {
        popup(errorType.c_str());
    }

#ifdef DEBUG_GUI
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
#endif

    ImGui::PopItemWidth();

    ImGui::End();
    return out;


    return 0;
}



int Gui::init(void) {

    if (!al_init()){
        fprintf(stderr, " failed to initialize allegro !\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives addon!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize keyboard!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "failed to initialize mouse!\n");
        return -1;
    }
   
    return 0;
}
 
int Gui::checkData() {
    
    //Control blobN
    if (initialBlobCount <= 0){
 
        errorType = "The number of blobs must be greater than 0.";
        return -1;
    }
    else if (initialBlobCount > 20) {
        errorType = "The number of blobs must not exceed 20.";
        return -1;
    }

    //Control relative speed

    if(relativeSpeed < 0){
        errorType = "The simulation cant go back in time.";
        return -1;
    }
    else if (relativeSpeed > 1) {
        errorType = "The simulation speed must be 1 or less.";
        return -1;
    }
    
    //Control max speed
    if(maxSpeed > 30){
        errorType = "The maximum blob speed is capped at 30 pixels per simulation tick";
        return -1;
    }
    else if (maxSpeed <= 0) {
        errorType = "The maximun blob speed must be greater than 0;";
        return -1;
    }

    //Control Smell Radius
    if (smellRadius > 50) {
        errorType = "SmellRadius cant be greater than 50 pixels.";
        return -1;
    }
    else if (smellRadius <= 0) {
        errorType = "SmellRadius must be positive.";
        return -1;
    }

    //Control jiggle
    if (jiggleLimit > 360) {
        errorType = "JiggleLimit must be less than 360 degrees.";
        return -1;
    }
    else if (jiggleLimit < 0) {
        errorType = "JiggleLimit must be at least 0.";
        return -1;
    }

    //Control P muerte
    for (int i = 0; i < 3; i++) {
        if (deathProbability[i] <= 0) {
        
            errorType = "Blobs cant have a death probability less or equal to cero.";
            return -1;
        }
        else if (deathProbability[i] >= 1) {
            errorType = "Blobs cant have a death probability greater or equal to 1.";
            return -1;
        }
    }

    //Control comida
    if (foodCount > 15) {
        errorType = "The maximum available food is 15.";
        return -1;
    }
    else if (foodCount <= 0) {
        errorType = "There must be at least 1 unit of food.";
        return -1;
    }
    return 0;
}

void Gui::helpMarker(const char* desc){

    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void Gui::popup(const char* msg){

    /*if (ImGui::BeginPopup("error"))
    {
        std::cout << "error popup" << std::endl;
        std::cout << msg << std::endl;

        ImGui::Text(msg);
        ImGui::EndPopup();
    }*/

    if(ImGui::BeginPopup("error")){
        ImGui::Text(msg);
        ImGui::EndPopup();
    }
}

int Gui::configureEvents(void) {
    queue = al_create_event_queue();

    // Controla que la cola de eventos se haya generado
    if (!queue)
    {
        fprintf(stderr, "Failed to create event queue !\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    al_register_event_source(queue, al_get_timer_event_source(simTimer));
    al_register_event_source(queue, al_get_timer_event_source(flipTimer));

    return 0;
}

int Gui::configureImGui(void) {

    IMGUI_CHECKVERSION();			
    ImGui::CreateContext();
    ImGui_ImplAllegro5_Init(display);
    ImGui::StyleColorsLight();
    
    return 0; 
}


int Gui::loadBitmaps(void) {

    background = al_load_bitmap("background.jpg");
    if (!background){
        fprintf(stderr, "Failed to load background bitmap!\n");
        return -1;
    }
    
    babyBlob = al_load_bitmap("Blobs/babyblob.png");
    if (!babyBlob) {
        fprintf(stderr, "Failed to create babyBlob bitmpap!\n");
        return -1;
    }
    
    goodOldBlob = al_load_bitmap("Blobs/goodoldblob.png");
    if (!goodOldBlob) {
        fprintf(stderr, "Failed to create goodOldBlob bitmpap!\n");
        return -1;
    }
    
    grownBlob = al_load_bitmap("Blobs/grownblob.png");
    if (!grownBlob) {
        fprintf(stderr, "Failed to create grownBlob bitmpap!\n");
        return -1;
    }
    
    food = al_load_bitmap("food.png");
    if (!food) {
        fprintf(stderr, "Failed to create food bitmap!\n");
        return -1;
    }
    return 0;
}

int Gui::drawBlobs(World& sim) {
    bool out = true;

    Blob* bobElBlob= sim.getNextBlob();
    while (bobElBlob != NULL) {
        
        double posX, posY, angle;
        bobElBlob->getCoordinates(posX, posY, angle);

        switch (bobElBlob->getAge()) {

            //optimizar codigo
        case BABYBLOB: al_draw_bitmap(babyBlob, posX, posY, 0);
            if (posX > (displaySizeX - al_get_bitmap_width(babyBlob)) && posY > (displaySizeY - al_get_bitmap_height(babyBlob))) {

                al_draw_bitmap_region(babyBlob, (displaySizeX - posX), (displaySizeY - posY), al_get_bitmap_width(babyBlob) - (displaySizeX - posX), al_get_bitmap_height(babyBlob) - (displaySizeY - posY), 0.0f, 250, 0);

            }
        
        
        case GROWNBLOB: al_draw_bitmap(grownBlob, posX, posY, 0);
            if (posX > (displaySizeX - al_get_bitmap_width(grownBlob)) && posY > (displaySizeY - al_get_bitmap_height(grownBlob))) {


                al_draw_bitmap_region(grownBlob, (displaySizeX - posX), (displaySizeY - posY), al_get_bitmap_width(grownBlob) - (displaySizeX - posX), al_get_bitmap_height(grownBlob) - (displaySizeY - posY), 0.0f, 250, 0);


            }
            else if (posX > (displaySizeX - al_get_bitmap_width(grownBlob))) {

                al_draw_bitmap_region(grownBlob, (displaySizeX - posX), 0.0f, al_get_bitmap_width(grownBlob) - (displaySizeX - posX), al_get_bitmap_height(grownBlob), 0.0f, posY, 0);

            }
            else if (posY > (displaySizeY - al_get_bitmap_height(grownBlob))) {

                al_draw_bitmap_region(grownBlob, 0.0f, (displaySizeY - posY), al_get_bitmap_width(grownBlob), al_get_bitmap_height(grownBlob) - (displaySizeY - posY), posX, 250, 0);

            }
            break;

        case GOODOLDBLOB: al_draw_bitmap(goodOldBlob, posX, posY, 0);
            if (posX > (displaySizeX - al_get_bitmap_width(goodOldBlob)) && posY > (displaySizeY - al_get_bitmap_height(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, (displaySizeX - posX), (displaySizeY - posY), al_get_bitmap_width(goodOldBlob) - (displaySizeX - posX), al_get_bitmap_height(goodOldBlob) - (displaySizeY - posY), 0.0f, 250, 0);

            }
            else if (posX > (displaySizeX - al_get_bitmap_width(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, (displaySizeX - posX), 0.0f, al_get_bitmap_width(goodOldBlob) - (displaySizeX - posX), al_get_bitmap_height(goodOldBlob), 0.0f, posY, 0);

            }
            else if (posY > (displaySizeY - al_get_bitmap_height(goodOldBlob))) {

                al_draw_bitmap_region(goodOldBlob, 0.0f, (displaySizeY - posY), al_get_bitmap_width(goodOldBlob), al_get_bitmap_height(goodOldBlob) - (displaySizeY - posY), posX, 250, 0);

            }
            break;
        }

        bobElBlob = sim.getNextBlob(bobElBlob);
    }
    return 0;
}

int Gui::drawFood(World& sim) {

    //falta
    return 1;
}

int Gui::drawBackground(World& sim) {

    al_draw_scaled_bitmap(background, 0.0f, 0.0f, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 250, displaySizeX, displaySizeY, 0);
    return 0;
}


//getters
bool Gui::getClose(void) {
    return closeWindow;
}

int Gui::getMode(void) {
    return mode + 1;
}

int Gui::getBlobNum(void) {
    return initialBlobCount;
}

int Gui::getFoodCount(void) {
    return foodCount;
}

float Gui::getMaxSpeed(void) {
    return maxSpeed;
}

float Gui::getRelativeSpeed(void) {
    return relativeSpeed;
}

float Gui::getDead(int age){
    enum lifespan{BABY, GROWN, GOODOLD};
    float prob;
    
    switch (age){
    case BABY:
        prob = deathProbability[BABY];
        break;
    case GROWN:
        prob = deathProbability[GROWN];
        break;
    case GOODOLD:
        prob = deathProbability[GOODOLD];
        break;
    }
    return prob;
}

float Gui::getSmellRadius(void) {
    return smellRadius;
}

float Gui::getJiggle(void) {
    return jiggleLimit;
}


