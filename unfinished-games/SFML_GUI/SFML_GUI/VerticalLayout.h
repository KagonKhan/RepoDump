#pragma once
#include "Layout.h"
class VerticalLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    VerticalLayout(float padding, std::optional<std::reference_wrapper<Widget>> parent);
    virtual ~VerticalLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;
};

