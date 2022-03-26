#pragma once

#include "SFML/Graphics.hpp"

class EllipseShape : public sf::Shape
{
private:
	unsigned int pointCount;
	sf::Vector2f radius; 
public:
	EllipseShape();
	~EllipseShape();
	void setRadius(const sf::Vector2f radius);
	sf::Vector2f getRadius() const;
	// Inherited via Shape
	virtual std::size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(std::size_t index) const override;
};
