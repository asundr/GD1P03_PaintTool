#include <queue>
#include "Layer.h"
#include "BrushFill.h"

void BrushFill::MouseDown(const sf::Vector2f& position, Layer& layer)
{
	int width = layer.GetSize().x, height = layer.GetSize().y;
	int x = (int)position.x, y = (int)position.y;
	sf::Image img = layer.CopyToImage();
	sf::Color targetColor = img.getPixel(x, y);
	if (img.getPixel(x, y) == color)
	{
		return;
	}

	// Checks a pixel to see if it's the fill colour. If not, sets color and checks neighbors
	// Could probably be made faster
	std::queue<std::pair<int, int>> queue;
	queue.push(std::pair<int, int>(x, y));
	while (!queue.empty())
	{
		unsigned int length = queue.size();
		for (unsigned int i = 0; i < length; ++i)
		{
			std::pair<int, int> curr = queue.front();
			queue.pop();
			if (curr.first < 0 || curr.first >= width || curr.second < 0 || curr.second >= height)
			{
				continue;
			}
			if (img.getPixel(curr.first, curr.second) != targetColor)
			{
				continue;
			}
			img.setPixel(curr.first, curr.second, color);
			queue.push(std::pair<int, int>(curr.first - 1, curr.second));
			queue.push(std::pair<int, int>(curr.first + 1, curr.second));
			queue.push(std::pair<int, int>(curr.first, curr.second - 1));
			queue.push(std::pair<int, int>(curr.first, curr.second + 1));
		}
	}
	sf::Texture tx;
	tx.create(width, height);
	tx.update(img.getPixelsPtr());
	sf::Sprite sp(tx);
	layer.draw(sp);
}

Layer* BrushFill::Update(const sf::Vector2f& position, Layer& layer)
{
    return nullptr;
}

Layer* BrushFill::MouseUp(const sf::Vector2f& position, Layer& layer)
{
	return nullptr;
}
