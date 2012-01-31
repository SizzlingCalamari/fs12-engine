#pragma once

#include <vector>

class BaseInterface;
class SpawnPoint;
class Trigger;
class Emitter;

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	void UpdateObjects(float dt);
	void RenderObjects();
	void AddObject(BaseInterface* object);
	void RemoveAllObjects();
	void CheckCollision();
	void AddSpawn(SpawnPoint* spawn);
	void RemoveSpawn(SpawnPoint* spawn);
	void RemoveAllSpawns();
	void AddTrigger(Trigger* trigger);
	void RemoveTrigger(Trigger* trigger);
	void RemoveAllTriggers();
	void AddEmitter(Emitter* emitter);
	void RemoveEmitter(Emitter* emitter);
	void RemoveAllEmitters();

private:
	std::vector<BaseInterface*> objectList;
	std::vector<SpawnPoint*> spawnList;
	std::vector<Trigger*> triggerList;
	std::vector<Emitter*> emitterList;
};