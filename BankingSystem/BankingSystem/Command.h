#pragma once
#include "Application.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void execute(Application* app) = 0;
};