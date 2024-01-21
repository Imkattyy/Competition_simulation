#include <iostream>

using namespace std;

#ifndef COURSEWORK_PARTICIPANT_H
#define COURSEWORK_PARTICIPANT_H

class Participant {
private:
    string id;
    string name;
    int points;
    bool isAbsent;

public:
    Participant(int nParticipants, string name, int points, bool isAbsent);

    string getId();
    string getName();
    int getPoints();
    bool getIsAbsent();

    void addPoints(int points);

};


#endif //COURSEWORK_PARTICIPANT_H
