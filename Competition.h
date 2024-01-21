#include <iostream>
#include <vector>
#include <fstream>
#include "Participant.h"

#ifndef COURSEWORK_COMPETITION_H
#define COURSEWORK_COMPETITION_H


class Competition {
private:
    long maxParticipants;
    vector <Participant*> participants;

    const string fileName = "/Users/imkattyy/CLionProjects/courseWork/competition.txt";

public:
    Competition(long maxParticipants);
    void openRegistration();
    void registerParticipant(int nParticipants);
    void closeRegistration();
    void registerPoint(string choice);
    void openCompetition();
    void endOfCompetition();
    int getParticipantsAmount();
    void sortParticipants();
    void competitionResults();
    void outputParticipants();
    void writeParticipantsToFile();
    void inputParticipantsFromFile();
};


#endif //COURSEWORK_COMPETITION_H
