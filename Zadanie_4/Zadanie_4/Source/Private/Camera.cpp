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