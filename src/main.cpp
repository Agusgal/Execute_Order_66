#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include "Gui.h"
#include "World.h"
#include "randomGenerators.h"

int main(int, char**)
{
    initRandom(); //Crea seed para generar numeros al azar 
    Gui myGui; //creo la gui que recibe la data del usuario 

    if (!myGui.showInitialWindow()) {
        
        //Inicio la simulacion con parametros iniciales sacados por la gui
        if (!myGui.initWorld()) {
            return 1;
        }

        while (!myGui.getClose()) {
        
            if (!myGui.showMainWindow()) { //con un return distinto a 0 hubo error 
                return -1;
            }

        }
        return 0;
    }
    
    return 0;
}

