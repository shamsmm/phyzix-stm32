#include "app/engine/Scene.h"
#include "Application.h"
#include "lcd_st7735/graphics/gfx.h"

Scene * Application::scene;
Camera * Application::camera;
uint32_t Application::last_tick;

void Application::update() {
    while (true) {
        if (scene) {
            scene->forEachDrawable([] (Drawable * d) {
                if (auto * it = dynamic_cast<DynamicObject*>(d)) {
                    float dt = Tick - last_tick; // in 10 millisecond ticks

                    it->x += it->v_x * dt;
                    it->y += it->v_y * dt;
                    it->v_x += it->a_x * dt;
                    it->v_y += it->a_y * dt;
                    it->a_x = 0; // Or if movement going add value here
                    it->a_y = -9.81 * 0.1 * 1 / 100; // 9.81 [m/s], 1 meter = 1 pixels, 1 second = 100 10ms
                }
            });
        }

        last_tick = Tick;

        os_schedule();
    }
}

void Application::render() {
    while (true) {
        if (scene && camera/* && last_tick % 4 == 0*/) {
            fillScreen(BLACK);
            scene->forEachDrawable([] (Drawable * d) {
                // TODO: handle camera movement
                d->draw();
            });
        }

        os_schedule();
    }
}

void Application::game() {
    OS_TASK_LOCK();

    ST7735_WriteString(0, 18 + 1, "HEllo", Font_11x18, RED,BLACK);
    // TODO: move logic to other class or something


    // Beginning scene
    scene = new Scene(160, 256);
    camera = new Camera(160, 128);
    ST7735_WriteString(0, 18 + 1, "HEllo2222", Font_11x18, RED,BLACK);

    scene->addDrawable(new StaticObject([] {
        ST7735_FillRectangle(0, 0, 25,25,GREEN);
    }));

    scene->addDrawable(
    new DynamicObject([] (uint16_t x, uint16_t y) {
                ST7735_FillRectangle(x, y, 25,25,GREEN);
            },
          70,
          120
    ));

    OS_TASK_UNLOCK();

    while (true);
}
