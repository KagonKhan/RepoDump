#pragma once
#include "ActionMap.h"
#include "ResourceManager.h"
#include "Random.h"

class Configuration
{
private:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator= (const Configuration&) = delete;

	enum Fonts: int {Gui};
	enum PlayerInputs : int {TurnLeft, TurnRight, MoveLeft, MoveRight, HardDrop};
	enum Sounds : int {Spawn, Explosion, LevelUp};
	enum Musics : int {	Theme};

	static ResourceManager<sf::Font, int> fonts;
	static ResourceManager<sf::Music, int> musics;
	static ResourceManager<sf::SoundBuffer, int> sounds;

	static ActionMap<int> playerInputs;

	static void initialize();
public:
	static void initTextures ();
	static void initFonts ();
	static void initSounds ();
	static void initMusics ();
	static void initPlayerInputs ();


};

inline void Configuration::initialize()
{
	initTextures();
	initFonts();
	initSounds();
	initMusics();

	initPlayerInputs();

	rand_init();

	musics.get(Musics::Theme).setLoop(true);
	musics.get(Musics::Theme).play();

}

inline void Configuration::initSounds()
{
	sounds.load(Sounds::Spawn, "media/sounds/spawn.flac");
	sounds.load(Sounds::Explosion, "media/sounds/explosion.flac");
	sounds.load(Sounds::LevelUp, "media/sounds/levelup.flac");
}

inline void Configuration::initPlayerInputs()
{
	playerInputs.Map(PlayerInputs::TurnRight,	Action(sf::Keyboard::Up));
	playerInputs.Map(PlayerInputs::TurnLeft,	Action(sf::Keyboard::Down));
	playerInputs.Map(PlayerInputs::MoveLeft,	Action(sf::Keyboard::Left));
	playerInputs.Map(PlayerInputs::MoveRight,	Action(sf::Keyboard::Right));
	playerInputs.Map(PlayerInputs::HardDrop,	Action(sf::Keyboard::Space, Action::Type::Released));
}

inline void Configuration::initTextures()
{
}

inline void Configuration::initFonts()
{
	fonts.load(Fonts::Gui, "media/font/trs-million.ttf");
}

inline void Configuration::initMusics()
{
	musics.load(Musics::Theme, "media/musics/theme.ogg");
}
