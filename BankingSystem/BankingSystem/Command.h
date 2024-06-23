#pragma once
#include "Application.h"

class Command {
protected:
	Application* app;

public:
	Command() { app = &Application::getInstance(); }
	virtual ~Command() = default;
	virtual int execute() = 0;
	//
};