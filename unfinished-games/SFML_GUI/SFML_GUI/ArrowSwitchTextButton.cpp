#include "ArrowSwitchTextButton.h"

#pragma region Arrow Switch Area


#pragma region DRAWING AREA

void ArrowSwitchTextButton::ArrowSwitchArea::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	drawBackground(target);
	drawArrows(target);
	drawCurrentOption(target);
}

void ArrowSwitchTextButton::ArrowSwitchArea::drawBackground(sf::RenderTarget& target) const
{
	target.draw(m_AreaShape);
}

void ArrowSwitchTextButton::ArrowSwitchArea::drawArrows(sf::RenderTarget& target) const
{
	for (auto&& arrow : m_Arrows)
		target.draw(arrow);
}

void ArrowSwitchTextButton::ArrowSwitchArea::drawCurrentOption(sf::RenderTarget& target) const
{
	target.draw(m_Options.get());
}

#pragma endregion 

#pragma region EVENT PROCESSING
void ArrowSwitchTextButton::ArrowSwitchArea::processEvent(const sf::Event& sfevent)
{
	processArrowButtonsEvent(sfevent);
}

void ArrowSwitchTextButton::ArrowSwitchArea::processArrowButtonsEvent(const sf::Event& sfevent)
{
	for (auto&& arrow : m_Arrows)
		arrow.process(sfevent);
}


#pragma endregion


ArrowSwitchTextButton::ArrowSwitchArea::ArrowSwitchArea(opt_ref parent, unsigned int numberOfOptions, const sf::Vector2f& size, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size)
	: Widget(parent),    m_Padding(5.f),    m_Options(numberOfOptions),    m_AreaShape(size),    m_Arrows{ {opt_ref(*this), arrow_size, left}, {opt_ref(*this), arrow_size, right} }
{
	puts("ArrowSwitch\tctor");

	initColors();

	initButtonFunctionalities();

	reposition();
}

void ArrowSwitchTextButton::ArrowSwitchArea::initColors()
{
	m_FillColor = sf::Color::Transparent;
	m_HoverColor = sf::Color::Transparent;
	m_AreaShape.setFillColor(m_HoverColor);
}

void ArrowSwitchTextButton::ArrowSwitchArea::initButtonFunctionalities()
{
	m_Arrows[0].on_click = [this](const sf::Event&, Button&) {
		m_Options.previous();
	};

	m_Arrows[1].on_click = [this](const sf::Event&, Button&) {
		m_Options.next();
	};
}

ArrowSwitchTextButton::ArrowSwitchArea::~ArrowSwitchArea()
{
	puts("ArrowSwitch\tdtor");
}


void ArrowSwitchTextButton::ArrowSwitchArea::reposition() {
	repositionButtons();
	repositionOptions();
}

void ArrowSwitchTextButton::ArrowSwitchArea::repositionButtons()
{
	const sf::Vector2f area_size(m_AreaShape.getSize());
	const sf::Vector2f arrow_size(m_Arrows[0].getSize());

	// positioned middle vertically
	sf::Vector2f arrow_pos(m_AreaShape.getPosition() + sf::Vector2f(m_Padding, (area_size.y - arrow_size.y) / 2.f));

	m_Arrows[0].setPosition(arrow_pos);

	arrow_pos.x += area_size.x - arrow_size.x - m_Padding;
	m_Arrows[1].setPosition(arrow_pos);
}

void ArrowSwitchTextButton::ArrowSwitchArea::repositionOptions()
{
	const sf::Vector2f pos(m_AreaShape.getPosition());
	const sf::Vector2f area_size(m_AreaShape.getSize());

	// middle
	for (auto&& label : m_Options.getMembers())
		label.setPosition(pos + (area_size - label.getSize()) / 2.f);

}

void ArrowSwitchTextButton::ArrowSwitchArea::addOption(std::string_view option, sf::Font& font, unsigned int charSize)
{
	m_Options.emplace(opt_ref(*this), option, font, charSize);
}

void ArrowSwitchTextButton::ArrowSwitchArea::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_AreaShape.setPosition(m_Position);
	reposition();
}

void ArrowSwitchTextButton::ArrowSwitchArea::setSize(const sf::Vector2f& size) {
	m_AreaShape.setSize(size);
	reposition();
}

sf::Vector2f ArrowSwitchTextButton::ArrowSwitchArea::getSize() const
{
	return m_AreaShape.getSize();
}



#pragma endregion






void ArrowSwitchTextButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Shape);
	target.draw(m_Label);
	target.draw(m_SwitchArea);

}

