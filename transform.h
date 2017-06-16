#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"
#include <glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& axis = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), const float& angle = 0.0)
	{
		this->pos = pos;
		this->axis = axis;
		this->angle = angle;
		this->scale = scale;
		this->curQuaternion = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
		
		//this->isSaved = isSaved;
	}

	inline glm::mat4 GetModel()
	{
		//if (isSaved) return model;
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::quat quaternion = glm::angleAxis(angle, axis);
//		glm::rotate(curQuaternion, angle, axis);
		curQuaternion = quaternion * curQuaternion;
		glm::mat4 rotMat = glm::toMat4(curQuaternion);
		//quaternion[0][0] = 1;
		angle = 0.0f;
		return posMat * rotMat * scaleMat;
	}

	inline glm::mat4 GetMVP(Camera& camera) {
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();
		glm::mat4 MNP = VP * M;

		return VP * M;//camera.GetViewProjection() * GetModel();
	}

	inline glm::mat4 GetModelView(Camera& camera) {
		return camera.GetView() * GetModel();
	}

	inline glm::vec3 GetPos() { return pos; }
	inline float* GetRotAngle() { return &angle; }
	inline glm::vec3* GetRotAxis() { return &axis; }
	inline glm::vec3 GetScale() { return scale; }

	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
	inline void SetRotAxis(glm::vec3& axis) { this->axis = axis; }
	inline void SetRotAngle(float& angle) { this->angle = angle; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
	inline void SetQuaternion(glm::quat& quat) { this->curQuaternion = quat; }
	inline void SetQuaternion(glm::mat4& rotMat) { this->curQuaternion = glm::quat_cast(rotMat); }

	inline void EditPos(glm::vec3& pos) { this->pos.x += pos.x; this->pos.y += pos.y; this->pos.z += pos.z; }
	//inline void SetRotAxis(glm::vec3& axis) { this->axis = axis; }
	//inline void SetRotAngle(float& angle) { this->angle = angle; }

	inline void EditScale(glm::vec3& scale) { this->scale.x *= scale.x; this->scale.y *= scale.y; this->scale.z *= scale.z; }

	//inline void SetModel(glm::mat4 model) { this->model = model; }
	inline glm::mat4 GetRotMat() {
		return glm::toMat4(curQuaternion);
	}

	//inline void SetSaved(bool isSaved) { this->isSaved = isSaved; }
private:
	glm::vec3 pos;
	//glm::vec3 rot;
	float angle;
	glm::vec3 axis;
	glm::vec3 scale;
	glm::quat curQuaternion;


	//glm::mat4 model;
	//bool isSaved;
	//glm::mat4 curRotMat;
//	glm::mat4 curPosMat;
	//glm::mat4 curScaleMat;
};

#endif