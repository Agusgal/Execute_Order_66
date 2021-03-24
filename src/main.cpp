#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include "Gui.h"
#include "World.h"

int main(int, char**)
{
    World sim(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); //se crea la simulacion a la que luego le aprseamos los datos 
    
    Gui myGui; //creo la gui que recibe la data del usuario 

    if (!myGui.showInitialWindow()) {
        
        //Inicio la simulacion con parametros iniciales sacados por la gui
        //parse, init sim, etc
        

        while (!myGui.getClose()) {
        
            if (myGui.showMainWindow(sim)) { //con un return distinto a 0 hubo error 
                
                std::cout << "Fallo el metodo que grafica che, mala suerte" << std::endl;
                return 0;
            }

        }
        return 0;
    }
    
    return 0;
}