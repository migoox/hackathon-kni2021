#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

enum class Direction { North, East, South, West };

class Map : public sf::Drawable, public sf::Transformable
{
private:

    sf::Vector2u m_MapSize;

    float m_CellSize;

    sf::VertexArray m_Vertices;
    sf::VertexArray m_VerticalLinesVertices;
    sf::VertexArray m_HorizontalLinesVertices;

    std::vector<bool> m_CurrentMapState;
    std::vector<bool> m_NextMapState;

    float m_FrameTime = 0.10f;
    float m_Timer = 0.0f;
    bool m_Grid = true;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // draw the vertex array
        target.draw(m_Vertices, states);
        if (m_Grid)
        {
            target.draw(m_VerticalLinesVertices, states);
            target.draw(m_HorizontalLinesVertices, states);
        }
    }

    void SetState(sf::Vector2u matrixPos, bool state);

    void UpdateGraphicalRepresentation();

public:
    Map() = delete;
    Map(int xMapSize, int yMapSize, float cellSize);

    void Redefine(int xMapSize, int yMapSize, float cellSize);

    void OneStepForward();

    void Update(float dTime);

    bool& Grid();

    void Clear();

    void SetStateOnPos(sf::Vector2f position, bool state);

    std::string LoadPreset(int id);

    void SavePreset(int id);

    void MoveLivingCells(Direction direction);
};