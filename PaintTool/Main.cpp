#include "SFML/Graphics.hpp"
#include <vector>
#include "Canvas.h"
#include "Layer.h"
#include "InputManager.h"
#include "Brush.h"
#include "ToolManager.h"

void BatchCards(); // Not part of assignment

void Resize(sf::RenderWindow& window, sf::Event& event);
void IncrementZoomLevel(int delta);
void DrawRenderTexture(sf::RenderWindow& window, sf::RenderTexture& texture);
void UpdateZoom(sf::RenderWindow& window, int prevZoomLevel);
void UpdatePanX(sf::RenderWindow& window, float direction);
void UpdatePanY(sf::RenderWindow& window, float direction);
sf::Vector2f MousePosition(sf::RenderWindow& window);
void RenderWindow(sf::RenderWindow& window, Canvas* canvas, std::vector<Layer*>* layers);
int zoomLevel = 0;

int main()
{
    //unsigned int width = 1080, height = 720;
    unsigned int width = 823, height = 1180;
    std::vector<Layer*>* layers = new std::vector<Layer*>();
    sf::RenderWindow window(sf::VideoMode(width, height), "NFT Generator");
    Canvas* canvas = new Canvas(width, height);

    BatchCards();
    RenderWindow(window, canvas, layers);
    return 0;
    /////////////////////////////////////////  Acual program loop below here

    ToolManager toolManager(canvas);
    toolManager.UpdateView(window);
    Brush* brush = &toolManager.GetCurrentBrush();
    
    layers->push_back(new Layer(*canvas));

    Layer* brushUI = nullptr;
    int focusLayer = layers->size()-1;
    while (window.isOpen())
    {
        sf::Event event;
        InputManager::UpdateState(event); // updates user input state
        bool windowUpdate = false;
        while (window.pollEvent(event))
        {
            Layer* drawLayer = layers->at(focusLayer); // active layer being edited
            brush = &toolManager.GetCurrentBrush();
            // Window close / resizing events
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            if (event.type == sf::Event::Resized)
            {
                Resize(window, event);
                toolManager.UpdateView(window);
                windowUpdate = true;
            }
            // Listen for menu events
            if (toolManager.IsInBounds(sf::Vector2f(sf::Mouse::getPosition(window))))
            {
                toolManager.HandleMenuEvent(event, *canvas, focusLayer, *layers, sf::Vector2f(sf::Mouse::getPosition(window)));
                windowUpdate = true;
                break;
            }
            // Mouse wheel events used to zoom and pan around the canvas
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (InputManager::ControlPressed())
                    {
                        int prevZoomLevel = zoomLevel;
                        IncrementZoomLevel((int)event.mouseWheelScroll.delta);
                        UpdateZoom(window, prevZoomLevel);
                    }
                    else if (InputManager::AltPressed())
                    {
                        UpdatePanX(window, event.mouseWheelScroll.delta);
                    }
                    else
                    {
                        UpdatePanY(window, event.mouseWheelScroll.delta);
                    }
                }
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                {
                    UpdatePanX(window, event.mouseWheelScroll.delta);
                }
                windowUpdate = true;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (window.hasFocus())
                {
                    // Tells the brush that he mouse has started clicking
                    brush->MouseDown(MousePosition(window), *layers->at(focusLayer));
                }
                windowUpdate = true; 
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                // Tells the brush the mouse is no longer clicking
                brushUI = brush->MouseUp(MousePosition(window), *layers->at(focusLayer));
                windowUpdate = true;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                toolManager.HandleKeyEvent(event, *canvas, *layers);
                windowUpdate = true;
            }

            // Update the brush between clicks
            if (InputManager::MouseLeftPressed() || brushUI)
            {
                brushUI = brush->Update(MousePosition(window), *layers->at(focusLayer));
                windowUpdate = true;
            }
        }

        // Draw to the window if changes have been made
        if (windowUpdate)
        {
            canvas->clear();
            canvas->draw(*canvas->Sprite());
            for (Layer* layer : *layers)
            {
                canvas->draw(*layer);
            }
            if (brushUI)
            {
                canvas->draw(*brushUI);
            }
            window.clear();
            DrawRenderTexture(window, *canvas->RenderTexture());
            toolManager.DisplayUI(window);
            window.display();
        }
    }

    for (Layer* l : *layers)
    {
        delete l;
    }
    delete layers;

    return 0;
}

void Resize(sf::RenderWindow& window, sf::Event& event)
{
    window.setSize(sf::Vector2u(event.size.width, event.size.height));
    sf::View view(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height));
    window.setView(view);
}

void IncrementZoomLevel(int delta)
{
    zoomLevel += delta * (InputManager::ShiftPressed() ? 3 : 1);
}

