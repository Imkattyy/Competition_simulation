#include "Participant.h"

Participant::Participant(int nParticipants, string name, int points, bool isAbsent) {
    this->id = to_string(++nParticipants);
    this->points = points;
    this->name = name;
    this->isAbsent = isAbsent;
}

string Participant::getId() {
    return id;
}

string Participant::getName() {
    return name;
}

int Participant::getPoints() {
    return points;
}

bool Participant::getIsAbsent() {
    return isAbsent;
}

void Participant::addPoints(int points) {
    this->points += points;
    if (isAbsent)
        isAbsent = false;
}



