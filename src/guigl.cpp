#include "window.hpp"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

void nemo::stopImguiGL() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
}
void nemo::frameImguiGL() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
}
