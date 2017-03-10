#include <iostream>
#include "Display.h"
#include"mesh.h"
#include"shader.h"
#undef main?



int main() {
	Display display(800, 600, "title");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5, 0.0)),
						Vertex(glm::vec3(0.0, 0.5, 0.0)),
						Vertex(glm::vec3(0.5, -0.5,0)), };
	//unsigned int indices[] = { 0 , 1, 2 };

	

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));//, indices, sizeof(indices)/sizeof(indices[0])) ;
	Shader shader("./res/basicShader");

	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();
		mesh.Draw();

		display.Update();
	}
	return 0;
}


