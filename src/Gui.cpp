#include "Gui.h"


Gui::Gui() {
    showMainGuiWindow = true;
    showRunningGuiWindow = false;

    running = true;

    displaySizeX = 1280;
    displaySizeY = 720;

    guiWindowSizeX = 500;

}


int Gui::Graph(void) {

    Init();

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(displaySizeX, displaySizeY);
    if (!display){
        
        fprintf(stderr, "Failed to create display !\n");
        return -1;
    }

    al_set_window_title(display, "Blob Simulation");


    if (ConfigureEvents() == -1) {
        return -1;
    }

    if (ConfigureImGui() == -1) {
        return -1; 
    }


    //MainLoop
    while (running) {

        while (al_get_next_event(queue, &ev)) {

            ImGui_ImplAllegro5_ProcessEvent(&ev);	// Mandar el evento a Dear ImGui para que lo procese

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false;
                //cerrar
            }
            if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
            {
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
            }
        }

        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);


        if (MainWindow()) {
            running = false; 
        }
        
        ImGui::Render();	//No dibuja! Solamente calcula que es lo que tiene que dibujarse

                // Puedo usar funciones de dibujo de Allegro ademas de las de 
                // ImGui.
                // Todo lo que dibuje antes de ImGui_ImplAllegro5_RenderDrawData
                // va a quedar detras de las ventanas de DearImGui, y todo lo 
                // que dibuje despues va a quedar encima de las ventanas de 
                // DearImGui.

        al_clear_to_color(al_map_rgba_f(1, 1, 0.8, 1));	//Va a quedar detras de las ventanas.

        //Todo lo que dibuje aca va a quedar por detrás de las ventanas de DearImGui

        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());	//Dibuja las ventanas, pero no hace al_flip_display()

        //Todo lo que dibuje aca va a quedar por encima de las ventanas de DearImGui

        al_flip_display(); //DearImGui nunca hace al_flip_display()

    }

    // Cleanup final
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_shutdown_primitives_addon();

    return 0;
}


int Gui::MainWindow(void) {

    static bool NoTitlebar = true;
    static bool NoMenu = true;
    static bool NoCollapse = true;
    static bool NoResize = true;
    static bool NoMove = true;
    static bool NoClose = true;
    static bool NoBackground = true;
    static bool NoScrollbar = true;

    ImGuiWindowFlags window_flags = 0;
    if (NoTitlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (NoScrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!NoMenu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (NoMove)            window_flags |= ImGuiWindowFlags_NoMove;
    if (NoResize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (NoCollapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (NoBackground)      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::SetNextWindowSize(ImVec2(guiWindowSizeX, displaySizeY), ImGuiCond_Always); //Aca pongo tamaño de la pantalla

    // Main body of the Demo window starts here.
    ImGui::Begin("Configure Simulation", NULL, window_flags);
   

    const char* items[] = { "Mode 1", "Mode 2" };
    static int item_current = 0;
    ImGui::Combo("Mode", &item_current, items, IM_ARRAYSIZE(items)); //chequear modo simulacion 

    static int blobN = 0;
    ImGui::InputInt("Blob number", &blobN); //chequear al final que no sean 2 millones
    ImGui::SameLine(); HelpMarker("Enter values between 0 and 50");

    static float relSpeed = 0.123f;
    //ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::SliderFloat("Relative speed", &relSpeed, 0.0f, 1.0f, "speed ratio = %.3f");

    static int maxSpeed = 0;
    ImGui::SliderInt("Max blob speed", &maxSpeed, 1, 30);
    ImGui::SameLine(); HelpMarker("contrl + click to enter value, must not exceed 50 pixels per tick");

    static int smellRadius = 0;
    ImGui::InputInt("Smell Radius", &smellRadius);//chequear que este bien ingresado
    ImGui::SameLine(); HelpMarker("Enter values between 0 and 50");

    static float jiggle = 0.0f;
    ImGui::SliderAngle("Jiggle Limit", &jiggle);

    static float pDeath1 = 0.0f;
    ImGui::SliderFloat("BabyBlob", &pDeath1, 0.01f, 0.99f, "P.death = %.3f");

    static float pDeath2 = 0.0f;
    ImGui::SliderFloat("GrownBlob", &pDeath2, 0.01f, 0.99f, "P.death = %.3f");

    static float pDeath3 = 0.0f;
    ImGui::SliderFloat("GoodOldBlob", &pDeath3, 0.01f, 0.99f, "P.death = %.3f");

    static int foodCount = 0;
    ImGui::InputInt("Food count", &foodCount); //Chequear que sea un numero valido
    ImGui::SameLine(); HelpMarker("Enter values between 0 and 50");

    ImGui::End();
    return 0;
}

int Gui::Init(void) {

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
 

void Gui::HelpMarker(const char* desc){

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

int Gui::ConfigureEvents(void) {
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
    //faltan eventos de timers

    return 0;
}

int Gui::ConfigureImGui(void) {

    IMGUI_CHECKVERSION();			
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplAllegro5_Init(display);
    ImGui::StyleColorsLight();
    
    return 0; 
}