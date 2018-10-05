#include "Renderer.h"

Renderer::Renderer(const std::shared_ptr<sf::RenderWindow>& w, const std::shared_ptr<Inventory>& i) : window(w), inv(i)
{
	setScale(sf::Vector2f(3, 3));
	activeMap = 0;
	renderMap.setPrimitiveType(sf::Quads);
	player.setPosition(64, 80);
	//800 = window width, 600 = window height
	setPosition(sf::Vector2f((800.0f / 2.0f - player.getPosition().x * 3.0f), (600.0f / 2.0f - player.getPosition().y * 3.0f)));

	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	if (!Outline.loadFromFile("Outline.png"))
	{
		// error...
	}

	if (!Disc.loadFromFile("Disc.jpg"))
	{
		// error...
	}
	/*Creates TextSpawn*/
	textSpawn.floater.setString("Text");
	textSpawn.x = 200;
	textSpawn.y = 200;
	textSpawn.floater.setFont(font);
	textSpawn.floater.setCharacterSize(34);
	textSpawn.floater.setFillColor(sf::Color::Black);
	textSpawn.floater.setStyle(sf::Text::Bold);
	textSpawn.floater.setPosition(sf::Vector2f(200, 200));

	/*Creates the Menu Buttons*/
	Menubutton1.setSize(sf::Vector2f(250, 75));
	Menubutton2.setSize(sf::Vector2f(250, 75));
	Menubutton3.setSize(sf::Vector2f(250, 75));
	Menubutton4.setSize(sf::Vector2f(250, 75));

	/*Creates the Players*/
	P1.setSize(sf::Vector2f(150, 150));
	P1.setTexture(&Outline);
	P2.setSize(sf::Vector2f(150, 150));
	P2.setTexture(&Outline);
	P3.setSize(sf::Vector2f(150, 150));
	P3.setTexture(&Outline);

	/*Sets the Position of the Player Sprites*/
	P1.setPosition(sf::Vector2f(75, 45));
	P2.setPosition(sf::Vector2f(300, 230));
	P3.setPosition(sf::Vector2f(75, 400));

	/*Sets the Position of the Menu Buttons*/
	Menubutton1.setPosition(sf::Vector2f(415, 50));
	Menubutton2.setPosition(sf::Vector2f(450, 200));
	Menubutton3.setPosition(sf::Vector2f(450, 350));
	Menubutton4.setPosition(sf::Vector2f(415, 500));

	/*Creates the Text for the Players*/
	play1.setFont(font);
	play1.setString("P1");
	play1.setCharacterSize(50);
	play1.setFillColor(sf::Color::Black);
	play1.setStyle(sf::Text::Bold);
	play1.setPosition(sf::Vector2f(110, 85));

	play2.setFont(font);
	play2.setString("P2");
	play2.setCharacterSize(50);
	play2.setFillColor(sf::Color::Black);
	play2.setStyle(sf::Text::Bold);
	play2.setPosition(sf::Vector2f(335, 270));

	play3.setFont(font);
	play3.setString("P3");
	play3.setCharacterSize(50);
	play3.setFillColor(sf::Color::Black);
	play3.setStyle(sf::Text::Bold);
	play3.setPosition(sf::Vector2f(110, 440));

	/*Sets the Color of the Menu Buttons*/
	Menubutton1.setFillColor(sf::Color(255, 215, 0));
	Menubutton2.setFillColor(sf::Color(255, 215, 0));
	Menubutton3.setFillColor(sf::Color(255, 215, 0));
	Menubutton4.setFillColor(sf::Color(255, 215, 0));

	/*Creates the Text for Menubutton1*/
	Discs.setFont(font);
	Discs.setString("Discs");
	Discs.setCharacterSize(34);
	Discs.setFillColor(sf::Color::Black);
	Discs.setStyle(sf::Text::Bold);
	Discs.setPosition(sf::Vector2f(500, 60));

	/*Creates the Text for Menubutton2*/
	Skills.setFont(font);
	Skills.setString("Skills");
	Skills.setCharacterSize(34);
	Skills.setFillColor(sf::Color::Black);
	Skills.setStyle(sf::Text::Bold);
	Skills.setPosition(sf::Vector2f(540, 210));

	/*Creates the Text for Menubutton3*/
	InventoryT.setFont(font);
	InventoryT.setString("Inventory");
	InventoryT.setCharacterSize(34);
	InventoryT.setFillColor(sf::Color::Black);
	InventoryT.setStyle(sf::Text::Bold);
	InventoryT.setPosition(sf::Vector2f(530, 365));

	/*Creates the Text for Menubutton4*/
	Exit.setFont(font);
	Exit.setString("Exit");
	Exit.setCharacterSize(34);
	Exit.setFillColor(sf::Color::Black);
	Exit.setStyle(sf::Text::Bold);
	Exit.setPosition(sf::Vector2f(510, 515));

	/*Creating and Designing the Circle*/
	circle.setRadius(500);
	circle.setFillColor(sf::Color(255, 0, 0));
	circle.setPosition(sf::Vector2f(-500, -200));
	circle.setPointCount(125);

	player1Attack.setFont(font);
	player1Attack.setCharacterSize(15);
	player1Attack.setFillColor(sf::Color::Black);
	player1Attack.setStyle(sf::Text::Bold);
	player1Attack.setPosition(sf::Vector2f(175, 55));

	player1MagicAttack.setFont(font);
	player1MagicAttack.setCharacterSize(15);
	player1MagicAttack.setFillColor(sf::Color::Black);
	player1MagicAttack.setStyle(sf::Text::Bold);
	player1MagicAttack.setPosition(sf::Vector2f(175, 75));

	player1PhysicalDefense.setFont(font);
	player1PhysicalDefense.setCharacterSize(15);
	player1PhysicalDefense.setFillColor(sf::Color::Black);
	player1PhysicalDefense.setStyle(sf::Text::Bold);
	player1PhysicalDefense.setPosition(sf::Vector2f(175, 95));

	player1MagicalDefense.setFont(font);
	player1MagicalDefense.setCharacterSize(15);
	player1MagicalDefense.setFillColor(sf::Color::Black);
	player1MagicalDefense.setStyle(sf::Text::Bold);
	player1MagicalDefense.setPosition(sf::Vector2f(175, 115));

	player1Speed.setFont(font);
	player1Speed.setCharacterSize(15);
	player1Speed.setFillColor(sf::Color::Black);
	player1Speed.setStyle(sf::Text::Bold);
	player1Speed.setPosition(sf::Vector2f(175, 135));

	player1Health.setFont(font);
	player1Health.setCharacterSize(15);
	player1Health.setFillColor(sf::Color::Black);
	player1Health.setStyle(sf::Text::Bold);
	player1Health.setPosition(sf::Vector2f(175, 155));

	player1Rom.setFont(font);
	player1Rom.setCharacterSize(15);
	player1Rom.setFillColor(sf::Color::Black);
	player1Rom.setStyle(sf::Text::Bold);
	player1Rom.setPosition(sf::Vector2f(175, 175));

	player1Ram.setFont(font);
	player1Ram.setCharacterSize(15);
	player1Ram.setFillColor(sf::Color::Black);
	player1Ram.setStyle(sf::Text::Bold);
	player1Ram.setPosition(sf::Vector2f(175, 195));

	player2Attack.setFont(font);
	player2Attack.setCharacterSize(15);
	player2Attack.setFillColor(sf::Color::Black);
	player2Attack.setStyle(sf::Text::Bold);
	player2Attack.setPosition(sf::Vector2f(175, 55));

	player2MagicAttack.setFont(font);
	player2MagicAttack.setCharacterSize(15);
	player2MagicAttack.setFillColor(sf::Color::Black);
	player2MagicAttack.setStyle(sf::Text::Bold);
	player2MagicAttack.setPosition(sf::Vector2f(175, 75));

	player2PhysicalDefense.setFont(font);
	player2PhysicalDefense.setCharacterSize(15);
	player2PhysicalDefense.setFillColor(sf::Color::Black);
	player2PhysicalDefense.setStyle(sf::Text::Bold);
	player2PhysicalDefense.setPosition(sf::Vector2f(175, 95));

	player2MagicalDefense.setFont(font);
	player2MagicalDefense.setCharacterSize(15);
	player2MagicalDefense.setFillColor(sf::Color::Black);
	player2MagicalDefense.setStyle(sf::Text::Bold);
	player2MagicalDefense.setPosition(sf::Vector2f(175, 115));

	player2Speed.setFont(font);
	player2Speed.setCharacterSize(15);
	player2Speed.setFillColor(sf::Color::Black);
	player2Speed.setStyle(sf::Text::Bold);
	player2Speed.setPosition(sf::Vector2f(175, 135));

	player2Health.setFont(font);
	player2Health.setCharacterSize(15);
	player2Health.setFillColor(sf::Color::Black);
	player2Health.setStyle(sf::Text::Bold);
	player2Health.setPosition(sf::Vector2f(175, 155));

	player2Rom.setFont(font);
	player2Rom.setCharacterSize(15);
	player2Rom.setFillColor(sf::Color::Black);
	player2Rom.setStyle(sf::Text::Bold);
	player2Rom.setPosition(sf::Vector2f(175, 175));

	player2Ram.setFont(font);
	player2Ram.setCharacterSize(15);
	player2Ram.setFillColor(sf::Color::Black);
	player2Ram.setStyle(sf::Text::Bold);
	player2Ram.setPosition(sf::Vector2f(175, 195));

	player3Attack.setFont(font);
	player3Attack.setCharacterSize(15);
	player3Attack.setFillColor(sf::Color::Black);
	player3Attack.setStyle(sf::Text::Bold);
	player3Attack.setPosition(sf::Vector2f(175, 55));

	player3MagicAttack.setFont(font);
	player3MagicAttack.setCharacterSize(15);
	player3MagicAttack.setFillColor(sf::Color::Black);
	player3MagicAttack.setStyle(sf::Text::Bold);
	player3MagicAttack.setPosition(sf::Vector2f(175, 75));

	player3PhysicalDefense.setFont(font);
	player3PhysicalDefense.setCharacterSize(15);
	player3PhysicalDefense.setFillColor(sf::Color::Black);
	player3PhysicalDefense.setStyle(sf::Text::Bold);
	player3PhysicalDefense.setPosition(sf::Vector2f(175, 95));

	player3MagicalDefense.setFont(font);
	player3MagicalDefense.setCharacterSize(15);
	player3MagicalDefense.setFillColor(sf::Color::Black);
	player3MagicalDefense.setStyle(sf::Text::Bold);
	player3MagicalDefense.setPosition(sf::Vector2f(175, 115));

	player3Speed.setFont(font);
	player3Speed.setCharacterSize(15);
	player3Speed.setFillColor(sf::Color::Black);
	player3Speed.setStyle(sf::Text::Bold);
	player3Speed.setPosition(sf::Vector2f(175, 135));

	player3Health.setFont(font);
	player3Health.setCharacterSize(15);
	player3Health.setFillColor(sf::Color::Black);
	player3Health.setStyle(sf::Text::Bold);
	player3Health.setPosition(sf::Vector2f(175, 155));

	player3Rom.setFont(font);
	player3Rom.setCharacterSize(15);
	player3Rom.setFillColor(sf::Color::Black);
	player3Rom.setStyle(sf::Text::Bold);
	player3Rom.setPosition(sf::Vector2f(175, 175));

	player3Ram.setFont(font);
	player3Ram.setCharacterSize(15);
	player3Ram.setFillColor(sf::Color::Black);
	player3Ram.setStyle(sf::Text::Bold);
	player3Ram.setPosition(sf::Vector2f(175, 195));

	//menu 2

	menu2Test.setSize(sf::Vector2f(300, 350));

	//menu 3

	//Creates Back Button
	backButton.setSize(sf::Vector2f(150, 50));
	backButton.setPosition(sf::Vector2f(650, 550));
	backButton.setFillColor(sf::Color(255, 215, 0));

	backbutton.setFont(font);
	backbutton.setString("Back");
	backbutton.setCharacterSize(35);
	backbutton.setFillColor(sf::Color::Black);
	backbutton.setStyle(sf::Text::Bold);
	backbutton.setPosition(sf::Vector2f(685, 555));

	//Creates the 2 Big Rectangles
	rect1.setSize(sf::Vector2f(260, 475));
	rect2.setSize(sf::Vector2f(156, 475));

	//Sets the Position of the 2 Big Rectangles
	rect1.setPosition(sf::Vector2f(50, 50));
	rect2.setPosition(sf::Vector2f(600, 50));

	//Creates the Player Icons
	pIcon.setSize(sf::Vector2f(125, 237));

	//Sets the Sprite for Player Icons
	pIcon.setTexture(&Outline);

	//Sets the Position of Player Icons
	pIcon.setPosition(sf::Vector2f(50, 50));

	//Creates the 6 Small Squares
	square1.setSize(sf::Vector2f(96, 96));
	square2.setSize(sf::Vector2f(96, 96));
	square3.setSize(sf::Vector2f(96, 96));
	square4.setSize(sf::Vector2f(96, 96));
	square5.setSize(sf::Vector2f(96, 96));
	square6.setSize(sf::Vector2f(96, 96));

	//Postions the 6 Small Squares
	square1.setPosition(sf::Vector2f(346, 50));
	square2.setPosition(sf::Vector2f(346, 175));
	square3.setPosition(sf::Vector2f(346, 302));
	square4.setPosition(sf::Vector2f(346, 429));
	square5.setPosition(sf::Vector2f(471, 367));
	square6.setPosition(sf::Vector2f(471, 115));

	//Creates the text for the 6 Small Squares
	Helmet.setFont(font);
	Helmet.setString("Helmet");
	Helmet.setCharacterSize(18);
	Helmet.setFillColor(sf::Color::Black);
	Helmet.setStyle(sf::Text::Bold);
	Helmet.setPosition(sf::Vector2f(361, 60));

	Chest.setFont(font);
	Chest.setString("Chest");
	Chest.setCharacterSize(18);
	Chest.setFillColor(sf::Color::Black);
	Chest.setStyle(sf::Text::Bold);
	Chest.setPosition(sf::Vector2f(366, 185));

	Gauntlet.setFont(font);
	Gauntlet.setString("Gauntlet");
	Gauntlet.setCharacterSize(18);
	Gauntlet.setFillColor(sf::Color::Black);
	Gauntlet.setStyle(sf::Text::Bold);
	Gauntlet.setPosition(sf::Vector2f(356, 312));

	Leg.setFont(font);
	Leg.setString("Leg");
	Leg.setCharacterSize(18);
	Leg.setFillColor(sf::Color::Black);
	Leg.setStyle(sf::Text::Bold);
	Leg.setPosition(sf::Vector2f(376, 439));

	Ac1.setFont(font);
	Ac1.setString("Ac1");
	Ac1.setCharacterSize(18);
	Ac1.setFillColor(sf::Color::Black);
	Ac1.setStyle(sf::Text::Bold);
	Ac1.setPosition(sf::Vector2f(501, 125));

	Ac2.setFont(font);
	Ac2.setString("Ac2");
	Ac2.setCharacterSize(18);
	Ac2.setFillColor(sf::Color::Black);
	Ac2.setStyle(sf::Text::Bold);
	Ac2.setPosition(sf::Vector2f(501, 377));

	//Creates the Squares for the Discs
	d1.setSize(sf::Vector2f(96, 96));
	d2.setSize(sf::Vector2f(96, 96));
	d3.setSize(sf::Vector2f(96, 96));
	d4.setSize(sf::Vector2f(96, 96));

	//Sets the Position of the Disc Squares
	d1.setPosition(sf::Vector2f(630, 60));
	d2.setPosition(sf::Vector2f(630, 180));
	d3.setPosition(sf::Vector2f(630, 300));
	d4.setPosition(sf::Vector2f(630, 419));

	//Sets the Texture of the Squares
	d1.setTexture(&Disc);
	d2.setTexture(&Disc);
	d3.setTexture(&Disc);
	d4.setTexture(&Disc);

	//Creates the Border of the Squares
	d1.setOutlineColor(sf::Color::Black);
	d1.setOutlineThickness(5);
	d2.setOutlineColor(sf::Color::Black);
	d2.setOutlineThickness(5);
	d3.setOutlineColor(sf::Color::Black);
	d3.setOutlineThickness(5);
	d4.setOutlineColor(sf::Color::Black);
	d4.setOutlineThickness(5);

	//set size to window's size
	trans.setSize(sf::Vector2f(800, 600));
	trans.setFillColor(sf::Color(0, 0, 0, 0));

	textBoxText.setFont(font);
	textBoxText.setCharacterSize(19);
	textBoxText.setFillColor(sf::Color::Black);
	textBoxText.setStyle(sf::Text::Bold);
	textBoxText.setPosition(sf::Vector2f(115, 510));

	npcName.setFont(font);
	npcName.setCharacterSize(22);
	npcName.setFillColor(sf::Color(175, 175, 175, 255));
	npcName.setStyle(sf::Text::Bold);
	npcName.setPosition(sf::Vector2f(115, 460));

	if (!textBoxTexture.loadFromFile("MapTextBox.png"))
	{
		// error...
	}

	if (!basicTab.loadFromFile("BasicInvTabs.png"))
	{
		// error...
	}

	if (!medTab.loadFromFile("MedInvTabs.png"))
	{
		// error...
	}

	if (!equipTab.loadFromFile("EquipInvTabs.png"))
	{
		// error...
	}

	textBox.setTexture(textBoxTexture);
	textBox.setPosition(sf::Vector2f(100, 450));

	invTabs.setTexture(basicTab);
	invTabs.setPosition(sf::Vector2f(100, 50));

	basicInvGui = InventoryGUI(100, 100, &(inv->basicInv), 6);
	medInvGui = MedInventoryGUI(100, 100, &(inv->medInv), 6);
	equipInvGui = EquipInventoryGUI(100, 100, &(inv->equipInv), 6);
}

