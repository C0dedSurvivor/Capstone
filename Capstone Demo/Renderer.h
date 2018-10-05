#ifndef RENDERER_H
#define RENDERER_H

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include "EquipInventoryGUI.h"
#include "MedInventoryGUI.h"
#include "InventoryGUI.h"
#include "Inventory.h"
#include "Map.h"
#include "MapPlayer.h"
#include "TextSpawn.h"

class Renderer : public sf::Drawable, public sf::Transformable {
public:
	int activeMap = 0;
	int loadedGui = 0;
	bool transitioning = false;
	bool npcTalking = false;
	bool cont = false;
	std::vector<std::unique_ptr<Map>> mapList;
	MapPlayer player;

	std::shared_ptr<sf::RenderWindow> window;

	//gui shit
	sf::Font font;
	sf::Texture Outline;
	sf::Texture Disc;
	TextSpawn textSpawn;
	sf::RectangleShape Menubutton1;
	sf::RectangleShape Menubutton2;
	sf::RectangleShape Menubutton3;
	sf::RectangleShape Menubutton4;

	sf::RectangleShape P1;
	sf::RectangleShape P2;
	sf::RectangleShape P3;

	sf::Text play1;
	sf::Text play2;
	sf::Text play3;

	sf::Text Discs;
	sf::Text Skills;
	sf::Text InventoryT;
	sf::Text Exit;
	sf::CircleShape circle;

	sf::Text player1Attack;
	sf::Text player1MagicAttack;
	sf::Text player1PhysicalDefense;
	sf::Text player1MagicalDefense;
	sf::Text player1Speed;
	sf::Text player1Health;
	sf::Text player1Rom;
	sf::Text player1Ram;

	sf::Text player2Attack;
	sf::Text player2MagicAttack;
	sf::Text player2PhysicalDefense;
	sf::Text player2MagicalDefense;
	sf::Text player2Speed;
	sf::Text player2Health;
	sf::Text player2Rom;
	sf::Text player2Ram;

	sf::Text player3Attack;
	sf::Text player3MagicAttack;
	sf::Text player3PhysicalDefense;
	sf::Text player3MagicalDefense;
	sf::Text player3Speed;
	sf::Text player3Health;
	sf::Text player3Rom;
	sf::Text player3Ram;
	
	//menu 2

	sf::RectangleShape menu2Test;

	//menu 3
	sf::RectangleShape backButton;
	sf::Text backbutton;
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;
	sf::RectangleShape pIcon;
	sf::RectangleShape square1;
	sf::RectangleShape square2;
	sf::RectangleShape square3;
	sf::RectangleShape square4;
	sf::RectangleShape square5;
	sf::RectangleShape square6;

	sf::Text Helmet;
	sf::Text Chest;
	sf::Text Gauntlet;
	sf::Text Leg;
	sf::Text Ac1;
	sf::Text Ac2;

	sf::RectangleShape d1;
	sf::RectangleShape d2;
	sf::RectangleShape d3;
	sf::RectangleShape d4;

	sf::RectangleShape trans;

	//NPC text stuff
	sf::Text textBoxText;
	sf::Text npcName;
	sf::Texture textBoxTexture;
	sf::Sprite textBox;
	std::string passedText;
	bool contTalk = false;
	sf::Clock textTimer;
	int textTime = 1;

	sf::VertexArray renderMap;

	std::shared_ptr<Inventory> inv;

	int subInv = 0;
	InventoryGUI basicInvGui;
	MedInventoryGUI medInvGui;
	EquipInventoryGUI equipInvGui;
	sf::Texture basicTab;
	sf::Texture medTab;
	sf::Texture equipTab;
	sf::Sprite invTabs;

	Renderer(const std::shared_ptr<sf::RenderWindow>& w, const std::shared_ptr<Inventory>& i);
	~Renderer();

	void renderEverything();
	void movePlayer(int x, int y);
	void switchGUI(int i) { loadedGui = i; }
	void switchSubGUI(int i) { subInv = i; };
	void stairTrans(int map, int pX, int pY);
	void npcConv(int npc);
	void openChest(int chest);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif