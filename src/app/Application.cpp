#include <algorithm>
#include "app/engine/Scene.h"
#include "Application.h"
#include "lcd_st7735/graphics/gfx.h"
#include "app/engine/LineSegmentBoundary.h"
#include "app/engine/CircleBoundary.h"
#include "app/math/Math.h"

Scene * Application::scene;
Camera * Application::camera;
uint32_t Application::last_tick;
uint32_t Application::last_render_tick;

void handle_physics(Scene * scene, float dt) {
    for (size_t i = 0; i < scene->drawableCount; ++i) {
        auto I = scene->drawables[i];

        if (auto * it = dynamic_cast<DynamicObject*>(I)) {
            it->s = it->s + it->v * dt;
            it->v = it->v + it->a * dt;
            it->updateBoundaryFunction(it->boundaries, it->s);

            it->a = it->forceFunction(it->s.x, it->s.y, it->v.x, it->v.y, it->m) * (1 / it->m);

            auto scene_collision = Boundary::intersects(it->boundaries, scene->boundaries);
            if (scene_collision.intersected) {
                float v_n = it->v * scene_collision.normal;
                float v_p = it->v * scene_collision.normal.getPerpendicular(); // Dot product

                it->s = it->s + scene_collision.normal * 1;
                v_n = -v_n * scene_collision.other->e;

                it->v = scene_collision.normal * v_n + scene_collision.normal.getPerpendicular() * v_p; // Scalar product
            }

            for (size_t j = i + 1; j < scene->drawableCount; ++j) {
                auto J = scene->drawables[j];
                if (auto * other = dynamic_cast<DynamicObject*>(J)) {
                    auto object_collision = Boundary::intersects(it->boundaries, other->boundaries);
                    if (object_collision.intersected) {
                        it->s = it->s + object_collision.normal * 1;
                        other->s = other->s + object_collision.normal * -1;

                        float v1_n = it->v * object_collision.normal;
                        float v2_n = other->v * object_collision.normal;
                        float v1_p = it->v * object_collision.normal.getPerpendicular();
                        float v2_p = other->v * object_collision.normal.getPerpendicular();

                        // Momentum Conservation
                        float m1 = it->m;
                        float m2 = other->m;
                        float v1, v2;
                        float e = (object_collision.it->e + object_collision.other->e) / 2; // TODO: collision policy

                        // Momentum conservation around the normal
                        v1 = v1_n;
                        v2 = v2_n;
                        v1_n = ((m1 - e * m2) * v1 + (1 + e) * m2 * v2) / (m1 + m2);
                        v2_n = ((m2 - e * m1) * v2 + (1 + e) * m1 * v1) / (m1 + m2);

                        // Momentum conservation around the perpendicular
                        v1 = v1_p;
                        v2 = v2_p;
                        v1_p = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
                        v2_p = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);

                        it->v = object_collision.normal * v1_n + object_collision.normal.getPerpendicular() * v1_p;
                        other->v = object_collision.normal * v2_n + object_collision.normal.getPerpendicular() * v2_p;
                    }
                }
                else if (auto * other_s = dynamic_cast<StaticObject*>(J)) {
                    auto object_collision = Boundary::intersects(it->boundaries, other_s->boundaries);
                    if (object_collision.intersected) {
                        it->s = it->s + object_collision.normal * 1;
                        float v_n = it->v * object_collision.normal;
                        float v_p = it->v * object_collision.normal.getPerpendicular();
                        v_n = -v_n * object_collision.other->e;
                        it->v = object_collision.normal * v_n + object_collision.normal.getPerpendicular() * v_p;
                    }
                }
            }
        }
        else if (auto * it_s = dynamic_cast<StaticObject*>(I)) {
            for (size_t j = i + 1; j < scene->drawableCount; ++j) {
                auto J = scene->drawables[j];
                if (auto * other = dynamic_cast<DynamicObject*>(J)) {
                    auto object_collision = Boundary::intersects(other->boundaries, it_s->boundaries);
                    if (object_collision.intersected) {
                        other->s = other->s + object_collision.normal * 1;

                        float v_n = other->v * object_collision.normal;
                        float v_p = other->v * object_collision.normal.getPerpendicular();

                        v_n = -v_n * object_collision.other->e;
                        other->v = object_collision.normal * v_n + object_collision.normal.getPerpendicular() * v_p;
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
            handle_physics(scene, (Tick - Application::last_tick) * 1);
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
                OS_TASK_LOCK();
                if (auto * object = dynamic_cast<DynamicObject *>(d)) {
                    object->blackOut();


                    object->prev_x = object->s.x;
                    object->prev_y = object->s.y;
                }


                d->draw();
                OS_TASK_UNLOCK();
//                os_schedule();
            });

            last_render_tick = Tick;
        }

        os_schedule();
    }
}