Renderer::~Renderer()
{
}

void Renderer::renderEverything()
{
	renderMap.clear();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (mapList.at(activeMap)->map[i][j] != 0) {
				int x = ((mapList.at(activeMap)->map[i][j] - 1) % 3) * 16;
				int y = ((mapList.at(activeMap)->map[i][j]) / 3) * 16;
				if (mapList.at(activeMap)->map[i][j] % 3 == 0)
					y -= 16;
				renderMap.append(sf::Vertex(sf::Vector2f(i * 16, j * 16), sf::Vector2f(x, y)));
				renderMap.append(sf::Vertex(sf::Vector2f((i + 1) * 16, j * 16), sf::Vector2f(x + 16, y)));
				renderMap.append(sf::Vertex(sf::Vector2f((i + 1) * 16, (j + 1) * 16), sf::Vector2f(x + 16, y + 16)));
				renderMap.append(sf::Vertex(sf::Vector2f(i * 16, (j + 1) * 16), sf::Vector2f(x, y + 16)));
			}
		}
	}
	setPosition(sf::Vector2f((800.0f / 2.0f - player.getPosition().x * 3.0f), (600.0f / 2.0f - player.getPosition().y * 3.0f)));
}

void Renderer::movePlayer(int x, int y)
{
	player.move(x, y);
	//800 = window width, 600 = window height
	setPosition(sf::Vector2f((800.0f / 2.0f - player.getPosition().x * 3.0f), (600.0f / 2.0f - player.getPosition().y * 3.0f)));
}

