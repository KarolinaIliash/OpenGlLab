#include"object.h"

#define _USE_MATH_DEFINES
#include <math.h> 


void Pyramid::DrawStandart() {
	Vertex1 = Vertex(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	Vertex2 = Vertex(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	Vertex3 = Vertex(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	Vertex4 = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	Top = Vertex(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	Base = Vertex(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.4f, 0.0f, 0.0f, 1.0f));
	std::vector<Vertex> vertices = {
		Vertex1, Vertex2, Vertex3, Vertex4, Top
	};
	std::vector<unsigned int> indiceSquare{ 0, 3, 1, 3, 1, 2 };
	
	std::vector<unsigned int> indiceTriangle1{ 0, 3, 4 };

	std::vector<unsigned int> indiceTriangle2{ 3, 4, 2 };
	
	std::vector<unsigned int> indiceTriangle3{ 2, 4, 1 };
	
	std::vector<unsigned int> indiceTriangle4{ 1, 4, 0 };

	Shader shader("./res/basicShader");
	shader.Bind();
	shader.Update(transform, camera);
	
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorSquare.x;
		vertices[i].GetColor()->y = colorSquare.y;
		vertices[i].GetColor()->z = colorSquare.z;
		vertices[i].GetColor()->w = colorSquare.w;
	}
	Mesh meshSquare(vertices, 5, indiceSquare, 6);
	meshSquare.Draw(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorTriangle1.x;
		vertices[i].GetColor()->y = colorTriangle1.y;
		vertices[i].GetColor()->z = colorTriangle1.z;
		vertices[i].GetColor()->w = colorTriangle1.w;
	}
	Mesh meshTriangle1(vertices, 5, indiceTriangle1, 3);
	meshTriangle1.Draw(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorTriangle2.x;
		vertices[i].GetColor()->y = colorTriangle2.y;
		vertices[i].GetColor()->z = colorTriangle2.z;
		vertices[i].GetColor()->w = colorTriangle2.w;
	}
	Mesh meshTriangle2(vertices, 5, indiceTriangle2, 3);
	meshTriangle2.Draw(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorTriangle3.x;
		vertices[i].GetColor()->y = colorTriangle3.y;
		vertices[i].GetColor()->z = colorTriangle3.z;
		vertices[i].GetColor()->w = colorTriangle3.w;
	}
	Mesh meshTriangle3(vertices, 5, indiceTriangle3, 3);
	meshTriangle3.Draw(GL_TRIANGLES);

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorTriangle4.x;
		vertices[i].GetColor()->y = colorTriangle4.y;
		vertices[i].GetColor()->z = colorTriangle4.z;
		vertices[i].GetColor()->w = colorTriangle4.w;
	}
	Mesh meshTriangle4(vertices, 5, indiceTriangle4, 3);
	meshTriangle4.Draw(GL_TRIANGLES);

	for (unsigned int i = 0; i < 5; i++) {
		vertices[i].GetColor()->x = 1.0f;
		vertices[i].GetColor()->y = 1.0f;
		vertices[i].GetColor()->z = 1.0f;
		vertices[i].GetColor()->w = 1.0f;
	}
	std::vector<unsigned int> indiceEdge { 0, 4, 1, 2, 4, 3, 2, 1, 0, 3 };
	Mesh meshEdge(vertices, 5, indiceEdge, 10);
	meshEdge.Draw(GL_LINE_STRIP);
//	mesh.Draw(GL_TRIANGLE_STRIP);
	
}

glm::vec3 Pyramid::GetObjectAxis() {
	glm::vec4 axis = this->GetModel()*glm::vec4(*Top.GetPos(), 1.0f) - this->GetModel()*glm::vec4(*Base.GetPos(), 1.0f);
	return glm::vec3(axis.x, axis.y, axis.z);
}

void Pyramid::ChangeColor(int param) {
	glm::vec4 newColorSquare = colorSquare;
	glm::vec4 newColorTr1 = colorTriangle1;
	glm::vec4 newColorTr2 = colorTriangle2;
	glm::vec4 newColorTr3 = colorTriangle3;
	glm::vec4 newColorTr4 = colorTriangle4;

	if (newColorSquare.x == 0.5f) {
		newColorSquare.x = 1.0f;
	}
	else {
		newColorSquare.x = 0.5f;
	}

	if (newColorTr1.x == 0.5f) {
		newColorTr1.x = 1.0f;
	}
	else {
		newColorTr1.x = 0.5f;
	}

	if (newColorTr2.x == 0.5f) {
		newColorTr2.x = 1.0f;
	}
	else {
		newColorTr2.x = 0.5f;
	}

	if (newColorTr3.x == 0.5f) {
		newColorTr3.x = 1.0f;
	}
	else {
		newColorTr3.x = 0.5f;
	}


	if (newColorTr4.x == 0.5f) {
		newColorTr4.x = 1.0f;
	}
	else {
		newColorTr4.x = 0.5f;
	}

	switch (param) {
	case 0:
		colorSquare = newColorSquare;
		colorTriangle1 = newColorTr1;
		colorTriangle2 = newColorTr2;
		colorTriangle3 = newColorTr3;
		colorTriangle4 = newColorTr4;
		break;
	case 1:
		colorTriangle1 = newColorTr1;
		break;
	case 2:
		colorTriangle2 = newColorTr2;
		break;
	case 3:
		colorTriangle3 = newColorTr3;
		break;
	case 4:
		colorTriangle4 = newColorTr4;
		break;
	case 5:
		colorSquare = newColorSquare;
		break;
	}
}

void Cone::DrawStandart() {
	std::vector<unsigned int> indicesTopCircle;
	std::vector<unsigned int> indicesBottomCircle;
	std::vector<unsigned int> indicesBody;
	std::vector<Vertex> vertices;
	glm::vec3 positions;
	glm::vec2 texCoords;
	glm::vec3 normals;
	glm::vec4 colors;
	std::vector<unsigned int> indicesTopEdge;
	std::vector<unsigned int> indicesBottomEdge;
	radiusBottom = 1.0f;
	radiusTop = delta;
	positions.x = 0.0f;
	positions.y = -1.0f;
	positions.z = 0.0f;
	texCoords.x = 1;
	texCoords.y = 0;

	normals.x = 0;
	normals.y = 0;
	normals.z = 1;

	colors[0] = colorBottom.x;
	colors[1] = colorBottom.y;
	colors[2] = colorBottom.z;
	colors[3] = colorBottom.w;

	posTopCenter.x = positions.x;
	posTopCenter.y = positions.y;
	posTopCenter.z = positions.z;

	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	//float x = posBottomCenter.x;
	//float z = posBottomCenter.z;

	positions.x = 0.0f;
	positions.y = 0.0f;
	positions.z = 0.0f;

	posBottomCenter.x = positions.x;
	posBottomCenter.y = positions.y;
	posBottomCenter.z = positions.z;

	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	indicesBottomCircle.push_back(1);
	indicesTopCircle.push_back(0);

	int slices = 200;
	for (unsigned int i = 0; i < slices; i++) {
		float theta = (float)i * 2.0f * M_PI / float(slices);
		positions.x = radiusTop*cos(theta);
		positions.y = -1.0f;
		positions.z = radiusTop*sin(theta);
		texCoords.x = 1.0f;
		texCoords.y = 0.0f;

		normals.x = 0.0f;
		normals.y = 0.0f;
		normals.z = 1.0f;
		vertices.push_back(Vertex(positions, texCoords, normals, colors));
		indicesTopCircle.push_back(vertices.size() - 1);
		indicesTopEdge.push_back(vertices.size() - 1);
		indicesBody.push_back(vertices.size() - 1);

		positions.x = radiusBottom*cos(theta);
		positions.y = 0.0f;
		positions.z = radiusBottom*sin(theta);
		vertices.push_back(Vertex(positions, texCoords, normals, colors));
		indicesBottomCircle.push_back(vertices.size() - 1);
		indicesBottomEdge.push_back(vertices.size() - 1);
		indicesBody.push_back(vertices.size() - 1);
	}
	indicesBody.push_back(2);
	indicesBody.push_back(3);
	indicesTopCircle.push_back(2);
	indicesBottomCircle.push_back(3);

	/*for (int i = 0; i < indicesBottomCircle.size(); i++) {
		indicesBottomCircle[i] = 2 * i + 1;
	}

	for (int i = 0; i < indicesTopCircle.size(); i++) {
		indicesTopCircle[i] = 2 * i;
	}
*/

	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorBottom.x;
		vertices[i].GetColor()->y = colorBottom.y;
		vertices[i].GetColor()->z = colorBottom.z;
		vertices[i].GetColor()->w = colorBottom.w;
	}

	Shader shader("./res/basicShader");

	shader.Bind();
	shader.Update(transform, camera);
	Mesh meshBCircle(vertices, vertices.size(), indicesBottomCircle, indicesBottomCircle.size());
	meshBCircle.Draw(GL_TRIANGLE_FAN);
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorTop.x;
		vertices[i].GetColor()->y = colorTop.y;
		vertices[i].GetColor()->z = colorTop.z;
		vertices[i].GetColor()->w = colorTop.w;
	}
	Mesh meshTCircle(vertices, vertices.size(), indicesTopCircle, indicesTopCircle.size());
	meshTCircle.Draw(GL_TRIANGLE_FAN);
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = colorBody.x;
		vertices[i].GetColor()->y = colorBody.y;
		vertices[i].GetColor()->z = colorBody.z;
		vertices[i].GetColor()->w = colorBody.w;
	}
	Mesh meshBody(vertices, vertices.size(), indicesBody, indicesBody.size());
	meshBody.Draw(GL_TRIANGLE_STRIP);
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i].GetColor()->x = 1.0f;
		vertices[i].GetColor()->y = 1.0f;
		vertices[i].GetColor()->z = 1.0f;
		vertices[i].GetColor()->w = 1.0f;
	}
	Mesh meshTopEdge(vertices, vertices.size(), indicesTopEdge, indicesTopEdge.size());
	meshTopEdge.Draw(GL_LINE_STRIP);
	Mesh meshBottomEdge(vertices, vertices.size(), indicesBottomEdge, indicesBottomEdge.size());
	meshBottomEdge.Draw(GL_LINE_STRIP);
}

