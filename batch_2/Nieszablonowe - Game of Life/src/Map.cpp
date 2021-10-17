#include "Map.h"

void Map::SetState(sf::Vector2u matrixPos, bool state)
{
    int currCell = matrixPos.x + matrixPos.y * m_MapSize.x;

    sf::Vertex* currQuad = &m_Vertices[currCell * 4];

    m_CurrentMapState[currCell] = state;

    if (m_CurrentMapState[currCell])
    {
        currQuad[0].color = sf::Color::White;
        currQuad[1].color = sf::Color::White;
        currQuad[2].color = sf::Color::White;
        currQuad[3].color = sf::Color::White;
    }
    else
    {
        currQuad[0].color = sf::Color::Black;
        currQuad[1].color = sf::Color::Black;
        currQuad[2].color = sf::Color::Black;
        currQuad[3].color = sf::Color::Black;
    }
}

void Map::UpdateGraphicalRepresentation()
{
    for (size_t y = 0; y < m_MapSize.y; y++)
    {
        for (size_t x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;

            sf::Vertex* currQuad = &m_Vertices[currCell * 4];

            if (m_CurrentMapState[currCell])
            {
                currQuad[0].color = sf::Color::White;
                currQuad[1].color = sf::Color::White;
                currQuad[2].color = sf::Color::White;
                currQuad[3].color = sf::Color::White;
            }
            else
            {
                currQuad[0].color = sf::Color::Black;
                currQuad[1].color = sf::Color::Black;
                currQuad[2].color = sf::Color::Black;
                currQuad[3].color = sf::Color::Black;
            }
        }
    }
}

Map::Map(int xMapSize, int yMapSize, float cellSize)
{
    m_MapSize.x = xMapSize;
    m_MapSize.y = yMapSize;
    m_CellSize = cellSize;

    m_CurrentMapState.resize(m_MapSize.x * m_MapSize.y);
    m_NextMapState.resize(m_MapSize.x * m_MapSize.y);

    m_Vertices.setPrimitiveType(sf::Quads);
    m_Vertices.resize(m_MapSize.x * m_MapSize.y * 4);

    m_VerticalLinesVertices.setPrimitiveType(sf::Lines);
    m_HorizontalLinesVertices.setPrimitiveType(sf::Lines);
    m_VerticalLinesVertices.resize((m_MapSize.x - 1) * 2);
    m_HorizontalLinesVertices.resize((m_MapSize.y - 1) * 2);

    // initialize all vectors and graphics
    for (int y = 0; y < m_MapSize.y; y++)
    {
        for (int x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;
            m_CurrentMapState[currCell] = false;
            m_NextMapState[currCell] = false;

            sf::Vertex* currQuad = &m_Vertices[currCell * 4];
            currQuad[0].position = sf::Vector2f(x * m_CellSize, y * m_CellSize);
            currQuad[1].position = sf::Vector2f((x + 1) * m_CellSize, y * m_CellSize);
            currQuad[2].position = sf::Vector2f((x + 1) * m_CellSize, (y + 1) * m_CellSize);
            currQuad[3].position = sf::Vector2f(x * m_CellSize, (y + 1) * m_CellSize);

            currQuad[0].color = sf::Color::Black;
            currQuad[1].color = sf::Color::Black;
            currQuad[2].color = sf::Color::Black;
            currQuad[3].color = sf::Color::Black;
        }
    }
    // initialize grid
    for (int y = 0; y < m_MapSize.y - 1; y++)
    {
        sf::Vertex* currLine = &m_HorizontalLinesVertices[y * 2];
        currLine[0].position = sf::Vector2f(0.0f, (y+1) * m_CellSize);
        currLine[1].position = sf::Vector2f(m_MapSize.x * m_CellSize, (y + 1) * m_CellSize);

        currLine[0].color = sf::Color(255.f, 255.f, 255.f, 20.f);
        currLine[1].color = sf::Color(255.f, 255.f, 255.f, 20.f);
    }

    for (int x = 0; x < m_MapSize.x - 1; x++)
    {
        sf::Vertex* currLine = &m_VerticalLinesVertices[x * 2];
        currLine[0].position = sf::Vector2f((x+1) * m_CellSize, 0.0f);
        currLine[1].position = sf::Vector2f((x + 1) * m_CellSize, m_MapSize.y * m_CellSize);

        currLine[0].color = sf::Color(255.f, 255.f, 255.f, 20.f);
        currLine[1].color = sf::Color(255.f, 255.f, 255.f, 20.f);
    }
}

