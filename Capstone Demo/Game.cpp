#include "Game.h"

Game::Game()
{
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "Battle Test"));
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);


	inventory = std::shared_ptr<Inventory>(new Inventory());
	inventory->printInv();
	inventory->addItem("Arrow", 150);
	inventory->printInv();
	inventory->addItem("Health Potion", 30);
	inventory->printInv();
	inventory->addItem("Dragon Scale", 50);
	inventory->printInv();
	inventory->addItem("Eternal Flame", 150);
	inventory->printInv();
	inventory->addItem("Bones", 150);
	inventory->printInv();
	inventory->addItem("Quartz", 150);
	inventory->printInv();
	inventory->addItem("Werewolf Fangs", 150);
	inventory->printInv();
	inventory->addItem("Sword", 1);
	inventory->printInv();

	renderer = std::shared_ptr<Renderer>(new Renderer(window, inventory));

	playerList.emplace_back(std::make_shared<Player>(Player()));
	playerList.emplace_back(std::make_shared<Player>(Player()));
	playerList.emplace_back(std::make_shared<Player>(Player()));
	playerList.at(0)->genRandomPlayer();
	playerList.at(1)->genRandomPlayer();
	playerList.at(2)->genRandomPlayer();

	AttackDisc disk1("Disk 1", 0, 0, 1.5);
	playerList.at(0)->equippedDiscs.emplace_back(std::make_shared<AttackDisc>(disk1));
	AttackDisc disk2("Disk 2", 0, 0, 1, 0.5);
	playerList.at(0)->equippedDiscs.emplace_back(std::make_shared<AttackDisc>(disk2));

	GUISwitchButton discs(415, 50, 250, 75, window, renderer);
	discs.action = &Renderer::switchGUI;
	discs.pass = 2;
	discs.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(discs));

	GUISwitchButton exit(510, 515, 250, 75, window, renderer);
	exit.action = &Renderer::switchGUI;
	exit.pass = 0;
	exit.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(exit));

	GUISwitchButton p1(75, 45, 150, 150, window, renderer);
	p1.action = &Renderer::switchGUI;
	p1.pass = 3;
	p1.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(p1));

	GUISwitchButton p2(300, 230, 150, 150, window, renderer);
	p2.action = &Renderer::switchGUI;
	p2.pass = 4;
	p2.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(p2));

	GUISwitchButton p3(75, 400, 150, 150, window, renderer);
	p3.action = &Renderer::switchGUI;
	p3.pass = 5;
	p3.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(p3));

	GUISwitchButton BackButton(650, 550, 150, 50, window, renderer);
	BackButton.action = &Renderer::switchGUI;
	BackButton.pass = 1;
	BackButton.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(BackButton));

	GUISwitchButton InvButton(450, 350, 250, 75, window, renderer);
	InvButton.action = &Renderer::switchGUI;
	InvButton.pass = 6;
	InvButton.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(InvButton));

	GUISwitchButton BasicInvButton(100, 50, 50, 50, window, renderer);
	BasicInvButton.action = &Renderer::switchSubGUI;
	BasicInvButton.pass = 1;
	BasicInvButton.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(BasicInvButton));

	GUISwitchButton MedInvButton(150, 50, 50, 50, window, renderer);
	MedInvButton.action = &Renderer::switchSubGUI;
	MedInvButton.pass = 2;
	MedInvButton.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(MedInvButton));

	GUISwitchButton EquipInvButton(200, 50, 50, 50, window, renderer);
	EquipInvButton.action = &Renderer::switchSubGUI;
	EquipInvButton.pass = 3;
	EquipInvButton.enabled = false;
	buttons.emplace_back(std::make_unique<GUISwitchButton>(EquipInvButton));
}

Game::~Game()
{
}

