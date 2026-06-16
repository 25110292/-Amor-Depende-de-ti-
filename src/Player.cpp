#include "../include/Player.h"

Player::Player() : name(""), loveInterestName(""), gender(""), totalPoints(0), eventCount(0), psychopathCount(0) {}

void Player::setName(const std::string& n) { name = n; }
void Player::setLoveInterestName(const std::string& n) { loveInterestName = n; }
void Player::setGender(const std::string& g) { gender = g; }

void Player::addPoints(int points, const std::string& optionType) {
    totalPoints += points;
    if (optionType == "Psicopata") psychopathCount++;
}

std::string Player::getName() const { return name; }
std::string Player::getLoveInterestName() const { return loveInterestName; }
std::string Player::getGender() const { return gender; }
int Player::getTotalPoints() const { return totalPoints; }
int Player::getEventCount() const { return eventCount; }
int Player::getPsychopathCount() const { return psychopathCount; }
void Player::incrementEventCount() { eventCount++; }

void Player::setTotalPoints(int p) { totalPoints = p; }
void Player::setPsychopathCount(int c) { psychopathCount = c; }
void Player::setEventCount(int c) { eventCount = c; }

std::string Player::getRelationshipType() const {
    if (hasPsychopathPath()) return "Psicopata";
    if (totalPoints >= 22) return "Romantico";
    if (totalPoints >= 13) return "PorLastima";
    if (totalPoints >= 5)  return "Toxico";
    return "Psicopata";
}

bool Player::hasPsychopathPath() const { return psychopathCount >= 3; }
