/// <summary>
/// @author David Hájek
/// @date March 2024
///
#include "Item.h"
#include "Game.h"
#include <iostream>


float Item::m_frameIncrement{ 0.15 }; // how fast our frames move
float movementFrames;

Item::Item()
{

}



void Item::checkDiection()
{
	if (itemDirection != Direction::Static && itemDirection != Direction::BottomRight) // checks if the item is moving or not
	{
		itemLocation.x = itemLocation.x + movement.x; // moves the item
		itemSprite.setPosition(itemLocation); // updates the position of movement is registered
	}
	if (itemDirection == Direction::TopLeft)
	{
		itemLocation.y = itemLocation.y + movement.y; // move to item up in the y direction
		itemLocation.x = itemLocation.x + movement.x; // move the item to the left of the x direction 
		itemScale.x = itemScale.x - scale; // scake the item down in boh of the axis
		itemScale.y = itemScale.y - scale;
		itemSprite.setPosition(itemLocation);
		itemSprite.setScale(itemScale); // update the scale
	}
	if (itemDirection == Direction::BottomRight)
	{
		itemLocation.y = itemLocation.y - movement.y; // move the item down in the y direction
		itemLocation.x = itemLocation.x - movement.x; // move the item right in the x direction
		itemLocation.x = itemLocation.x - movement.x; // twice as fast 
		itemScale.x = itemScale.x + scale; // scale up the item
		itemScale.y = itemScale.y + scale; // scale up the item
		itemSprite.setPosition(itemLocation); // update the pos 
		itemSprite.setScale(itemScale); // update the item scale 
	}


}



