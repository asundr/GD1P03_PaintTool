#include "SFML/Graphics.hpp"
#include <vector>

#include "Canvas.h"
#include "Layer.h"
#include "InputManager.h"

#include "Brush.h"
#include "BrushMove.h"
#include "BrushLine.h"
#include "BrushPencil.h"
#include "BrushBox.h"
#include "BrushEllipse.h"
#include "BrushFill.h"
#include "BrushPolygon.h"

#include <iostream>
#include "CHelperClass.h"

/*
Requirements:
    !Lines, !Boxes, !Ellipses, +polygons, +stamp, !fill
    Menu options for: color, width, brush, +save, +load, (layers), (rotate), (crop)
    ! Rezising windows doesn't affect canvas
    (cursor)
Extras
    Save & laod
    draw poly
    bitmap stamps for paiting
    standard colour dialogue
        Add these options to the menu
A++
    + Camera: Zoom, pan
    Fill brush
    Layers: move, scale, rotate, show/hide w/ menu
    Rotate and crop caanvas
    Cursor
*/

void Resize(sf::RenderWindow& window, sf::Event& event);
void IncrementZoomLevel(int delta);
void DrawRenderTexture(sf::RenderWindow& window, sf::RenderTexture& texture);
void UpdateZoom(sf::RenderWindow& window, int prevZoomLevel);
void UpdatePanX(sf::RenderWindow& window, float direction);
void UpdatePanY(sf::RenderWindow& window, float direction);
sf::Vector2f MousePosition(sf::RenderWindow& window);

void InitializeUI();
void UpdateUI(sf::RenderWindow& window);

void RenderWindow(sf::RenderWindow& window, Canvas* canvas, std::vector<Layer*>* layers);

void BatchCards(Canvas& canvas, std::vector<Layer*>& layers);

int zoomLevel = 0; //TODO Add to camera obj
std::vector<sf::Shape*> uiElementVector;    //TODO Move to UI class

