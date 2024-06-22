#pragma once
#include "Application.h"

class Command {
protected:
	Application* app;

public:
	Command() { app = &Application::getInstance(); }
	virtual ~Command() = default;
	virtual int execute() = 0; //dali da smeni sesiqta -1 -> ne,  0-> non 1->clientSe 2->emp
};