void Game::run()
{
	makeLevels();
	while (isRunning) {
		while (window->pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::Closed) {
				isRunning = false;
				window->close();
			}
			if (windowEvent.type == sf::Event::MouseButtonReleased) {
				if (windowEvent.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < buttons.size(); i++) {
						if (buttons.at(i)->enabled && buttons.at(i)->checkButton()) {
							buttons.at(i)->runFunction();
							break;
						}
					}
				}
			}
			if (windowEvent.type == sf::Event::MouseWheelScrolled) {
				if (inMenu) {
					if (windowEvent.mouseWheelScroll.delta > 0) {
						if(renderer->subInv == 1)
							renderer->basicInvGui.up();
						if (renderer->subInv == 2)
							renderer->medInvGui.up();
						if (renderer->subInv == 3)
							renderer->equipInvGui.up();
					}
					if (windowEvent.mouseWheelScroll.delta < 0) {
						if (renderer->subInv == 1)
							renderer->basicInvGui.down();
						if (renderer->subInv == 2)
							renderer->medInvGui.down();
						if (renderer->subInv == 3)
							renderer->equipInvGui.down();
					}
				}
			}
			if (windowEvent.type == sf::Event::KeyPressed) {
				if (windowEvent.key.code == sf::Keyboard::Escape && !inBattle) {
					if (renderer->loadedGui == 0) {
						renderer->loadedGui = 1;
						inMenu = true;
					}
					else if (renderer->loadedGui == 1) {
						renderer->loadedGui = 0;
						inMenu = false;
					}
					else if (renderer->loadedGui == 2 || renderer->loadedGui == 3 || renderer->loadedGui == 4 || renderer->loadedGui == 5 || renderer->loadedGui == 6) {
						renderer->loadedGui = 1;
					}
				}
				if (windowEvent.key.code == sf::Keyboard::E) {
					//stairs
					if (renderer->player.facing == 'U') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 3) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->stairList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 - 1) {
										canMove = false;
										renderer->stairTrans(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetMap,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).x * 16.0f,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).y * 16.0f);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'D') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 + 1] == 3) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->stairList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 + 1) {
										canMove = false;
										renderer->stairTrans(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetMap,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).x * 16.0f,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).y * 16.0f);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'L') {
						if ((int)(renderer->player.getPosition().x) % 16  == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 3) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->stairList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 - 1 &&
										renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->stairTrans(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetMap,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).x * 16.0f,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).y * 16.0f);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'R') {
						if ((int)(renderer->player.getPosition().x) % 16  == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 3) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->stairList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 + 1 &&
										renderer->mapList.at(renderer->activeMap)->stairList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->stairTrans(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetMap,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).x * 16.0f,
											renderer->mapList.at(renderer->activeMap)->startList.at(renderer->mapList.at(renderer->activeMap)->stairList.at(i).targetSpawn).y * 16.0f);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}

					//NPC
					if (renderer->player.facing == 'U') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->npcList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 - 1) {
										canMove = false;
										renderer->npcConv(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'D') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 + 1] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->npcList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 + 1) {
										canMove = false;
										renderer->npcConv(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'L') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->npcList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 - 1 &&
										renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->npcConv(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'R') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->npcList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 + 1 &&
										renderer->mapList.at(renderer->activeMap)->npcList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->npcConv(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}

					//Battle Trigger
					if (renderer->player.facing == 'U') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->bTriggers.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 - 1) {
										canMove = false;
										enterBattle(renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).specCond);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'D') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 + 1] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->bTriggers.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 + 1) {
										canMove = false;
										enterBattle(renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).specCond);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'L') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->bTriggers.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 - 1 &&
										renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										enterBattle(renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).specCond);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'R') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 9) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->bTriggers.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 + 1 &&
										renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										enterBattle(renderer->mapList.at(renderer->activeMap)->bTriggers.at(i).specCond);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}

					//door
					if (renderer->player.facing == 'U') {
						if ((int)(renderer->player.getPosition().y) % 16 < 8) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 5) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] = 6;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] = false;
								renderer->renderEverything();
							}
							else if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 6) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] = 5;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] = true;
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'D') {
						if ((int)(renderer->player.getPosition().y + 8) % 16 < 9) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] == 5) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] = 6;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] = false;
								renderer->renderEverything();
							}
							else if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] == 6) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] = 5;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y + 8) / 16 + 1] = true;
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'L') {
						if ((int)(renderer->player.getPosition().x) % 16 < 8) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 7) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] = 8;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] = false;
								renderer->renderEverything();
							}
							else if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 8) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] = 7;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] = true;
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'R') {
						if ((int)(renderer->player.getPosition().x + 8) % 16 < 9) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 7) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] = 8;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] = false;
								renderer->renderEverything();
							}
							else if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 8) {
								renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] = 7;
								renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x + 8) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] = true;
								renderer->renderEverything();
							}
						}
					}

					//Chest
					if (renderer->player.facing == 'U') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 - 1] == 4) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->chestList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 - 1) {
										canMove = false;
										renderer->openChest(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'D') {
						if ((int)(renderer->player.getPosition().y) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x + 8) / 16][(int)(renderer->player.getPosition().y) / 16 + 1] == 4) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->chestList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 &&
										renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16 + 1) {
										canMove = false;
										renderer->openChest(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'L') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y + 8) / 16] == 4) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->chestList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 - 1 &&
										renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->openChest(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
					else if (renderer->player.facing == 'R') {
						if ((int)(renderer->player.getPosition().x) % 16 == 0) {
							if (renderer->mapList.at(renderer->activeMap)->map[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y + 8) / 16] == 4) {
								for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->chestList.size(); i++) {
									if (renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.x == (int)(renderer->player.getPosition().x + 8) / 16 + 1 &&
										renderer->mapList.at(renderer->activeMap)->chestList.at(i).pos.y == (int)(renderer->player.getPosition().y + 8) / 16) {
										canMove = false;
										renderer->openChest(i);
										canMove = true;
									}
								}
								renderer->renderEverything();
							}
						}
					}
				}
			}
		}
		if (!inMenu && canMove && !inBattle) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				renderer->player.facing = 'U';
				if (collision('U')) {
					renderer->movePlayer(0, -1);
					checkBattle();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				renderer->player.facing = 'D';
				if (collision('D')) {
					renderer->movePlayer(0, 1);
					checkBattle();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				renderer->player.facing = 'L';
				if (collision('L')) {
					renderer->movePlayer(-1, 0);
					checkBattle();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				renderer->player.facing = 'R';
				if (collision('R')) {
					renderer->movePlayer(1, 0);
					checkBattle();
				}
			}
		}
		itsHighNoon();
	}
}

