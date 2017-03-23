#pragma once
#include"camera.h"
#include"transform.h"
#include"mesh.h"
#include"shader.h"
#include"Ray.h"

static const int DISPLAY_WIDTH = 900;
static const int DISPLAY_HEIGHT = 600;
static glm::vec3 cameraPosition(2.0f, 5.0f, 5.0f);
static Camera camera(cameraPosition, 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.01f, 100.0f);

class Object {
public:
	virtual void EditPosTransfrom(glm::vec3 pos) = 0;
	virtual void EditScaleTransform(glm::vec3 scale) = 0;
	virtual glm::mat4 GetModel() = 0;
	virtual void SetAngleRotation(float angle) = 0;
	virtual void SetAxisRotation(glm::vec3 axis) = 0;
	virtual glm::vec3 GetObjectAxis() = 0;
	virtual void DrawStandart() = 0;
	virtual void ChangeColor(int) = 0;
};

class Pyramid : public Object {
private:
	Vertex Vertex1;
	Vertex Vertex2;
	Vertex Vertex3;
	Vertex Vertex4;
	Vertex Top;
	Vertex Base;
	Transform transform;
	glm::vec3 height;
	glm::vec4 colorSquare;
	glm::vec4 colorTriangle1;
	glm::vec4 colorTriangle2;
	glm::vec4 colorTriangle3;
	glm::vec4 colorTriangle4;
public:
	Pyramid() {
		colorSquare = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
		colorTriangle1 = glm::vec4(0.5, 0.0f, 0.0f, 1.0f);
		colorTriangle2 = glm::vec4(0.5, 0.0f, 0.0f, 1.0f);
		colorTriangle3 = glm::vec4(0.5, 0.0f, 0.0f, 1.0f);
		colorTriangle4 = glm::vec4(0.5, 0.0f, 0.0f, 1.0f);
	}
	void EditPosTransfrom(glm::vec3 pos) override {
		transform.EditPos(pos);
	}
	void EditScaleTransform(glm::vec3 scale) override {
		transform.EditScale(scale);
	}

	glm::mat4 GetModel() override{
		return transform.GetModel();
	}

	void SetAngleRotation(float angle) override{
		transform.SetRotAngle(angle);
	}

	void SetAxisRotation(glm::vec3 axis) override{
		transform.SetRotAxis(axis);
	}
	glm::vec3 GetObjectAxis() override;
	void DrawStandart() override;
	void ChangeColor(int) override;
};

class Cone : public Object {
private:
	float radiusBottom;
	float radiusTop;
	glm::vec3 posBottomCenter;
	glm::vec3 posTopCenter;
	glm::vec4 colorTop;
	glm::vec4 colorBottom;
	glm::vec4 colorBody;
	Transform transform;
	glm::vec3 height;
	float delta;
public:
	void EditPosTransfrom(glm::vec3 pos) override {
		transform.EditPos(pos);
	}
	void EditScaleTransform(glm::vec3 scale) override {
		transform.EditScale(scale);
	}
	void SetAngleRotation(float angle) override{
		transform.SetRotAngle(angle);
	}

	void SetAxisRotation(glm::vec3 axis) override{
		transform.SetRotAxis(axis);
	}
	glm::vec3 GetObjectAxis() override;

	glm::mat4 GetModel() override{
		return transform.GetModel();
	}
	Cone(float delta) {
		this->delta = delta;
		colorTop = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
		colorBottom = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
		colorBody = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
	}

	void SetColorTop(glm::vec4 colorTop) {
		this->colorTop = colorTop;
	}

	void SetColorBottom(glm::vec4 colorBottom) {
		this->colorBottom = colorBottom;
	}

	void SetColorBody(glm::vec4 colorBody) {
		this->colorBody = colorBody;
	}

	glm::vec4 GetColorTop() {
		return colorTop;
	}

	glm::vec4 GetColorBottom() {
		return colorBottom;
	}

	glm::vec4 GetColorBody() {
		return colorBody;
	}

	void DrawStandart() override;

	void ChangeColor(int) override;
};