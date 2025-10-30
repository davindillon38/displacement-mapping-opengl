#include "AftrImGui_displacement_grid.h"
#include "AftrImGuiIncludes.h"
#include "GLSLShaderDisplacement.h"  // ADD THIS LINE
#include "GLSLUniform.h" 
#include <fmt/core.h>
#include <chrono>
#include <cmath>  // ADD THIS LINE for std::pow

void Aftr::AftrImGui_displacement_grid::draw()
{
    this->draw_orbit_controls();
    this->draw_wave_controls();  // ADD THIS LINE
}

void Aftr::AftrImGui_displacement_grid::draw_orbit_controls()
{
    if (ImGui::Begin("Moon Spy"))
    {
        if (ImGui::Button((this->isPaused ? "Resume Motion" : "Pause Motion")))
        {
            this->isPaused = !this->isPaused;
            if (this->isPaused)
                this->pause_time = std::chrono::system_clock::now();
            else
                this->start_time = (std::chrono::system_clock::now() - pause_time) + start_time;
            fmt::print("Moon Orbiter Status: {:b}...\n", this->isPaused);
        }
        if (ImGui::SliderFloat("Radius (m)", &this->radius_m, 1.0f, 100.0f))
            fmt::print("Adjusted Moon Orbiter radius to {:f} meters... Good job...\n", this->radius_m);
        if (ImGui::SliderInt("Orbit time (msec)", &this->orbitTime_msec, 50, 10000))
            fmt::print("Adjusted Moon Orbiter time to {:d} milliseconds... Better job...\n", this->orbitTime_msec);
        ImGui::End();
    }
}

void Aftr::AftrImGui_displacement_grid::draw_wave_controls()
{
    if (ImGui::Begin("Wave Controls"))
    {
        // Speed slider
        if (ImGui::SliderFloat("Speed Power", &this->speedPower, -3.0f, 2.0f, "2^%.1f"))
        {
            float speed = std::pow(2.0f, this->speedPower);
            if (this->displacementShader != nullptr && this->displacementShader->speedMultiplier != nullptr)
                this->displacementShader->speedMultiplier->setValues(&speed);
            fmt::print("Speed multiplier set to {:f} (2^{:f})\n", speed, this->speedPower);
        }

        // Frequency slider
        if (ImGui::SliderFloat("Frequency Power", &this->frequencyPower, -2.0f, 3.0f, "2^%.1f"))
        {
            float freq = std::pow(2.0f, this->frequencyPower);
            if (this->displacementShader != nullptr && this->displacementShader->frequencyMultiplier != nullptr)
                this->displacementShader->frequencyMultiplier->setValues(&freq);
            fmt::print("Frequency multiplier set to {:f} (2^{:f})\n", freq, this->frequencyPower);
        }

        // ADD THIS - Height slider
        if (ImGui::SliderFloat("Height Power", &this->heightPower, -3.0f, 6.0f, "2^%.1f"))
        {
            float height = std::pow(2.0f, this->heightPower);
            if (this->displacementShader != nullptr && this->displacementShader->displacementScale != nullptr)
                this->displacementShader->displacementScale->setValues(&height);
            fmt::print("Height multiplier set to {:f} (2^{:f})\n", height, this->heightPower);
        }

        ImGui::End();
    }
}

Aftr::Mat4 Aftr::AftrImGui_displacement_grid::compute_pose(Mat4 const& origin)
{
    if (!this->isPaused)
        this->now_time = std::chrono::system_clock::now();
    //one revolution completes in exactly REV_TIME, compute parametric offset based on the current time
    std::chrono::duration REV_TIME = std::chrono::milliseconds(this->orbitTime_msec);
    auto delta_t = std::chrono::duration<float>(now_time - start_time);
    float t = float(delta_t / REV_TIME); //parametric distance [0,1], between start time and now
    //fmt::print( "Num revolutions is {:f}\n", t);
    //Compute the pose of the orbiting object -- the position and the orientation
    Vector pos = origin.getPosition();
    Vector fwdVec = origin.getX();
    Vector upVec = origin.getZ();
    Vector orbit_pos = pos + (fwdVec * radius_m).rotate(upVec, t * Aftr::PI * 2.0f);
    Vector relX = (pos - orbit_pos).normalizeMe();
    Vector relY = upVec.crossProduct(relX);
    Vector relZ = relX.crossProduct(relY);
    Mat4 pose(relX, relY, relZ);
    pose.setPosition(orbit_pos);
    return pose;
}