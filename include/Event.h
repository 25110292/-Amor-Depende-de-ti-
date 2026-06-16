#pragma once
#include <string>
#include <vector>

struct Option {
    std::string text;
    int points;
    std::string type; // "Romantico", "PorLastima", "Toxico", "Psicopata"
};

struct Event {
    int id;
    std::string title;
    std::string description;
    std::string imagePath;
    std::vector<Option> options;
};
