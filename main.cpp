#include <iostream>
#include <algorithm> 
#include <SDL/SDL.h>
#include "display.h"
#include "texture.h"
#include"Ray.h"
#include"object.h"

#include"sqlite3.h"

void DrawAxes();
void GetInfoCone(float& bottomRadius, float& topRadius, float& coneHeight);
void GetInfoPyramid(float& height, float& halfDiagonal);
void GetTablesData(sqlite3 *db, std::vector<Object*>& obj);
void AddTables(sqlite3* db, std::vector<Object*>& objects);

int main(int argc, char** argv)
{
	std::vector<Object *> objects;
	sqlite3 *db = 0; 

	if (sqlite3_open("database.dblite", &db))
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
	

	else {
		GetTablesData(db, objects);
	}
	sqlite3_close(db);
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Ray ray(camera);

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
			display.ChangeTitle("Enter s - to scale, r - to rotation, t - to translation, c - to change color, d - to delete elements");
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
				}
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_DELETE:
					for (int i = 0; i < objects.size(); i++) {
						delete objects[i];
					}
					objects.resize(0);
					chosenObjects.resize(0);
					break;
				case SDLK_d:
					if (mode == MODE::ChoosingEdit) {
						std::vector<Object*>::iterator it;
						for (int i = 0; i < chosenObjects.size(); i++) {
							it = std::find(objects.begin(), objects.end(), chosenObjects[i]);
							objects.erase(it);
						}
						for (int i = 0; i < chosenObjects.size(); i++) {
							delete chosenObjects[i];
						}
						chosenObjects.resize(0);
						mode = MODE::PickingObject;
					}
					break;
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(-2.0f, 1.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(0.0f, 2.0f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(2.0f, 0.5f, -2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(2.0f, -2.0f, 0.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(0.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
						GetInfoPyramid(height, halfDiagonal);
						obj = new Pyramid();
						obj->EditScaleTransform(glm::vec3(halfDiagonal, height, halfDiagonal));
						obj->EditPosTransfrom(glm::vec3(-2.0f, -2.5f, 2.0f));
						objects.push_back(obj);
						break;
					case MODE::DrawingCone:
						GetInfoCone(bottomRadius, topRadius, coneHeight);
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
	

	if (sqlite3_open("database.dblite", &db)) {
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
	}
	else {
		AddTables(db, objects);
	}
	sqlite3_close(db);
	return 0;
}


void AddTables(sqlite3* db, std::vector<Object*>& objects) {
	char *err = 0;
	const char* SQL1 = "CREATE TABLE IF NOT EXISTS pyramid(id INT,m00 REAL,m01 REAL,m02 REAL,m03 REAL,m10 REAL,m11 REAL,m12 REAL,m13 REAL,m20 REAL,m21 REAL,m22 REAL,m23 REAL,m30 REAL,m31 REAL,m32 REAL,m33 REAL,cs0 REAL,cs1 REAL,cs2 REAL,cs3 REAL,ct10 REAL,ct11 REAL,ct12 REAL,ct13 REAL,ct20 REAL,ct21 REAL,ct22 REAL,ct23 REAL,ct30 REAL,ct31 REAL,ct32 REAL,ct33 REAL,ct40 REAL,ct41 REAL,ct42REAL,ct43 REAL); DELETE FROM PYRAMID;";
	if (sqlite3_exec(db, SQL1, 0, 0, &err))
	{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
	}

	const char* SQL2 = "CREATE TABLE IF NOT EXISTS cone(id INT,m00 REAL,m01 REAL,m02 REAL,m03 REAL,m10 REAL,m11 REAL,m12 REAL,m13 REAL,m20 REAL,m21 REAL,m22 REAL,m23 REAL,m30 REAL,m31 REAL,m32 REAL,m33 REAL,cb0 REAL,cb1 REAL,cb2 REAL,cb3 REAL,ct0 REAL,ct1 REAL,ct2 REAL,ct3 REAL,cbd0 REAL,cbd1 REAL,cbd2 REAL,cbd3 REAL,delta REAL); DELETE FROM CONE;";
	if (sqlite3_exec(db, SQL2, 0, 0, &err))
	{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
	}

	for (unsigned int i = 0; i < objects.size(); i++) {
		std::string sql;
		if (objects[i]->IsPyramid()) {
			sql = "INSERT INTO PYRAMID VALUES(";
		}
		else {
			sql = "INSERT INTO CONE VALUES(";
		}
		sql += std::to_string(int(i));
		glm::mat4 Model = objects[i]->GetModel();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				sql += ", " + std::to_string(Model[i][j]);
			}
		std::vector<glm::vec4> colors = objects[i]->GetColors();
		for (int i = 0; i < colors.size(); i++) {
			for (int j = 0; j < 4; j++) {
				sql += ", " + std::to_string(colors[i][j]);
			}
		}
		if (!objects[i]->IsPyramid()) {
			float delta = objects[i]->GetDelta();
			sql += ", " + std::to_string(delta);
		}
		sql += ");";
		const char* SQL = sql.c_str();
		int result;
		sqlite3_stmt *statement;
		if (sqlite3_prepare(db, SQL, -1, &statement, 0) == SQLITE_OK) {
			int res = sqlite3_step(statement);
			result = res;
			sqlite3_finalize(statement);
		}
	}
}

void GetPyramidTableData(sqlite3 *db, std::vector<Object*>& objects)
{
	sqlite3_stmt *statement;

	char *query = "select * from pyramid";

	if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK)
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				glm::mat4 model;
				glm::vec4 colorSquare;
				glm::vec4 colorTr1;
				glm::vec4 colorTr2;
				glm::vec4 colorTr3;
				glm::vec4 colorTr4;


				for (int i = 1; i <= 16; i++) {
					model[(i - 1) / 4][(i - 1) % 4] = sqlite3_column_double(statement, i);
				}

				int counter = 0;
				for (int i = 17; i <= 20; i++) {
					colorSquare[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 21; i <= 24; i++) {
					colorTr1[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 25; i <= 28; i++) {
					colorTr2[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 29; i <= 32; i++) {
					colorTr3[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 33; i <= 36; i++) {
					colorTr4[counter] = sqlite3_column_double(statement, i);
					counter++;
				}

				Object* obj = new Pyramid(colorSquare, colorTr1, colorTr2, colorTr3, colorTr4);
				obj->SetSaved(true);
				obj->SetModel(model);
				objects.push_back(obj);
			}
			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				break;
			}
		}
	}
}


void GetConeTableData(sqlite3 *db, std::vector<Object*>& objects)
{
	sqlite3_stmt *statement;

	char *query = "select * from cone";

	if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK)
	{
		int ctotal = sqlite3_column_count(statement);
		int res = 0;

		while (1)
		{
			res = sqlite3_step(statement);

			if (res == SQLITE_ROW)
			{
				glm::mat4 model;
				glm::vec4 colorBottom;
				glm::vec4 colorTop;
				glm::vec4 colorBody;


				for (int i = 1; i <= 16; i++) {
					model[(i - 1) / 4][(i - 1) % 4] = sqlite3_column_double(statement, i);
				}

				int counter = 0;
				for (int i = 17; i <= 20; i++) {
					colorBottom[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 21; i <= 24; i++) {
					colorTop[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				counter = 0;
				for (int i = 25; i <= 28; i++) {
					colorBody[counter] = sqlite3_column_double(statement, i);
					counter++;
				}
				float delta = sqlite3_column_double(statement, 29);
				Object* obj = new Cone(delta, colorTop, colorBottom, colorBody);
				obj->SetSaved(true);
				obj->SetModel(model);
				objects.push_back(obj);
			}
			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				break;
			}
		}
	}
}

void GetTablesData(sqlite3* db, std::vector<Object*>& objects) {
	GetPyramidTableData(db, objects);
	GetConeTableData(db, objects);
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

void GetInfoPyramid(float& height, float& halfDiagonal) {
	std::cout << "Enter height of pyramid\n";
	std::cin >> height;
	std::cout << "Enter half of diagonal of square of  pyramid\n";
	std::cin >> halfDiagonal;
}

void GetInfoCone(float& bottomRadius, float& topRadius, float& coneHeight) {
	std::cout << "Enter radius of bottom circle for this cone\n";
	std::cin >> bottomRadius;
	std::cout << "Enter radius of top circle for this cone\n";
	std::cin >> topRadius;
	std::cout << "Enter height of this cone\n";
	std::cin >> coneHeight;
}