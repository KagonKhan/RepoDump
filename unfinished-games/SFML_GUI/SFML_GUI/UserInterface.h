#pragma once
#include "Layout.h"
class UserInterface :
    public Widget
{
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    std::vector<std::unique_ptr<Layout>> m_Layouts;
    void recalculatePositionVariable();

public:


    UserInterface();
    virtual ~UserInterface();

    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(const sf::Vector2f&) override {};
    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(float, float) override {};

   void setPositionAtIndex(const sf::Vector2f& pos, unsigned int index);
   void setPositionAtIndex(float x, float y, unsigned int index);

    void processEvent(const sf::Event& sfevent);

    sf::Vector2f getSize() const;

    /* std::move into this*/
    void addLayout(std::unique_ptr<Layout> layout);

    void update(const sf::Time& deltaTime);
};

