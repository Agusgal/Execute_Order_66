// Dear ImGui: standalone example application for Allegro 5
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../lib/ImGui/imgui.h"
#include "../lib/ImGui/imgui_impl_allegro5.h"

#include "Gui.h"

int main(int, char**)
{
    Gui myGui; 

    if (!myGui.Graph()) {
        return 0;
    }
    
    return 0;
}