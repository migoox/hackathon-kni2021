#include "Message.h"
#include <iostream>
Message::Message(const sf::Font& font)
{

    m_Text.setFont(font);
    m_Text.setString("");
    m_Text.setCharacterSize(64);
    m_Text.setScale(0.5f, 0.5f);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setPosition(15.0f, 96.0f);
    m_CurrentAlpha = 0.0f;
}

void Message::Send(std::string message)
{
    m_Text.setString(message);
    m_Text.setFillColor(sf::Color::White);
    m_Text.setPosition(5.0f, 0.0f);
    m_CurrentAlpha = 255.0f;
}

void Message::Update(float dTime)
{
    if (m_CurrentAlpha - m_AlphaVelocity * dTime < 0.0f)
    {
        m_CurrentAlpha = 0.0f;
    }
    else
    {
        m_CurrentAlpha -= m_AlphaVelocity * dTime;
        m_Text.move(0.0f, m_Velocity * dTime);
    }

    m_Text.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, m_CurrentAlpha));
}

void Message::Render(sf::RenderTarget& target)
{
    target.draw(m_Text);
}
