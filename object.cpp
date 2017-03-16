#include"object.h"

#define _USE_MATH_DEFINES
#include <math.h> 

Pyramid::Pyramid(Vertex Top, Vertex Base, Vertex Vertex1) {
	this->Top = Top;
	this->Base = Base;
	this->Vertex1 = Vertex1;
	//this->isPyramide = isPyramide;
}
//std::vector<Vertex> GetVertices() {
//return vertices;
//}
//void SetVertices(std::vector<Vertex> vertices) {
//this->vertices = vertices;
//}


void Pyramid::FindVerticesPyramid(glm::vec3 posTop, glm::vec3 posBase, glm::vec3 posVertexSquare1, glm::vec3& posVertexSquare2,
	glm::vec3& posVertexSquare3, glm::vec3& posVertexSquare4) {
	glm::vec3 vectorHeight = glm::vec3(posTop.x - posBase.x, posTop.y - posBase.y, posTop.z - posBase.z);
	glm::vec3 vectorDiagonal = glm::vec3(posVertexSquare1.x - posBase.x, posVertexSquare1.y - posBase.y,
		posVertexSquare1.z - posBase.z);
	glm::vec3 vectorSecondDiagonal = glm::cross(vectorHeight, vectorDiagonal);
	float coeficient1;
	float coeficient2;
	float SquareHalfOfDiagonal = pow((posVertexSquare1.x - posBase.x), 2) + pow((posVertexSquare1.y - posBase.y), 2) +
		pow((posVertexSquare1.z - posBase.z), 2);
	float xExactlyVector = vectorSecondDiagonal.x - posBase.x;
	float yExactlyVector = vectorSecondDiagonal.y - posBase.y;
	float zExactlyVector = vectorSecondDiagonal.z - posBase.z;
	//Now we have quadratic equation relative to variable coeficient. let coefs of this equation = a, b, c
	float a = pow(xExactlyVector, 2) + pow(yExactlyVector, 2) + pow(zExactlyVector, 2);
	float b = -2 * (xExactlyVector*posBase.x + yExactlyVector*posBase.y + zExactlyVector*posBase.z);
	float c = -SquareHalfOfDiagonal + pow(posBase.x, 2) + pow(posBase.y, 2) + pow(posBase.z, 2);
	float Discriminant = b*b - 4 * a*c;
	coeficient1 = (-b + sqrt(Discriminant)) / (2 * a);
	coeficient2 = (-b - sqrt(Discriminant)) / (2 * a);
	posVertexSquare2 = glm::vec3(coeficient1*xExactlyVector, coeficient1*yExactlyVector, coeficient1*zExactlyVector);
	posVertexSquare3 = glm::vec3(2 * posBase.x - posVertexSquare1.x, 2 * posBase.y - posVertexSquare1.y, 2 * posBase.z - posVertexSquare1.z);
	posVertexSquare4 = glm::vec3(coeficient2*xExactlyVector, coeficient2*yExactlyVector, coeficient2*zExactlyVector);
}


