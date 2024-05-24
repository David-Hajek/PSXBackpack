/// <summary>
/// author David Hajek March 2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Item.h"
#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setupFontAndText();
	void setupSprite();
	void setupUI();
	void updateOppacity();
	void removeOppacity();
	float oppacity = 0;
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
	sf::Sound m_backgroundMusic; // background music
	sf::Sprite downArrowSpriteUI;		   // UI ELEMENTS
	sf::Texture downArrowTextureUI;		   // UI ELEMENTS
	sf::Sprite rightArrowSpriteUI;		   // UI ELEMENTS
	sf::Texture rightArrowTextureUI;	   // UI ELEMENTS
	sf::Sprite itemOpenSpriteUi;		   // UI ELEMENTS
	sf::Texture itemOpenTextureUI;		   // UI ELEMENTS
	sf::Sprite leftArrowSpriteUI;		   // UI ELEMENTS
	sf::Texture leftArrowSpriteTextureUI;  // UI ELEMENTS
	sf::SoundBuffer backgroundBuffer; // buffer for the bg
	sf::Sound backgroundMusic; // self explanatory
	sf::SoundBuffer uiBuffer; // buffer fir the button presses
	sf::Sound UISoundIn; // sound for when the player presses buttons
	sf::SoundBuffer uiBufferOut; // buffer for the sound out
	sf::Sound UISoundOut; // sound for when the player leaves the ui

	void setupSound(); // sets up sound
	void animateBG(); // animates the background
	float m_bgIncrement{ 0.22f };	  // variables used for the background animations
	float m_bgFrameTimer{ 0.0f };	  // variables used for the background animations
	int bgFrame = 0;				  // variables used for the background animations
	const int SIZE = 500;			  // variables used for the background animations
	const int SIZEY = 400;			  // variables used for the background animations
	int col;						  // variables used for the background animations
	int row;						  // variables used for the background animations

	void setupBackground();
	sf::Texture m_backgroundTexture; // background texture
	sf::Sprite m_backgroundSprite;	// background sprite


	Item Revolver;	   // all of our items
	Item VHS;		   // all of our items
	Item Mask;		   // all of our items
	Item Rock;		   // all of our items
	Item Knife;		   // all of our items
	Item Flashlight; // all of our items
};

#endif // !GAME_HPP

