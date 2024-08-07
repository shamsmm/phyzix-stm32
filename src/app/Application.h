//
// Created by shams on 8/5/24.
//

#ifndef C0_APPLICATION_H
#define C0_APPLICATION_H

#include "app/engine/Scene.h"
#include "app/engine/Camera.h"
#include "os/os.h"
#include "app/engine/StaticObject.h"
#include "lcd_st7735/lcd.h"

class Application {
private:
    static Scene * scene;
    static Camera * camera;
    static uint32_t last_update;

    Application() {
        scene = nullptr;
        camera = nullptr;
        last_update = Tick;
    };

public:
    static Application& getInstance() {
        static Application instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Application(Application const&) = delete;
    void operator = (Application const&) = delete;

    [[noreturn]] static void update() {
        if (!scene)
            os_schedule();

        while (true);
    }

    [[noreturn]] static void render() {
        while (true) {
            if (scene && camera) {
                scene->drawAllDrawables();
            }

            os_schedule();
        }
    }

    [[noreturn]] static void game() {
        ST7735_WriteString(0, 18 + 1, "HEllo", Font_11x18, RED,BLACK);
        // TODO: move logic to other class or something

        if (!scene) {
            // Beginning scene
            scene = new Scene(160, 256);
            camera = new Camera(160, 128);
            ST7735_WriteString(0, 18 + 1, "HEllo2222", Font_11x18, RED,BLACK);
            scene->addDrawable(new StaticObject([] {
                ST7735_WriteString(0, 18 + 1, "ZZZZZZZZ", Font_11x18, BLUE,BLACK);
            }));
        }

        while (true);
    }
};

#endif //C0_APPLICATION_H
