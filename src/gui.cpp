#include "window.hpp"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

void nemo::stopImgui() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
}
bool nemo::updateImgui(SDL_Event &event) {
    return ImGui_ImplSDL3_ProcessEvent(&event);
}
void nemo::frameImgui() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
}
