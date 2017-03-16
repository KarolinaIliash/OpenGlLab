//#include <iostream>
//#include <SDL/SDL.h>
//#include "display.h"
//#include "mesh.h"
//#include "shader.h"
//#include "texture.h"
//#include "transform.h"
//#include "camera.h"
//
//static const int DISPLAY_WIDTH = 800;
//static const int DISPLAY_HEIGHT = 600;
//
//void DrawPyramide();
//void DrawCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop);
//void FindVerticesCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
//void DrawAxes();
//
//class Object {
//private:
//	std::vector<Vertex> vertices;
//	std::vector<unsigned int> indices;
//	bool isPyramide;
//	Transform transform;
//public:
//	Object(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool isPyramide) {
//		this->vertices = vertices;
//		this->indices = indices;
//		this->isPyramide = isPyramide;
//	}
//	std::vector<Vertex> GetVertices() {
//		return vertices;
//	}
//	void SetVertices(std::vector<Vertex> vertices) {
//		this->vertices = vertices;
//	}
//	void EditPosTransfrom(glm::vec3 pos) {
//		transform.EditPos(pos);
//	}
//	void EditScaleTransform(glm::vec3 scale) {
//		transform.EditScale(scale);
//	}
//	void DrawObject() {
//		Vertex* vertice = new Vertex[vertices.size()];
//		for (unsigned int i = 0; i < vertices.size(); i++) {
//			vertice[i] = vertices[i];
//		}
//		unsigned int* indice = new unsigned int[indices.size()];
//		for (unsigned int i = 0; i < indices.size(); i++) {
//			indice[i] = indices[i];
//		}
//		static float counter = 0.0f;
//		Shader shader("./res/basicShader");
//		Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//		Mesh mesh(vertice, vertices.size(), indice, indices.size());
//		float count = 10 * cos(counter);
//		transform.SetRotAngle(count);
//		transform.GetRotAxis()->x = 0.0f;
//		transform.GetRotAxis()->y = 1.0f;
//		transform.GetRotAxis()->z = 1.0f;
//		shader.Bind();
//		shader.Update(transform, camera);
//		mesh.Draw(GL_TRIANGLE_STRIP);
//		transform.SetQuaternion(glm::quat(0.0f, 0.0f, 0.0f, 1.0f));
//
//		counter += 0.001f;
//	}
//};
//
//int main(int argc, char** argv)
//{
//	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
//
//	//Vertex vertices[] =
//	//{
//		/*Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
//		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
//		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
//		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),
//
//		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
//		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
//		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
//		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),
//
//		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
//		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
//		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
//		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
//
//		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
//		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
//		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
//		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),
//
//		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
//		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
//		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
//		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),
//
//		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
//		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
//		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
//		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
//		Vertex(glm::vec3(0.0f, 0.0f ,0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 0.0f ,1.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 0.0f ,1.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0.5f, 0.0f, 0.0f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 0.0f , 1.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0.0f, 0.9f, 0.0f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f))
//	};
//	*/
//
//	std::vector<Object> objects;
//	std::cout << "How many pyramids do you want?\n";
//	unsigned int numPyramides;
//	std::cin >> numPyramides;
//	float temp1;
//	float temp2;
//	float temp3;
//	std::vector<unsigned int> indicesPyramid =
//	{
//		0, 1, 2,
//		0, 3, 2,
//		0, 1, 4,
//		1, 2, 4,
//		2, 3, 4,
//		0, 3, 4
//	};
//	glm::vec3 posTop;
//	glm::vec3 posBase;
//	glm::vec3 posVertex1;
//	glm::vec3 posVertex2;
//	glm::vec3 posVertex3;
//	glm::vec3 posVertex4;
//	glm::vec2 texCoord(0.0f, 0.0f);
//	glm::vec3 normal(0.0f, 0.0f, 1.0f);
//	glm::vec4 color(0.5f, 0.0f, 0.0f, 1.0f);
//	std::vector<Vertex> vertice(5);
//	for (int i = 0; i < numPyramides; i++) {
//		std::cout << "Enter coords of top of " << i + 1 << " pyramide\n";
//		std::cin >> temp1;
//		std::cin >> temp2;
//		std::cin >> temp3;
//		posTop.x = temp1;
//		posTop.y = temp2;
//		posTop.z = temp3;
//		//pos = glm::normalize(pos);
//		//vertice.push_back(Vertex{ pos, texCoord, normal, color });
//		std::cout << "Enter coords of base of height of " << i + 1 << " pyramide\n";
//		std::cin >> temp1;
//		std::cin >> temp2;
//		std::cin >> temp3;
//		posBase.x = temp1;
//		posBase.y = temp2;
//		posBase.z = temp3;
//		std::cout << "Enter coords of first of vertices of square of " << i + 1 << " pyramide\n";
//		while (true) {
//			std::cin >> temp1;
//			std::cin >> temp2;
//			std::cin >> temp3;
//			if ((posTop.x - posBase.x)*(temp1 - posBase.x) + (posTop.y - posBase.y)*(temp2 - posBase.y) +
//				(posTop.z - posBase.z)*(temp3 - posBase.z) == 0) break;
//			else
//				std::cerr << "Vertice of square has to be in plane perpendicular to height of pyramide\nTry one more time\n";
//		}
//		posVertex1.x = temp1;
//		posVertex1.y = temp2;
//		posVertex1.z = temp3;
//
//		std::cout << "Enter coords of second of vertices of square of " << i + 1 << " pyramide\n";
//		while (true) {
//			std::cin >> temp1;
//			std::cin >> temp2;
//			std::cin >> temp3;
//			if ((posTop.x - posBase.x)*(temp1 - posBase.x) + (posTop.y - posBase.y)*(temp2 - posBase.y) +
//				(posTop.z - posBase.z)*(temp3 - posBase.z) == 0) break;
//			else
//				std::cerr << "Vertice of square has to be in plane perpendicular to height of pyramide\nTry one more time\n";
//		}
//		posVertex2.x = temp1;
//		posVertex2.y = temp2;
//		posVertex2.z = temp3;
//
//		std::cout << "Enter coords of first of vertices of square of " << i + 1 << " pyramide\n";
//		while (true) {
//			std::cin >> temp1;
//			std::cin >> temp2;
//			std::cin >> temp3;
//			if ((posTop.x - posBase.x)*(temp1 - posBase.x) + (posTop.y - posBase.y)*(temp2 - posBase.y) +
//				(posTop.z - posBase.z)*(temp3 - posBase.z) == 0) break;
//			else
//				std::cerr << "Vertice of square has to be in plane perpendicular to height of pyramide\nTry one more time\n";
//		}
//		posVertex3.x = temp1;
//		posVertex3.y = temp2;
//		posVertex3.z = temp3;
//
//		std::cout << "Enter coords of first of vertices of square of " << i + 1 << " pyramide\n";
//		while (true) {
//			std::cin >> temp1;
//			std::cin >> temp2;
//			std::cin >> temp3;
//			if ((posTop.x - posBase.x)*(temp1 - posBase.x) + (posTop.y - posBase.y)*(temp2 - posBase.y) +
//				(posTop.z - posBase.z)*(temp3 - posBase.z) == 0) break;
//			else
//				std::cerr << "Vertice of square has to be in plane perpendicular to height of pyramide\nTry one more time\n";
//		}
//		posVertex4.x = temp1;
//		posVertex4.y = temp2;
//		posVertex4.z = temp3;
//		vertice[0] = Vertex{ posVertex1, texCoord, normal, color };
//		vertice[1] = Vertex{ posVertex2, texCoord, normal, color };
//		vertice[2] = Vertex{ posVertex3, texCoord, normal, color };
//		vertice[3] = Vertex{ posVertex4, texCoord, normal, color };
//		vertice[4] = Vertex{ posTop, texCoord, normal, color };
//		objects.push_back(Object{ vertice, indicesPyramid, true });
//	}
//
//	std::cout << "\nHow many frustrum cones do you want?\n";
//	unsigned int numCones;
//	std::cin >> numCones;
//	glm::vec3 posBottomCenter;
//	glm::vec3 posTopCenter;
//	float radiusBottom;
//	float radiusTop;
//	std::vector<Vertex> verticesCone;
//	std::vector<unsigned int> indicesCone;
//	for (unsigned int i = 0; i < numCones; i++) {
//		std::cout << "Enter coordinates of bottom center of " << i + 1 << " cone\n";
//		std::cin >> posBottomCenter.x;
//		std::cin >> posBottomCenter.y;
//		std::cin >> posBottomCenter.z;
//		std::cout << "Enter radius of bottom circle of" << i + 1 << " cone\n";
//		std::cin >> radiusBottom;
//		std::cout << "Enter coordinates of top center of " << i + 1 << " cone\n";
//		std::cin >> posTopCenter.x;
//		std::cin >> posTopCenter.y;
//		std::cin >> posTopCenter.z;
//		std::cout << "Enter radius of top circle of" << i + 1 << " cone\n";
//		std::cin >> radiusTop;
//		FindVerticesCone(radiusBottom, radiusTop, Vertex(posBottomCenter, texCoord, normal, color), Vertex(posTopCenter, texCoord, normal, color), verticesCone, indicesCone);
//		objects.push_back(Object(verticesCone, indicesCone, false));
//	}
//
//	unsigned int indices[] = /*{ 0, 1, 2,
//							 0, 2, 3,
//
//							 6, 5, 4,
//							 7, 6, 4,
//
//							 10, 9, 8,
//							 11, 10, 8,
//
//							 12, 13, 14,
//							 12, 14, 15,
//
//							 16, 17, 18,
//							 16, 18, 19,
//
//							 22, 21, 20,
//							 23, 22, 20
//							 };*/
//	{
//		0, 1, 2,
//		0, 3, 2,
//		0, 1, 4,
//		1, 2, 4,
//		2, 3, 4,
//		0, 3, 4
//	};
//
//	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
//	//Mesh monkey("./res/monkey3.obj");
//	//Shader shader("./res/basicShader");
//	//Texture texture("./res/bricks.jpg");
//	//Transform transform;
//	//Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//
//	SDL_Event e;
//	bool isRunning = true;
//	float counter = 0.0f;
//	while (isRunning)
//	{
//		while (SDL_PollEvent(&e))
//		{
//			if (e.type == SDL_QUIT)
//				isRunning = false;
//		}
//
//		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
//
//		float sinCounter = sinf(counter);
//		float absSinCounter = abs(sinCounter);
//		//DrawPyramide();
//		Vertex centerBottom{
//			glm::vec3(0.0, 0.0, 0.0), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
//		};
//
//		Vertex centerTop{
//			glm::vec3(2.0, 1.0, 0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
//		};
//		DrawAxes();
//		for (unsigned int i = 0; i < objects.size(); i++) {
//			objects[i].DrawObject();
//		}
//		//DrawCone(0.5, 0.3, centerBottom, centerTop);
//		//	transform.GetPos()->x = sinCounter;
//		//transform.GetRot()->y = 0.5*counter;
//		//transform.GetRot()->x = 0.5*counter;
//		//transform.GetRot()->z = 0.5*counter;
//		//transform.GetScale()->x = absSinCounter;
//		//transform.GetScale()->y = absSinCounter;
//
//
//		//shader.Bind();
//		//texture.Bind();
//		//shader.Update(transform, camera);
//		//monkey.Draw();
//		//mesh.Draw();
//
//		display.SwapBuffers();
//		SDL_Delay(1);
//		//	counter += 0.01f;
//	}
//
//	return 0;
//}
//
//void DrawPyramide() {//Vertex* vertices) {
//					 /*Vertex vertices[]{
//					 Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//					 Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//					 Vertex(glm::vec3(0, 0, -0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
//					 Vertex(glm::vec3(0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
//					 Vertex(glm::vec3(0, 2.0 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
//					 };
//					 unsigned int indices[] =
//					 {
//					 0, 1, 2,
//					 0, 3, 2,
//					 0, 1, 4,
//					 1, 2, 4,
//					 2, 3, 4,
//					 0, 3, 4
//					 };*/
//					 //	Vertex vertices[]{
//					 //Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//					 //Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//					 //	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
//					 //Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
//					 //Vertex(glm::vec3(0.5, -0.5 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
//					 //};
//					 //unsigned int indices[] =
//					 //{
//					 //0, 1, 2,
//					 //0, 3, 2,
//					 //0, 1, 4,
//					 //1, 2, 4,
//					 //2, 3, 4,
//					 //0, 3, 4
//					 //};
//					 //static float counter = 0.0f;
//					 //Mesh mesh(vertices, 5, indices, sizeof(indices) / sizeof(indices[0]));
//					 //Shader shader("./res/basicShader");
//					 //Texture texture("./res/bricks.jpg");
//					 //Transform transform;
//					 //Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//					 //transform.GetRot()->y = 0.5*counter;
//					 //transform.GetRot()->x = 0.5*counter;
//					 //transform.GetRot()->z = 0.5*counter;
//					 //float count = counter*0.5;
//					 //transform.SetRotAngle(count);
//					 //transform.GetRotAxis()->x = 0.0;
//
//					 //transform.GetScale()->x = absSinCounter;
//					 //transform.GetScale()->y = absSinCounter;
//
//
//					 //shader.Bind();
//					 //texture.Bind();
//					 //shader.Update(transform, camera);
//					 //monkey.Draw();
//					 //mesh.Draw();
//					 //counter += 0.01f;
//
//	Vertex vertices[]{
//		Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0, 0, -0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)),
//		Vertex(glm::vec3(0, 0.9, 0), glm::vec2(1,0), glm::vec3(0, 0, 1), glm::vec4(0.5f, 0.0f, 0.0f, 1.0f))
//	};
//	unsigned int indices[] =
//	{
//		0, 1, 2,
//		0, 3, 2,
//		0, 1, 4,
//		1, 2, 4,
//		2, 3, 4,
//		0, 3, 4
//	};
//
//	static float counter = 0.0f;
//	Mesh mesh(vertices, 5, indices, 18);
//	//Mesh mesh(vertices, counterVertices+1, indices, counterIndices+1);
//
//	Shader shader("./res/basicShader");
//	Texture texture("./res/bricks.jpg");
//	Transform transform;
//	Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//	//transform.GetRot()->y = 100*cos(counter);
//	//	transform.GetRot()->x = 100*cos(counter);
//	//transform.GetRot()->z = 40*cos(counter);
//	//transform.GetScale()->x = absSinCounter;
//	//transform.GetScale()->y = absSinCounter;
//	float count = 100 * cos(counter);
//	transform.SetRotAngle(count);
//	transform.GetRotAxis()->x = 0.0;
//	transform.GetRotAxis()->y = 1.0;
//	transform.GetRotAxis()->z = 1.0;
//	shader.Bind();
//	texture.Bind();
//	shader.Update(transform, camera);
//	//monkey.Draw();
//	mesh.Draw(GL_TRIANGLE_STRIP);
//	counter += 0.01f;
//}
//
//void DrawCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop) {
//	const int N = 10000;
//	Vertex vertices[N];
//	glm::vec3 positions;
//	glm::vec2 texCoords;
//	glm::vec3 normals;
//	glm::vec4 colors;
//	positions.x = 0.0;
//	positions.y = 1.0;
//	positions.z = 0.0;
//	texCoords.x = 1;
//	texCoords.y = 0;
//
//	normals.x = 0;
//	normals.y = 0;
//	normals.z = 1;
//
//	colors[0] = 0.5f;
//	colors[1] = 0.0f;
//	colors[2] = 0.0f;
//	colors[3] = 1.0f;
//
//	vertices[0] = Vertex(positions, texCoords, normals, colors);
//
//	positions.x = 0.0;
//	positions.y = 0.0;
//	positions.z = 0.0;
//	vertices[1] = Vertex(positions, texCoords, normals, colors);
//
//	unsigned int indices[N];
//	int slices = 400;
//	int counterVertices = 1;
//	int counterIndices = -1;
//	for (unsigned int i = 0; i < slices; i++) {
//		float theta = ((float)i)*2.0*M_PI / float(slices);
//		float nextTheta = ((float)i + 1)*2.0*M_PI / float(slices);
//		//positions.x = centerTop.GetPos()->x + radiusTop*cos(theta);
//		//positions.y = centerTop.GetPos()->y;
//		//positions.z = centerTop.GetPos()->z + radiusTop*sin(theta);
//		positions.x = radiusTop*cos(theta);
//		positions.y = 1.0;
//		positions.z = radiusTop*sin(theta);
//
//		texCoords.x = 1;
//		texCoords.y = 0;
//
//		normals.x = 0;
//		normals.y = 0;
//		normals.z = 1;
//
//		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//
//
//		//positions.x = centerTop.GetPos()->x + radiusTop*cos(nextTheta);
//		//positions.y = centerTop.GetPos()->y;
//		//positions.z = centerTop.GetPos()->z + radiusTop*sin(nextTheta);
//
//		positions.x = radiusTop*cos(nextTheta);
//		positions.y = 1.0;
//		positions.z = radiusTop*sin(nextTheta);
//
//		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//
//
//		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(theta);
//		//positions.y = centerBottom.GetPos()->y;
//		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(theta);
//		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals);
//		positions.x = radiusBottom*cos(theta);
//		positions.y = 0.0;
//		positions.z = radiusBottom*sin(theta);
//		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//
//
//
//		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(nextTheta);
//		//positions.y = centerBottom.GetPos()->y;
//		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(nextTheta);
//		positions.x = radiusBottom*cos(nextTheta);
//		positions.y = 0.0;
//		positions.z = radiusBottom*sin(nextTheta);
//		vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//
//
//
//		indices[++counterIndices] = 0;
//		indices[++counterIndices] = counterVertices - 3;
//		indices[++counterIndices] = counterVertices - 2;
//
//		indices[++counterIndices] = counterVertices - 3;
//		indices[++counterIndices] = counterVertices - 2;
//		indices[++counterIndices] = counterVertices - 1;
//
//		indices[++counterIndices] = counterVertices - 2;
//		indices[++counterIndices] = counterVertices - 1;
//		indices[++counterIndices] = counterVertices;
//
//		indices[++counterIndices] = counterVertices - 1;
//		indices[++counterIndices] = counterVertices;
//		indices[++counterIndices] = 1;
//	}
//	///////////////////////////////////////
//	/*Vertex vertices[]{
//	//Vertex(glm::vec3(0, 0 ,0.5), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//	//Vertex(glm::vec3(-0.5, 0, 0), glm::vec2(1,0), glm::vec3(0, 0 ,1)),
//	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
//	Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1,0), glm::vec3(0, 0 , 1)),
//	Vertex(glm::vec3(0.5, -0.5 , 0), glm::vec2(1,0), glm::vec3(0, 0, 1))
//	};
//	unsigned int indices[] =
//	{
//	0, 1, 2,
//	//0, 3, 2,
//	//0, 1, 4,
//	//1, 2, 4,
//	//2, 3, 4,
//	//0, 3, 4
//	};
//	*/
//	static float counter = 0.0f;
//	//Mesh mesh(vertices, 3, indices, 3);
//	Mesh mesh(vertices, counterVertices + 1, indices, counterIndices + 1);
//
//	Shader shader("./res/basicShader");
//	//Texture texture("./res/bricks.jpg");
//	Transform transform;
//	Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//	//transform.GetRot()->y = 100*cos(counter);
//	//	transform.GetRot()->x = 100*cos(counter);
//	//transform.GetRot()->z = 40*cos(counter);
//	//transform.GetScale()->x = absSinCounter;
//	//transform.GetScale()->y = absSinCounter;
//	float count = 100 * cos(counter);
//	transform.SetRotAngle(count);
//	transform.GetRotAxis()->x = 0.0;
//	transform.GetRotAxis()->y = 1.0;
//	transform.GetRotAxis()->z = 0.0;
//	shader.Bind();
//	//texture.Bind();
//	shader.Update(transform, camera);
//	//monkey.Draw();
//	mesh.Draw(GL_TRIANGLE_STRIP);
//	counter += 0.01f;
//}
//
//void FindVerticesPyramid(Vertex top, Vertex base, Vertex vertexSquare1, Vertex& vertexSquare2, Vertex& vertexSquare3, Vertex& vertexSquare4) {
//	glm::vec3 vectorHeight = glm::vec3(top.GetPos()->x - base.GetPos()->x, top.GetPos()->y - base.GetPos()->y, top.GetPos()->z - base.GetPos()->z);
//	glm::vec3 vectorDiagonal = glm::vec3(vertexSquare1.GetPos()->x - base.GetPos()->x, vertexSquare1.GetPos()->y - base.GetPos()->y,
//		vertexSquare1.GetPos()->z - base.GetPos()->z);
//	glm::vec3 vectorSecondDiagonal = glm::cross(vectorHeight, vectorDiagonal);
//	float coeficient1;
//	float coeficient2;
//	float SquareHalfOfDiagonal = pow((vertexSquare1.GetPos()->x - base.GetPos()->x), 2) + pow((vertexSquare1.GetPos()->y - base.GetPos()->y), 2) +
//		pow((vertexSquare1.GetPos()->z - base.GetPos()->z), 2);
//	float xExactlyVector = vectorSecondDiagonal.x - base.GetPos()->x;
//	float yExactlyVector = vectorSecondDiagonal.y - base.GetPos()->y;
//	float zExactlyVector = vectorSecondDiagonal.z - base.GetPos()->z;
//	//Now we have quadratic equation relative to variable coeficient. let coefs of this equation = a, b, c
//	float a = pow(xExactlyVector, 2) + pow(yExactlyVector, 2) + pow(zExactlyVector, 2);
//	float b = -2 * (xExactlyVector*base.GetPos()->x + yExactlyVector*base.GetPos()->y + zExactlyVector*base.GetPos()->z);
//	float c = -SquareHalfOfDiagonal + pow(base.GetPos()->x, 2) + pow(base.GetPos()->y, 2) + pow(base.GetPos()->z, 2);
//	float Discriminant = b*b - 4 * a*c;
//	coeficient1 = (-b + sqrt(Discriminant)) / (2 * a);
//	coeficient2 = (-b - sqrt(Discriminant)) / (2 * a);
//	vertexSquare2 = Vertex(glm::vec3(coeficient1*xExactlyVector, coeficient1*yExactlyVector, coeficient1*zExactlyVector), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.5, 0.0, 0.0, 1.0));
//	vertexSquare3 = Vertex(glm::vec3(2 * base.GetPos()->x - vertexSquare1.GetPos()->x, 2 * base.GetPos()->y - vertexSquare1.GetPos()->y, 2 * base.GetPos()->z - vertexSquare1.GetPos()->z),
//		glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.5, 0.0, 0.0, 1.0));
//	vertexSquare4 = Vertex(glm::vec3(coeficient2*xExactlyVector, coeficient2*yExactlyVector, coeficient2*zExactlyVector), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec4(0.5, 0.0, 0.0, 1.0));
//}
//
//
//void FindVerticesCone(float radiusBottom, float radiusTop, Vertex centerBottom, Vertex centerTop, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
//	glm::vec3 positions;
//	glm::vec2 texCoords;
//	glm::vec3 normals;
//	glm::vec4 colors;
//	positions.x = 0.0;
//	positions.y = 1.0;
//	positions.z = 0.0;
//	texCoords.x = 1;
//	texCoords.y = 0;
//
//	normals.x = 0;
//	normals.y = 0;
//	normals.z = 1;
//
//	colors[0] = 0.5f;
//	colors[1] = 0.0f;
//	colors[2] = 0.0f;
//	colors[3] = 1.0f;
//
//	vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//	positions.x = 0.0;
//	positions.y = 0.0;
//	positions.z = 0.0;
//	vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//	int slices = 400;
//	//int counterVertices = 1;
//	//int counterIndices = -1;
//	for (unsigned int i = 0; i < slices; i++) {
//		float theta = ((float)i)*2.0*M_PI / float(slices);
//	float nextTheta = ((float)i + 1)*2.0*M_PI / float(slices);
//		//positions.x = centerTop.GetPos()->x + radiusTop*cos(theta);
//		//positions.y = centerTop.GetPos()->y;
//		//positions.z = centerTop.GetPos()->z + radiusTop*sin(theta);
//		positions.x = radiusTop*cos(theta);
//		positions.y = 1.0;
//		positions.z = radiusTop*sin(theta);
//
//		texCoords.x = 1;
//		texCoords.y = 0;
//
//		normals.x = 0;
//		normals.y = 0;
//		normals.z = 1;
//
//		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//		vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//		//positions.x = centerTop.GetPos()->x + radiusTop*cos(nextTheta);
//		//positions.y = centerTop.GetPos()->y;
//		//positions.z = centerTop.GetPos()->z + radiusTop*sin(nextTheta);
//
//		positions.x = radiusTop*cos(nextTheta);
//		positions.y = 1.0;
//		positions.z = radiusTop*sin(nextTheta);
//
//		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//		vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(theta);
//		//positions.y = centerBottom.GetPos()->y;
//		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(theta);
//		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals);
//		positions.x = radiusBottom*cos(theta);
//		positions.y = 0.0;
//		positions.z = radiusBottom*sin(theta);
//		//	vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//		vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//
//		//positions.x = centerBottom.GetPos()->x + radiusBottom*cos(nextTheta);
//		//positions.y = centerBottom.GetPos()->y;
//		//positions.z = centerBottom.GetPos()->z + radiusBottom*sin(nextTheta);
//		positions.x = radiusBottom*cos(nextTheta);
//		positions.y = 0.0;
//		positions.z = radiusBottom*sin(nextTheta);
//		//vertices[++counterVertices].MakeVertex(positions, texCoords, normals, colors);
//		vertices.push_back(Vertex(positions, texCoords, normals, colors));
//
//
//		indices.push_back(0);
//		indices.push_back(vertices.size() - 4);
//		indices.push_back(vertices.size() - 3);
//
//		indices.push_back(vertices.size() - 4);
//		indices.push_back(vertices.size() - 3);
//		indices.push_back(vertices.size() - 2);
//
//		indices.push_back(vertices.size() - 3);
//		indices.push_back(vertices.size() - 2);
//		indices.push_back(vertices.size() - 1);
//
//		indices.push_back(vertices.size() - 2);
//		indices.push_back(vertices.size() - 1);
//		indices.push_back(1);
//	}
//}
//
//
//void DrawAxes() {
//	Vertex vertices[]{
//		Vertex(glm::vec3(0.0f,0.0f,-10.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
//		Vertex(glm::vec3(0.0f, 0.0f, 10.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
//	};
//	unsigned int indices[]{
//		0, 1
//	};
//	Transform transform;
//	float count = 10;
//	//transform.SetRotAngle(count);
//	//transform.GetRotAxis()->x = 0.1f;
//	//transform.GetRotAxis()->y = 0.0f;
//	//transform.GetRotAxis()->z = 0.5f;
//	Shader shader("./res/basicShader");
//	Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);
//	Mesh meshZ(vertices, 2, indices, 2);
//	shader.Bind();
//	shader.Update(transform, camera);
//	//meshZ.Draw(GL_LINES);
//	vertices[0] = Vertex(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//	vertices[1] = Vertex(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//	Mesh meshY(vertices, 2, indices, 2);
//	meshY.Draw(GL_LINES);
//	vertices[0] = Vertex(glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//	vertices[1] = Vertex(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//	Mesh meshX(vertices, 2, indices, 2);
//	meshX.Draw(GL_LINES);
//}