void Game::makeLevels()
{
	Map map;
	map.addHollowWallRect(0, 0, 9, 7);
	map.addFilledFloorRect(1, 1, 7, 5);
	map.addHollowWallRect(8, 0, 10, 10);
	map.addFilledFloorRect(9, 1, 8, 8);
	map.addDoor(8, 2, 'H');
	std::vector<Item> i;
	i.emplace_back(Item("Sword", 1));
	i.emplace_back(Item("Health Potion", 200));
	i.emplace_back(Item("Arrow", 20));
	i.emplace_back(Item("Dragon Scale", 100));
	map.addChest(5, 3, i);
	map.addWallLine(2, 1, 'V', 2);
	map.addEncounterSpace(9, 1, 8, 8, "dungeon", 1);
	//map 2 at 2, 3
	map.addStairs(1, 1, 'U', 1, 2, 3);
	renderer->mapList.emplace_back(std::make_unique<Map>(map));

	Map map2;
	map2.addHollowWallRect(0, 0, 7, 7);
	map2.addFilledFloorRect(1, 1, 5, 5);
	map2.addFilledFloorRect(7, 1, 13, 13);
	map2.addWallLine(7, 1, 'H', 13);
	map2.addWallLine(19, 1, 'V', 4);
	map2.addHollowWallRect(7, 5, 5, 9);
	map2.addHollowWallRect(15, 5, 5, 9);
	map2.addWallLine(8, 9, 'H', 3);
	map2.addWallLine(16, 9, 'H', 3);
	map2.addHollowWallRect(11, 14, 5, 5);
	map2.addFilledFloorRect(12, 15, 3, 3);
	map2.addStairs(1, 3, 'U', 0, 1, 2);
	map2.addDoor(6, 3, 'H');
	map2.addDoor(9, 5, 'V');
	map2.addDoor(17, 5, 'V');
	map2.addDoor(11, 11, 'H');
	map2.addDoor(15, 11, 'H');
	map2.addDoor(13, 14, 'V');
	std::vector<std::pair<std::string, std::string>> text;
	text.emplace_back(std::make_pair("Wise Guy", "Hello good sir."));
	text.emplace_back(std::make_pair("Player", "Who are you?"));
	text.emplace_back(std::make_pair("Wise Guy", "I am an NPC."));
	text.emplace_back(std::make_pair("Player", "Well, what useful information do you have for me?"));
	text.emplace_back(std::make_pair("Wise Guy", "Battling things is fun."));
	text.emplace_back(std::make_pair("Wise Guy", "That is all."));
	text.emplace_back(std::make_pair("Player", "Thank you, I think."));
	text.emplace_back(std::make_pair("Player", "Muttering: I already knew that."));
	text.emplace_back(std::make_pair("Wise Guy", "I heard that!"));
	map2.addNPC(13, 16, "Wise Guy", text);
	map2.addOther(3, 0, 13);
	map2.addOther(9, 1, 13);
	map2.addOther(13, 1, 13);
	map2.addOther(17, 1, 13);
	map2.addOther(10, 5, 10);
	map2.addOther(10, 6, 11);
	map2.addOther(10, 7, 16);
	map2.addOther(10, 8, 17);
	map2.addOther(8, 11, 14);
	std::vector<std::pair<std::string, std::string>> text2;
	text2.emplace_back(std::make_pair("Main Boss-kun", "Here shall become your grave!"));
	map2.addBattleTriggerWText(17, 7, "Boss1", text2);
	renderer->mapList.emplace_back(std::make_unique<Map>(map2));

	renderer->renderEverything();
}

