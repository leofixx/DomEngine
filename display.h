#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear(float r, float g, float b, float a);
	void UpdateBuffers();
	bool IsClosed();

	virtual ~Display();

protected:

private:
	Display(const Display& other) {}
	void operator=(const Display& other) {}

	SDL_Window* m_Window;
	SDL_GLContext m_glContext;
	bool m_IsClosed;
};

#endif // DISPLAY_H