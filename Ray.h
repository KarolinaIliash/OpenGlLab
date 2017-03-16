#pragma once
#include"camera.h"
#include"transform.h"

class Ray {
private:
	Camera camera;
	Transform transform;
	//glm::vec3 ray;
public:
	Ray(Camera camera) {
		this->camera = camera;
	}
	glm::vec3 RayUnProj(float mouseX, float mouseY, int width, int height) {
		//GLfloat params[4];
		//glGetFloatv(GL_VIEWPORT, params);
		glm::vec4 viewport(0, 0 , width, height);
		//viewport[0] = params[0];
		//viewport[1] = params[1];
		//viewport[2] = params[2];
		//viewport[3] = params[3];
		return glm::normalize(glm::unProject(glm::vec3(mouseX, mouseY, 1.0f), transform.GetModelView(camera), camera.GetProjection(), viewport) - glm::unProject(glm::vec3(mouseX, mouseY, 0.0f), transform.GetModelView(camera), camera.GetProjection(), viewport));
	}
	glm::vec3 GetRay(float mouseX, float mouseY, int width, int height);// {
		//glm::unProject(glm::vec3(mouseX, mouseY, 0.0f), transform.g)
	//}
	bool TriangleIntersection(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 rayOrigin, glm::vec3 rayDirection, float* out);
};

