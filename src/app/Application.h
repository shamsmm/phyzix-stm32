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
#include "app/lib/class_id.h"


class Application: public ClassIdentifiable {
private:
    static Scene * scene; /**< The current `Scene` displayed in the `Application` */
    static Camera * camera; /**< The current `Camera` used to show only some portion of the `Scene` */

    Application() {
        scene = nullptr;
        camera = nullptr;
        last_tick = Tick;
        last_render_tick = 0;
    };

public:
    static uint32_t last_tick;
    static uint32_t last_render_tick;

    ClassId getId() const override {
        return ClassId::APPLICATION;
    }

    static Application& getInstance() {
        static Application instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Application(Application const&) = delete;
    void operator = (Application const&) = delete;

    /**
     * @brief This function should run in a separate thread, be scheduled every small time increments to update dynamic objects
     * */
    [[noreturn]] static void update();

    /**
     * @brief This function should run in a separate thread, be scheduled whenever display should show a new frame or update the frame
     * */
    [[noreturn]] static void render();

    /**
     * @brief This function should run in a separate thread, be scheduled whenever scene changes, starts and so
     * */
    [[noreturn]] static void game();
};

#endif //C0_APPLICATION_H
