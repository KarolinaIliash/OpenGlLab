#include <iostream>
#include <SDL/SDL.h>
#include "display.h"
#include "texture.h"
#include"Ray.h"
#include"object.h"

void DrawAxes();
void getInfoCone(float& bottomRadius, float& topRadius, float& coneHeight);
void getInfoPyramid(float& height, float& halfDiagonal);


int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Ray ray(camera);

	std::vector<Object *> objects;

	enum class MODE {
		DrawingPyramid,
		DrawingCone,
		ChoosingEdit,
		Rotation,
		Translating,
		Scaling,
		ChangingColor,
		PickingObject
	};
	SDL_Event e;
	MODE mode = MODE::DrawingPyramid;
	bool isRunning = true;
	float counter = 0.0f;
	display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
	float height;
	float halfDiagonal;
	glm::vec3 posBase;
	glm::vec3 posTop;
	glm::vec3 posVertex1;
	bool isDrawing = true;
	glm::vec3 posBottomCenter;
	glm::vec3 posTopCenter;
	float bottomRadius;
	float topRadius;
	float coneHeight;
	Object* obj;
	bool isFirstPointTR = false;
	bool isSecondPointTR = false;
	float angle;
	bool isAngleSet = false;
	GLuint index;
	std::vector<Object*> chosenObjects;
	glm::vec3 toTranslate(0, 0, 0);
	glm::vec3 firstPoint(0, 0, 0);
	glm::vec3 secondPoint(0, 0, 0);
	while (isRunning) {
		switch (mode) {
		case MODE::DrawingPyramid:
			display.ChangeTitle("Drawing pyramids. Enter key from 0 to 6 and get pyramid in certain area. Enter n - go to drawing cones");
			break;
		case MODE::DrawingCone:
			display.ChangeTitle("Drawing cones. Enter key from 0 to 6 and get cone in certain area. Enter n - go to editing");
			break;
		case MODE::PickingObject:
			display.ChangeTitle("Pick the objects by clicking left mouse button on them. Enter n - go to choosing what you want to edit");
			break;
		case MODE::ChoosingEdit:
			display.ChangeTitle("Enter s - to scale, r - to rotation, t - to translation, c - to change color");
			break;
		case MODE::Translating:
			display.ChangeTitle("Enter arrows to translate chosen objects");
			break;
		case MODE::Scaling:
			display.ChangeTitle("Enter up and down arrows to scale chosen objects");
			break;
		case MODE::Rotation:
			display.ChangeTitle("Pick by mouse object's axis or by keys axis x, y or z and enter angle of rotation in consol");
			break;
		case MODE::ChangingColor:
			display.ChangeTitle("Enter keys from 1 to 5 to change color of object's element(for cone only 1-3) and 0 - of all object");
			break;
		}
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONUP:
				switch (mode) {
				case MODE::PickingObject:
					if (e.button.button == SDL_BUTTON_LEFT) {
					GLbyte color[4];
					GLfloat depth;
					//GLuint index;

					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
					if (index) {
						chosenObjects.push_back(objects[index-1]);
					}
					}
					else {
						if (e.button.button == SDL_BUTTON_RIGHT) {
							mode = MODE::ChoosingEdit;
						}
					}
					break;
				case MODE::Rotation:
					//GLuint index;
					glReadPixels(e.button.x, DISPLAY_HEIGHT - e.button.y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
					if (index) {
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->SetAxisRotation(objects[index - 1]->GetObjectAxis());
							if (!isAngleSet) {
								std::cout << "Enter angle of rotation\n";
								std::cin >> angle;
								isAngleSet = true;
								for (unsigned int i = 0; i < chosenObjects.size(); i++) {
									chosenObjects[i]->SetAngleRotation(angle);
								}
							}
						}
					}
					break;
				//case MODE::Translating:

				//	if (!isFirstPointTR) {
				//	//	firstPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
				//	//	firstPoint = (3.0f / firstPoint.z)*firstPoint + glm::vec3(0.0f, 0.0f, -3.0f);
				//		isFirstPointTR = true;
				//	}
				//	else {
				//		if (!isSecondPointTR) {
				//		//	secondPoint = ray.RayUnProj(e.button.x, e.button.y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
				//		//	secondPoint = (3.0f / secondPoint.z)*secondPoint + glm::vec3(0.0f, 0.0f, -3.0f);
				//			isSecondPointTR = true;
				//		}
				//	}
				//	if (isSecondPointTR) {
				//		toTranslate = secondPoint - firstPoint;
				//		//		toTranslate = glm::normalize(toTranslate);
				//		for (unsigned int i = 0; i < chosenObjects.size(); i++) {
				//			chosenObjects[i]->EditPosTransfrom(toTranslate);
				//		}
				//		chosenObjects.resize(0);
				//		mode = MODE::PickingObject;
				//	}
				//	break;
					/*case MODE::Scaling:
					glm::vec3 scale;
					std::cout << "Enter in how many times you want to scale object(s)\nx = ";
					std::cin >> scale.x;
					std::cout << "y = ";
					std::cin >> scale.y;
					std::cout << "z = ";
					std::cin >> scale.z;
					for (unsigned int i = 0; i < chosenObjects.size(); i++) {
					chosenObjects[i]->EditScaleTransform(scale);
					}
					chosenObjects.resize(0);
					mode = MODE::PickingObject;
					break;*/
					//case MODE::Rotation: //choosing object in order to find axes to do rotation

					//	break;
				}
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_c:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::ChangingColor;
					}
					break;
				case SDLK_t:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Translating;
						isFirstPointTR = false;
						isSecondPointTR = false;
					}
					break;
				case SDLK_r:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Rotation;
						isAngleSet = false;
					}
					break;
				case SDLK_s:
					if (mode == MODE::ChoosingEdit) {
						mode = MODE::Scaling;
					}
					break;
				case SDLK_0:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(0);
						}
						break;
					}
					break;
				case SDLK_1:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(-2.0f, 1.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(-2.0f, 1.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(1);
						}
						break;
					}
					break;
				case SDLK_2:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(0.0f, 2.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius/bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(0.0f, 2.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(2);
						}
						break;
					}
					break;
				case SDLK_3:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(2.0f, 0.5f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(2.0f, 0.5f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(3);
						}
						break;
					}
					break;
				case SDLK_4:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(2.0f, -2.0f, 0.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(2.0f, -2.0f, 0.0f));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(4);
						}
						break;
					}
					break;
				case SDLK_5:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(0.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(0.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					case MODE::ChangingColor:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->ChangeColor(5);
						}
						break;
					}
					break;
				case SDLK_6:
					switch (mode) {
					case MODE::DrawingPyramid:
						getInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(-2.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						getInfoCone(bottomRadius, topRadius, coneHeight);
						obj = new Cone(topRadius / bottomRadius);
						obj->EditScaleTransform(glm::vec3(bottomRadius, coneHeight, bottomRadius));
						obj->EditPosTransfrom(glm::vec3(-2.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					}
					break;
				case SDLK_n://next
					switch (mode) {
					case MODE::DrawingPyramid:
						mode = MODE::DrawingCone;
						break;
					case MODE::DrawingCone:
						mode = MODE::PickingObject;
						break;
					case MODE::PickingObject:
						mode = MODE::ChoosingEdit;
						break;
					}
					break;
				case SDLK_b://back
					switch (mode) {
					case MODE::DrawingCone:
						mode = MODE::DrawingPyramid;
						break;
					case MODE::PickingObject:
						mode = MODE::DrawingCone;
						break;
					case MODE::ChoosingEdit:
						mode = MODE::PickingObject;
						break;
					case MODE::Translating:
					case MODE::Rotation:
					case MODE::Scaling:
					case MODE::ChangingColor:
						mode = MODE::ChoosingEdit;
						break;
					}
					break;
				case SDLK_x:
					if (mode == MODE::Rotation) {
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->SetAxisRotation(glm::vec3(1.0f, 0.0f, 0.0f));
							//mode = MODE::ChoosingEdit;
						}
						if (!isAngleSet) {
							std::cout << "Enter angle of rotation\n";
							std::cin >> angle;
							isAngleSet = true;
							for (unsigned int i = 0; i < chosenObjects.size(); i++) {
								chosenObjects[i]->SetAngleRotation(angle);
							}
						}
						mode = MODE::ChoosingEdit;
					}
					break;
				case SDLK_y:
					if (mode == MODE::Rotation) {
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->SetAxisRotation(glm::vec3(0.0f, 1.0f, 0.0f));
							//mode = MODE::ChoosingEdit;
						}
						if (!isAngleSet) {
							std::cout << "Enter angle of rotation\n";
							std::cin >> angle;
							isAngleSet = true;
							for (unsigned int i = 0; i < chosenObjects.size(); i++) {
								chosenObjects[i]->SetAngleRotation(angle);
							}
						}
						mode = MODE::ChoosingEdit;
					}
					break;
				case SDLK_z:
					if (mode == MODE::Rotation) {
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->SetAxisRotation(glm::vec3(0.0f, 0.0f, 1.0f));
							//mode = MODE::ChoosingEdit;
						}
						if (!isAngleSet) {
							std::cout << "Enter angle of rotation\n";
							std::cin >> angle;
							isAngleSet = true;
							for (unsigned int i = 0; i < chosenObjects.size(); i++) {
								chosenObjects[i]->SetAngleRotation(angle);
							}
						}
						mode = MODE::ChoosingEdit;
					}
					break;
				case SDLK_ESCAPE:
					switch (mode) {
					case MODE::ChoosingEdit:
					case MODE::Rotation:
					case MODE::Scaling:
					case MODE::Translating:
					case MODE::ChangingColor:
						chosenObjects.resize(0);
						mode = MODE::PickingObject;
					}
				case SDLK_LEFT:
					switch (mode) {
					case MODE::Translating:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditPosTransfrom(glm::vec3(-0.2f, 0.0f, 0.0f));
						}
						break;
					}
					break;
				case SDLK_RIGHT:
					switch (mode) {
					case MODE::Translating:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditPosTransfrom(glm::vec3(0.2f, 0.0f, 0.0f));
						}
						break;
					}
					break;
				case SDLK_UP:
					switch (mode) {
					case MODE::Translating:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditPosTransfrom(glm::vec3(0.0f, 0.2f, 0.0f));
						}
						break;
					case MODE::Scaling:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditScaleTransform(glm::vec3(1.1f, 1.1f, 1.1f));
						}
						break;
					}
					break;
				case SDLK_DOWN:
					switch (mode) {
					case MODE::Translating:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditPosTransfrom(glm::vec3(0.0f, -0.2f, 0.0f));
						}
						break;
					case MODE::Scaling:
						for (unsigned int i = 0; i < chosenObjects.size(); i++) {
							chosenObjects[i]->EditScaleTransform(glm::vec3(0.9f, 0.9f, 0.9f));
						}
						break;
					}
					break;
				}
			}
		}
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		glClearStencil(0);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		DrawAxes();
		for (unsigned int i = 0; i < objects.size(); i++) {
			glStencilFunc(GL_ALWAYS, i + 1, -1);
			objects[i]->DrawStandart();
		}
		
		display.SwapBuffers();
		SDL_Delay(100);
	}

	return 0;
}