void Pyramid::Draw(){
	glm::vec3 posVertex2;
	glm::vec3 posVertex3;
	glm::vec3 posVertex4;
	//	Vertex* vertice = new Vertex[vertices.size()];
	//for (unsigned int i = 0; i < vertices.size(); i++) {
	//vertice[i] = vertices[i];
	//}
	//unsigned int* indice = new unsigned int[indices.size()];
	//for (unsigned int i = 0; i < indices.size(); i++) {
	//indice[i] = indices[i];
	//}
	FindVerticesPyramid(*Top.GetPos(), *Base.GetPos(), *Vertex1.GetPos(), posVertex2, posVertex3, posVertex4);
	/*	Vertex2.GetPos()->x = posVertex2.x;
	Vertex2.GetPos()->y = posVertex2.y;
	Vertex2.GetPos()->z = posVertex2.z;

	Vertex3.GetPos()->x = posVertex3.x;
	Vertex3.GetPos()->y = posVertex3.y;
	Vertex3.GetPos()->z = posVertex3.z;

	Vertex4.GetPos()->x = posVertex4.x;
	Vertex4.GetPos()->y = posVertex4.y;
	Vertex4.GetPos()->z = posVertex4.z;*/
	Vertex2.MakeVertex(posVertex2, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex3.MakeVertex(posVertex3, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex4.MakeVertex(posVertex4, glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	Vertex vertice[]{
		Vertex1, Vertex2, Vertex3, Vertex4, Top
	};
	unsigned int indice[]{
		0, 1, 2,
		0, 3, 2,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		0, 3, 4
	};
	static float counter = 0.0f;
	Shader shader("./res/basicShader");
	//Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	Mesh mesh(vertice, 5, indice, 18);
	float count = 10 * cos(counter);
	//transform.SetRotAngle(count);
	//	transform.GetRotAxis()->x = 0.0f;
	//transform.GetRotAxis()->y = 1.0f;
	//transform.GetRotAxis()->z = 1.0f;
	shader.Bind();
	shader.Update(transform, camera);
	mesh.Draw(GL_TRIANGLE_STRIP);
	//	transform.SetQuaternion(glm::quat(0.0f, 0.0f, 0.0f, 1.0f));

	counter += 0.001f;
}

Cone::Cone(float radiusBottom, float radiusTop, glm::vec3 posBottomCenter, glm::vec3 posTopCenter) {
	this->radiusBottom = radiusBottom;
	this->radiusTop = radiusTop;
	this->posBottomCenter.x = posBottomCenter.x;
	this->posBottomCenter.y = posBottomCenter.y;
	this->posBottomCenter.z = posBottomCenter.z;
	this->posTopCenter.x = posTopCenter.x;
	this->posTopCenter.y = posTopCenter.y;
	this->posTopCenter.z = posTopCenter.z;
}

void Cone::FindVerticesCone(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
	glm::vec3 positions;
	glm::vec2 texCoords;
	glm::vec3 normals;
	glm::vec4 colors;
	positions.x = posTopCenter.x;
	positions.y = posTopCenter.y;
	positions.z = posTopCenter.z;
	texCoords.x = 1;
	texCoords.y = 0;

	normals.x = 0;
	normals.y = 0;
	normals.z = 1;

	colors[0] = 0.5f;
	colors[1] = 0.0f;
	colors[2] = 0.0f;
	colors[3] = 1.0f;

	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	positions.x = posBottomCenter.x;
	positions.y = posBottomCenter.y;
	positions.z = posBottomCenter.z;
	vertices.push_back(Vertex(positions, texCoords, normals, colors));

	int slices = 400;
	//int counterVertices = 1;
	//int counterIndices = -1;
	for (unsigned int i = 0; i < slices; i++) {
		float theta = ((float)i)*2.0*M_PI / float(slices);
		float nextTheta = ((float)i + 1)*2.0*M_PI / float(slices);
		//positions.x = centerTop.GetPos()->x + radiusTop*cos(theta);
		//positions.y = centerTop.GetPos()->y;
		//positions.z = centerTop.GetPos()->z + radiusTop*sin(theta);
		positions.x = radiusTop*cos(theta);
		positions.y = posTopCenter.y;
		positions.z = radiusTop*sin(theta);

		texCoords.x = 1;
		texCoords.y = 0;

		normals.x = 0;
		normals.y = 0;
		normals.z = 1;

		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
		vertices.push_back(Vertex(positions, texCoords, normals, colors));

		//positions.x = centerTop.GetPos()->x + radiusTop*cos(nextTheta);
		//positions.y = centerTop.GetPos()->y;
		//positions.z = centerTop.GetPos()->z + radiusTop*sin(nextTheta);

		positions.x = radiusTop*cos(nextTheta);
		positions.y = posTopCenter.y;
		positions.z = radiusTop*sin(nextTheta);

		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
		vertices.push_back(Vertex(positions, texCoords, normals, colors));

		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(theta);
		//positions.y = centerBottom.GetPos()->y;
		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(theta);
		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals);
		positions.x = radiusBottom*cos(theta);
		positions.y = posBottomCenter.y;
		positions.z = radiusBottom*sin(theta);
		//	vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
		vertices.push_back(Vertex(positions, texCoords, normals, colors));


		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(nextTheta);
		//positions.y = centerBottom.GetPos()->y;
		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(nextTheta);
		positions.x = radiusBottom*cos(nextTheta);
		positions.y = posBottomCenter.y;
		positions.z = radiusBottom*sin(nextTheta);
		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
		vertices.push_back(Vertex(positions, texCoords, normals, colors));


		indices.push_back(0);
		indices.push_back(vertices.size() - 4);
		indices.push_back(vertices.size() - 3);

		indices.push_back(vertices.size() - 4);
		indices.push_back(vertices.size() - 3);
		indices.push_back(vertices.size() - 2);

		indices.push_back(vertices.size() - 3);
		indices.push_back(vertices.size() - 2);
		indices.push_back(vertices.size() - 1);

		indices.push_back(vertices.size() - 2);
		indices.push_back(vertices.size() - 1);
		indices.push_back(1);
	}
}
void Cone::Draw(){
	Vertex centerBottom(posBottomCenter, glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec4(0.5, 0.0, 0.0, 1.0));
	Vertex centerTop(posTopCenter, glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 1.0), glm::vec4(0.5, 0.0, 0.0, 1.0));
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	FindVerticesCone(vertices, indices);
	Vertex* vertice = new Vertex[vertices.size()];
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertice[i] = vertices[i];
	}
	unsigned int* indice = new unsigned int[indices.size()];
	for (unsigned int i = 0; i < indices.size(); i++) {
		indice[i] = indices[i];
	}
	Mesh mesh(vertice, vertices.size(), indice, indices.size());
	Shader shader("./res/basicShader");
	shader.Bind();
	shader.Update(transform, camera);
	mesh.Draw(GL_TRIANGLE_STRIP);
}