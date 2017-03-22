#include "display.h"
#include <GL/glew.h>
#include <iostream>

Display::Display(int width, int height, const std::string& title)
{
	this->width = width;
	this->height = height;
	//const SDL_VideoInfo* info = NULL;
	/* Dimensions of our window. */
	//int width = 0;
	//int height = 0;
	/* Color depth in bits of our window. */
	//int bpp = 0;
	/* Flags we will pass into SDL_SetVideoMode. */
	//int flags = 0;
	
	/* First, initialize SDL's video subsystem. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		/* Failed, exit. */
		fprintf(stderr, "Video initialization failed: %s\n",
			SDL_GetError());
		//quit_tutorial(1);
	}

	//info = SDL_GetVideoInfo();


	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

	glViewport(0, 0, width, height);

	

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
//	m_ScreenSurface = SDL_GetWindowSurface(m_window);
	m_glContext = SDL_GL_CreateContext(m_window);

	//SDL_GL_SetSwapInterval(1);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glEnable(GL_FRONT);
}

Display::~Display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Display::SwapBuffers()
{
	
	SDL_GL_SwapWindow(m_window);
}

void Display::ChangeTitle(const std::string& title) {
	SDL_SetWindowTitle(m_window, title.c_str());
}