/// <summary>
/// @author David Hájek
/// @date March 2024
///
#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
class Item
{
public:
	Item();
	float speed = 3.0f; // how fast our sprites move - DO NOT CHANGE
	float scale = 0.0196; // used for opening and closing ui
	bool isOnCenter = true;
	Direction itemDirection = Direction::Static;
	void checkDiection(); // checks where the item is heading
	void animate(); // animating our items
	void checkBoundary(); // checks if item is offscreen or not
	void move(); // move object
	void setupRevolver(); // sets up the sprite items
	void setupVHS();	// set up for each of our items
	void setupMask();	// set up for each of our items
	void setupRock();	// set up for each of our items
	void setupKnife(); 	// set up for each of our items
	void stupFlashLight(); // set up for each of our items
	void generateStats(); // randomly generates stats for each item
	void teleportItem(); // teleports the item if it gets past a certain boundary
	void setupItemText(); // sets up the font adn text

	float m_frameCounter{ 0.0f }; // what frame are we on
	sf::Vector2f movement{ 0.0f, 0.0f }; // used for moving items
	sf::Vector2f itemScale{ 1.5, 1.5 }; // scale of our items

	sf::Sprite itemSprite;	// item necessities
	sf::Text itemName;		// item necessities
	sf::Text itemInfo;		// item necessities
	int quantity = 0;		 // variables used for the random generation
	sf::Text itemQuantity;	 // variables used for the random generation
	int durability = 0;		 // variables used for the random generation
	sf::Text itemDurability; // variables used for the random generation
	int power = 0;			 // variables used for the random generation
	sf::Text itemPower;		 // variables used for the random generation
	int randomNumber = 0;	 // variables used for the random generation
	std::string quality;	 // variables used for the random generation
	sf::Text itemQuality;	 // variables used for the random generation
	sf::Text controls; // controls of our game
	bool buttonPressed = false; // for hiding the ui
	bool isOpen = false; // is the item open
	bool isMovingLeft = false; // is the item moving left
	bool isMovingRight = false; // is the item moving right
	sf::Vector2f itemLocation{ 500.0f, 350.0f }; // where is our item

private:


	sf::Vector2f m_itemLocation; // location of the item
	int m_frameNumber{ 0 }; // what frame is the item on
	static float m_frameIncrement; // increment of our current frame
	sf::Texture revolverTexture;	// textures of our items
	sf::Texture vhsTexture;			// textures of our items
	sf::Texture maskTexture;		// textures of our items
	sf::Texture rockTexture;		// textures of our items
	sf::Texture knifeTexture;		// textures of our items
	sf::Texture flashLightTexture; // last texture for our items
	sf::Font silentHillFont; // font we use
	const float RIGHT_EDGE = 1499.0f;			  // boundaries where the items stop
	const float LEFT_EDGE = -499.0f;			  // boundaries where the items stop
	const float SECOND_RIGHT_EDGE = 2498.0f;	  // boundaries where the items stop
	const float THIRD_RIGHT_EDGE = 3497.0f;		  // boundaries where the items stop
	const float FOURTH_RIGHT_EDGE = 4499.0f;	  // boundaries where the items stop
	const float FIFTH_RIGHT_EDGE = 5501.0f;			// boundaries where the items stop
	const float SECOND_LEFT_EDGE = -1501.0f;	  // boundaries where the items stop
	const float THIRD_LEFT_EDGE = -2500.0f;		  // boundaries where the items stop
	const float FOURTH_LEFT_EDGE = -3499.0f;	  // boundaries where the items stop
	const float FIFTH_LEFT_EDGE = -4501.0f;			// boundaries where the items stop

	const int CENTER = 500.0f; // center of the screen
	const int ITEM_FRAMES = 29;	// how many animation frames an itemsprite has
	const int FRAME_WIDTH_LENGTH = 512;		//dimensions of a single sprite
	const int UI_FRAME_BOUNDARY = 209; 		// where the item will stop when being opened








};

