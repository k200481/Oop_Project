#pragma once

#include "textureManager.h"
#include "image.h"
#include "Vec2.h"
#include <vector>

// manages everything related to animation
class Animation
{
public:
	// keeping this class public because it makkes little sense to use "animation" for cases like the ninja being idle
	// one frame of animation
	class Frame {
	public:
		Frame(Graphics* graphics, LPCWSTR file, float scaling)
		{
			if (!texManager.initialize(graphics, file))
				throw GameError(gameErrorNS::FATAL_ERROR, "Unable to load texture");
			if(!image.initialize(graphics, 0, 0, 0, &texManager))
				throw GameError(gameErrorNS::FATAL_ERROR, "Unable to load image");
			
			image.setScale(scaling);
		}
		Frame(const Frame& other)
			:
			texManager(other.texManager),
			image(other.image)
		{
			// the address of the tex manager will change after it is copied
			image.setTextureManager(&texManager);
		}
		void Draw(const Vec2<float>& position) {
			// call the other guy, cuz I don't wanna type the same thing again
			Draw(position.x, position.y);
		}
		void Draw(float x, float y) {
			// set the sprite's position
			image.setX(x);
			image.setY(y);
			// draw it
			image.draw();
		}
	private:
		TextureManager texManager;
		Image image;
	};
public:
	// constructor loads all the images in given vector into the class
	Animation(Graphics* graphics, const std::vector<LPCWSTR>& files, float scaling, float frameHoldDuration = 0.1f);
	//
	Animation(float frameHoldDuration = 0.1f) 
		:
		frameHoldDuration(frameHoldDuration)
	{
	}
	void AddFrame(Graphics* graphics, LPCWSTR file, float scaling) {
		frames.push_back(Frame(graphics, file, scaling));
	}
	// moves to the next frome after given hold duration
	void Advance(float deltatime);
	// draw a frame on the given location
	void Draw(const Vec2<float>& position);
	void Draw(float x, float y);
private:
	// vector of frames
	std::vector<Frame> frames;
	// total time to hold the fame for
	const float frameHoldDuration;
	// time the current frame has already been held for
	float frameHeldFor = 0.0f;
	// index of the current frame being drawn
	int currentFrame = 0;
};

