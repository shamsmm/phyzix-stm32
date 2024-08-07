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
    static uint32_t last_tick;

    Application() {
        scene = nullptr;
        camera = nullptr;
        last_tick = Tick;
    };

public:
    static Application& getInstance() {
        static Application instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Application(Application const&) = delete;
    void operator = (Application const&) = delete;

    [[noreturn]] static void update();

    [[noreturn]] static void render();

    [[noreturn]] static void game();
};

#endif //C0_APPLICATION_H