void Game::itsHighNoon()
{
	window->clear(sf::Color(200, 200, 200, 255));
	sf::Texture texture;
	texture.loadFromFile("SpriteSheet.png");
	sf::RenderStates states;
	states.texture = &texture;
	states.transform = renderer->getTransform();
	renderer->basicInvGui.update();
	renderer->draw(*window, states);
	if (renderer->loadedGui == 0) {
		buttons.at(0)->enabled = false;
		buttons.at(1)->enabled = false;
		buttons.at(2)->enabled = false;
		buttons.at(3)->enabled = false;
		buttons.at(4)->enabled = false;
		buttons.at(5)->enabled = false;
		buttons.at(6)->enabled = false;
		buttons.at(7)->enabled = false;
		buttons.at(8)->enabled = false;
		buttons.at(9)->enabled = false;
		inMenu = false;
	}
	else if (renderer->loadedGui == 1) {
		buttons.at(0)->enabled = true;
		buttons.at(1)->enabled = true;
		buttons.at(2)->enabled = true;
		if (playerList.size() > 1)
			buttons.at(3)->enabled = true;
		if (playerList.size() > 2)
			buttons.at(4)->enabled = true;
		buttons.at(5)->enabled = false;
		buttons.at(6)->enabled = true;
		buttons.at(7)->enabled = false;
		buttons.at(8)->enabled = false;
		buttons.at(9)->enabled = false;
		renderer->subInv = 0;
		renderer->textSpawn.move();
	}
	else if (renderer->loadedGui == 2) {
		buttons.at(0)->enabled = false;
		buttons.at(1)->enabled = false;
		buttons.at(2)->enabled = false;
		buttons.at(3)->enabled = false;
		buttons.at(4)->enabled = false;
		buttons.at(5)->enabled = true;
		buttons.at(6)->enabled = false;
	}
	else if (renderer->loadedGui == 3 || renderer->loadedGui == 4 || renderer->loadedGui == 5) {
		buttons.at(0)->enabled = false;
		buttons.at(1)->enabled = false;
		buttons.at(2)->enabled = false;
		buttons.at(3)->enabled = false;
		buttons.at(4)->enabled = false;
		buttons.at(5)->enabled = true;
		buttons.at(6)->enabled = false;

		renderer->player1Attack.setString("Atk: " + std::to_string(playerList.at(0)->pAtk));
		renderer->player1MagicAttack.setString("MAtk: " + std::to_string(playerList.at(0)->mAtk));
		renderer->player1PhysicalDefense.setString("Def: " + std::to_string(playerList.at(0)->pDef));
		renderer->player1MagicalDefense.setString("MDef: " + std::to_string(playerList.at(0)->mDef));
		renderer->player1Speed.setString("Spd: " + std::to_string(playerList.at(0)->speed));
		renderer->player1Health.setString("Health: " + std::to_string(*playerList.at(0)->curHealth) + "/" + std::to_string(*playerList.at(0)->maxHealth));
		renderer->player1Rom.setString("ROM: " + std::to_string(playerList.at(0)->curRom) + "/" + std::to_string(playerList.at(0)->maxRom));
		renderer->player1Ram.setString("RAM: " + std::to_string(playerList.at(0)->curRam) + "/" + std::to_string(playerList.at(0)->maxRam));

		if (playerList.size() > 1) {
			renderer->player2Attack.setString("Atk: " + std::to_string(playerList.at(1)->pAtk));
			renderer->player2MagicAttack.setString("MAtk: " + std::to_string(playerList.at(1)->mAtk));
			renderer->player2PhysicalDefense.setString("Def: " + std::to_string(playerList.at(1)->pDef));
			renderer->player2MagicalDefense.setString("MDef: " + std::to_string(playerList.at(1)->mDef));
			renderer->player2Speed.setString("Spd: " + std::to_string(playerList.at(1)->speed));
			renderer->player2Health.setString("Health: " + std::to_string(*playerList.at(1)->curHealth) + "/" + std::to_string(*playerList.at(1)->maxHealth));
			renderer->player2Rom.setString("ROM: " + std::to_string(playerList.at(1)->curRom) + "/" + std::to_string(playerList.at(1)->maxRom));
			renderer->player2Ram.setString("RAM: " + std::to_string(playerList.at(1)->curRam) + "/" + std::to_string(playerList.at(1)->maxRam));
		}

		if (playerList.size() > 2) {
			renderer->player3Attack.setString("Atk: " + std::to_string(playerList.at(2)->pAtk));
			renderer->player3MagicAttack.setString("MAtk: " + std::to_string(playerList.at(2)->mAtk));
			renderer->player3PhysicalDefense.setString("Def: " + std::to_string(playerList.at(2)->pDef));
			renderer->player3MagicalDefense.setString("MDef: " + std::to_string(playerList.at(2)->mDef));
			renderer->player3Speed.setString("Spd: " + std::to_string(playerList.at(2)->speed));
			renderer->player3Health.setString("Health: " + std::to_string(*playerList.at(2)->curHealth) + "/" + std::to_string(*playerList.at(2)->maxHealth));
			renderer->player3Rom.setString("ROM: " + std::to_string(playerList.at(2)->curRom) + "/" + std::to_string(playerList.at(2)->maxRom));
			renderer->player3Ram.setString("RAM: " + std::to_string(playerList.at(2)->curRam) + "/" + std::to_string(playerList.at(2)->maxRam));
		}
	}
	else if (renderer->loadedGui == 6) {
		if (renderer->subInv == 0)
			renderer->subInv = 1;
		buttons.at(0)->enabled = false;
		buttons.at(1)->enabled = false;
		buttons.at(2)->enabled = false;
		buttons.at(3)->enabled = false;
		buttons.at(4)->enabled = false;
		buttons.at(5)->enabled = true;
		buttons.at(6)->enabled = false;
		buttons.at(7)->enabled = true;
		buttons.at(8)->enabled = true;
		buttons.at(9)->enabled = true;
		renderer->basicInvGui.update();
		renderer->medInvGui.update();
		renderer->equipInvGui.update();
		if (renderer->subInv == 1) {
			renderer->invTabs.setTexture(renderer->basicTab);
		}
		else if (renderer->subInv == 2) {
			renderer->invTabs.setTexture(renderer->medTab);
		}
		else if (renderer->subInv == 3) {
			renderer->invTabs.setTexture(renderer->equipTab);
		}
	}
	window->display();
}

