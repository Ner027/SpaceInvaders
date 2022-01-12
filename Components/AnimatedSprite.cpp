#include "AnimatedSprite.h"

void AnimatedSprite::execute(char curTick)
{
    if (!frames.contains(curTick))
        return;
    if (currentFrame == -1)
    {
        currentFrame = curTick;
        frames.find(curTick)->second.draw();
    }
    else
    {
        frames.find(currentFrame)->second.erase();
        frames.find(curTick)->second.draw();
        currentFrame = curTick;
    }

}

void AnimatedSprite::exitCleanly()
{
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.erase();
}

AnimatedSprite::AnimatedSprite(const map<char, Sprite> &frames)
{
    this->frames = frames;
}