void DrawRenderTexture(sf::RenderWindow& window, sf::RenderTexture& texture)
{
    texture.display();
    sf::Sprite temp(texture.getTexture());
    window.draw(temp);
}

void UpdateZoom(sf::RenderWindow& window, int prevZoomLevel) 
{
    sf::View newView(window.getView());
    float prevZoom = fmax(0.1f, fmin(5.0f, 1.0f - prevZoomLevel / 10.0f));
    float fZoom = fmax(0.1f, fmin(5.0f, 1.0f - zoomLevel / 10.0f));
    newView.zoom(fZoom / prevZoom);
    window.setView(newView);
}

void UpdatePanX(sf::RenderWindow& window, float direction)
{
    sf::View newView(window.getView());
    float dx = direction * (InputManager::ShiftPressed() ? -100 : -10);
    newView.move(dx, 0);
    window.setView(newView);
}

void UpdatePanY(sf::RenderWindow& window, float direction)
{
    sf::View newView(window.getView());
    float dy = direction * (InputManager::ShiftPressed() ? -100 : -10);
    newView.move(0, dy);
    window.setView(newView);
}

sf::Vector2f MousePosition(sf::RenderWindow& window)
{
    sf::Vector2i base = sf::Mouse::getPosition(window);
    return window.mapPixelToCoords(base);
}

void RenderWindow(sf::RenderWindow& window, Canvas* canvas, std::vector<Layer*>* layers)
{
    canvas->RenderTexture()->clear();
    canvas->RenderTexture()->draw(*canvas->Sprite());
    for (Layer* l : *layers)
    {
        canvas->RenderTexture()->draw(*l);
    }
    window.clear();
    DrawRenderTexture(window, *canvas->RenderTexture());
    window.display();
}




///////////////////  Below code not part of assignment /////////////////////////////
// 
// Below code was hastily written to batch create cards for GD1J01BSE Game Design Principles
// 

struct Card
{
    std::string title;
    std::string value;
    std::string attack;
    std::string defense;
    std::string category;
    std::string type;
    std::string description;
    //int count = 0;
    std::string filename;
    Card(std::vector<std::string> line)
    {
        title = line[0];
        value = line[1];
        attack = line[2];
        defense = line[3];
        int slashIndex = line[4].find_first_of('/');
        category = line[4].substr(0, slashIndex);
        type = line[4].substr(slashIndex + 1, line[4].size());
        description = line[5];
        //count = stoi(line[6]);
        if (line.size() == 8)
            filename = line[7]; 
    }
    std::string GetFileName() const
    {
        if (filename.length())
            return filename;
        return category + '_' + type;
    }
    const std::string GetFilePath(std::string folderpath) const { return folderpath + GetFileName() + ".png"; }
};


