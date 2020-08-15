#ifndef APPLICATION_H
#define APPLICATION_H

#include "Timer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool GetMouseUpdate();

	static bool exitProgram;

	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;

	static int GetWindowHeight();
	static int GetWindowWidth();

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	const static int m_window_width = 800;
	const static int m_window_height = 600;
	//Declare a window object
	StopWatch m_timer;
};

#endif

