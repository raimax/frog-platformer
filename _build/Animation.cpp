#include "Animation.h"
#include <iostream>
#include "SpriteManager.h"

Animation::Animation(Texture2D sprite, int totalFrames, int framesSpeed)
{
    this->sprite = sprite;
    this->totalFrames = totalFrames;
    this->framesSpeed = framesSpeed;
}

void Animation::update()
{
    framesCounter++;

    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > totalFrames-1) currentFrame = 0;

        frameRec.x = (float)currentFrame * 16.0f;
    }
}

void Animation::play(GameObject* gameObject)
{
    update();
    DrawTexturePro(
        sprite,
        frameRec,
        *gameObject->getHitBox(),
        Vector2{ 0, 0 },
        0,
        WHITE);
}