#pragma once
#include "AftrConfig.h"
#ifdef  AFTR_CONFIG_USE_IMGUI
#include "Vector.h"
#include "Mat4.h"
#include <functional>
#include <chrono>

namespace Aftr
{
	class WO;
	class GLSLShaderDisplacement;  // Forward declaration

	class AftrImGui_displacement_grid
	{
	public:
		//main draw method called from GLView
		void draw();
		//Given an origin, this returns a radial orbit in the XY plan specified by the
		//origin orientation and position. Each revolution takes the specified time.
		Mat4 compute_pose(Mat4 const& origin_pose);
		GLSLShaderDisplacement* displacementShader = nullptr;

	private:
		//draws the gui widgets that let the user manipulate orbit parameters
		void draw_orbit_controls();
		void draw_wave_controls();  // NEW function

		// Moon orbit variables
		float radius_m = 100.0f;   //adjusted by gui slider
		bool isPaused = false;     //adjusted by gui button in draw_orbit_controls
		int orbitTime_msec = 5000; //adjusted by gui slider in draw_orbit_controls

		// Wave control variables - NEW
		float speedPower = 0.0f;
		float frequencyPower = 0.0f;
		float heightPower = 1.0f;
		

		// Timing variables
		std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now(); //used by draw_orbit_controls
		std::chrono::system_clock::time_point pause_time; //used by draw_orbit_controls
		std::chrono::system_clock::time_point now_time;   //used by compute_pose()
	};
}
#endif //  AFTR_CONFIG_USE_IMGUI