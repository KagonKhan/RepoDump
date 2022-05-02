#pragma once
#include "Button.h"
#include "Label.h"
#include "SpriteButton.h"



class ArrowSwitchTextButton :
	public Button
{
    template<typename T>
    class CircularArray
    {
    private:
        unsigned short int m_Index;
        std::vector<T> m_Buffer;

    public:
        CircularArray(int size)
            : m_Index(0)
        {
            m_Buffer.reserve(size);
        }
     
        template<typename ... Args>
        void emplace(Args&& ... args)
        {
            m_Buffer.emplace_back(std::forward<Args>(args)...);
        }

        void next() {
            if (++m_Index >= m_Buffer.size())
                m_Index = 0;
        }
        void previous() {
            if (m_Index == 0)
                m_Index = static_cast<unsigned short>(m_Buffer.size()) - 1;
            else
                --m_Index;
        }
        const T& get() const {
            return m_Buffer.at(m_Index);
        }
        T& get() {
            return m_Buffer.at(m_Index);
        }

        bool hasMembers()const  {
            return m_Buffer.size() > 0;
        }

        std::vector<T>& getMembers() {
            return m_Buffer;
        }
    };

	struct ArrowSwitchArea : public Widget
	{
    friend ArrowSwitchTextButton;
	private:
        float m_Padding;
        sf::RectangleShape m_AreaShape;
        CircularArray<Label> m_Options;
        SpriteButton m_Arrows[2];

        sf::Color m_FillColor, m_HoverColor;

		void draw(sf::RenderTarget& target, sf::RenderStates) const override;
            void drawBackground(sf::RenderTarget& target) const;
            void drawArrows(sf::RenderTarget& target) const;
            // Will crash if no options exist
            void drawCurrentOption(sf::RenderTarget& target) const;

        
        void processEvent(const sf::Event& sfevent) override;
            void processArrowButtonsEvent(const sf::Event& sfevent);
        
        void initColors();
        void initButtonFunctionalities();

        void reposition();
        void repositionButtons();
        void repositionOptions();

    public:
		ArrowSwitchArea(opt_ref parent, unsigned int numberOfOptions, const sf::Vector2f& size, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size);
		virtual ~ArrowSwitchArea();

        void addOption(std::string_view option, sf::Font& font, unsigned int charSize);

        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        sf::Vector2f getSize() const;

	};

private:
    float m_Padding;
    sf::RectangleShape m_Shape;
    Label m_Label;
    ArrowSwitchArea m_SwitchArea;

    sf::Color m_FillColor, m_HoverColor;

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    
    virtual void processEvent(const sf::Event& sfevent) override;
    virtual void onMouseEntered() override;
    virtual void onMouseLeft() override;

    void initColors();

    void reposition();
    void repositionLabel();
    void repositionSwitchArea();

public:
	ArrowSwitchTextButton(opt_ref parent, const sf::Vector2f& size, 
        std::string_view text, sf::Font& font, unsigned int charSize,
        unsigned int numberOfOptions, const sf::Vector2f& switchAreaSize, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size = std::nullopt);

	virtual ~ArrowSwitchTextButton();

    void addOption(std::string_view option, sf::Font& font, unsigned int charSize);

#pragma region SETTERS / GETTERS

    /* BUTTON SETTERS */
    void setPosition(const sf::Vector2f& pos) override;
    void setOutlineThickness(float thickness);
    void setOutlineColor(const sf::Color& color);

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;


    /* TEXT SETTERS */
    void setString(const std::string& string);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setLineSpacing(float spacingFactor);
    void setLetterSpacing(float spacingFactor);
    void setTextStyle(sf::Uint32 style);
    void setTextFillColor(const sf::Color& color);
    void setTextOutlineColor(const sf::Color& color);
    void setTextOutlineThickness(float thickness);
    unsigned int getCharacterSize() const;

#pragma endregion

};
