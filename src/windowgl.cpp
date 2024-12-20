#include "window.hpp"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

nemo::windowgl::windowgl(std::string title, SDL_Point size) { create(title, size); }
nemo::windowgl::windowgl(std::string title, SDL_Point size, SDL_WindowFlags flags) { create(title, size, flags); }
nemo::windowgl::~windowgl() { destroy(); }

void nemo::windowgl::initgl() {
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    #define glsl_version "#version 100"
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    #define glsl_version "#version 300 es"
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    #define glsl_version "#version 150"
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    #define glsl_version "#version 130"
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
}
void nemo::windowgl::create(std::string title, SDL_Point size) {
    // cleanup
    destroy();
    initgl();

    // create
    Window = SDL_CreateWindow(title.c_str(), size.x, size.y, SDL_WINDOW_OPENGL);
    if (Window == nullptr) {
        throw windowError::initwindow;
    }
    glcontext = SDL_GL_CreateContext(Window);
    if (glcontext == nullptr) {
        throw windowError::initrenderer;
    }
    SDL_GL_MakeCurrent(Window, glcontext);
}
void nemo::windowgl::create(std::string title, SDL_Point size, SDL_WindowFlags flags) {
    // cleanup
    destroy();
    initgl();

    // create
    Window = SDL_CreateWindow(title.c_str(), size.x, size.y, SDL_WINDOW_OPENGL | flags);
    if (Window == nullptr) {
        throw windowError::initwindow;
    }
    glcontext = SDL_GL_CreateContext(Window);
    if (glcontext == nullptr) {
        throw windowError::initrenderer;
    }
    SDL_GL_MakeCurrent(Window, glcontext);
}
void nemo::windowgl::destroy() {
    if (glcontext != nullptr) {
        SDL_GL_DestroyContext(glcontext);
    }
    if (Window != nullptr) {
        SDL_DestroyWindow(Window);
    }
}
void nemo::windowgl::color(SDL_Color newColor) {
    glColor4b(newColor.r, newColor.g, newColor.b, newColor.a);
}
void nemo::windowgl::clear() {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void nemo::windowgl::clearNoColor() {
    glClear(GL_COLOR_BUFFER_BIT);
}
void nemo::windowgl::present() {
    if (!SDL_GL_SwapWindow(Window)) {
        throw windowError::present;
    }
}
void nemo::windowgl::presentFps(uint32_t fps) {
    if (!SDL_GL_SwapWindow(Window)) {
        throw windowError::present;
    }
    SDL_Delay(1000 / fps);
}
void nemo::windowgl::presentDefault() {
    if (!SDL_GL_SwapWindow(Window)) {
        throw windowError::present;
    }
    SDL_Delay(1000 / 60);
}
void nemo::windowgl::startImgui() {
    if (!ImGui_ImplSDL3_InitForOpenGL(Window, glcontext)) {
        throw windowError::initimguiimpl;
    }
    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        throw windowError::initimguirender;
    }
}
void nemo::windowgl::renderImgui() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void nemo::windowgl::renderViewports() {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(Window, glcontext);
}
