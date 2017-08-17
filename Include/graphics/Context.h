#pragma once

struct GLFWwindow;

class Context
{
private:
	GLFWwindow* handle;

public:
	bool getKey(int Key);

	bool getMouseButton(int button);

	void getMousePosition(double &x_out, double &y_out);

	float* GetJoystick(int joy, int count) const;

	int getJoystickXAxes();
	int getJoystickXAxis();
	int getJoystickYAxis();
	double getTime();

	bool init(size_t width = 800, size_t height = 600, const char* title = "Graphics");

	bool step();

	bool Terminate();


};
