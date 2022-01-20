#include "AnimatedSprite.h"
#include "../Managers/AssetManager.h"
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

void AnimatedSprite::moveBy(const Vector2 &df)
{
    for (auto& pair : frames)
        pair.second.moveBy(df);
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.draw();
}

void AnimatedSprite::moveTo(const Vector2 &nPos)
{
    for(auto& pair : frames)
        pair.second.moveTo(nPos);
    if (frames.contains(currentFrame))
        frames.find(currentFrame)->second.draw();
}

Vector2 AnimatedSprite::getSize()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second.getSize();
    return frames.find(currentFrame)->second.getSize();
}

Vector2 AnimatedSprite::getPosition()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second.getPosition();
    return frames.find(currentFrame)->second.getPosition();
}

Sprite AnimatedSprite::getCurrentSprite()
{
    if (!frames.contains(currentFrame))
        return frames.begin()->second;
    return frames.find(currentFrame)->second;
}

AnimatedSprite::AnimatedSprite(const string& name)
{
    this->frames = AssetManager::getInstance()->getAnimation(name);
}

