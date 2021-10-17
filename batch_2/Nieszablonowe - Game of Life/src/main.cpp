#include "Input.h"
#include "Map.h"
#include "Message.h"

enum class GameState { Info, Drawing, Game };
enum class MapSize { Small, Medium, Large };
int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game of life");
    bool windowFocus = true;

    srand(NULL);

    // font
    sf::Font font;
    if (!font.loadFromFile("pixel.ttf"))
    {
        std::cout << "Error: font cannot be loaded.\n";
    }

    // Text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("GAME OF LIFE");
    titleText.setCharacterSize(256);
    titleText.setScale(0.5f, 0.5f);
    titleText.setFillColor(sf::Color(255.f, 80.f, 80.f));
    titleText.setOrigin(titleText.getLocalBounds().width / 2.0f,
        titleText.getLocalBounds().height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, titleText.getLocalBounds().height / 2.0f - 20.0f);

    sf::Text hotkeysText;
    hotkeysText.setFont(font);
    hotkeysText.setString("All modes:\n  [Spacebar] - switches between drawing and game state\n  [I] - returns to info panel\n  [C] - clears entire world\n  [G] - grid on/off\n\nDrawing mode:\n  [Ctrl + RArrow] - one step in game forward\n  [Arrows] - move all living cells\n  [LMB] - draw\n  [RMB] - erase\n  [1, 2, 3] + L - load prebuilt preset\n  [4, 5, 6, 7, 8, 9, 0] + L - load your preset\n  [4, 5, 6, 7, 8, 9, 0] + S - save preset\n  [F1, F2, F3] - map size");

    hotkeysText.setCharacterSize(64);
    hotkeysText.setScale(0.5f, 0.5f);
    hotkeysText.setFillColor(sf::Color::White);
    hotkeysText.setPosition(50.0f, titleText.getPosition().y + 150.0f);

    sf::Text stateText;
    stateText.setFont(font);
    stateText.setString("");
    stateText.setCharacterSize(48);
    stateText.setScale(0.5f, 0.5f);
    stateText.setFillColor(sf::Color(255.f, 80.f, 80.f));
    stateText.setOrigin(0.0f, 0.0f);
    stateText.setPosition(5.0f, 800.0f - 35.0f);
    
    sf::Text startText;
    startText.setFont(font);
    startText.setString("Press spacebar to leave info panel");
    startText.setCharacterSize(64);
    startText.setScale(0.5f, 0.5f);
    startText.setFillColor(sf::Color(255.f, 80.f, 80.f));
    startText.setOrigin(startText.getLocalBounds().width / 2.0f, startText.getLocalBounds().height / 2.0f);
    startText.setPosition(window.getSize().x / 2.0f, window.getSize().y - 70.0f);

    // message class
    Message msg(font);

    // variables
    GameState currentGameState = GameState::Info;
    MapSize currentMapSize = MapSize::Medium;
    Map map(100, 100, 8.0f);
    Mouse mouse;
    HotKeys hotKeys;

    float dTime = 0.0f;
    sf::Clock clock;

    // game loop
    while (window.isOpen())
    {
        // Event update
        sf::Event event;
        hotKeys.PreUpdate();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::GainedFocus)
                windowFocus = true;
            if (event.type == sf::Event::LostFocus)
                windowFocus = false;

            hotKeys.EventUpdate(event);
        }

        if (!windowFocus)
        {
            clock.restart();
            dTime = 0.0f;
            continue;
        }

        mouse.Update();
        hotKeys.Update();
        // Update
        if (currentGameState == GameState::Info)
        {
            if (hotKeys.SpaceClicked)
                currentGameState = GameState::Drawing;

            stateText.setString("");
        }
        else if (currentGameState == GameState::Drawing)
        {
            if (hotKeys.SpaceClicked)
            {
                currentGameState = GameState::Game;
            }
            if (hotKeys.CClicked)
            {
                map.Clear();
                msg.Send("Cleared");
            }
            if (hotKeys.IClicked)
            {
                currentGameState = GameState::Info;
            }
            if (hotKeys.GClicked)
            {
                map.Grid() = !map.Grid();
                if (currentMapSize == MapSize::Large)
                {
                    map.Grid() = false;
                    msg.Send("Grid is unavailable when map is large");
                    continue;
                }

                if (map.Grid())
                    msg.Send("Grid on");
                else
                    msg.Send("Grid off");
            }
            if (hotKeys.CtrlPressed)
            {
                if (hotKeys.RArrowPressed)
                {
                    map.OneStepForward();
                    msg.Send("Step forward");
                }
            }
            else
            {
                if (hotKeys.UArrowPressed)
                {
                    map.MoveLivingCells(Direction::North);
                }
                else if (hotKeys.RArrowPressed)
                {
                    map.MoveLivingCells(Direction::East);
                }
                else if (hotKeys.DArrowPressed)
                {
                    map.MoveLivingCells(Direction::South);
                }
                else if (hotKeys.LArrowPressed)
                {
                    map.MoveLivingCells(Direction::West);
                }
            }

            for (int i = 0; i < 10; i++)
            {
                // save on given slot
                if (hotKeys.SPressed)
                {
                    if (hotKeys.NumClicked[i])
                    {
                        if (i <= 3 && i > 0)
                        {
                            msg.Send("Slot is reserved for prebuilt preset!");
                        }
                        else
                        {
                            map.SavePreset(i);
                            msg.Send("Saved: Preset " + std::to_string(i));
                        }
                    }
                }
                // load
                else if (hotKeys.LPressed)
                {
                    if (hotKeys.NumClicked[i])
                    {
                        msg.Send(map.LoadPreset(i));
                    }
                }
            }

            if (hotKeys.F1Clicked)
            {
                map.Redefine(50, 50, 16.0f);
                currentMapSize = MapSize::Small;
                msg.Send("Size: small");
            }
            else if (hotKeys.F2Clicked)
            {
                map.Redefine(100, 100, 8.0f);
                currentMapSize = MapSize::Medium;
                msg.Send("Size: medium");

            }
            else if (hotKeys.F3Clicked)
            {
                map.Redefine(400, 400, 2.0f);
                currentMapSize = MapSize::Large;
                map.Grid() = false;
                msg.Send("Size: large");
            }

            if (mouse.LeftMouseButtonPressed)
            {
                map.SetStateOnPos(mouse.CurrentMousePosition(window), true);
            }
            if (mouse.RightMouseButtonPressed)
            {
                map.SetStateOnPos(mouse.CurrentMousePosition(window), false);
            }

            stateText.setString("Game is paused(drawing mode)");
        }
        else
        {
            if (hotKeys.SpaceClicked)
            {
                currentGameState = GameState::Drawing;
            }
            if (hotKeys.CClicked)
            {
                map.Clear();
                msg.Send("Cleared");
            }
            if (hotKeys.IClicked)
            {
                currentGameState = GameState::Info;
            }
            if (hotKeys.GClicked)
            {
                map.Grid() = !map.Grid();
                if (currentMapSize == MapSize::Large)
                {
                    map.Grid() = false;
                    msg.Send("Grid is unavailable when map is large");
                    continue;
                }

                if (map.Grid())
                    msg.Send("Grid on");
                else
                    msg.Send("Grid off");
            }

            stateText.setString("Game is runnig");
            map.Update(dTime);
        }

        msg.Update(dTime);

        // Rendering
        window.clear();

        if (currentGameState == GameState::Info)
        {
            window.draw(titleText);
            window.draw(hotkeysText);
            window.draw(startText);
        }
        else if (currentGameState == GameState::Drawing)
        {
            window.draw(map);
            window.draw(stateText);
            msg.Render(window);
        }
        else
        {
            window.draw(map);
            window.draw(stateText);
            msg.Render(window);
        }

        window.display();

        dTime = clock.restart().asSeconds();
    }

    return 0;
}