bool Game::collision(char d)
{
	if (d == 'U') {
		if ((int)(renderer->player.getPosition().y) % 16 == 0) {
			if (renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16][(int)(renderer->player.getPosition().y) / 16 - 1]) {
				return false;
			}
			if ((int)(renderer->player.getPosition().x) % 16 != 0 && renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y) / 16 - 1]) {
				return false;
			}
		}
	}
	else if (d == 'D') {
		if ((int)(renderer->player.getPosition().y) % 16 == 0) {
			if (renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x / 16)][(int)(renderer->player.getPosition().y / 16) + 1]) {
				return false;
			}
			if ((int)(renderer->player.getPosition().x) % 16 != 0 && renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y) / 16 + 1]) {
				return false;
			}
		}
	}
	else if (d == 'L') {
		if ((int)(renderer->player.getPosition().x) % 16 == 0) {
			if (renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y) / 16]) {
				return false;
			}
			if ((int)(renderer->player.getPosition().y) % 16 != 0 && renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 - 1][(int)(renderer->player.getPosition().y) / 16 + 1]) {
				return false;
			}
		}
	}
	else if (d == 'R') {
		if ((int)(renderer->player.getPosition().x) % 16 == 0) {
			if (renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y) / 16]) {
				return false;
			}
			if ((int)(renderer->player.getPosition().y) % 16 != 0 && renderer->mapList.at(renderer->activeMap)->collision[(int)(renderer->player.getPosition().x) / 16 + 1][(int)(renderer->player.getPosition().y) / 16 + 1]) {
				return false;
			}
		}
	}
	return true;
}

