#include <iostream>
#include "Participant.h"
#include "Competition.h"

using namespace std;


int main() {
    string fromFile;
    int nParticipants;

    cout << "Добро пожаловать!";
    do {
        cout << endl << "Возможные операции:" << endl;
        cout << "1 – организовать конкурс с уже существующим списком участников" << endl;
        cout << "2 – начать новый конкурс" << endl;
        cout << "Введите номер желаемой операции: ";
        getline(cin, fromFile);

        if (fromFile == "1") {
            ifstream file("/Users/imkattyy/CLionProjects/courseWork/competition.txt");
            if (!file) {
                cout
                        << "Файл не может быть открыт. Данные не могут быть извлечены. Пожалуйста, зарегистрируйте участников вновь или уточните путь к файлу.";
                fromFile = "2";
                break;
            }

            if (file.peek() == EOF) {
                cout
                        << "Данные в файле отсутствуют. Пожалуйста, зарегистрируйте участников вновь или уточните путь к файлу."
                        << endl;
                fromFile = "2";
                break;
            }

            file >> nParticipants;


        } else if (fromFile != "2") {
            cerr << "Неверно введен номер операции. Пожалуйста, повторите ввод." << endl;
        }
    } while (fromFile != "1" && fromFile != "2");

    if (fromFile == "2") {
        cout << endl << "Введите максимальное кол-во участников конкурса: ";

        string maxParticipants;
        bool isNumber = false;
        do {
            getline(cin, maxParticipants);
            for (char c: maxParticipants) {
                if (!isdigit(c)) {
                    cerr << "Введено не число или число введено неверно. Пожалуйста, повторите ввод: ";
                    break;
                }

                if (stol(maxParticipants) > INT_MAX) {
                    cerr << "Число больше максимального возможного. Пожалуйста, повторите ввод: ";
                    break;
                }

                if (maxParticipants == "0") {
                    cerr << "Число участников не может быть нулевым. Пожалуйста, повторите ввод.";
                    break;
                }

                isNumber = true;
            }
        } while (!isNumber);

        nParticipants = stoi(maxParticipants);
    }

    auto *competition = new Competition(nParticipants);
    if (fromFile == "1")
        competition->inputParticipantsFromFile();

    string operation;
    do {
        cout << endl << "Возможные операции:" << endl;
        cout << "1 – открытие регистрации" << endl;
        cout << "2 – отмена конкурса с сохранением данных об участниках в файл" << endl;
        cout << "3 – отмена конкурса без сохранения данных об участниках в файл" << endl;
        cout << "Введите номер желаемой операции: ";
        cin >> operation;

        if (operation == "1")
            competition->openRegistration();
        else if (operation == "2") {
            competition->writeParticipantsToFile();
            return 0;
        } else if (operation == "3")
            return 0;
        else
            cerr << "Неверно введен номер операции. Повторите, пожалуйста, ввод." << endl;

    } while (operation != "1");

    do {
        cout << endl << "Возможные операции:" << endl;
        cout << "1 – регистрация участника" << endl;
        cout << "2 – завершение регистрации участников" << endl;
        cout << "3 – выход из программы с сохранением данных об участниках в файл" << endl;
        cout << "4 – выход из программы без сохранения данных об участниках в файл" << endl;
        cout << "Введите номер желаемой операции: ";
        cin >> operation;

        if (operation == "1")
            competition->registerParticipant(competition->getParticipantsAmount());
        else if (operation == "2")
            competition->closeRegistration();
        else if (operation == "3") {
            competition->writeParticipantsToFile();
            return 0;
        } else if (operation == "4")
            return 0;
        else
            cerr << "Неверно введен номер операции. Повторите, пожалуйста, ввод." << endl;

    } while (operation != "2" || operation == "2" && competition->getParticipantsAmount() == 0);

    do {
        cout << endl << "Возможные операции:" << endl;
        cout << "1 – проведение конкурса" << endl;
        cout << "2 – выход из программы с сохранением данных об участниках в файл." << endl;
        cout << "3 – выход из программы без сохранения данных об участниках в файл." << endl;
        cout << "Введите номер желаемой операции: ";
        cin >> operation;

        if (operation == "1")
            competition->openCompetition();
        else if (operation == "2") {
            competition->writeParticipantsToFile();
            return 0;
        } else if (operation == "3")
            return 0;
        else
            cerr << "Неверно введен номер операции. Повторите, пожалуйста, ввод." << endl;

    } while (operation != "1");

    do {
        cout << endl << "Список возможных операций" << endl;
        cout << "1 – начисление участнику баллов" << endl;
        cout << "2 – штраф участнику" << endl;
        cout << "3 – отображение списка участников" << endl;
        cout << "4 – выход из программы с сохранением данных об участниках в файл." << endl;
        cout << "5 – выход из программы без сохранения данных об участниках в файл." << endl;
        cout << "6 – завершение конкурса" << endl;
        cout << "Выберите операцию из предложенных: ";
        cin >> operation;

        if (operation == "1" || operation == "2")
            competition->registerPoint(operation);
        else if (operation == "3")
            competition->outputParticipants();
        else if (operation == "4") {
            competition->writeParticipantsToFile();
            return 0;
        } else if (operation == "5")
            return 0;
        else if (operation != "6")
            cout << endl << "Введена несуществующая операция. Пожалуйста, повторите ввод." << endl;

    } while (operation != "6");


    do {
        cout << endl << "Возможные операции:" << endl;
        cout << "1 – подведение итогов" << endl;
        cout << "2 – выход из программы с сохранением данных об участниках в файл." << endl;
        cout << "3 – выход из программы без сохранения данных об участниках в файл." << endl;
        cout << "Введите номер желаемой операции: ";
        cin >> operation;

        if (operation == "1")
            competition->endOfCompetition();
        else if (operation == "2") {
            competition->writeParticipantsToFile();
            return 0;
        } else if (operation == "3")
            return 0;
        else
            cerr << "Неверно введен номер операции. Повторите, пожалуйста, ввод." << endl;
    } while (operation != "1");


    return 0;
}