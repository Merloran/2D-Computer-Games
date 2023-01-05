#include "../Public/Camera.h"

Camera::Camera(sf::Vector2f Size, sf::FloatRect Border)
	: View(sf::View(sf::Vector2f(0.0f, 0.0f), Size))
    , m_Border(Border)
{
}

void Camera::UpdatePosition(sf::Vector2f Target)
{
    if (Target.x - View.getSize().x / 2 < m_Border.left)
    {
        m_Position.x = m_Border.left + View.getSize().x / 2;
    }
    else if (Target.x + View.getSize().x / 2 > m_Border.left + m_Border.width)
    {
        m_Position.x = m_Border.left + m_Border.width - View.getSize().x / 2;
    }
    else
    {
        m_Position.x = Target.x;
    }

    if (Target.y - View.getSize().y / 2 < m_Border.top)
    {
        m_Position.y = m_Border.top + View.getSize().y / 2;
    }
    else if (Target.y + View.getSize().y / 2 > m_Border.top + m_Border.height)
    {
        m_Position.y = m_Border.top + m_Border.height - View.getSize().y / 2;
    }
    else
    {
        m_Position.y = Target.y;
    }

    View.setCenter(m_Position);
}

void Camera::UpdateSize(sf::Vector2f Target1, sf::Vector2f Target2, sf::RenderWindow& Window)
{
    sf::Vector2f Diff = (Target1 - Target2);
    float Distance = Diff.x * Diff.x + Diff.y * Diff.y;
    if (Distance >= Window.getSize().x * Window.getSize().x)
    {
        float DistanceRoot = sqrt(Distance) * 1.2f;
        if (DistanceRoot <= m_Border.width && DistanceRoot <= m_Border.height)
        {
            View.setSize(DistanceRoot, DistanceRoot);
        }
        else
        {
            View.setSize(m_Border.width, m_Border.width);
        }
    }
    else
    {
        View.setSize(Window.getSize().x * 1.2f, Window.getSize().y * 1.2f);
    }
}

void Camera::SetBorder(sf::FloatRect Border)
{
    m_Border = Border;
}

bool Camera::IsVisible(sf::Vector2f Position)
{
    float X = View.getCenter().x;
    float Y = View.getCenter().y;
    float W = View.getSize().x * 0.5f;
    float H = View.getSize().y * 0.5f;

    if (Position.x > X - W && Position.x < X + W && Position.y > Y - H && Position.y < Y + H)
    {
        return true;
    }
    else
    {
        return false;
    }
}
