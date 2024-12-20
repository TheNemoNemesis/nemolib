#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>

// BUG: fix autoloop not drawing and unable to use args
/*
#include "window.hpp"
#include <functional>
#include <vector>
#define callbackType std::function<void(nemo::updateIterator*,nemo::autoLoop*,T)>
#define callbackNoArgsType std::function<void(nemo::updateIterator*,nemo::autoLoop*)>
*/

namespace nemo {
    class loop {
    public:
        loop() = default;
        loop(loop &&) = default;
        loop(const loop &) = default;
        loop &operator=(loop &&) = default;
        loop &operator=(const loop &) = default;
        ~loop() = default;

        SDL_Event event;
        bool shouldRun = true;

        bool update();
        bool shouldQuit();
        bool shouldQuitKey(SDL_Keycode key);
        bool shouldQuitMulti();
        bool shouldQuitMultiKey(SDL_Keycode key);
    };

    // BUG: fix autoloop not drawing and unable to use args
    /* 
    struct updateIterator {
        nemo::window *window;
        bool shouldRun = true;
    };
    class autoLoop {
    public:
        autoLoop() = default;
        autoLoop(autoLoop &&) = default;
        autoLoop(const autoLoop &) = default;
        autoLoop &operator=(autoLoop &&) = default;
        autoLoop &operator=(const autoLoop &) = default;
        ~autoLoop() = default;

        SDL_Event event;

        bool update();
        bool shouldQuit();
        bool shouldQuitKey(SDL_Keycode key);
        bool shouldQuitMulti();
        bool shouldQuitMultiKey(SDL_Keycode key);

        void runDefault(nemo::window *window);
        void runMultiDefault(std::vector<nemo::window> window);
        template <typename T> void run(nemo::updateIterator iterator, callbackType callback, T args);
        void runNoArgs(nemo::updateIterator iterator, callbackNoArgsType callback);
        template <typename T> void runMulti(std::vector<nemo::updateIterator> iterator, std::vector<callbackType> callback, T args);
        void runMultiNoArgs(std::vector<nemo::updateIterator> iterator, std::vector<callbackNoArgsType> callback);
    }; */
}
