//
// Created by shams on 8/7/24.
//

#ifndef PHYZIX_SCENE_H
#define PHYZIX_SCENE_H


#include <cstdint>
#include <cstdio>
#include <algorithm>
#include "Drawable.h"
#include "Boundary.h"

class Scene {
//private:
    uint16_t x_size;
    uint16_t y_size;
    Drawable ** drawables = nullptr;
    size_t drawableCount = 0;
    size_t drawableCapacity = 0;
public:
    uint16_t boundaryCount;
    Boundary ** boundaries;

    void resizeDrawables(size_t newCapacity) {
        auto ** newDrawables = new Drawable*[newCapacity];

        if (drawables) {
            std::copy(drawables, drawables + drawableCount, newDrawables);
            delete[] drawables;
        }

        drawables = newDrawables;
        drawableCapacity = newCapacity;
    }

public:
    Scene(uint16_t x_size, uint16_t y_size) {
        this->x_size = x_size;
        this->y_size = y_size;
    };

    void addDrawable(Drawable* drawable) {
        if (drawableCount == drawableCapacity) {
            resizeDrawables(drawableCapacity == 0 ? 1 : drawableCapacity * 2);
        }
        drawables[drawableCount++] = drawable;
    }

    void removeDrawable(Drawable* drawable) {
        for (size_t i = 0; i < drawableCount; ++i) {
            if (drawables[i] == drawable) {
                // Shift remaining elements to the left
                for (size_t j = i; j < drawableCount - 1; ++j) {
                    drawables[j] = drawables[j + 1];
                }
                --drawableCount;
                break;
            }
        }
    }

    void forEachDrawable(void (* func)(Drawable*)) {
        for (size_t i = 0; i < drawableCount; ++i) {
            func(drawables[i]);
        }
    }
};


#endif //PHYZIX_SCENE_H
