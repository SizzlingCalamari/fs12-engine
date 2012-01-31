#pragma once

#include <vector>

class Animation;

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void AddAnimation(Animation* animation);
	void RemoveAnimation(int animationID);
private:
	std::vector<Animation*> animationList;
};