int main()
{
    //unsigned int width = 1000, height = 1000;     //TODO Reset
    unsigned int width = 823, height = 1180;
    unsigned int focusLayer = 1;
    std::vector<Layer*>* layers = new std::vector<Layer*>();
    std::vector<Layer*> uiLayers;

    sf::RenderWindow window(sf::VideoMode(width, height), "Paint Tool"); //, sf::Style::Fullscreen);
    //sf::Texture texture;
    //if (!texture.loadFromFile("C:\\users\\user\\downloads\\image.png"))       // Delete these lines
    //{
    //    std::cout << "Could not load textre image.png\n";
    //}
    
    Canvas* canvas = new Canvas(width, height);

    //BatchCards(*canvas, *layers);
    //RenderWindow(window, canvas, layers);
    //return 0;
    /////////////////////////////////////////  Acual program loop below here

    layers->push_back(new Layer(*canvas, "C:\\users\\user\\downloads\\image.png"));   // guts
    

    //Layer* drawLayer = new Layer(*canvas);
    layers->push_back(new Layer(*canvas));

    sf::CircleShape* circle = new sf::CircleShape(10);
    circle->setFillColor(sf::Color::Green);

    Brush* brush;
    Brush* pencil = new BrushPencil();
    Brush* grab = new BrushMove();
    Brush* line = new BrushLine();
    Brush* box = new BrushBox();
    Brush* ellipse = new BrushEllipse();
    Brush* polygon = new BrushPolygon();
    Brush* fill = new BrushFill();
    brush = ellipse;

    CHelperClass winHelper;
    InitializeUI();

    Layer* brushUI = nullptr;
    while (window.isOpen())
    {
        sf::Event event;
        InputManager::UpdateState(event);
        bool windowUpdate = false;
        while (window.pollEvent(event))
        {
            Layer* drawLayer = layers->at(focusLayer);
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            if (event.type == sf::Event::Resized)
            {
                Resize(window, event);
                //UpdateUI(window);
            }
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
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                //drawLayer->draw(*circle);
                if (window.hasFocus())
                {
                    if (uiElementVector[0]->getGlobalBounds().contains(MousePosition(window)))
                    {
                        std::string loadName = (std::string)winHelper.LoadFile();
                        if (loadName.length() != 0)
                        {
                            if (loadName.find_last_of('.') == -1)
                            {
                                loadName += ".png";
                            }
                            Layer* img = new Layer(*canvas, (const std::string)loadName);
                            layers->push_back(img);
                        }
                    }
                    else
                    {
                        brush->MouseDown(MousePosition(window), *layers->at(focusLayer));
                    }
                }
                UpdateUI(window);
                windowUpdate = true;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                brush->MouseUp(MousePosition(window), *layers->at(focusLayer));
                windowUpdate = true;
                brushUI = 0;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                float speed = InputManager::ShiftPressed() ? 10.f : 1.f;
                if (event.key.code == sf::Keyboard::Right)
                {
                    drawLayer->move(sf::Vector2f(speed, 0.0f));
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    drawLayer->move(sf::Vector2f(-speed, 0.0f));
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    focusLayer = (focusLayer + 1) % layers->size();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    focusLayer = (focusLayer - 1) % layers->size();
                }
                else if (event.key.code == sf::Keyboard::S && InputManager::ControlPressed())
                {
                    std::string saveName = (std::string)winHelper.SaveFile();
                    if (saveName.length() != 0)
                    {
                        if (saveName.find_last_of('.') == -1)
                        {
                            saveName += ".png";
                        }
                        canvas->Save(*layers,  saveName);
                    }
                    //canvas->Save(*layers, "C:\\users\\user\\downloads\\canvas_test.png");
                }
                else
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Num1:
                        brush = grab; break;
                    case sf::Keyboard::Num2:
                        brush = pencil; break;
                    case sf::Keyboard::Num3:
                        brush = line; break;
                    case sf::Keyboard::Num4:
                        brush = box; break;
                    case sf::Keyboard::Num5:
                        brush = ellipse; break;
                    case sf::Keyboard::Num6:
                        brush = polygon; break;
                    case sf::Keyboard::Num7:
                        brush = fill; break;
                    }
                }
            }


            if (InputManager::MouseLeftPressed())
            {
                brushUI = brush->Update(MousePosition(window), *layers->at(focusLayer));
                windowUpdate = true;
            }
        }

        

        circle->setPosition(MousePosition(window));
        canvas->RenderTexture()->clear();
        canvas->RenderTexture()->draw(*canvas->Sprite());
        //if (windowUpdate)
        //{
            for (Layer* l : *layers)
            {
                canvas->RenderTexture()->draw(*l);
            }
            if (brushUI)
                canvas->RenderTexture()->draw(*brushUI);
            //brushUI = nullptr;
            
            //for (int i = uiLayers.size() - 1; i >= 0; --i)
            //{
            //    canvas->RenderTexture()->draw(*uiLayers[i]);
            //}
            uiLayers.clear();
            window.clear();
            DrawRenderTexture(window, *canvas->RenderTexture());
            for (auto shape : uiElementVector)
            {
                window.draw(*shape);
            }
            window.draw(*circle);
            window.display();
        //}

    }

    for (Layer* l : *layers)
    {
        delete l;
    }
    delete layers;



    return 0;
}

void InitializeUI() //TODO add to UI class
{
    sf::RectangleShape* exampleButton = new sf::RectangleShape();
    exampleButton->setSize(sf::Vector2f(50, 30));
    exampleButton->setFillColor(sf::Color::Red);
    uiElementVector.push_back(exampleButton);

    sf::RectangleShape* saveButton = new sf::RectangleShape();
    saveButton->setSize(sf::Vector2f(50, 30));
    saveButton->setPosition(sf::Vector2f(60, 0));
    saveButton->setFillColor(sf::Color::Green);
    uiElementVector.push_back(saveButton);

    sf::RectangleShape* loadButton = new sf::RectangleShape();
    loadButton->setSize(sf::Vector2f(50, 30));
    loadButton->setPosition(sf::Vector2f(120, 0));
    loadButton->setFillColor(sf::Color::Blue);
    uiElementVector.push_back(loadButton);
}

