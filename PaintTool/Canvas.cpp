#include "Layer.h"
#include "Canvas.h"

Canvas::Canvas(int width, int height) : width(width), height(height)
{
    // create bg texture
    const sf::Color grey = sf::Color(192, 192, 192);
    sf::Color* pixels = new sf::Color[4];
    texture = new sf::Texture();
    texture->create(2, 2);
    pixels[0] = grey;
    pixels[1] = sf::Color::White;
    pixels[2] = sf::Color::White;
    pixels[3] = grey;
    texture->update((sf::Uint8*)pixels);
    texture->setRepeated(true);
    sprite = new sf::Sprite(*texture);
    sprite->setScale(sf::Vector2f(10, 10)); // set scale inverse to zoom level (nvm?)
    sprite->setTextureRect(sf::IntRect(0, 0, (int)(width/10.f), (int)(height/10.f)));

    rTexture = new sf::RenderTexture();
    rTexture->create(width, height);
    delete[] pixels;
}

Canvas::~Canvas()
{
    delete rTexture;
    delete sprite;
    delete texture;
}

unsigned int Canvas::Width() const
{
    return width;
}

unsigned int Canvas::Height() const
{
    return height;
}

sf::RenderTexture* Canvas::RenderTexture()
{
    return rTexture;
}

sf::Sprite* Canvas::Sprite()
{
    return sprite;
}

void Canvas::Resize(int newWidth, int newHeight)
{
    //TODO
}

void Canvas::clear()
{
    rTexture->clear(sf::Color::Transparent);
}

void Canvas::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
    rTexture->draw(drawable, states);
    rTexture->display(); // prevents flipping on y
}

void Canvas::Save(const std::vector<Layer*>& layers, std::string path)
{
    sf::RenderTexture* printCanvas = new sf::RenderTexture();
    printCanvas->create(width, height);
    for (Layer* layer : layers)
    {
        printCanvas->draw(*layer);
    }
    printCanvas->display();
    printCanvas->getTexture().copyToImage().saveToFile(path);
    delete printCanvas;
}
