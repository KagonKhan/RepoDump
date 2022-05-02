#pragma once
#include "Layout.h"
class HorizontalLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    HorizontalLayout(float padding, opt_ref parent);
    virtual ~HorizontalLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;
};