ArrowSwitchTextButton::ArrowSwitchTextButton(opt_ref parent, const sf::Vector2f& size, std::string_view text, sf::Font& font, unsigned int charSize, unsigned int numberOfOptions, const sf::Vector2f& switchAreaSize, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size)
	: Button(parent), m_Padding(10.f), m_Shape(size), m_Label(opt_ref(*this), text,font, charSize), m_SwitchArea(opt_ref(*this), numberOfOptions, switchAreaSize, left, right, arrow_size)
{
	puts("ArrowSwitchButton\tctor");
	initColors();
	setPosition({ 0, 0 });
}

ArrowSwitchTextButton::~ArrowSwitchTextButton()
{
	puts("ArrowSwitchButton\tdtor");
}

void ArrowSwitchTextButton::initColors()
{
	m_FillColor = sf::Color::Transparent;
	m_HoverColor = sf::Color(15, 26, 217);

	m_Shape.setFillColor(m_FillColor);
}

void ArrowSwitchTextButton::processEvent(const sf::Event& sfevent)
{
	m_SwitchArea.processEvent(sfevent);


	if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(static_cast<float>(sfevent.mouseMove.x), static_cast<float>(sfevent.mouseMove.y));

		Status old_status = m_Status;
		m_Status = Status::Idle;

		/* If pressed and still hovering, keep pressed */
		if (old_status == Status::HoverAndPressed && m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::HoverAndPressed;
		/* else check if just hovering */
		else if (m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::Hover;
		/* if neither hovering nor pressed = mouse left */
		if ((old_status == Status::Hover || old_status == Status::HoverAndPressed) && !(m_Status == Status::Hover || m_Status == Status::HoverAndPressed))
			onMouseLeft();
		else if (!(old_status == Status::Hover) && (m_Status == Status::Hover))
			onMouseEntered();
	}
}

void ArrowSwitchTextButton::onMouseEntered()
{
	m_Shape.setFillColor(m_HoverColor);
}

void ArrowSwitchTextButton::onMouseLeft()
{
	m_Shape.setFillColor(m_FillColor);
}

void ArrowSwitchTextButton::addOption(std::string_view option, sf::Font& font, unsigned int charSize)
{
	m_SwitchArea.addOption(option, font, charSize);
}


void ArrowSwitchTextButton::reposition()
{
	m_Shape.setPosition(m_Position);

	repositionLabel();
	repositionSwitchArea();
}

void ArrowSwitchTextButton::repositionLabel()
{
	sf::Vector2f pos(m_Position);
	pos.x += m_Padding;
	pos.y += (m_Shape.getSize().y - m_Label.getSize().y) / 2.f;

	m_Label.setPosition(pos);
}

void ArrowSwitchTextButton::repositionSwitchArea()
{
	const sf::Vector2f bg_size(m_Shape.getSize());
	const sf::Vector2f area_size(m_SwitchArea.getSize());

	sf::Vector2f pos(m_Position);
	pos.x += bg_size.x - area_size.x - m_Padding;
	pos.y += (bg_size.y - area_size.y) / 2.f;

	m_SwitchArea.setPosition(pos);
}



#pragma region SETTERS / GETTERS


void ArrowSwitchTextButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	reposition();
}

void ArrowSwitchTextButton::setOutlineThickness(float thickness)
{
	m_Shape.setOutlineThickness(thickness);
}

void ArrowSwitchTextButton::setOutlineColor(const sf::Color& color)
{
	m_Shape.setOutlineColor(color);
}

void ArrowSwitchTextButton::setSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);
	reposition();
}

sf::Vector2f ArrowSwitchTextButton::getSize() const
{
	return m_Shape.getSize();
}




/* TEXT SETTERS */
void ArrowSwitchTextButton::setString(const std::string& string)
{
	m_Label.setString(string);
}

void ArrowSwitchTextButton::setFont(const sf::Font& font)
{
	m_Label.setFont(font);
}

void ArrowSwitchTextButton::setCharacterSize(unsigned int size)
{
	m_Label.setCharacterSize(size);
}

void ArrowSwitchTextButton::setLineSpacing(float spacingFactor)
{
	m_Label.setLineSpacing(spacingFactor);
}

void ArrowSwitchTextButton::setLetterSpacing(float spacingFactor)
{
	m_Label.setLetterSpacing(spacingFactor);
}

void ArrowSwitchTextButton::setTextStyle(sf::Uint32 style)
{
	m_Label.setStyle(style);
}

void ArrowSwitchTextButton::setTextFillColor(const sf::Color& color)
{
	m_Label.setFillColor(color);
}

void ArrowSwitchTextButton::setTextOutlineColor(const sf::Color& color)
{
	m_Label.setOutlineColor(color);
}

void ArrowSwitchTextButton::setTextOutlineThickness(float thickness)
{
	m_Label.setOutlineThickness(thickness);
}

unsigned int ArrowSwitchTextButton::getCharacterSize() const
{
	return m_Label.getCharacterSize();
}

#pragma endregion