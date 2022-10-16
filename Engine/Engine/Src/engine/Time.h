#pragma once

#include <iostream>
#include <chrono>

class Time
{
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

private:
    static float frameStart;
    static TimePoint profileStart;
    static int fpsCollected[100];

public:
    static float deltaTime;
    static int tickCount;
    static int displayFps;

    static void Profile();
    static float EndProfile(const std::string& taskName);

    static float DeltaTime();

    static void FrameStart();
    static void FrameEnd();

    static void UpdateFps();
};