void Map::Redefine(int xMapSize, int yMapSize, float cellSize)
{
    m_MapSize.x = xMapSize;
    m_MapSize.y = yMapSize;
    m_CellSize = cellSize;

    m_CurrentMapState.resize(m_MapSize.x * m_MapSize.y);
    m_NextMapState.resize(m_MapSize.x * m_MapSize.y);

    m_Vertices.setPrimitiveType(sf::Quads);
    m_Vertices.resize(m_MapSize.x * m_MapSize.y * 4);

    m_VerticalLinesVertices.setPrimitiveType(sf::Lines);
    m_HorizontalLinesVertices.setPrimitiveType(sf::Lines);
    m_VerticalLinesVertices.resize((m_MapSize.x - 1) * 2);
    m_HorizontalLinesVertices.resize((m_MapSize.y - 1) * 2);

    // initialize all vectors and graphics
    for (int y = 0; y < m_MapSize.y; y++)
    {
        for (int x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;
            m_CurrentMapState[currCell] = false;
            m_NextMapState[currCell] = false;

            sf::Vertex* currQuad = &m_Vertices[currCell * 4];
            currQuad[0].position = sf::Vector2f(x * m_CellSize, y * m_CellSize);
            currQuad[1].position = sf::Vector2f((x + 1) * m_CellSize, y * m_CellSize);
            currQuad[2].position = sf::Vector2f((x + 1) * m_CellSize, (y + 1) * m_CellSize);
            currQuad[3].position = sf::Vector2f(x * m_CellSize, (y + 1) * m_CellSize);

            currQuad[0].color = sf::Color::Black;
            currQuad[1].color = sf::Color::Black;
            currQuad[2].color = sf::Color::Black;
            currQuad[3].color = sf::Color::Black;
        }
    }
    // initialize grid
    for (int y = 0; y < m_MapSize.y - 1; y++)
    {
        sf::Vertex* currLine = &m_HorizontalLinesVertices[y * 2];
        currLine[0].position = sf::Vector2f(0.0f, (y + 1) * m_CellSize);
        currLine[1].position = sf::Vector2f(m_MapSize.x * m_CellSize, (y + 1) * m_CellSize);

        currLine[0].color = sf::Color(255.f, 255.f, 255.f, 20.f);
        currLine[1].color = sf::Color(255.f, 255.f, 255.f, 20.f);
    }

    for (int x = 0; x < m_MapSize.x - 1; x++)
    {
        sf::Vertex* currLine = &m_VerticalLinesVertices[x * 2];
        currLine[0].position = sf::Vector2f((x + 1) * m_CellSize, 0.0f);
        currLine[1].position = sf::Vector2f((x + 1) * m_CellSize, m_MapSize.y * m_CellSize);

        currLine[0].color = sf::Color(255.f, 255.f, 255.f, 20.f);
        currLine[1].color = sf::Color(255.f, 255.f, 255.f, 20.f);
    }
}

void Map::OneStepForward()
{
    for (int y = 0; y < m_MapSize.y; y++)
    {
        for (int x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;
            bool result = m_CurrentMapState[currCell];

            int neighboursCount = 0;
            for (int i = -1; i < 2; i++)
            {
                if (y + i < 0 || y + i >= m_MapSize.y) continue;

                for (int j = -1; j < 2; j++)
                {
                    if (i == 0 && j == 0) continue;

                    if (x + j < 0 || x + j >= m_MapSize.x) continue;

                    int currNeighbourCell = (x + j) + (y + i) * m_MapSize.x;

                    if (m_CurrentMapState[currNeighbourCell])
                        neighboursCount++;
                }
            }

            if (m_CurrentMapState[currCell])
            {
                if (neighboursCount < 2)
                    result = false;
                else if (neighboursCount == 2 || neighboursCount == 3)
                    result = true;
                else if (neighboursCount > 3)
                    result = false;
            }
            else
            {
                if (neighboursCount == 3)
                    result = true;
            }

            m_NextMapState[currCell] = result;
        }
    }

    for (int i = 0; i < m_NextMapState.size(); i++)
        m_CurrentMapState[i] = m_NextMapState[i];

    UpdateGraphicalRepresentation();
}

void Map::Update(float dTime)
{
    bool stepForward = false;

    m_Timer += dTime;
    if (m_Timer >= m_FrameTime)
    {
        stepForward = true;
        m_Timer = 0.0f;
    }

    if (!stepForward) return;

    OneStepForward();
}

