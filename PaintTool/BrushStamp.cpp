#include "Layer.h"
#include "BrushStamp.h"

BrushStamp::BrushStamp() : sprite(0), texture(0)
{
}

BrushStamp::~BrushStamp()
{
    delete sprite;
    delete texture;
}

void BrushStamp::LoadFromFile(std::string path)
{
    if (sprite)
    {
        delete sprite;
        delete texture;
    }
    texture = new sf::Texture();
    if (!texture->loadFromFile(path))
    {
        sprite = 0;
        texture = 0;
    }
    else
    {
        sprite = new sf::Sprite(*texture);
    }
}

const sf::Texture& BrushStamp::GetTexture() const
{
    return *texture;
}

bool BrushStamp::HasSprite() const
{
    return sprite;
}

void BrushStamp::MouseDown(const sf::Vector2f& position, Layer& layer)
{
    if (!sprite)
    {
        return;
    }
    float scale = size / fmaxf(texture->getSize().x, texture->getSize().y);
    sprite->setScale(sf::Vector2f(scale, scale));
    sprite->setPosition(position);
    layer.draw(*sprite);
}

Layer* BrushStamp::Update(const sf::Vector2f& position, Layer& layer)
{
    return nullptr;
}

Layer* BrushStamp::MouseUp(const sf::Vector2f& position, Layer& layer)
{
    return nullptr;
}
