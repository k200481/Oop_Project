#include "Animation.h"
#include <fstream>
Animation::Animation(Graphics* graphics, const std::vector<LPCWSTR>& files, float scaling, float frameHoldDuration)
	:
	frameHoldDuration(frameHoldDuration)
{
	for (const wchar_t* f : files) {
		frames.push_back(Frame(graphics, f, scaling));
	}
}

void Animation::Advance(float deltatime)
{
	frameHeldFor += deltatime;
	while (frameHeldFor >= frameHoldDuration) {
		frameHeldFor -= frameHoldDuration;
		currentFrame++;
		if (currentFrame >= frames.size()) {
			currentFrame = 0;
		}
	}
}

void Animation::Draw(const Vec2<float>& position)
{
	frames[currentFrame].Draw(position);
}

void Animation::Draw(float x, float y)
{
	frames[currentFrame].Draw(x, y);
}