bool& Map::Grid()
{
    return m_Grid;
}

void Map::Clear()
{
    std::fill(m_CurrentMapState.begin(), m_CurrentMapState.end(), false);
    UpdateGraphicalRepresentation();
}

void Map::SetStateOnPos(sf::Vector2f position, bool state)
{
    sf::Vector2u matrixPos;
    matrixPos.x = int(position.x / m_CellSize);
    matrixPos.y = int(position.y / m_CellSize);

    if (matrixPos.x >= 0 && matrixPos.x < m_MapSize.x &&
        matrixPos.y >= 0 && matrixPos.y < m_MapSize.y)
        SetState(matrixPos, state);
}

std::string Map::LoadPreset(int id)
{
    std::fill(m_CurrentMapState.begin(), m_CurrentMapState.end(), false);

    std::ifstream file("presets/" + std::to_string(id) + ".txt");

    std::string name;

    int sizeX, sizeY;

    file >> name;
    std::replace(name.begin(), name.end(), '_', ' ');
    file >> sizeX >> sizeY;

    if (sizeX > m_MapSize.x || sizeY > m_MapSize.y)
        return "Map is to small.";

    int pivotX = int(m_MapSize.x / 2) - int(sizeX / 2), pivotY = int(m_MapSize.y / 2) - int(sizeY / 2);

    for (int y = pivotY; y < sizeY + pivotY; y++)
    {
        for (int x = pivotX; x < sizeX + pivotX; x++)
        {
            int currCell = x + y * m_MapSize.x;
            bool state;
            file >> state;
            m_CurrentMapState[currCell] = state;
        }
    }

    file.close();

    UpdateGraphicalRepresentation();

    return "Loaded: " + name;
}

void Map::SavePreset(int id)
{
    sf::Vector2i min = sf::Vector2i(INT_MAX, INT_MAX), max = sf::Vector2i(-INT_MAX, -INT_MAX);
    std::ofstream file("presets/" + std::to_string(id) + ".txt");

    for (int y = 0; y < m_MapSize.y; y++)
    {
        for (int x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;

            if (m_CurrentMapState[currCell])
            {
                min.x = std::min(x, min.x);
                min.y = std::min(y, min.y);
                max.x = std::max(x, max.x);
                max.y = std::max(y, max.y);
            }
        }
    }

    int sizeX = max.x - min.x + 1, sizeY = max.y - min.y + 1;

    if(id <= 3 && id > 0)
        file << "Preset_" << std::to_string(id) << "\n";
    else
        file << "s\n";

    file << sizeX << " " << sizeY << "\n";

    for (int y = min.y; y <= max.y; y++)
    {
        for (int x = min.x; x <= max.x; x++)
        {
            int currCell = x + y * m_MapSize.x;

            file << m_CurrentMapState[currCell];

            if (x != max.x)
                file << " ";
        }
        file << "\n";
    }

    file.close();
}

void Map::MoveLivingCells(Direction direction)
{
    std::fill(m_NextMapState.begin(), m_NextMapState.end(), false);

    for (int y = 0; y < m_MapSize.y; y++)
    {
        for (int x = 0; x < m_MapSize.x; x++)
        {
            int currCell = x + y * m_MapSize.x;

            if (m_CurrentMapState[currCell])
            {
                int newPlace;
                if (direction == Direction::North)
                {
                    if (y - 1 >= 0)
                    {
                        newPlace = x + (y - 1) * m_MapSize.x;
                        m_NextMapState[newPlace] = true;
                    }
                }
                if (direction == Direction::East)
                {
                    if (x + 1 < m_MapSize.x)
                    {
                        newPlace = (x + 1) + y * m_MapSize.x;
                        m_NextMapState[newPlace] = true;
                    }
                }
                if (direction == Direction::South)
                {
                    if (y + 1 < m_MapSize.y)
                    {
                        newPlace = x + (y + 1) * m_MapSize.x;
                        m_NextMapState[newPlace] = true;
                    }
                }
                if (direction == Direction::West)
                {
                    if (x - 1 >= 0)
                    {
                        newPlace = (x - 1) + y * m_MapSize.x;
                        m_NextMapState[newPlace] = true;
                    }
                }

            }
        }
    }

    for (int i = 0; i < m_NextMapState.size(); i++)
        m_CurrentMapState[i] = m_NextMapState[i];

    UpdateGraphicalRepresentation();
}
