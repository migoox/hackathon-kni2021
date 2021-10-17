#pragma once
#include <SFML/Graphics.hpp>

class Message
{
private:
	sf::Text m_Text;
	float m_Velocity = 50.0f;
	float m_AlphaVelocity = 210.0f;
	float m_CurrentAlpha = 0.0f;
public:
	Message() = delete;
	Message(const sf::Font& font);
	void Send(std::string message);
	void Update(float dTime);

	void Render(sf::RenderTarget& target);
};