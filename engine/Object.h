/*
Copyright (C) 2018 Dimitri Lozovoy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef FATELESS_OBJECT_H
#define FATELESS_OBJECT_H

#include <string>
#include "../thirdparty/glm/glm.hpp"
#include "Shape.h"
#include "Model2.h"
#include "FileIO.h"

typedef enum
{
	OBJTYPE_SPRITE,
	OBJTYPE_SHAPE,
	OBJTYPE_MODEL,
	OBJTYPE_HUMANOID,
    NUM_OBJTYPES
} ObjType;

class Object: FileIO
{
public:
	void setDeltaXZ(float heading, float vel);
	void setDeltaXYZ(float heading, float pitch, float vel);
	void move();
	void MoveBackward(float factor = 1.00);
	void MoveForward(float factor = 1.00);
	void MoveLeft(float factor = 1.00);
	void MoveRight(float factor = 1.00);
	void MoveUp(float factor = 1.00);
	void MoveDown(float factor = 1.00);
	void MoveYaw(float amount);
	void MovePitch(float amount);
	void MoveRoll(float amount);
	float distanceTo(Object *other);
	float getYawTo(Object *other);
	float getPitchTo(Object *other);
	void moveByVelocity();
	void capVelocity();
	void moveTowardsNextPosition();
	std::string toString();
	void save(FILE *f);
	void load(FILE *f);
	bool checkCollision(Object *other, float multiplier);
	bool checkVoxelCollision(Object *voxelObj, float multiplier);
	bool checkVoxelCollisionCircular(Object *voxObj, float multiplier);
	void worldToVoxelCoords(Object *voxObj, float wx, float wy, float wz, int &x, int &y, int &z);

    std::string name;
    ObjType type;
    ObjShapeType shapeType;
    Shape *shape = nullptr;
	std::string shapeName; // For saving and loading states
	Model2 *model = nullptr;
	std::string modelName; // For saving and loading states
	Mesh *batchedMesh = nullptr;
	bool mainOfBatch = false;
	bool partOfBatch = false;
	glm::vec4 color;
    std::string textureName;
    float size;
	glm::vec3 scale;
    glm::vec4 position;
	glm::vec4 nextPosition;
	glm::vec4 delta;
	glm::vec4 velocity = glm::vec4(0.0, 0.0, 0.0, 0.0);
	float maxVelocity = 4.0;
    float yaw = 0.1;
	float pitch = 0;
	float roll = 0;
	float secondaryYaw = 0.1;
	int secondaryYawMesh = -1;
    int glTexID = -1;
	const float moveDistance = 1.0;
	bool moveSmoothly = false;
	float fadeNearDistance = 600;
	float fadeFarDistance = 900;
	bool alwaysFacePlayer = false;
	bool isPartOfVehicle = false;
	bool mapTexture = false;
	int hitPoints = 0;
	bool fireTriggerOn = false;
	float speed = 0.0;

	glm::vec4 destination;

	bool visible = true;
	bool system = false;
	std::string category = "";

	glm::mat4 DepthMVP;

	bool operator<(const Object &rhs) const { return name < rhs.name; }
	
	std::map<std::string, int> ints;
	std::map<std::string, std::string> strings;
	std::map<std::string, float> floats;

	std::vector<Object *> nearCollisions;
	glm::vec3 physSize = glm::vec3(0.0, 0.0, 0.0);

	bool collNorth = false;
	bool collEast = false;
	bool collSouth = false;
	bool collWest = false;

	bool lastCollNorth = false;
	bool lastCollEast = false;
	bool lastCollSouth = false;
	bool lastCollWest = false;
};

#endif //FATELESS_OBJECT_H
