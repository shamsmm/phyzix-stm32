#include <algorithm>
#include "app/engine/Scene.h"
#include "Application.h"
#include "lcd_st7735/graphics/gfx.h"
#include "app/engine/LineSegmentBoundary.h"
#include "app/engine/CircleBoundary.h"

Scene * Application::scene;
Camera * Application::camera;
uint32_t Application::last_tick;
uint32_t Application::last_render_tick;

void handle_physics(Scene * scene) {
    for (size_t i = 0; i < scene->drawableCount; ++i) {
        auto I = scene->drawables[i];

        if (auto * it = dynamic_cast<DynamicObject*>(I)) {
            float dt = (Tick - Application::last_tick) * 1; // in 10 millisecond ticks

            it->prev_x = it->x; // For blackout
            it->prev_y = it->y;


            it->x += it->v_x * dt;
            it->y += it->v_y * dt;

            it->boundaryUpdateFunction(it->boundaries, it->boundaryCount, it->x, it->y);

            it->v_x += it->a_x * dt;
            it->v_y += it->a_y * dt;

            it->a_x = it->axFunction(it->x, it->y, it->a_x, it->a_y);
            it->a_y = it->ayFunction(it->x, it->y, it->a_x, it->a_y);



            if (Boundary::intersects(it->boundaries, it->boundaryCount, scene->boundaries, scene->boundaryCount)) {
                it->x = 50;
                it->y = 50;
                it->v_x = -it->v_x;
                it->v_y = -it->v_y;
            }

            for (size_t j = i; j < scene->drawableCount; ++j) {
                auto J = scene->drawables[j];
                if (auto * other = dynamic_cast<DynamicObject*>(J)) {
                    if (Boundary::intersects(it->boundaries, it->boundaryCount, other->boundaries, other->boundaryCount)) {
                        it->v_x = -it->v_x;
                        it->v_y = -it->v_y;

                        other->v_x = -other->v_x;
                        other->v_y = -other->v_y;
                    }
                }
            }
        }
    }
}

void Application::update() {
    last_tick = Tick;

    while (true) {
        if (scene) {
            handle_physics(scene);
        }

        last_tick = Tick;

        os_schedule();
    }
}

void Application::render() {
    last_render_tick = Tick;

    while (true) {
        if (scene && camera && (Tick - last_render_tick > 10)) {
            // TODO: handle camera movement over the scene; clipping objects

            //fillScreen(BLACK);

            scene->forEachDrawable([] (Drawable * d) {
                d->draw();
            });

            last_render_tick = Tick;
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
    scene->boundaries[0] = new LineSegmentBoundary(0.0,0.0,0.0,160.0);
    scene->boundaries[1] = new LineSegmentBoundary(0.0,0.0,128,0.0);
    scene->boundaries[2] = new LineSegmentBoundary(128,0.0,128,160.0);
    scene->boundaries[3] = new LineSegmentBoundary(0.0,160,128,160.0);
    camera = new Camera(160, 128);

    scene->addDrawable(new StaticObject([] {
        ST7735_FillRectangle(0, 0, 25,25,GREEN);
    }));

    DynamicObject * box = new DynamicObject([] (uint16_t x, uint16_t y) {


                                                ST7735_FillRectangle(x, y, 25,25,BLUE);


                                            },[] (uint16_t x, uint16_t y) {

                                                // TODO fill only coordinates, for scene to re render background for example
                                                ST7735_FillRectangle(x, y, 25,25,BLACK);


                                            },[] (Boundary ** boundaries, uint16_t _, uint16_t x, uint16_t y) {
                                                ((CircleBoundary *) boundaries[0])->x = x + 12.5;
                                                ((CircleBoundary *) boundaries[0])->y = y + 12.5;
                                            },
                                            50,120);
    box->boundaryCount = 1;
    box->boundaries = new Boundary * [1];
    box->boundaries[0] = new CircleBoundary(12.5, 12.5, 5);

    box->setAccelerationFunctions([](float x, float y, float v_x, float v_y) -> float {
        return -v_x * 0.1;
    },[](float x, float y, float v_x, float v_y) -> float {
        return  (-9.81 * 8 * 1 / 100 * 1 / 100); // -9.81m/s^2 * 8pixels/meter *1/1ms
    });

    box->v_x = 1.0 * 8 / 100;

    scene->addDrawable(box);

    OS_TASK_UNLOCK();

    while (true) {
    }

    // Monitor current level
    // Switch between scenes
}