void Item::animate()
{
	int frame = 0;
	m_frameCounter = m_frameCounter + m_frameIncrement;
	frame = static_cast<int>(m_frameCounter);
	if (frame >= ITEM_FRAMES)
	{
		frame = 0;
		m_frameCounter = 0.0f;
	}
	if (frame != m_frameNumber) // increment the position of the itemsprite that is displayed
	{
		m_frameNumber = frame;
		itemSprite.setTextureRect(sf::IntRect(frame * FRAME_WIDTH_LENGTH, 0, FRAME_WIDTH_LENGTH, FRAME_WIDTH_LENGTH));
	}

}
void Item::checkBoundary()
{
	if (itemLocation.x == LEFT_EDGE) // takes care of boundary checking, to stop items from flying off into the distance
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == RIGHT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == SECOND_RIGHT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == SECOND_LEFT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == THIRD_LEFT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == THIRD_RIGHT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == FOURTH_RIGHT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == FOURTH_LEFT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == FIFTH_LEFT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == FIFTH_RIGHT_EDGE)
	{
		itemDirection = Direction::Static;
	}
	if (itemLocation.x == CENTER)
	{
		itemDirection = Direction::Static;
		isOnCenter = true;
		isOpen = false;
	}
	if (itemLocation.y == UI_FRAME_BOUNDARY)
	{
		itemDirection = Direction::Static;
		isOpen = true;
	}
}
void Item::move()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isOpen == false) // if the player presses the left arrow, we move the item to the left
	{
		if (itemDirection != Direction::TopLeft && itemDirection != Direction::BottomRight && isOpen == false) // check if the item is not already moving up or down
		{
			itemDirection = Direction::Left;
			buttonPressed = true; // for hiding controls
		}
		if (itemDirection == Direction::Left)
		{
			movement.x = -speed;
			isOnCenter = false;
		}


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isOpen == false) // if the player presses the right arrow, we move the item to the right
	{
		if (itemDirection != Direction::TopLeft && itemDirection != Direction::BottomRight && isOpen == false) // check if the item is not already moving up or down
		{
			itemDirection = Direction::Right;
			buttonPressed = true; // for hiding controls
		}
		if (itemDirection == Direction::Right)
		{
			movement.x = +speed;
			isOnCenter = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // if the player presses space
	{
		if (itemLocation.x == CENTER)
		{
			itemDirection = Direction::TopLeft; // set the direction to topleft if the item is on center
			buttonPressed = true; // for hiding controls
		}
		if (itemDirection == Direction::TopLeft && itemLocation.x == CENTER) // move the item top left
		{
			movement.y = -speed;
			movement.x = -speed;
			itemName.setPosition(80, 20); // update the position of our item name
			isOnCenter = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && isOpen == true)
	{
		if (itemLocation.y == UI_FRAME_BOUNDARY) // if the item is in the boundary, send the item back to center 
		{
			itemDirection = Direction::BottomRight; // change the item direction 
			isOpen = false; // close the item
		}
		if (itemDirection == Direction::BottomRight && itemLocation.y == UI_FRAME_BOUNDARY) // update the itemname position to be in the center 
		{
			itemName.setPosition(185.0f, 610.0f);
		}
	}

}
void Item::setupRevolver()
{
	if (!revolverTexture.loadFromFile("ASSETS/IMAGES/Revolver.png"))
	{
		std::cout << "Cannot load revolver texture" << std::endl;
	}
	itemSprite.setTexture(revolverTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemSprite.setPosition(itemLocation);
	itemDirection = Direction::Static;
	// ------------------------------------------------Text
	Item::setupItemText();
	itemName.setString("Colt Python .357 Magnum Revolver");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A standard issue revolver. \n\nOnce belonging to a police officer,\nwho was the first responder when the \npanic erupted.\n\nA weapon for true marskmen, \neasily punctures flesh and armor \n\nLooted from a husk of a man.");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("POWER : " + std::to_string(power));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality

	itemQuality.setString("QUALITY : " + quality);
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);
	isOnCenter = true;



}
void Item::setupVHS()
{
	if (!vhsTexture.loadFromFile("ASSETS/IMAGES/vhs.png"))
	{
		std::cout << "Cannot load VHS" << std::endl;
	}
	itemSprite.setTexture(vhsTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemLocation.x = RIGHT_EDGE;
	itemSprite.setPosition(itemLocation);
	Item::setupItemText();
	itemName.setString("ZONY Industry Handycam Camcorder");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A regular handycam. \n\nUsed for creating memories,\nor capturing a moment \n\nUsed primarily by the, \nones brave enough to venture outside\nand check if they missed anything.  \n\nFound on a bedside table");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("POWER : " + std::to_string(power));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality
	itemQuality.setString("QUALITY : " + quality);
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);

	itemDirection = Direction::Static;
	isOnCenter = false;
}

void Item::setupMask()
{
	if (!maskTexture.loadFromFile("ASSETS/IMAGES/gasmask.png"))
	{
		std::cout << "Cannot load mask" << std::endl;
	}
	itemSprite.setTexture(maskTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemLocation.x = SECOND_RIGHT_EDGE;
	itemSprite.setPosition(itemLocation);
	Item::setupItemText();
	itemName.setString("MERC Military Issued Tactical Gasmask");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A Tactical grade gasmask. \n\nUsed for handling gas,\nor gas environments. \n\nWas the military standard \nfor the MERC units\nthat were called when\nthe police was helpless.  \n\nFound in an irradiated yard");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("FILTER : " + std::to_string(power));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality
	itemQuality.setString("QUALITY : " + quality);
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);

	itemDirection = Direction::Static;
	isOnCenter = false;
}

void Item::setupRock()
{
	if (!rockTexture.loadFromFile("ASSETS/IMAGES/rock.png"))
	{
		std::cout << "Cannot load rock" << std::endl;
	}
	itemSprite.setTexture(rockTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemLocation.x = THIRD_RIGHT_EDGE;
	itemSprite.setPosition(itemLocation);
	Item::setupItemText();
	itemName.setString("A mote of an ?????? ????? ?????");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A Rock like stone. \n\nHas glowing properties,\ncan be used as a glowstick. \n\nA rock with vein like structure \nit appears to pulsate\nand faint humming can be heard\ncoming from the rock.  \n\nFound inside the Zagor forest");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability + 400) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("STRENGTH : " + std::to_string(power + 500));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality
	itemQuality.setString("QUALITY : Perfect");
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);

	itemDirection = Direction::Static;
	isOnCenter = false;
}

void Item::setupKnife()
{
	if (!knifeTexture.loadFromFile("ASSETS/IMAGES/knife.png"))
	{
		std::cout << "Cannot load knife" << std::endl;
	}
	itemSprite.setTexture(knifeTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemLocation.x = FOURTH_RIGHT_EDGE;
	itemSprite.setPosition(itemLocation);
	Item::setupItemText();
	itemName.setString("A MERC Ballistic training dagger");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A Training knife. \n\nUsed by the special forces\nto train in hand to hand combat \n\nMade out of rubber and silicone \nit poses no immedieate danger\nCan cause damage if \nan artery is hit.  \n\nFound in a training facility");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("STRENGTH : " + std::to_string(power - 25));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality
	itemQuality.setString("QUALITY : " + quality);
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);

	itemDirection = Direction::Static;
	isOnCenter = false;
}

void Item::stupFlashLight()
{
	if (!flashLightTexture.loadFromFile("ASSETS/IMAGES/flashlight.png"))
	{
		std::cout << "Cannot load flashlight" << std::endl;
	}
	itemSprite.setTexture(flashLightTexture);
	itemSprite.setScale(1.5, 1.5);
	itemSprite.setOrigin(256.0f, 256.0f);
	itemLocation.x = FIFTH_RIGHT_EDGE;
	itemSprite.setPosition(itemLocation);
	Item::setupItemText();
	itemName.setString("An old LUMEN1 brand LED flashlignt");
	itemName.setPosition(185.0f, 610.0f);
	itemName.setCharacterSize(70U);
	// ----------------------------------------------- ItemInfo
	itemInfo.setString("A regular flashlight. \n\nHas many uses\ncan be used as a light source \n\nMade out of aluminium metal \nthe light flickers from time to time.\nNeeds maintenance \nfor prolonged use. \n\nFound inside a shed.");
	itemInfo.setCharacterSize(55);
	itemInfo.setLineSpacing(0.9);
	itemInfo.setPosition(375.0f, 120.0f);
	// ----------------------------------------------- ItemQuantity
	itemQuantity.setString("QUANTITY : 1/1");
	itemQuantity.setCharacterSize(55);
	itemQuantity.setPosition(85.0f, 330.0f);
	// ----------------------------------------------- ItemDurabilityy
	generateStats();
	itemDurability.setString("DURABILITY : " + std::to_string(durability) + "%");
	itemDurability.setCharacterSize(55);
	itemDurability.setPosition(85.0f, 420.0f);
	//  --------------------------------------------- ItemPower
	itemPower.setString("POWER : " + std::to_string(power - 25));
	itemPower.setCharacterSize(55);
	itemPower.setPosition(85.0f, 510.0f);
	// --------------------------------------------- ItemQuality
	itemQuality.setString("QUALITY : " + quality);
	itemQuality.setCharacterSize(50);
	itemQuality.setPosition(85.0f, 600.0f);

	itemDirection = Direction::Static;
	isOnCenter = false;
}

void Item::generateStats()
{
	srand(time(NULL) + rand()); // each time this gets generated, we assing a random number to it, so that we always end up with a different outcome, no matter how many times a second it gets run
	randomNumber = rand() % 5 + 1; // if the randomly generated number equals to anything below, quality is assigned
	if (randomNumber == 1)
	{
		quality = "Very Fine";
	}
	if (randomNumber == 2)
	{
		quality = "Fine";
	}
	if (randomNumber == 3)
	{
		quality = "Standard";
	}
	if (randomNumber == 4)
	{
		quality = "Coarse";
	}
	if (randomNumber == 5)
	{
		quality = "Rough";
	}

	randomNumber = rand() % 100 + 1;
	durability = randomNumber;

	randomNumber = rand() % 76 + 25;
	power = randomNumber;
}

void Item::teleportItem()
{
	if (itemLocation.x < FIFTH_LEFT_EDGE) // if the item is past the fourth left edge, we teleport it to the right edge
	{
		itemLocation.x = RIGHT_EDGE;
	}
	if (itemLocation.x > FIFTH_RIGHT_EDGE) // vice versa
	{
		itemLocation.x = LEFT_EDGE;
	}
}


void Item::setupItemText()
{
	if (!silentHillFont.loadFromFile("ASSETS\\FONTS\\SLNTHLC.ttf"))
	{
		std::cout << "Silent hill font not loaded" << std::endl;
	}
	itemInfo.setFont(silentHillFont);		  // sets the font for the item stats
	itemName.setFont(silentHillFont);		  // sets the font for the item stats
	itemQuality.setFont(silentHillFont);	  // sets the font for the item stats
	itemQuantity.setFont(silentHillFont);	  // sets the font for the item stats
	itemPower.setFont(silentHillFont);		  // sets the font for the item stats
	itemDurability.setFont(silentHillFont);   // sets the font for the item stats


	// control setup
	controls.setFont(silentHillFont);
	controls.setString(" LEFT and RIGHT ARROW KEYS to move items\n SPACEBAR to open item \n DOWN ARROW to close the item");
	controls.setCharacterSize(50);
	controls.setLineSpacing(0.9);
	controls.setPosition(0, 0);
}

