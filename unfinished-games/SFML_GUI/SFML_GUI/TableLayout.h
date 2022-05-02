#pragma once
#include "Layout.h"
class TableLayout :
    public Layout
{
private:
    const sf::FloatRect m_Boundaries;

    void updateShape() override;

public:
    TableLayout(float padding, opt_ref parent, const sf::FloatRect& boundaries);
    virtual ~TableLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;
};