void Game::checkBattle()
{
	for (int i = 0; i < renderer->mapList.at(renderer->activeMap)->encounters.size(); i++) {
		if (renderer->player.getPosition().x >= renderer->mapList.at(renderer->activeMap)->encounters.at(i).x &&
			renderer->player.getPosition().x + renderer->player.size.x <= renderer->mapList.at(renderer->activeMap)->encounters.at(i).x + renderer->mapList.at(renderer->activeMap)->encounters.at(i).xL &&
			renderer->player.getPosition().y >= renderer->mapList.at(renderer->activeMap)->encounters.at(i).y &&
			renderer->player.getPosition().y + renderer->player.size.y <= renderer->mapList.at(renderer->activeMap)->encounters.at(i).y + renderer->mapList.at(renderer->activeMap)->encounters.at(i).yL) {
			if (rand() % 100 < 1) {
				enterBattle("");
			}
		}
	}
}

void Game::enterBattle(std::string s)
{
	inBattle = true;
	sf::Texture texture;
	texture.loadFromFile("SpriteSheet.png");
	sf::RenderStates states;
	states.texture = &texture;
	states.transform = renderer->getTransform();
	for (int i = 0; i < 20; i++) {
		renderer->rotate(2.0f * i);
		states.transform = renderer->getTransform();
		window->clear(sf::Color(200, 200, 200, 255));
		renderer->draw(*window, states);
		window->display();
		sf::sleep(sf::milliseconds(10));
	}
	if(s.compare("") == 0)
		BattleManager battle(window, playerList);
	else
		BattleManager battle(window, playerList, s);
	renderer->setRotation(0.0f);
	inBattle = false;
	itsHighNoon();
}
