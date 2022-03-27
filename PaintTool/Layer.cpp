#include "Canvas.h"
#include "Layer.h"

Layer::Layer(unsigned int width, unsigned int height) : hidden(0)
{
	rTexture = new sf::RenderTexture();
	rTexture->create(width, height);
	sprite = new sf::Sprite(rTexture->getTexture());
}

Layer::Layer(Canvas& canvas) : Layer(canvas.Width(), canvas.Height())
{
}

// Create layer from image file
Layer::Layer(Canvas& canvas, const std::string path) : hidden(0)
{
	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(path))
	{
		sprite = 0;
		rTexture = 0;
		return;
	}
	rTexture = new sf::RenderTexture();
	sprite = new sf::Sprite(*texture);
	sf::Vector2u size = sf::Vector2u(std::max(texture->getSize().x, canvas.Width()), std::max(texture->getSize().y, canvas.Height()));
	rTexture->create(size.x, size.y);
	rTexture->draw(*sprite);
	delete sprite;
	sprite = new sf::Sprite(rTexture->getTexture());
	rTexture->display();
	delete texture;
}

Layer::~Layer()
{
	delete rTexture;
	delete sprite;
}

const sf::Vector2f& Layer::GetPosition() const
{
	return sprite->getPosition();
}

sf::Vector2u Layer::GetSize() const
{
	return rTexture->getSize();
}

const sf::Image Layer::CopyToImage() const
{
	return rTexture->getTexture().copyToImage();
}

const sf::Texture& Layer::GetTexture() const
{
	return rTexture->getTexture();
}

void Layer::SetHidden(bool hidden)
{
	this->hidden = hidden;
}

void Layer::move(const sf::Vector2f& offset)
{
	sprite->move(offset);
	UpdateRenderTexture();
}

void Layer::SetPosition(const sf::Vector2f& position)
{
	sprite->setPosition(position);
	UpdateRenderTexture();
}

// Used to apply any changes made to to the layer to the RenderTexture
// Warning: Currently crops layers that are moved outside of the canvas
void Layer::UpdateRenderTexture()
{
	const sf::Vector2f& offset = sprite->getPosition();
	sf::RenderTexture* newRT = new sf::RenderTexture();
	newRT->create(rTexture->getSize().x, rTexture->getSize().y);
	newRT->draw(*sprite);
	sprite->setPosition(sf::Vector2f(0.f, 0.f));
	delete rTexture;
	rTexture = newRT;
	rTexture->display();
	sprite->setTexture(rTexture->getTexture());
}

void Layer::Clear()
{
	rTexture->clear(sf::Color::Transparent);
}

void Layer::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	rTexture->draw(drawable, states);
	rTexture->display(); // prevents flipping on y
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (hidden)
		return;
	target.draw(*sprite, states);
}