void Renderer::stairTrans(int map, int pX, int pY)
{
	sf::Texture texture;
	texture.loadFromFile("SpriteSheet.png");
	sf::RenderStates states;
	states.texture = &texture;
	states.transform = getTransform();
	transitioning = true;
	for (int i = 0; i <= 255; i += 15) {
		trans.setFillColor(sf::Color(0, 0, 0, i));
		window->clear(sf::Color(200, 200, 200, 255));
		draw(*window, states);
		window->display();
		sf::sleep(sf::milliseconds(10));
	}
	activeMap = map;
	player.setPosition(pX, pY);
	setPosition(sf::Vector2f((800.0f / 2.0f - player.getPosition().x * 3.0f), (600.0f / 2.0f - player.getPosition().y * 3.0f)));
	states.transform = getTransform();
	renderEverything();
	sf::sleep(sf::milliseconds(340));
	for (int i = 255; i >= 0; i -= 15) {
		trans.setFillColor(sf::Color(0, 0, 0, i));
		window->clear(sf::Color(200, 200, 200, 255));
		draw(*window, states);
		window->display();
		sf::sleep(sf::milliseconds(10));
	}
	transitioning = false;
}

void Renderer::npcConv(int npc)
{
	sf::Texture texture;
	texture.loadFromFile("SpriteSheet.png");
	sf::RenderStates states;
	states.texture = &texture;
	states.transform = getTransform();
	npcTalking = true;
	for (int i = 0; i < mapList.at(activeMap)->npcList.at(npc).conv.size(); i++) {
		npcName.setString(mapList.at(activeMap)->npcList.at(npc).conv.at(i).first);
		textBoxText.setString("");
		for (int j = 1; j <= mapList.at(activeMap)->npcList.at(npc).conv.at(i).second.length(); j++) {
			textBoxText.setString(mapList.at(activeMap)->npcList.at(npc).conv.at(i).second.substr(0, j));
			window->clear(sf::Color(200, 200, 200, 255));
			draw(*window, states);
			window->display();
			sf::sleep(sf::milliseconds(50));
		}
		sf::sleep(sf::milliseconds(mapList.at(activeMap)->npcList.at(npc).conv.at(i).second.length() * 30));
	}
	npcTalking = false;
}

