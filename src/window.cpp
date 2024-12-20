#include "window.hpp"
#include <SDL3/SDL_timer.h>
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

nemo::window::window(std::string title, SDL_Point size) { create(title, size); }
nemo::window::window(std::string title, SDL_Point size, SDL_WindowFlags flags) { create(title, size, flags); }
nemo::window::~window() { destroy(); }
void nemo::window::create(std::string title, SDL_Point size) {
    // cleanup
    destroy();
    
    // create
    if (!SDL_CreateWindowAndRenderer(title.c_str(), size.x, size.y, 0, &Window, &renderer)) {
        if (Window == nullptr) {
            throw windowError::initwindow;
        }
        else if (renderer == nullptr) {
            throw windowError::initrenderer;
        }
    }
}
void nemo::window::create(std::string title, SDL_Point size, SDL_WindowFlags flags) {
    // cleanup
    destroy();
    
    // create
    if (!SDL_CreateWindowAndRenderer(title.c_str(), size.x, size.y, flags, &Window, &renderer)) {
        if (Window == nullptr) {
            throw windowError::initwindow;
        }
        else if (renderer == nullptr) {
            throw windowError::initrenderer;
        }
    }
}
void nemo::window::destroy() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (Window != nullptr) {
        SDL_DestroyWindow(Window);
    }
}

void nemo::window::color(SDL_Color newColor) {
    if (!SDL_SetRenderDrawColor(renderer, newColor.r, newColor.g, newColor.b, newColor.a)) {
        throw windowError::changecolor;
    }
}
void nemo::window::clear() {
    if (!SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a)) {
        throw windowError::changecolor;
    }
    if (!SDL_RenderClear(renderer)) {
        throw windowError::clear;
    }
}
void nemo::window::clearNoColor() {
    if (!SDL_RenderClear(renderer)) {
        throw windowError::clear;
    }
}
void nemo::window::present() {
    if (!SDL_RenderPresent(renderer)) {
        throw windowError::present;
    }
}
void nemo::window::presentFps(uint32_t fps) {
    if (!SDL_RenderPresent(renderer)) {
        throw windowError::present;
    }
    SDL_Delay(1000 / fps);
}
void nemo::window::presentDefault() {
    if (!SDL_RenderPresent(renderer)) {
        throw windowError::present;
    }
    SDL_Delay(1000 / 60);
}
void nemo::window::startImgui() {
    if (!ImGui_ImplSDL3_InitForSDLRenderer(Window, renderer)) {
        throw windowError::initimguiimpl;
    }
    if (!ImGui_ImplSDLRenderer3_Init(renderer)) {
        throw windowError::initimguirender;
    }
}
void nemo::window::renderImgui() {
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}
