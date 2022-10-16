#include "glfw3.h"

#include "Time.h"
#include "Log.h"

int Time::fpsCollected[100];
int Time::displayFps;

float Time::deltaTime = 0.016f;
float Time::frameStart;
int Time::tickCount;

Time::TimePoint Time::profileStart;

void Time::Profile()
{
    profileStart = std::chrono::high_resolution_clock::now();
}

float Time::EndProfile(const std::string& taskName)
{
    auto profileStop = Time::Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(profileStop - profileStart);
    float time_ms = duration.count() / 1000.0f;

    Log::Profile(taskName, time_ms);
    return time_ms;
}

void Time::FrameStart()
{
    frameStart = glfwGetTime();
}

void Time::FrameEnd()
{
    deltaTime = glfwGetTime() - frameStart;
    tickCount++;

    UpdateFps();
}

float Time::DeltaTime()
{
    return deltaTime;
}

void Time::UpdateFps()
{
    int sum = 0;

    for (int i = 99; i >= 1; i--)
    {
        fpsCollected[i] = fpsCollected[i - 1];
        sum += fpsCollected[i];
    }

    fpsCollected[0] = int(1.0f / deltaTime);
    sum += fpsCollected[0];

    if (Time::tickCount % 30 == 0)
    {
        displayFps = sum / 100;
    }
}