void Application::game() {
    OS_TASK_LOCK();
    fillScreen(BLACK);

    ST7735_WriteString(0, 18 + 1, "PhyziX", Font_11x18, RED,BLACK);
    // TODO: move logic to other class or something


    // Beginning scene
    scene = new Scene(160, 256);
    scene->boundaries.list = new Boundary * [4];
    scene->boundaries.count = 4;
    scene->boundaries.list[0] = new LineSegmentBoundary(0.0,0.0,0.0,160.0);
    scene->boundaries.list[1] = new LineSegmentBoundary(0.0,0.0,128,0.0);
    scene->boundaries.list[2] = new LineSegmentBoundary(128,0.0,128,160.0);
    scene->boundaries.list[3] = new LineSegmentBoundary(0.0,160,128,160.0);
    camera = new Camera(160, 128);

    auto * s1 = new StaticObject([] {
        ST7735_FillRectangle(0, 0, 25,25,GREEN);
    });

    s1->boundaries.count = 1;
    s1->boundaries.list = new Boundary * [1];
    s1->boundaries.list[0] = new CircleBoundary(12.5, 12.5, 12.5);

    scene->addDrawable(s1);

    auto * box1 = new DynamicObject(
            [] (float x, float y) {
                ST7735_FillRectangle(x, y, 25,25,BLUE);
            },
            [] (float x, float y) {
                // TODO fill only coordinates, for scene to re render background for example
                ST7735_FillRectangle(x, y, 25,25,BLACK);
            },
            [] (Boundaries& boundaries, Vector& s) {
                ((CircleBoundary *) boundaries.list[0])->r = 12.5f;
                ((CircleBoundary *) boundaries.list[0])->x = s.x + 12.5f;
                ((CircleBoundary *) boundaries.list[0])->y = s.y + 12.5f;
            },
            100,120);

    box1->boundaries.count = 1;
    box1->boundaries.list = new Boundary * [1];
    box1->boundaries.list[0] = new CircleBoundary();
    box1->forceFunction = [](float x, float y, float v_x, float v_y, float m) -> Vector {
        return Vector(0, -9.81 * m * 8 * 1 / 100 * 1 / 100);
    };

    auto * box2 = new DynamicObject(
            [] (float x, float y) {
                ST7735_FillRectangle(x, y, 25,25,RED);
            },
            [] (float x, float y) {
                // TODO fill only coordinates, for scene to re render background for example
                ST7735_FillRectangle(x, y, 25,25,BLACK);
            },
            [] (Boundaries& boundaries, Vector& s) {
                ((CircleBoundary *) boundaries.list[0])->r = 12.5f;
                ((CircleBoundary *) boundaries.list[0])->x = s.x + 12.5f;
                ((CircleBoundary *) boundaries.list[0])->y = s.y + 12.5f;
            },
            20,120);

    box2->v.x = 100.0 / 100;
    box2->v.y = 100.0 / 100;

    box2->boundaries.count = 1;
    box2->boundaries.list = new Boundary * [1];
    box2->boundaries.list[0] = new CircleBoundary();
    box2->forceFunction = [](float x, float y, float v_x, float v_y, float m) -> Vector {
        return Vector(0, -9.81 * m * 8 * 1 / 100 * 1 / 100 /*- 0.005 * m *v_y*/);
    };

//    auto * box3 = new DynamicObject(
//            [] (float x, float y) {
//                ST7735_FillRectangle(x, y, 10,10,WHITE);
//            },
//            [] (float x, float y) {
                 //TODO fill only coordinates, for scene to re render background for example
//                ST7735_FillRectangle(x, y, 10,10,BLACK);
//            },
//            [] (Boundaries& boundaries, Vector& s) {
//                ((CircleBoundary *) boundaries.list[0])->r = 5;
//                ((CircleBoundary *) boundaries.list[0])->x = s.x + 5;
//                ((CircleBoundary *) boundaries.list[0])->y = s.y + 5;
//            },
//            80,80);

//    box3->boundaries.count = 1;
//    box3->boundaries.list = new Boundary * [1];
//    box3->boundaries.list[0] = new CircleBoundary();
//    box3->forceFunction = [](float x, float y, float v_x, float v_y, float m) -> Vector {
//        return Vector(0, -9.81 * m * 8 * 1 / 100 * 1 / 100 /*- 0.005 * m *v_y*/);
//    };
    //scene->addDrawable(box3);

    scene->addDrawable(box1);
    scene->addDrawable(box2);

    auto * s2 = new StaticObject([] {
        ST7735_FillRectangle(128 - 50, 0, 50,50,MAGENTA);
    });

    s2->boundaries.count = 1;
    s2->boundaries.list = new Boundary * [1];
    s2->boundaries.list[0] = new LineSegmentBoundary(128 - 50, 50, 128, 50);

    scene->addDrawable(s2);

    OS_TASK_UNLOCK();

    while (true) {
    }

    // Monitor current level
    // Switch between scenes
}
