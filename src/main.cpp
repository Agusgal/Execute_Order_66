// Dear ImGui: standalone example application for Allegro 5
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include "Gui.h"
#include "World.h"

int main(int, char**)
{
    //World sim; se crea la simulacion a la que luego le aprseamos los datos 
    
    
    Gui myGui; //creo la gui que recibe la data del usuario 

    if (!myGui.initialGraph()) {
        
        //Inicio la simulacion con parametros iniciales sacados por la gui
        //parse, init sim, etc

        while (!myGui.getClose()) {
        
            if (myGui.mainGraph()) { //con un return distinto a 0 hubo error 
                
                std::cout << "Fallo el metodo que grafica che, mala suerte" << std::endl;
                return 0;
            }

        }
        return 0;
    }
    
    return 0;
}