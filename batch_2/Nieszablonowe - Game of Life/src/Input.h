#pragma once
#include <SFML/Graphics.hpp>

struct HotKeys
{
    bool SpaceClicked = false;
    bool SpacePressed = false;

    bool CClicked = false;
    bool CPressed = false;

    bool IClicked = false;
    bool IPressed = false;

    bool CtrlClicked = false;
    bool CtrlPressed = false;

    bool RArrowPressed = false;

    bool LArrowPressed = false;

    bool UArrowPressed = false;

    bool DArrowPressed = false;

    bool GClicked = false;
    bool GPressed = false;

    bool SClicked = false;
    bool SPressed = false;

    bool LClicked = false;
    bool LPressed = false;

    bool F1Clicked = false;
    bool F1Pressed = false;

    bool F2Clicked = false;
    bool F2Pressed = false;

    bool F3Clicked = false;
    bool F3Pressed = false;

    bool NumClicked[10] = { false, false, false, false, false, false, false, false, false };
    bool NumPressed[10] = { false, false, false, false, false, false, false, false, false };

    void PreUpdate()
    {
        RArrowPressed = false;

        LArrowPressed = false;

        UArrowPressed = false;

        DArrowPressed = false;
    }
    void EventUpdate(sf::Event &ev)
    {
        if (ev.type == sf::Event::KeyPressed)
        {
            LArrowPressed = ev.key.code == sf::Keyboard::Left;
            RArrowPressed = ev.key.code == sf::Keyboard::Right;
            UArrowPressed = ev.key.code == sf::Keyboard::Up;
            DArrowPressed = ev.key.code == sf::Keyboard::Down;
        }
    }
    void Update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            if (!SpacePressed)
                SpaceClicked = true;
            else
                SpaceClicked = false;
            SpacePressed = true;
        }
        else
        {
            SpaceClicked = false;
            SpacePressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            if (!CPressed)
                CClicked = true;
            else
                CClicked = false;
            CPressed = true;
        }
        else
        {
            CClicked = false;
            CPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        {
            if (!IPressed)
                IClicked = true;
            else
                IClicked = false;
            IPressed = true;
        }
        else
        {
            IClicked = false;
            IPressed = false;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            if (!CtrlPressed)
                CtrlClicked = true;
            else
                CtrlClicked = false;
            CtrlPressed = true;
        }
        else
        {
            CtrlClicked = false;
            CtrlPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            if (!GPressed)
                GClicked = true;
            else
                GClicked = false;
            GPressed = true;
        }
        else
        {
            GClicked = false;
            GPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            if (!LPressed)
                LClicked = true;
            else
                LClicked = false;
            LPressed = true;
        }
        else
        {
            LClicked = false;
            LPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (!SPressed)
                SClicked = true;
            else
                SClicked = false;
            SPressed = true;
        }
        else
        {
            SClicked = false;
            SPressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            if (!F1Pressed)
                F1Clicked = true;
            else
                F1Clicked = false;
            F1Pressed = true;
        }
        else
        {
            F1Clicked = false;
            F1Pressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        {
            if (!F2Pressed)
                F2Clicked = true;
            else
                F2Clicked = false;
            F2Pressed = true;
        }
        else
        {
            F2Clicked = false;
            F2Pressed = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
        {
            if (!F3Pressed)
                F3Clicked = true;
            else
                F3Clicked = false;
            F3Pressed = true;
        }
        else
        {
            F3Clicked = false;
            F3Pressed = false;
        }

        sf::Keyboard::Key nums[10] = {
            sf::Keyboard::Num0,
            sf::Keyboard::Num1,
            sf::Keyboard::Num2,
            sf::Keyboard::Num3,
            sf::Keyboard::Num4,
            sf::Keyboard::Num5,
            sf::Keyboard::Num6,
            sf::Keyboard::Num7,
            sf::Keyboard::Num8,
            sf::Keyboard::Num9,
        };

        for (int i = 0; i < 10; i++)
        {
            if (sf::Keyboard::isKeyPressed(nums[i]))
            {
                if (!NumPressed[i])
                    NumClicked[i] = true;
                else
                    NumClicked[i] = false;
                NumPressed[i] = true;
            }
            else
            {
                NumClicked[i] = false;
                NumPressed[i] = false;
            }
        }
    }
};

struct Mouse
{
    bool LeftMouseButtonPressed = false;
    bool LeftMouseButtonClicked = false;
    bool RightMouseButtonPressed = false;
    bool RightMouseButtonClicked = false;

    void Update()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!LeftMouseButtonPressed)
            {
                LeftMouseButtonClicked = true;
            }
            else
            {
                LeftMouseButtonClicked = false;
            }
            LeftMouseButtonPressed = true;
        }
        else
        {
            LeftMouseButtonPressed = false;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            if (!RightMouseButtonPressed)
            {
                RightMouseButtonClicked = true;
            }
            else
            {
                RightMouseButtonClicked = false;
            }
            RightMouseButtonPressed = true;
        }
        else
        {
            RightMouseButtonPressed = false;
        }
    }

    sf::Vector2f CurrentMousePosition(const sf::RenderWindow& window)
    {
        return window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }
};