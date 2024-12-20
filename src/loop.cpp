#include "loop.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

bool nemo::loop::update() {
    return SDL_PollEvent(&event);
}
bool nemo::loop::shouldQuit() {
    return event.type == SDL_EVENT_QUIT;
}
bool nemo::loop::shouldQuitKey(SDL_Keycode key) {
    return event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == key);
}
bool nemo::loop::shouldQuitMulti() {
    return event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || event.type == SDL_EVENT_QUIT;
}
bool nemo::loop::shouldQuitMultiKey(SDL_Keycode key) {
    return event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == key);
}

// BUG: fix autoloop not drawing and unable to use args
/*
#include <cstddef>
bool nemo::autoLoop::update() {
    return SDL_PollEvent(&event);
}
bool nemo::autoLoop::shouldQuit() {
    return event.type == SDL_EVENT_QUIT;
}
bool nemo::autoLoop::shouldQuitKey(SDL_Keycode key) {
    return event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == key);
}
bool nemo::autoLoop::shouldQuitMulti() {
    return event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || event.type == SDL_EVENT_QUIT;
}
bool nemo::autoLoop::shouldQuitMultiKey(SDL_Keycode key) {
    return event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED || event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == key);
}

void nemo::autoLoop::runDefault(nemo::window *window) {
    bool shouldRun = true;
    while (shouldRun) {
        while (update()) {
            if (shouldQuit()) {
                shouldRun = false;
            }
        }
        window->clear();
        window->presentDefault();
    }
}
void nemo::autoLoop::runMultiDefault(std::vector<nemo::window> window) {
    bool shouldRun[window.size()];
    size_t counter = window.size();
    for (size_t i = 0; i < counter; i++) {
        shouldRun[i] = true;
    }
    while (counter > 0) {
        while (update()) {
            for (size_t i = 0; i < window.size(); i++) {
                if (event.window.windowID == SDL_GetWindowID(window[i].Window)) {
                    if (shouldRun[i] && shouldQuitMulti()) {
                        shouldRun[i] = false;
                        counter--;
                    }
                    break;
                }
            }
        }
        for(auto &entry : window) {
            entry.clear();
            entry.present();
        }
        SDL_Delay(1000 / 60);
    }
}
template <typename T> void nemo::autoLoop::run(nemo::updateIterator iterator, callbackType callback, T args) {
    while (iterator.shouldRun) {
        iterator.window->clear();
        while (update()) {
            callback(&iterator, this, args);
        }
        iterator.window->presentDefault();
    }
}
void nemo::autoLoop::runNoArgs(nemo::updateIterator iterator, callbackNoArgsType callback) {
    while (iterator.shouldRun) {
        iterator.window->clear();
        while (update()) {
            callback(&iterator, this);
        }
        iterator.window->presentDefault();
    }
}
template <typename T> void nemo::autoLoop::runMulti(std::vector<nemo::updateIterator> iterator, std::vector<callbackType> callback, T args) {
    size_t counter = iterator.size();
    while (counter > 0) {
        for(auto &entry : iterator) {
            entry.window->clear();
        }
        while (update()) {
            for (size_t i = 0; i < iterator.size(); i++) {
                if (iterator[i].shouldRun) {
                    callback[i](&iterator[i], this, args);
                    if (!iterator[i].shouldRun) { counter--; }
                }
            }
        }
        for(auto &entry : iterator) {
            entry.window->present();
        }
        SDL_Delay(1000 / 60);
    }
}
void nemo::autoLoop::runMultiNoArgs(std::vector<nemo::updateIterator> iterator, std::vector<callbackNoArgsType> callback) {
    size_t counter = iterator.size();
    while (counter > 0) {
        for(auto &entry : iterator) {
            entry.window->clear();
        }
        while (update()) {
            for (size_t i = 0; i < iterator.size(); i++) {
                if (iterator[i].shouldRun) {
                    callback[i](&iterator[i], this);
                    if (!iterator[i].shouldRun) { counter--; }
                }
            }
        }
        for(auto &entry : iterator) {
            entry.window->present();
        }
        SDL_Delay(1000 / 60);
    }
} */
