#pragma once
#include "Layout.h"
class UnorderedLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    UnorderedLayout(float padding, std::optional<std::reference_wrapper<Widget>> parent);
    virtual ~UnorderedLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;
};


