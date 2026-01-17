#pragma once

#include "../Module.h"
#include "../ModuleCategory.h"
#include "../../config/ActionRowValue.h"
#include "../../il2cpp/unity.h"
#include "../../util/logger.h"

class TestModule : Module
{
public:
    TestModule() : Module("Test", Misc)
    {
    }

    ActionRowValue* test = conf(new ActionRowValue([&]
    {
        run_test();
    }, "Test"));

    void draw_overlay(ImDrawList* draw_list) override
    {
    }

    void init() override
    {
    }

    static void run_test()
    {
        Il2CppImage* unity = il2utils::resolve_image("UnityEngine.CoreModule.dll");
        Il2CppObject* camera_type = il2utils::get_system_type(unity, "UnityEngine", "Camera");

        size_t count = 0;
        Il2CppObject** cameras = unity::find_objects_of_type(camera_type, &count);

        logger::info("Found Cameras: " + std::to_string(count));
        for (size_t i = 0; i < count; ++i)
        {
            logger::info(unity::get_name(cameras[i]));
        }
    }
};
