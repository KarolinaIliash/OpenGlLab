#pragma once
#include"camera.h"
#include"transform.h"
#include"mesh.h"
#include"shader.h"

static const int DISPLAY_WIDTH = 900;
static const int DISPLAY_HEIGHT = 600;
static Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);//position also is in function which return ray!

class Object {
public:
	virtual void Draw() = 0;
	virtual void EditPosTransfrom(glm::vec3 pos) = 0;
	virtual void EditScaleTransform(glm::vec3 scale) = 0;
};

class Pyramid : public Object {
private:
	Vertex Top;
	Vertex Base;
	Vertex Vertex1;
	Vertex Vertex2;
	Vertex Vertex3;
	Vertex Vertex4;
	glm::vec2 textureFirstTriangle;
	glm::vec2 textureSecondTriangle;
	glm::vec2 textureThirdTriangle;
	glm::vec2 textureFourthTriangle;
	glm::vec2 textureSquare;
	Transform transform;
public:
	Pyramid(Vertex Top, Vertex Base, Vertex Vertex1/*, glm::vec2 tex1Triangle, glm::vec2 tex2Triangle,
		glm::vec2 tex3Triangle, glm::vec2 tex4Triangle, glm::vec2 texSquare*/);
	//std::vector<Vertex> GetVertices() {
	//return vertices;
	//}
	//void SetVertices(std::vector<Vertex> vertices) {
	//this->vertices = vertices;
	//}
	void EditPosTransfrom(glm::vec3 pos) override {
		transform.EditPos(pos);
	}
	void EditScaleTransform(glm::vec3 scale) override {
		transform.EditScale(scale);
	}

	/*void SetTexture1Triangle(glm::vec2 texture) {
		this->textureFirstTriangle = texture;
	}

	void SetTexture2Triangle(glm::vec2 texture) {
		this->textureSecondTriangle = texture;
	}
	void SetTexture3Triangle(glm::vec2 texture) {
		this->textureThirdTriangle = texture;
	}
	void SetTexture4Triangle(glm::vec2 texture) {
		this->textureFourthTriangle = texture;
	}
	void SetTextureSquare(glm::vec2 texture) {
		this->textureSquare = texture;
	}*/

	void FindVerticesPyramid(glm::vec3 posTop, glm::vec3 posBase, glm::vec3 posVertexSquare1, glm::vec3& posVertexSquare2,
		glm::vec3& posVertexSquare3, glm::vec3& posVertexSquare4);


	void Draw() override;
};

class Cone : public Object {
private:
	float radiusBottom;
	float radiusTop;
	glm::vec3 posBottomCenter;
	glm::vec3 posTopCenter;

	Transform transform;
public:
	Cone(float radiusBottom, float radiusTop, glm::vec3 posBottomCenter, glm::vec3 posTopCenter);
	void EditPosTransfrom(glm::vec3 pos) override {
		transform.EditPos(pos);
	}
	void EditScaleTransform(glm::vec3 scale) override {
		transform.EditScale(scale);
	}
	void FindVerticesCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indicesBottomCircle, std::vector<unsigned int>& indicesTopCircle,
		std::vector<unsigned int>& indicesBody);
	void Draw() override;
};