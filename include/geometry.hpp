#pragma once
#include <SDL3/SDL_render.h>

namespace nemo {
    struct point3D {
        int x = 0, y = 0, z = 0;
    };
    struct point3DF {
        float x = 0.0f, y = 0.0f, z = 0.0f;
    };
    struct line {
        float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;
    };
    struct line3D {
        float x1 = 0.0f, y1 = 0.0f, z1 = 0.0, x2 = 0.0f, y2 = 0.0f, z2 = 0.0;
    };
    namespace shapes {
        struct circle {
            int x = 0, y = 0, r = 0;
        };
        struct circleF {
            float x = 0.0f, y = 0.0f, r = 0.0f;
        };
        typedef SDL_Vertex triangle[3];
        struct cube {
            int x = 0, y = 0, z = 0, w = 0, h = 0, l = 0;
        };
        struct cubeF {
            float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f, h = 0.0f, l = 0.0f;
        };
        struct sphere {
            int x = 0, y = 0, z = 0, r = 0;
        };
        struct sphereF {
            float x = 0.0f, y = 0.0f, z = 0.0f, r = 0.0f;
        };
    }
}
