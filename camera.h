#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	friend class Ray;
	Camera(){}
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		//this->forward = glm::vec3(0.342f, 0.47f, 0.814f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		//this->up = glm::vec3(0.0f, 0.866f, -0.5f);
	/*	this->forward = glm::vec3(-1.0f, 1.0f, 2.0f);
		this->up = glm::vec3(1.0f, 1.0f, -3.0f);*/
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), up);//look at in getview also!!!
	}

	inline glm::mat4 GetProjection() const
	{
		return this->projection;
	}

	inline glm::mat4 GetView() const
	{
		glm::mat4 view = glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), up);
		return view;//look at in getviewprojection also!!!
	}

	//void MoveForward(float amt)
	//{
	//	pos += forward * amt;
	//}

	//void MoveRight(float amt)
	//{
	//	pos += glm::cross(up, forward) * amt;
	//}

	//void Pitch(float angle)
	//{
	//	glm::vec3 right = glm::normalize(glm::cross(up, forward));

	//	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	//	up = glm::normalize(glm::cross(forward, right));
	//}

	//void RotateY(float angle)
	//{
	//	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	//	glm::mat4 rotation = glm::rotate(angle, UP);

	//	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	//	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	//}

	void set_pos(glm::vec3 pos) {
		this->pos = pos;
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif