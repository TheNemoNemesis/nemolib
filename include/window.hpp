#pragma once
#include "display.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <cstdint>
#include <string>

namespace nemo {
    enum class windowError { initwindow, initrenderer, changecolor, clear, present, initimguiimpl, initimguirender };
    class window {
    public:

        window() = default;
        window(window &&) = default;
        window(const window &) = default;
        window &operator=(window &&) = default;
        window &operator=(const window &) = default;

        SDL_Window *Window = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Color backgroundColor = nemo::color::nemowhite;

        window(std::string title, SDL_Point size);
        window(std::string title, SDL_Point size, SDL_WindowFlags flags);
        ~window();

        void create(std::string title, SDL_Point size);
        void create(std::string title, SDL_Point size, SDL_WindowFlags flags);
        void destroy();
        void clear();
        void clearNoColor();
        void present();
        void presentFps(uint32_t fps);
        void presentDefault();
        void color(SDL_Color newColor);
        void startImgui();
        void renderImgui();
    };
    class windowgl {
        void initgl();
    public:
        windowgl() = default;
        windowgl(windowgl &&) = default;
        windowgl(const windowgl &) = default;
        windowgl &operator=(windowgl &&) = default;
        windowgl &operator=(const windowgl &) = default;

        SDL_Window *Window = nullptr;
        SDL_GLContext glcontext = nullptr;
        SDL_Color backgroundColor = nemo::color::nemowhite;

        windowgl(std::string title, SDL_Point size);
        windowgl(std::string title, SDL_Point size, SDL_WindowFlags flags);
        ~windowgl();

        void create(std::string title, SDL_Point size);
        void create(std::string title, SDL_Point size, SDL_WindowFlags flags);
        void destroy();
        void clear();
        void clearNoColor();
        void present();
        void presentFps(uint32_t fps);
        void presentDefault();
        void color(SDL_Color newColor);
        void startImgui();
        void renderImgui();
        void renderViewports();
    };
    void stopImgui();
    void stopImguiGL();
    bool updateImgui(SDL_Event &event);
    void frameImgui();
    void frameImguiGL();
}
