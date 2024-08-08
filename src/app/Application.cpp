#include <algorithm>
#include "app/engine/Scene.h"
#include "Application.h"
#include "lcd_st7735/graphics/gfx.h"
#include "app/engine/LineSegmentBoundary.h"

Scene * Application::scene;
Camera * Application::camera;
uint32_t Application::last_tick;
uint32_t Application::last_render;

void updateDynamicObject(Drawable * d) {
    if (auto * it = dynamic_cast<DynamicObject*>(d)) {
        float dt = (Tick - Application::last_tick) * 1; // in 10 millisecond ticks

        it->prev_x = it->x;
        it->prev_y = it->y;
        it->x += it->v_x * dt;
        it->x += it->v_x * dt;
        it->y += it->v_y * dt;
        it->v_x += it->a_x * dt;
        it->v_y += it->a_y * dt;
        it->a_x = it->axFunction(it->x, it->y, it->a_x, it->a_y);
        it->a_y = it->ayFunction(it->x, it->y, it->a_x, it->a_y);

        if (it->y - 25 < 0) {
            it->y = 25;
            it->v_y = -it->v_y * 0.7;
        }
    }
}

void Application::update() {
    last_tick = Tick;

    while (true) {
        if (scene) {
            scene->forEachDrawable(updateDynamicObject);
        }

        last_tick = Tick;

        os_schedule();
    }
}

void Application::render() {
    last_render = Tick;

    while (true) {
        if (scene && camera && (Tick - last_render > 10)) {
            // TODO: handle camera movement

            fillScreen(BLACK);

            scene->forEachDrawable([] (Drawable * d) {
                d->draw();
            });

            last_render = Tick;
        }

        os_schedule();
    }
}

void Application::game() {
    OS_TASK_LOCK();
    fillScreen(BLACK);

    ST7735_WriteString(0, 18 + 1, "HEllo", Font_11x18, RED,BLACK);
    // TODO: move logic to other class or something


    // Beginning scene
    scene = new Scene(160, 256);
    scene->boundaries = new Boundary * [4];
    scene->boundaryCount = 4;
    scene->boundaries[0] = (Boundary *) (new LineSegmentBoundary(0.0,0.0,0.0,160.0));
    LineSegmentBoundary xx1(0.0,0.0,0.0,160.0);
    Boundary * zabood = &xx1;
    camera = new Camera(160, 128);
    ST7735_WriteString(0, 18 + 1, "HEllo2222", Font_11x18, RED,BLACK);

    scene->addDrawable(new StaticObject([] {
        ST7735_FillRectangle(0, 0, 25,25,GREEN);
    }));

    DynamicObject * box = new DynamicObject([] (uint16_t x, uint16_t y) {
                                                ST7735_FillRectangle(x, y, 25,25,GREEN);
                                            },[] (uint16_t x, uint16_t y) {
                                                ST7735_FillRectangle(x, y, 25,25,BLACK);
                                            },
                                            5,120);
    box->setAccelerationFunctions([](float x, float y, float v_x, float v_y) -> float {
        return 0;
    },[](float x, float y, float v_x, float v_y) -> float {
        return  (-9.81 * 8 * 1 / 100 * 1 / 100);
    });
    box->v_x = 1.0 * 8 / 100;
    scene->addDrawable(box);

    OS_TASK_UNLOCK();

    while (true);
}
