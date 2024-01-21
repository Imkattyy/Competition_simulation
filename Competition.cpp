#include "Competition.h"


Competition::Competition(long maxParticipants) {
    this->maxParticipants = maxParticipants;
}

void Competition::openRegistration() {
    cout << endl << "Регистрация успешно открыта. Участники могут регистрироваться." << endl;
}

int Competition::getParticipantsAmount() {
    return participants.size();
}

void Competition::registerParticipant(int nParticipants) {
    if (nParticipants >= maxParticipants) {
        cout << endl << "Участники уже набраны. Свободных лотов, к сожалению, нет." << endl;
        return;
    }

    string name;
    cout << endl << "Введите имя участника: ";
    cin >> name;
    auto *participant = new Participant(nParticipants, name, 0, true);
    participants.push_back(participant);
    cout << endl << "Участник успешно зарегистрирован." << endl;
}

void Competition::closeRegistration() {
    if (getParticipantsAmount() == 0)
        cout << endl << "Невозможно завершить регистрацию, тк достаточное кол-во участников ещё не набрано." << endl;
    else
        cout << endl << "Регистрация окончена." << endl;
}

void Competition::registerPoint(string choice) {
    string id, name;
    int nPoints;
    cout << endl << "Введите соответственно через пробел ID участника и кол-во начисляемых(штрафных) баллов:"
         << endl;
    cin >> id >> nPoints;

    bool isPoints = false;
    for (Participant *participant: participants)
        if (participant->getId() == id) {
            if (choice == "1")
                participant->addPoints(nPoints);
            else
                participant->addPoints(-nPoints);
            name = participant->getName();
            isPoints = true;
            break;
        }

    if (isPoints)
        cout << endl << "Баллы успешно начислены участнику " << name << " (" << id << ")" << endl;
    else
        cout << endl
             << "Баллы начислены не были, тк участника с таким ID не существует. Пожалуйста, повторите ввод."
             << endl;
}

void Competition::openCompetition() {
    cout << endl << "Начало конкурса!" << endl;
}

int findGreatestPosition(vector<Participant *> list, int startPosition, int listLength) {
    int greatestPosition = startPosition;

    for (int i = startPosition; i < listLength; i++) {
        if (list[i]->getPoints() > list[greatestPosition]->getPoints())
            greatestPosition = i;
    }
    return greatestPosition;
}

void selectionSort(vector<Participant *> &list, int listLength) {
    for (int i = 0; i < listLength; i++) {
        int greatestPosition = findGreatestPosition(list, i, listLength);
        swap(list[i], list[greatestPosition]);
    }
}

void Competition::sortParticipants() {
    selectionSort(participants, participants.size());
}

void Competition::writeParticipantsToFile() {
    if (participants.empty()) {
        cout << endl << "Список участников пуст.";
        return;
    }
    ofstream file(fileName);
    if (!file) {
        cerr << "Файл не может быть открыт, проверьте корректность всех данных.";
        return;
    }

    file << participants.size() << endl;
    for (Participant *participant: participants)
        file << participant->getId() << " " << participant->getName() << " " << participant->getPoints()
             << " " << participant->getIsAbsent() << endl;
}


void Competition::competitionResults() {
    int nWinners = 0;

    for (int i = 0; i < participants.size(); i++) {
        if (!participants[i]->getIsAbsent()) {
            cout << i + 1 << " место – " << participants[i]->getName() << " " << "(" << participants[i]->getId()
                 << ") – " << participants[i]->getPoints() << " баллов" << endl;
            nWinners++;
        }
        if (nWinners == 3)
            break;
    }

    if (nWinners == 0)
        cout << endl << "Победители выявлены не были, так как никто не явился." << endl;
}

void Competition::outputParticipants() {
    cout << endl << "ID\tИмя участника\tБаллы" << endl;
    for (Participant *participant: participants) {
        cout << participant->getId() << "\t" << participant->getName() << "\t\t" << participant->getPoints()
             << endl;
    }
}

void Competition::endOfCompetition() {
    cout << endl << "Конкурс окончен. Спасибо всем за участие!" << endl;

    sortParticipants();
    competitionResults();
    writeParticipantsToFile();
}

void Competition::inputParticipantsFromFile() {
    ifstream file(fileName);
    int n;
    file >> n;

    for (int i = 0; i < maxParticipants; i++) {
        string id, name;
        int points;
        bool isAbsent;
        file >> id >> name >> points >> isAbsent;
        auto *participant = new Participant(stoi(id), name, points, isAbsent);
        participants.push_back(participant);
    }

    file.close();
    cout << endl << "Данные об участниках были успешно импортированы" << endl;
}
