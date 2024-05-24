/// <summary>
/// @author David Hájek
/// @date February 2024
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include "Globals.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 800U, 32U }, "PSXBackpack" },
	m_exitGame{ false } //when true game will exit
{
	setupSound();
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	Revolver.setupRevolver();
	VHS.setupVHS();
	Mask.setupMask();
	Rock.setupRock();
	Knife.setupKnife();
	Flashlight.stupFlashLight();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{

}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 80.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 80 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 80 fps
			update(timePerFrame); //80 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (newEvent.type == sf::Event::KeyReleased)
		{
			if (sf::Keyboard::Right == newEvent.key.code) // plays a sound when the right key is pressed
			{
				UISoundIn.play();
			}
			if (sf::Keyboard::Left == newEvent.key.code) // plays a sound when the left key is pressed
			{
				UISoundIn.play();
			}
			if (sf::Keyboard::Space == newEvent.key.code && Revolver.isOnCenter == true || VHS.isOnCenter == true || Mask.isOnCenter == true || Rock.isOnCenter == true || Knife.isOnCenter == true || Flashlight.isOnCenter == true)
			{
				UISoundIn.play(); // plays a sound when space key is pressed
			}
			if (sf::Keyboard::Down == newEvent.key.code && Revolver.itemDirection == Direction::BottomRight || VHS.itemDirection == Direction::BottomRight || Mask.itemDirection == Direction::BottomRight || Rock.itemDirection == Direction::BottomRight || Knife.itemDirection == Direction::BottomRight || Flashlight.itemDirection == Direction::BottomRight)
			{
				UISoundOut.play(); // plays a different sound when the down key is pressed
			}
		}

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}


}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	// REVOLVER
	Revolver.animate();	// animates the item
	Revolver.checkDiection(); // checks which direction the item is heading
	Revolver.checkBoundary(); // checks if the item hits a boundary point
	Revolver.teleportItem(); // teleports the item if the item exceeds a certain point
	if (VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight && VHS.isOpen != true) // this is in place to stop the player from moving items when inspecting one
	{
		if (Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight && Mask.isOpen != true)
		{
			if (Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight && Rock.isOpen != true)
			{
				if (Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight && Knife.isOpen != true)
				{
					if (Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight && Flashlight.isOpen != true)
					{
						Revolver.move(); // moves the item
					}
				}
			}
		}

	}
	// VHS
	VHS.animate();
	VHS.checkDiection();
	VHS.checkBoundary();
	VHS.teleportItem();
	if (Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight && Revolver.isOpen != true) // same as with the revolver
	{
		if (Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight && Mask.isOpen != true)
		{
			if (Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight && Rock.isOpen != true)
			{
				if (Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight && Knife.isOpen != true)
				{
					if (Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight && Flashlight.isOpen != true)
					{
						VHS.move(); // moves the item
					}
				}
			}
		}
	}
	// MASK
	Mask.animate();
	Mask.checkDiection();
	Mask.checkBoundary();
	Mask.teleportItem();
	if (Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight && Revolver.isOpen != true) // same as with the previous
	{
		if (VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight && VHS.isOpen != true)
		{
			if (Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight && Rock.isOpen != true)
			{
				if (Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight && Knife.isOpen != true)
				{
					if (Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight && Flashlight.isOpen != true)
					{
						Mask.move(); // moves the item
					}
				}
			}
		}
	}
	// ROCK
	Rock.animate();
	Rock.checkDiection();
	Rock.checkBoundary();
	Rock.teleportItem();
	if (Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight && Revolver.isOpen != true)
	{
		if (VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight && VHS.isOpen != true)
		{
			if (Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight && Mask.isOpen != true)
			{
				if (Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight && Knife.isOpen != true)
				{
					if (Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight && Flashlight.isOpen != true)
					{
						Rock.move(); // moves the item
					}
				}
			}
		}
	}
	// KNIFE
	Knife.animate();
	Knife.checkDiection();
	Knife.checkBoundary();
	Knife.teleportItem();
	if (Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight && Revolver.isOpen != true)
	{
		if (VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight && VHS.isOpen != true)
		{
			if (Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight && Mask.isOpen != true)
			{
				if (Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight && Rock.isOpen != true)
				{
					if (Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight && Flashlight.isOpen != true)
					{
						Knife.move(); // moves the item
					}
				}
			}
		}
	}
	// FLASHLUGHT
	Flashlight.animate();
	Flashlight.checkDiection();
	Flashlight.checkBoundary();
	Flashlight.teleportItem();
	if (Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight && Revolver.isOpen != true)
	{
		if (VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight && VHS.isOpen != true)
		{
			if (Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight && Mask.isOpen != true)
			{
				if (Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight && Rock.isOpen != true)
				{
					if (Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight && Knife.isOpen != true)
					{
						Flashlight.move(); // moves the item
					}
				}
			}
		}
	}
	animateBG(); // animates the background
	if (Revolver.itemDirection == Direction::TopLeft) // takes care of the oppacity of the ui for each of the item
	{
		updateOppacity();
	}
	if (Revolver.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}
	if (VHS.itemDirection == Direction::TopLeft)
	{
		updateOppacity();
	}
	if (VHS.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}
	if (Mask.itemDirection == Direction::TopLeft)
	{
		updateOppacity();
	}
	if (Mask.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}
	if (Rock.itemDirection == Direction::TopLeft)
	{
		updateOppacity();
	}
	if (Rock.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}
	if (Knife.itemDirection == Direction::TopLeft)
	{
		updateOppacity();
	}
	if (Knife.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}
	if (Flashlight.itemDirection == Direction::TopLeft)
	{
		updateOppacity();
	}
	if (Flashlight.itemDirection == Direction::BottomRight)
	{
		removeOppacity();
	}


}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);
	m_window.draw(itemOpenSpriteUi);
	if (Revolver.buttonPressed == false) // if no button has been pressed, display controls
	{
		m_window.draw(Revolver.controls);
	}

	if (Revolver.isOnCenter == true || Revolver.itemDirection == Direction::TopLeft || Revolver.itemDirection == Direction::BottomRight) // if the item is on center or being opened / closed - draw the item name
	{
		m_window.draw(Revolver.itemName);
	}
	if (VHS.isOnCenter == true || VHS.itemDirection == Direction::TopLeft || VHS.itemDirection == Direction::BottomRight)
	{
		m_window.draw(VHS.itemName);
	}
	if (Mask.isOnCenter == true || Mask.itemDirection == Direction::TopLeft || Mask.itemDirection == Direction::BottomRight)
	{
		m_window.draw(Mask.itemName);
	}
	if (Rock.isOnCenter == true || Rock.itemDirection == Direction::TopLeft || Rock.itemDirection == Direction::BottomRight)
	{
		m_window.draw(Rock.itemName);
	}
	if (Knife.isOnCenter == true || Knife.itemDirection == Direction::TopLeft || Knife.itemDirection == Direction::BottomRight)
	{
		m_window.draw(Knife.itemName);
	}
	if (Flashlight.isOnCenter == true || Flashlight.itemDirection == Direction::TopLeft || Flashlight.itemDirection == Direction::BottomRight)
	{
		m_window.draw(Flashlight.itemName);
	}
	m_window.draw(VHS.itemSprite);
	m_window.draw(Revolver.itemSprite);
	m_window.draw(Mask.itemSprite);
	m_window.draw(Rock.itemSprite);
	m_window.draw(Knife.itemSprite);
	m_window.draw(Flashlight.itemSprite);
	if (Revolver.isOpen == false && Revolver.itemDirection != Direction::TopLeft && Revolver.itemDirection != Direction::BottomRight) // close the ui if arrows if the item is being opened
	{
		if (VHS.isOpen == false && VHS.itemDirection != Direction::TopLeft && VHS.itemDirection != Direction::BottomRight) // and draw them once the user leaves the ui screen
		{
			if (Mask.isOpen == false && Mask.itemDirection != Direction::TopLeft && Mask.itemDirection != Direction::BottomRight)
			{
				if (Rock.isOpen == false && Rock.itemDirection != Direction::TopLeft && Rock.itemDirection != Direction::BottomRight)
				{
					if (Knife.isOpen == false && Knife.itemDirection != Direction::TopLeft && Knife.itemDirection != Direction::BottomRight)
					{
						if (Flashlight.isOpen == false && Flashlight.itemDirection != Direction::TopLeft && Flashlight.itemDirection != Direction::BottomRight)
						{
							m_window.draw(rightArrowSpriteUI);
							m_window.draw(leftArrowSpriteUI);
						}
					}
				}
			}
		}
	}
	m_window.draw(downArrowSpriteUI);
	if (Revolver.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(Revolver.itemInfo);
		m_window.draw(Revolver.itemQuantity);
		m_window.draw(Revolver.itemDurability);
		m_window.draw(Revolver.itemPower);
		m_window.draw(Revolver.itemQuality);
	}
	if (VHS.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(VHS.itemInfo);
		m_window.draw(VHS.itemQuantity);
		m_window.draw(VHS.itemDurability);
		m_window.draw(VHS.itemPower);
		m_window.draw(VHS.itemQuality);
	}
	if (Mask.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(Mask.itemInfo);
		m_window.draw(Mask.itemQuantity);
		m_window.draw(Mask.itemDurability);
		m_window.draw(Mask.itemPower);
		m_window.draw(Mask.itemQuality);
	}
	if (Rock.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(Rock.itemInfo);
		m_window.draw(Rock.itemQuantity);
		m_window.draw(Rock.itemDurability);
		m_window.draw(Rock.itemPower);
		m_window.draw(Rock.itemQuality);
	}
	if (Knife.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(Knife.itemInfo);
		m_window.draw(Knife.itemQuantity);
		m_window.draw(Knife.itemDurability);
		m_window.draw(Knife.itemPower);
		m_window.draw(Knife.itemQuality);
	}
	if (Flashlight.isOpen == true) // if the item is open, draw its stats
	{
		m_window.draw(Flashlight.itemInfo);
		m_window.draw(Flashlight.itemQuantity);
		m_window.draw(Flashlight.itemDurability);
		m_window.draw(Flashlight.itemPower);
		m_window.draw(Flashlight.itemQuality);
	}
	m_window.display();

}