void UpdateUI(sf::RenderWindow& window) //TODO add to UI class
{
    for (unsigned int i = 0; i < uiElementVector.size(); ++i)
    {
        if (uiElementVector[i]->getGlobalBounds().contains(MousePosition(window)))
        {
            //std::cout << "button pressed" << std::endl;
        }
    }
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

void UpdateZoom(sf::RenderWindow& window, int prevZoomLevel) // need to update mouse pos based on scale
{
    sf::View newView(window.getView());
    float prevZoom = fmax(0.1f, fmin(5.0f, 1.0f - prevZoomLevel / 10.0f));
    float fZoom = fmax(0.1f, fmin(5.0f, 1.0f - zoomLevel / 10.0f));
    //std::cout << zoomLevel
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
    //if (brushUI)
    //    canvas->RenderTexture()->draw(*brushUI);
    //brushUI = nullptr;
    //for (int i = uiLayers.size() - 1; i >= 0; --i)
    //{
    //    canvas->RenderTexture()->draw(*uiLayers[i]);
    //}
    //uiLayers.clear();
    window.clear();
    DrawRenderTexture(window, *canvas->RenderTexture());
    //window.draw(*circle);
    window.display();
}

#include <fstream>
#include <sstream>
void BatchCards(Canvas& canvas, std::vector<Layer*>& layers)
{
    layers.push_back(new Layer(canvas, "C:\\users\\user\\downloads\\NorseGame\\card_blank.png"));
    Layer* textLayer = new Layer(canvas);
    layers.push_back(textLayer);

    std::vector<std::vector<std::string>> cards;
    std::vector<std::string> cardRow;
    std::string line, word;
    std::fstream file("C:\\users\\user\\downloads\\NorseGame\\cards_lok.csv", std::ios::in);
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

    unsigned int cardTotal = 1;
    for (unsigned int row = 1; row < cards.size(); ++row)
    {
        cardTotal += stoi(cards[row][6]);
    }
    std::cout << cardTotal << std::endl;
    int atlasRows = (int)std::min(7.f, floorf(sqrt((float)cardTotal)));
    int atlasCols = (int)ceilf(cardTotal / (float)atlasRows);
    sf::RenderTexture* rtAtlas = new sf::RenderTexture();
    rtAtlas->create(atlasCols * canvas.Width(), atlasRows * canvas.Height());

    int atlasIndex = 0;
    for (unsigned int row = 1; row < cards.size(); ++row)
    {
        sf::Color color = sf::Color::Black;
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("C:\\users\\user\\downloads\\NorseGame\\Norse.otf"))
        {
        }
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
        float paddingY = (60 - text.getLocalBounds().height) / 2;
        text.setPosition(230 + paddingX, 20 + paddingY);
        textLayer->draw(text);
        // value
        text.setString(cards[row][1]);
        text.setCharacterSize(40);
        paddingX = (350 - text.getLocalBounds().width) / 2;
        paddingY = (40 - text.getLocalBounds().height) / 2;
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
        //canvas.Save(layers, "C:\\users\\user\\downloads\\NorseGame\\cards\\" + cards[row][0] + ".png");
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
        textLayer = new Layer(canvas);
        layers.push_back(textLayer);
    }
    Layer* hidden = new Layer(canvas, "C:\\users\\user\\downloads\\NorseGame\\hidden.png");
    sf::Vector2f hiddenCoord((atlasIndex% atlasCols) * (float)canvas.Width(), atlasIndex / atlasCols * (float)canvas.Height());
    hidden->SetPosition(hiddenCoord);
    //hidden->UpdateRenderTexture();
    rtAtlas->draw(*hidden);

    rtAtlas->display();
    rtAtlas->getTexture().copyToImage().saveToFile("C:\\users\\user\\downloads\\NorseGame\\atlas.png");

    layers.pop_back();
    delete hidden;
    delete textLayer;
    delete rtAtlas;
    // combine
    
}
