#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class NPC{
public:
	sf::Vector2f pos;
	std::string name;
	std::vector<std::pair<std::string, std::string>> conv;
	NPC() {}

	NPC(int x, int y, std::string n) {
		pos.x = x;
		pos.y = y;
		name = n;
	}

	NPC(int x, int y, std::vector<std::pair<std::string, std::string>> s) {
		pos.x = x;
		pos.y = y;
		name = "";
		for (int i = 0; i < s.size(); i++)
			conv.emplace_back(s.at(i));
	}

	NPC(int x, int y, std::string n, std::vector<std::pair<std::string, std::string>> s) {
		pos.x = x;
		pos.y = y;
		name = n;
		for(int i = 0; i < s.size(); i++)
			conv.emplace_back(s.at(i));
	}

	void addText(std::string name, std::string text) {
		if (name.compare("") == 0)
			name = conv.at(conv.size() - 1).first;
		conv.emplace_back(std::make_pair(name, text));
	}

	void replaceText(std::vector<std::pair<std::string, std::string>> s) {
		conv.clear();
		for (int i = 0; i < s.size(); i++)
			conv.emplace_back(s.at(i));
	}
};

#endif