/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	Item setupItemText();
}

/// <summary>
/// load the texture and setup the sprite for the background and ui
/// </summary>
void Game::setupSprite()
{
	setupBackground();
	setupUI();
}

void Game::setupUI()
{
	if (!downArrowTextureUI.loadFromFile("ASSETS\\IMAGES\\downarrow.png")) // if we cant load the arrow texture
	{
		std::cout << "Down arrow texture not loaded" << std::endl; // error message for the arrow 
	}
	downArrowSpriteUI.setTexture(downArrowTextureUI);
	downArrowSpriteUI.setOrigin(111.0f, 0.0f);
	downArrowSpriteUI.setScale(1.2, 1.0);
	downArrowSpriteUI.setPosition(500.0f, 720.0f);
	downArrowSpriteUI.setColor(sf::Color(255, 255, 255, 128));


	if (!rightArrowTextureUI.loadFromFile("ASSETS\\IMAGES\\rightarrow.png")) // if we cant load the arrow texture
	{
		std::cout << "Right arrow texture not loaded" << std::endl; // error message for the arrow 
	}
	rightArrowSpriteUI.setTexture(rightArrowTextureUI);
	rightArrowSpriteUI.setOrigin(0.0f, 88.5f);
	rightArrowSpriteUI.setScale(1.2, 1.0);
	rightArrowSpriteUI.setPosition(925.0f, 400.0f);
	rightArrowSpriteUI.setColor(sf::Color(255, 255, 255, 128));

	if (!leftArrowSpriteTextureUI.loadFromFile("ASSETS\\IMAGES\\leftarrow.png")) // if we cant load the arrow texture
	{
		std::cout << "Right arrow texture not loaded" << std::endl; // error message for the arrow 
	}
	leftArrowSpriteUI.setTexture(leftArrowSpriteTextureUI);
	leftArrowSpriteUI.setOrigin(0.0f, 88.5f);
	leftArrowSpriteUI.setScale(1.2, 1.0);
	leftArrowSpriteUI.setPosition(25.0f, 400.0f);
	leftArrowSpriteUI.setColor(sf::Color(255, 255, 255, 128));

	if (!itemOpenTextureUI.loadFromFile("ASSETS\\IMAGES\\UI.png")) // if we cant load the arrow texture
	{
		std::cout << "Item UI not loaded" << std::endl; // error message for the arrow 
	}
	itemOpenSpriteUi.setTexture(itemOpenTextureUI);
	itemOpenSpriteUi.setScale(1.25, 1.31);
	itemOpenSpriteUi.setColor(sf::Color(255, 255, 255, 0));
}


