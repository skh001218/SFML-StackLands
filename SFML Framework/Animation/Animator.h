#pragma once
#include "AnimationClip.h"

class Animator
{
protected:
	AnimationClip* currentClip;
	sf::Sprite* sprite;

	bool isPlaying = false;
	int currentFrame = 0;
	int totalFrame = 0;
	int checkFrame;

	float frameDuration = 0.f;

	float accumTime = 0.f;

	float speed = 1.f;

public:
	Animator() = default;
	~Animator() = default;

	void SetSpeed(float speed);

	void SetTarget(sf::Sprite* target) { sprite = target; }

	void Update(float dt);

	bool IsPlaying() const { return false; }

	void Play(const std::string& clipId);
	void Play(AnimationClip* clip);
	void Stop();

	//void Pause(bool pause);

	void SetFrame(const AnimationFrame& frame);

	const std::string& GetCurrentClipId() const
	{
		if (currentClip == nullptr)
			return "";
		return currentClip->id;
	}
};

