#include "EffectHandler.h"

std::string EffectHandler::activateEffect(int p) {
	return "";
}

std::vector<Effect> EffectHandler::find(std::string effectType, int user) 
{
	std::vector<Effect> es;
	for (int i = 0; i < effects.size(); i++) {
		if ((effects.at(i)->user == user && effects.at(i)->user != -1)) {
			if (effects.at(i)->effectType == effectType || effects.at(i)->actType == effectType || effects.at(i)->type == effectType) {
				es.emplace_back(*effects.at(i));
			}
		}
	}
	return es;
}

void EffectHandler::recalcStatMods() {

}

std::string EffectHandler::getString(std::string effect, int target, int user, double strength)
{
	std::string str = "";
	if (effect == "physicalAttackChange" || effect == "physicalDefenseChange" || effect == "magicalAttackChange" || effect == "magicalDefenseChange" || effect == "speedChange" || effect == "accuracyChange") {
		if (strength == 1)
			return "";
		if (strength > 1.33)
			effect += "GreatInc";
		else if (strength > 1)
			effect += "Inc";
		else if (strength > 0.66)
			effect += "Dec";
		else
			effect += "GreatDec";
	}
	for (int i = 0; i < textListL; i++) {
		if (text[i][0] == effect)
			str = text[i][1];
	}
	if (str.find("TARGET") != std::string::npos)
		str.replace(str.find("TARGET"), 6, pawns->at(target).name);
	if (str.find("USER") != std::string::npos)
		str.replace(str.find("USER"), 4, "replace when I figure out how to get the players over here");
	if (str.find("STRENGTH") != std::string::npos)
		str.replace(str.find("STRENGTH"), 8, std::to_string((int)strength));
	return str;
}

std::string EffectHandler::checkCanMove(int target){
	std::vector<Effect> p = find("moveDisable", target);
	for (int i = 0; i < p.size(); i++) {
			
			if((p.at(i).type == "paralyzed" && rand() % 100 < 25) || p.at(i).type != "paralyzed")
				return getString(p.at(i).type, target);
	}
	return "canMove";
}