void Game::updateOppacity()
{
	oppacity = oppacity + 5;
	static_cast<int>(oppacity);
	itemOpenSpriteUi.setColor(sf::Color(255, 255, 255, +oppacity));
	if (oppacity > 250) // if the oppacity gets above 250, set it ot 255 (to avoid the oppacity looping)
	{
		oppacity = 255;
		itemOpenSpriteUi.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Game::removeOppacity()
{
	oppacity = oppacity - 5;
	static_cast<int>(oppacity);
	itemOpenSpriteUi.setColor(sf::Color(255, 255, 255, +oppacity));
	if (oppacity < 5) // if the oppacity gets below 5, set it ot 0 (to avoid the oppacity looping)
	{
		oppacity = 0;
		itemOpenSpriteUi.setColor(sf::Color(255, 255, 255, 0));
	}

}

void Game::setupSound()
{
	if (!backgroundBuffer.loadFromFile("ASSETS\\SOUND\\Background.wav")) // if we cant load the background audio
	{
		std::cout << "Sound not loaded" << std::endl; // error message for the background 
	}
	backgroundMusic.setBuffer(backgroundBuffer);
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(3.0f);
	backgroundMusic.play();
	if (!uiBuffer.loadFromFile("ASSETS\\SOUND\\buttonclick.wav")) // if we cant load the button sound
	{
		std::cout << "buttonclick not loaded" << std::endl;
	}
	UISoundIn.setBuffer(uiBuffer);
	UISoundIn.setVolume(15.0f);
	if (!uiBufferOut.loadFromFile("ASSETS\\SOUND\\buttonrelease.wav")) // if we cant load the button sound
	{
		std::cout << "buttonrelease not loaded" << std::endl;
	}
	UISoundOut.setBuffer(uiBufferOut);
	UISoundOut.setVolume(15.0f);
}

void Game::animateBG()
{
	int frame = 0;
	m_bgFrameTimer += m_bgIncrement;
	frame = static_cast<int>(m_bgFrameTimer); // same as animating the item
	if (frame >= 100)
	{
		frame = 0;
		m_bgFrameTimer = 0.0f;
	}

	if (frame != m_bgFrameTimer) // I only figured out how to do a spritesheet that has an exact amount of sprites, so 10x10 and none were left out
	{
		col = frame % 10;
		row = frame / 10;
		m_backgroundSprite.setTextureRect(sf::IntRect(col * SIZE, row * SIZEY, 500, 400));
	}
}

void Game::setupBackground()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\bg.png")) // if we cant load the background texture
	{
		std::cout << "Background texture not loaded" << std::endl; // error message for the background 
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(2, 2);
	m_backgroundSprite.setTextureRect(sf::IntRect{ 0, 0, 500, 400 });
	m_backgroundSprite.setColor(sf::Color(128, 128, 128));

}