#include <fstream>
#include <sstream>
#include <iostream>
void BatchCards()
{
    Canvas canvas(823, 1180);
    std::vector<Layer*> layers;

    std::string path = "C:\\users\\user\\downloads\\NorseGame\\";
    std::string sourceCardPath = path + "input\\";
    std::string outputCardPAth = path + "output\\";
    layers.push_back(new Layer(canvas, "C:\\users\\user\\downloads\\NorseGame\\card_blank.png"));
    //Layer* textLayer = new Layer(canvas);
    //layers.push_back(textLayer);

    std::vector<std::vector<std::string>> cards;
    std::vector<std::string> cardRow;
    std::string line, word;
    std::fstream file("C:\\users\\user\\downloads\\NorseGame\\cards_item.csv", std::ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.length() == 0)
                continue;
            cardRow.clear();
            std::stringstream str(line);
            while (getline(str, word, ','))
            {
                cardRow.push_back(word);
            }
            cards.push_back(cardRow);
        }
        file.close();
    }

    unsigned int cardTotal = 0;
    for (unsigned int row = 1; row < cards.size(); ++row)
    {
        cardTotal += stoi(cards[row][6]);
    }
    std::cout << cardTotal << std::endl;
    int atlasRows = (int)std::min(7.f, floorf(sqrt((float)cardTotal)));
    int atlasCols = (int)ceilf(cardTotal / (float)atlasRows);
    sf::RenderTexture* rtAtlas = new sf::RenderTexture();
    rtAtlas->create(atlasCols * canvas.Width(), atlasRows * canvas.Height());


    sf::Font font;
    if (!font.loadFromFile("C:\\users\\user\\downloads\\NorseGame\\Norse.otf"))
    {
    }

    int atlasIndex = 0;
    for (unsigned int row = 1; row < cards.size(); ++row)
    {
        sf::Color color = sf::Color::Black;
        sf::Text text;

        Card card(cards[row]);
        std::cout << card.GetFilePath(sourceCardPath) << std::endl;
        //continue;
        Layer* textLayer = new Layer(canvas, card.GetFilePath(sourceCardPath));
        //layers.push_back(new Layer(canvas, card.GetFilePath(sourceCardPath)));
        layers.push_back(textLayer);


        text.setFont(font);
        text.setFillColor(color);
        //title
        text.setString(cards[row][0]); //220 start, 350 width
        text.setCharacterSize(72);
        if (text.getLocalBounds().width > 350)
        {
            text.setCharacterSize(72 * 350 / (int)text.getLocalBounds().width);
        }
        float paddingX = (350 - text.getLocalBounds().width) / 2;
        float paddingY = (90 - text.getLocalBounds().height) / 2;
        text.setPosition(230 + paddingX, 20 + paddingY);
        textLayer->draw(text);
        // value
        text.setString(cards[row][1]);
        text.setCharacterSize(40);
        paddingX = (350 - text.getLocalBounds().width) / 2;
        paddingY = (70 - text.getLocalBounds().height) / 2;
        text.setPosition(230 + paddingX, 90 + paddingY);
        textLayer->draw(text);
        // attack
        text.setString("Atk\n " + cards[row][2]);
        text.setCharacterSize(50);
        paddingX = (40 - text.getLocalBounds().width) / 2;
        paddingY = (40 - text.getLocalBounds().height) / 2;
        text.setPosition(70 + paddingX, 90 + paddingY);
        textLayer->draw(text);
        // defense
        text.setString("Def\n   " + cards[row][3]);
        text.setCharacterSize(50);
        paddingX = (40 - text.getLocalBounds().width) / 2;
        paddingY = (40 - text.getLocalBounds().height) / 2;
        text.setPosition(700 + paddingX, 90 + paddingY);
        textLayer->draw(text);
        // type
        std::string type = cards[row][4];
        int slashIndex = type.find_first_of('/');
        type = type.substr(0, slashIndex) + "  /  " + type.substr(slashIndex + 1, type.size());
        text.setString(type);
        text.setCharacterSize(45);
        paddingX = (350 - text.getLocalBounds().width) / 2;
        paddingY = (30 - text.getLocalBounds().height) / 2;
        text.setPosition(240 + paddingX, 955 + paddingY);
        textLayer->draw(text);
        // description
        text.setCharacterSize(30);
        std::string description = "", descLine = "", word;
        std::stringstream ssDesc(cards[row][5]);
        while (getline(ssDesc, word, ' '))
        {
            descLine += word + " ";
            text.setString(descLine);
            if (text.getLocalBounds().width > 600)
            {
                description += descLine + '\n';
                descLine = "";
            }
        }
        if (descLine != "")
        {
            description += descLine;
        }
        else
        {
            description = description.substr(0, description.size()-1);
        }
        text.setString(description);
        paddingX = (620 - text.getLocalBounds().width) / 2;
        paddingY = (120 - text.getLocalBounds().height) / 2;
        text.setPosition(100 + paddingX, 1010);
        textLayer->draw(text);

        textLayer->UpdateRenderTexture();
        canvas.Save(layers, "C:\\users\\user\\downloads\\NorseGame\\output\\" + cards[row][0] + ".png");
        for (int i = 0; i < stoi(cards[row][6]); i++)
        {
            // save individual cards
            //canvas.Save(layers, "C:\\users\\user\\downloads\\NorseGame\\cards\\" + cards[row][0] + "_" + std::to_string(i) + ".png");
            // adding to atlas
            for (Layer* l : layers)
            {
                canvas.RenderTexture()->draw(*l);
            }
            canvas.RenderTexture()->display();
            sf::Sprite finCard(canvas.RenderTexture()->getTexture());
            finCard.setPosition((atlasIndex % atlasCols) * (float)canvas.Width(), atlasIndex / atlasCols * (float)canvas.Height());
            rtAtlas->draw(finCard);
           // rtAtlas->display();
            atlasIndex++;
        }
        layers.pop_back();
        delete textLayer;
        //textLayer = new Layer(canvas);
        //layers.push_back(textLayer);
    }
    //Layer* hidden = new Layer(canvas, "C:\\users\\user\\downloads\\NorseGame\\hidden.png");
    //sf::Sprite hiddenSprite(hidden->GetTexture());
    //sf::Vector2f hiddenCoord((atlasIndex% atlasCols) * (float)canvas.Width(), atlasIndex / atlasCols * (float)canvas.Height());
    //hiddenSprite.setPosition(hiddenCoord);
    //rtAtlas->draw(hiddenSprite);

    rtAtlas->display();
    rtAtlas->getTexture().copyToImage().saveToFile("C:\\users\\user\\downloads\\NorseGame\\atlas.png");

    layers.pop_back();
    //delete hidden;
    //delete textLayer;
    delete rtAtlas;
}
