/*
ADVANTAGES/DISADVANTAGES LINKED LIST

Advantage: the linked list is dynamic meaning it can grow and shring in size to accomodate
however many commands/descriptions you want

Disadvantage: accessing elements in a linked list requires searching the whole list which 
isn't very efficient

ADVANTAGES/DISADVANTAGES ARRAY

Advantage: you can use indexing to quickly access a certain position in the array making it easier
to find users and their points

Disadvantage: an array may need to be resized if the contents of it start to exceed the set size. For 
my program I set the size of the array to 10 so if 11 profiles tried to be store, issues would arise.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "linkedList.h";
#include "array.h";

using namespace std;


int main()
{

    ifstream inputFStreamCommands;
    ifstream inputFStreamProfiles;

    inputFStreamCommands.open("commands.csv", ios::in);
    inputFStreamProfiles.open("profiles.csv", ios::in);

    ofstream outputFStreamCommands;
    ofstream outputFStreamProfiles;

    string userName, newCommandToAdd, oldCommandTodelete;
    string newDescriptionToAdd;
    int selection;

    LinkedList<string, string> commandList;
    Array<string, int> profileArray;

    if (inputFStreamCommands.is_open())
    {
        string line;

        while (getline(inputFStreamCommands, line))
        {
            char* cline = &line[0];

            char* command = strtok(cline, ",");
            char* description = strtok(nullptr, "");

            if (command != nullptr && description != nullptr)
            {
                string commandStr = command;
                string descriptionStr = description;

                if (!descriptionStr.empty() && descriptionStr.front() == '"' && descriptionStr.back() == '"')
                {
                    descriptionStr = descriptionStr.substr(1, descriptionStr.size() - 2);
                }

                commandList.insertAtFront(commandStr, descriptionStr);
            }
        }

        inputFStreamCommands.close();
    }
    else
    {
        cout << "Could not open commands.csv file." << endl;
    }

    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        cout << "Your selection: ";
        cin >> selection;

        if (cin.fail()) // the input is not an integer
        {
            cout << "Your selection is invalid. Please select again." << endl;
            cout << "=============================================================================" << endl << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            switch (selection)
            {
            case 1: // Game Rules
            {
                cout << "================================= Game Rule ===================================" << endl;
                cout << "To play the game, select \"2\" where you will be prompted for your name and number of questions.\n";
                cout << "Each question presents a specific Linux command where you will be able to choose from 3 different options. Each correct answer yields a point.\n";
                cout << "You can also add and delete commands as needed.\n";
                cout << "================================= Game Rule ===================================" << endl << endl;

                break;
            }

            case 2: case 3: // 2. Play Game; 3. Load Previous Game
            {
                cout << "Please enter your name: ";
                cin >> userName;

                if (selection == 2)
                {
                    // add user to profile array
                    profileArray.insertInArray(userName, 0);

                    // let user choose how many commands to match
               
                    int numCommands;
                    cout << "Enter the amount of commands you want to match: ";
                    cin >> numCommands;

                    int curCommand = 1;
                    const int maxCommands = 100;
                    string usedCommands[maxCommands];
                    int usedCommandCount = 0;

                    while (curCommand <= numCommands)
                    {
                        Node<string, string>* commandNode = nullptr;
                        string command, correctDescription;
                        bool used = true;

                        while (used == true)
                        {
                            used = false;

                            int randIndex = rand() % commandList.getSize();
                            commandNode = commandList.getNodeAt(randIndex);
                            command = commandNode->getCommand();
                            correctDescription = commandNode->getDescription();

                            for (int i = 0; i < usedCommandCount; i++)
                            {
                                if (usedCommands[i] == command)
                                {
                                    used = true;
                                    break;
                                }
                            }
                        }

                        usedCommands[usedCommandCount++] = command;

                        string descriptions[3];
                        descriptions[0] = correctDescription;

                        int numDescriptions = 1;
                        while (numDescriptions < 3)
                        {
                            int randIndex = rand() % commandList.getSize();
                            string randDescription = commandList.getNodeAt(randIndex)->getDescription();

                            if (randDescription != correctDescription)
                            {
                                descriptions[numDescriptions++] = randDescription;
                            }
                        }

                        for (int i = 2; i > 0; i--)
                        {
                            int j = rand() % (i + 1);

                            string temp = descriptions[j];
                            descriptions[j] = descriptions[i];
                            descriptions[i] = temp;
                        }

                        cout << "Question " << curCommand << ": What does " << command << " do?" << endl;

                        for (int i = 0; i < 3; i++)
                        {
                            cout << (i + 1) << "- " << descriptions[i] << endl;
                        }

                        int userAnswer;
                        cout << "Which do you think is correct? (1-3): ";
                        cin >> userAnswer;

                        if (descriptions[userAnswer - 1] == correctDescription)
                        {
                            cout << "You earned a point!" << endl << endl;

                            profileArray.getNodeAt(profileArray.getSize() - 1)->setPoints(profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() + 1);
                        }
                        else
                        {
                            cout << "Incorrect, the correct answer was: " << correctDescription << endl << endl;

                            profileArray.getNodeAt(profileArray.getSize() - 1)->setPoints(profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() - 1);

                        }

                        ++curCommand;
                    }

                    cout << "Good game, your total points is " << profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() << endl;
                    
                }

                if (selection == 3)
                {
                    bool userFound = false;
                    int userIndex = -1;

                    for (int i = 0; i < profileArray.getSize(); i++)
                    {
                        if (profileArray.getNodeAt(i)->getName() == userName)
                        {
                            userFound = true;
                            userIndex = i;
                            break;
                        }
                    }

                    if (userFound)
                    {
                        cout << "Hi " << userName << ", nice to see you again!" << endl;
                        cout << "You have " << profileArray.getNodeAt(userIndex)->getPoints() << " points." << endl << endl;

                        int numCommands;
                        cout << "Enter the amount of commands you want to match: ";
                        cin >> numCommands;

                        int curCommand = 1;
                        const int maxCommands = 100;
                        string usedCommands[maxCommands];
                        int usedCommandCount = 0;

                        while (curCommand <= numCommands)
                        {
                            Node<string, string>* commandNode = nullptr;
                            string command, correctDescription;
                            bool used = true;

                            while (used == true)
                            {
                                used = false;

                                int randIndex = rand() % commandList.getSize();
                                commandNode = commandList.getNodeAt(randIndex);
                                command = commandNode->getCommand();
                                correctDescription = commandNode->getDescription();

                                for (int i = 0; i < usedCommandCount; i++)
                                {
                                    if (usedCommands[i] == command)
                                    {
                                        used = true;
                                        break;
                                    }
                                }
                            }

                            usedCommands[usedCommandCount++] = command;

                            string descriptions[3];
                            descriptions[0] = correctDescription;

                            int numDescriptions = 1;
                            while (numDescriptions < 3)
                            {
                                int randIndex = rand() % commandList.getSize();
                                string randDescription = commandList.getNodeAt(randIndex)->getDescription();

                                if (randDescription != correctDescription)
                                {
                                    descriptions[numDescriptions++] = randDescription;
                                }
                            }

                            for (int i = 2; i > 0; i--)
                            {
                                int j = rand() % (i + 1);

                                string temp = descriptions[j];
                                descriptions[j] = descriptions[i];
                                descriptions[i] = temp;
                            }

                            cout << "Question " << curCommand << ": What does " << command << " do?" << endl;

                            for (int i = 0; i < 3; i++)
                            {
                                cout << (i + 1) << "- " << descriptions[i] << endl;
                            }

                            int userAnswer;
                            cout << "Which do you think is correct? (1-3): ";
                            cin >> userAnswer;

                            if (descriptions[userAnswer - 1] == correctDescription)
                            {
                                cout << "You earned a point!" << endl << endl;

                                profileArray.getNodeAt(profileArray.getSize() - 1)->setPoints(profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() + 1);
                            }
                            else
                            {
                                cout << "Incorrect, the correct answer was: " << correctDescription << endl << endl;

                                profileArray.getNodeAt(profileArray.getSize() - 1)->setPoints(profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() - 1);

                            }

                            ++curCommand;
                        }

                        cout << "Good game, your total points is " << profileArray.getNodeAt(profileArray.getSize() - 1)->getPoints() << endl;

                    }
                    else
                    {
                        cout << "User not found! Enter option 2 to start a new game." << endl;
                    }

                   
                }

                break;
            }

            case 4: // Add Command
            {
                cout << "To add a command to the library, please enter the command name that you would add: ";
                cin >> newCommandToAdd;

                cout << "Now write the description to the command you just added: ";
                cin >> newDescriptionToAdd;

                bool duplicateFound = false;
                Node<string, string>* pCur = commandList.getHeadPtr();

                while (pCur != nullptr)
                {
                    if (pCur->getCommand() == newCommandToAdd)
                    {
                        duplicateFound = true;
                        break;
                    }

                    pCur = pCur->getNextPtr();
                }

                if (duplicateFound)
                {
                    cout << "That command already exists, try adding a different one!" << endl;
                }
                else
                {
                    commandList.insertAtFront(newCommandToAdd, newDescriptionToAdd);
                    cout << "Command added." << endl;
                }

                break;
            }

            case 5: // Remove Command
            {
                cout << "Please enter the name of the command that you would remove: ";
                cin >> oldCommandTodelete;

                Node<string, string>* pCur = commandList.getHeadPtr();
                Node<string, string>* pPrev = nullptr;

                bool commandFound = false;

                while (pCur != nullptr)
                {
                    if (pCur->getCommand() == oldCommandTodelete)
                    {
                        commandFound = true;
                        break;
                    }

                    pPrev = pCur;
                    pCur = pCur->getNextPtr();
                }

                if (commandFound)
                {
                    if (pPrev == nullptr)
                    {
                        commandList.setHeadPtr(pCur->getNextPtr());
                    }
                    else
                    {
                        pPrev->setNextPtr(pCur->getNextPtr());
                    }

                    delete pCur;

                    cout << "Removed successfully!" << endl;
                }
                else
                {
                    cout << "Command not found!" << endl;
                }

                break;
            }

            case 6: // Exit
            {
                outputFStreamCommands.open("commands.csv");
                if (!outputFStreamCommands)
                {
                    cout << "Couldn't open commands for writting" << endl;
                    return 1;
                }

                Node<string, string>* curCommand = commandList.getHeadPtr();

                while (curCommand != nullptr)
                {
                    outputFStreamCommands << curCommand->getCommand() << ",\"" << curCommand->getDescription() << "\"" << endl;
                    curCommand = curCommand->getNextPtr();
                }

                outputFStreamCommands.close();

                outputFStreamProfiles.open("profiles.csv");

                if (!outputFStreamProfiles)
                {
                    cout << "Couldn't open profiles for writing" << endl;
                    return 1;
                }

                for (int i = 0; i < profileArray.getSize(); i++)
                {
                    ArrayNode<string, int>* profile = profileArray.getNodeAt(i);

                    outputFStreamProfiles << profile->getName() << "," << profile->getPoints() << endl;
                }

                outputFStreamProfiles.close();

                inputFStreamCommands.close();
                inputFStreamProfiles.close();

                // destructors deallocate linked list memory

                return 0;
            }


            } // end of switch(selection)
        } // end of else: check (cin.fail())

    } // end of while(true)
} // end of int main()