glm::vec3 Cone::GetObjectAxis() {
	glm::vec4 axes = this->GetModel()*glm::vec4(posTopCenter, 1.0f) - this->GetModel()*glm::vec4(posBottomCenter, 1.0f);
	return glm::vec3(axes.x, axes.y, axes.z);
}


void Cone::ChangeColor(int param) {
	glm::vec4 newColorTop = this->GetColorTop();
	glm::vec4 newColorBottom = this->GetColorBottom();
	glm::vec4 newColorBody = this->GetColorBody();
	if (newColorTop.x == 0.5f) {
		newColorTop.x = 1.0f;
	}
	else {
		newColorTop.x = 0.5f;
	}
	if (newColorBottom.x == 0.5f) {
		newColorBottom.x = 1.0f;
	}
	else {
		newColorBottom.x = 0.5f;
	}
	if (newColorBody.x == 0.5f) {
		newColorBody.x = 1.0f;
	}
	else {
		newColorBody.x = 0.5f;
	}
	switch (param) {
	case 0:
		colorBody = newColorBody;
		colorBottom = newColorBottom;
		colorTop = newColorTop;
		break;
	case 1:
		colorTop = newColorTop;
		break;
	case 2:
		colorBottom = newColorBottom;
		break;
	case 3:
		colorBody = newColorBody;
		break;
	}
}