void DrawAxes() {
	std::vector<Vertex> vertices{
		Vertex(glm::vec3(0.0f,0.0f,-1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)),
		Vertex(glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
	};
	std::vector<unsigned int> indices{
		0, 1
	};
	Transform transform;
	float count = 10;
	transform.EditScale(glm::vec3(100, 100, 100));
	Shader shader("./res/basicShader");
	Mesh meshZ(vertices, 2, indices, 2);
	shader.Bind();
	shader.Update(transform, camera);
	meshZ.Draw(GL_LINES);
	vertices[0] = Vertex(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Mesh meshY(vertices, 2, indices, 2);
	meshY.Draw(GL_LINES);
	vertices[0] = Vertex(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Mesh meshX(vertices, 2, indices, 2);
	meshX.Draw(GL_LINES);
}

void getInfoPyramid(float& height, float& halfDiagonal) {
	std::cout << "Enter height of pyramid\n";
	std::cin >> height;
	std::cout << "Enter half of diagonal of square of  pyramid\n";
	std::cin >> halfDiagonal;
}

void getInfoCone(float& bottomRadius, float& topRadius, float& coneHeight) {
	std::cout << "Enter radius of bottom circle for this cone\n";
	std::cin >> bottomRadius;
	std::cout << "Enter radius of top circle for this cone\n";
	std::cin >> topRadius;
	std::cout << "Enter height of this cone\n";
	std::cin >> coneHeight;
}