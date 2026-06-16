#pragma once
#include <string>

class Player {
private:
    std::string name;
    std::string loveInterestName;
    std::string gender;
    int totalPoints;
    int eventCount;
    int psychopathCount;

public:
    Player();
    void setName(const std::string& n);
    void setLoveInterestName(const std::string& n);
    void setGender(const std::string& g);
    void addPoints(int points, const std::string& optionType);
    std::string getName() const;
    std::string getLoveInterestName() const;
    std::string getGender() const;
    int getTotalPoints() const;
    int getEventCount() const;
    int getPsychopathCount() const;
    void incrementEventCount();
    // Setters para snapshot (regresar)
    void setTotalPoints(int p);
    void setPsychopathCount(int c);
    void setEventCount(int c);
    std::string getRelationshipType() const;
    bool hasPsychopathPath() const;
};