void Renderer::openChest(int chest)
{
	sf::Texture texture;
	texture.loadFromFile("SpriteSheet.png");
	sf::RenderStates states;
	states.texture = &texture;
	states.transform = getTransform();
	npcTalking = true;

	for (int i = 0; i < mapList.at(activeMap)->chestList.at(chest).inv.size(); i++) {
		npcName.setString("Chest");
		textBoxText.setString("");
		std::string invText;
		int x = inv->addItem(mapList.at(activeMap)->chestList.at(chest).inv.at(i).name, mapList.at(activeMap)->chestList.at(chest).inv.at(i).amt);
		if (x == mapList.at(activeMap)->chestList.at(chest).inv.at(i).amt) {
			invText = "You recieved " + std::to_string(x) + " " + mapList.at(activeMap)->chestList.at(chest).inv.at(i).name;
			mapList.at(activeMap)->chestList.at(chest).inv.erase(mapList.at(activeMap)->chestList.at(chest).inv.begin() + i);
			i--;
		}
		else if (x == 0) {
			invText = "Your inventory is too full of " + mapList.at(activeMap)->chestList.at(chest).inv.at(i).name + " to carry any more.";
		}
		else {
			invText = "You recieved " + std::to_string(x) + " " + mapList.at(activeMap)->chestList.at(chest).inv.at(i).name;
			mapList.at(activeMap)->chestList.at(chest).inv.at(i).amt -= x;
			i--;
		}
		for (int j = 1; j <= invText.length(); j++) {
			textBoxText.setString(invText.substr(0, j));
			window->clear(sf::Color(200, 200, 200, 255));
			draw(*window, states);
			window->display();
			sf::sleep(sf::milliseconds(50));
		}
		sf::sleep(sf::milliseconds(invText.length() * 30));
	}
	npcTalking = false;
}

void Renderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (loadedGui == 0) {
		target.draw(renderMap, states);
		target.draw(player, states);
	}
	else {
		if (loadedGui == 1) {
			target.draw(Menubutton1);
			target.draw(Menubutton2);
			target.draw(Menubutton3);
			target.draw(Menubutton4);
			target.draw(circle);
			target.draw(P1);
			target.draw(P2);
			target.draw(P3);
			target.draw(Discs);
			target.draw(Skills);
			target.draw(InventoryT);
			target.draw(Exit);
			target.draw(play1);
			target.draw(play2);
			target.draw(play3);
			//target.draw(textSpawn.floater);
		}
		else if (loadedGui == 2) {
			target.draw(menu2Test);
			target.draw(backButton);
			target.draw(backbutton);
		}
		else if (loadedGui == 3) {
			target.draw(backButton);
			target.draw(rect1);
			target.draw(rect2);
			target.draw(square1);
			target.draw(square2);
			target.draw(square3);
			target.draw(square4);
			target.draw(square5);
			target.draw(square6);
			target.draw(player1Attack);
			target.draw(player1MagicAttack);
			target.draw(player1PhysicalDefense);
			target.draw(player1MagicalDefense);
			target.draw(player1Speed);
			target.draw(player1Health);
			target.draw(player1Rom);
			target.draw(player1Ram);
			target.draw(backbutton);
			target.draw(pIcon);
			target.draw(Helmet);
			target.draw(Chest);
			target.draw(Gauntlet);
			target.draw(Leg);
			target.draw(Ac1);
			target.draw(Ac2);
			target.draw(d1);
			target.draw(d2);
			target.draw(d3);
			target.draw(d4);
		}
		else if (loadedGui == 4) {
			target.draw(backButton);
			target.draw(rect1);
			target.draw(rect2);
			target.draw(square1);
			target.draw(square2);
			target.draw(square3);
			target.draw(square4);
			target.draw(square5);
			target.draw(square6);
			target.draw(player2Attack);
			target.draw(player2MagicAttack);
			target.draw(player2PhysicalDefense);
			target.draw(player2MagicalDefense);
			target.draw(player2Speed);
			target.draw(player2Health);
			target.draw(player2Rom);
			target.draw(player2Ram);
			target.draw(backbutton);
			target.draw(pIcon);
			target.draw(Helmet);
			target.draw(Chest);
			target.draw(Gauntlet);
			target.draw(Leg);
			target.draw(Ac1);
			target.draw(Ac2);
			target.draw(d1);
			target.draw(d2);
			target.draw(d3);
			target.draw(d4);
		}
		else if (loadedGui == 5) {
			target.draw(backButton);
			target.draw(rect1);
			target.draw(rect2);
			target.draw(square1);
			target.draw(square2);
			target.draw(square3);
			target.draw(square4);
			target.draw(square5);
			target.draw(square6);
			target.draw(player3Attack);
			target.draw(player3MagicAttack);
			target.draw(player3PhysicalDefense);
			target.draw(player3MagicalDefense);
			target.draw(player3Speed);
			target.draw(player3Health);
			target.draw(player3Rom);
			target.draw(player3Ram);
			target.draw(backbutton);
			target.draw(pIcon);
			target.draw(Helmet);
			target.draw(Chest);
			target.draw(Gauntlet);
			target.draw(Leg);
			target.draw(Ac1);
			target.draw(Ac2);
			target.draw(d1);
			target.draw(d2);
			target.draw(d3);
			target.draw(d4);
		}
		else if (loadedGui == 6) {
			target.draw(invTabs);
			if(subInv == 1)
				target.draw(basicInvGui);
			if (subInv == 2)
				target.draw(medInvGui);
			if (subInv == 3)
				target.draw(equipInvGui);
			target.draw(backButton);
			target.draw(backbutton);
		}
	}
	if (npcTalking) {
		target.draw(textBox);
		target.draw(textBoxText);
		target.draw(npcName);
	}
	if (transitioning) {
		target.draw(trans);
	}
}
