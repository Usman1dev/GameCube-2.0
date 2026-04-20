#include "Game.h"
using namespace std;

// Function Prototypes
void clearScreen();
void credits();

int main() {
    srand(time(0));
    User currentUser;
    vector<Game *> games = 
	{ new RockPaperScissors(), new TicTacToe(), new RaceTo100(), new NumberGuessing() };
    int mainChoice;
    bool loggedIn = false;

    do {
        clearScreen();

        setColor(COLOR_HEADER);
        cout << "\n======== MAIN MENU ========\n";
        setColor(COLOR_DEV);
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Dev Tools\n";
        cout << "4. Credits\n";
        cout << "5. Exit\n";
        setColor(COLOR_PROMPT);
        cout << "Choose an option: ";
        setColor(COLOR_DEFAULT);
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            currentUser.signup();
            break;
        case 2:
            if (currentUser.login()) {
                loggedIn = true;
            }
            break;
        case 3: {
            Developer dev;
            int devChoice;
            string devPassword;

            setColor(COLOR_PROMPT);
            cout << "\nEnter Developer Password: ";
            setColor(COLOR_DEFAULT);
            cin >> devPassword;

            if (devPassword == "241914") {
                setColor(COLOR_MENU);
                cout << "Welcome back! Muhammad Bilal....\n";
            } else if (devPassword == "241950") {
                setColor(COLOR_MENU);
                cout << "Welcome back! Ali Imran....\n";
            } else if (devPassword == "241902") {
                setColor(COLOR_MENU);
                cout << "Welcome back! Aleena Mushtaq....\n";
            } else {
                setColor(COLOR_ERROR);
                cout << "Access Denied.\n";
                setColor(COLOR_DEFAULT);
                break;
            }
            setColor(COLOR_DEFAULT);

            do {
                setColor(COLOR_HEADER);
                cout << "\n--- Developer Tools ---\n";
                setColor(COLOR_DEV);
                cout << "1. List users\n";
                cout << "2. Delete a user\n";
                cout << "3. Exit to Main Menu\n";
                setColor(COLOR_PROMPT);
                cout << "Enter your choice: ";
                setColor(COLOR_DEFAULT);
                cin >> devChoice;

                switch (devChoice) {
                case 1:
                    dev.listUsers();
                    break;
                case 2: {
                    string delUser;
                    setColor(COLOR_PROMPT);
                    cout << "Enter username to delete: ";
                    setColor(COLOR_DEFAULT);
                    cin >> delUser;
                    dev.deleteUser(delUser);
                    break;
                }
                case 3:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    setColor(COLOR_ERROR);
                    cout << "Invalid developer option.\n";
                    setColor(COLOR_DEFAULT);
                }

                if (devChoice != 3) {
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    clearScreen();
                }

            } while (devChoice != 3);

            break;
        }
        case 4:
            credits();
            break;
        case 5:
            setColor(COLOR_SUCCESS);
            cout << "Goodbye!\n";
            setColor(COLOR_DEFAULT);
            break;
        default:
            setColor(COLOR_ERROR);
            cout << "Invalid choice.\n";
            setColor(COLOR_DEFAULT);
        }

        while (loggedIn) {
            int gameChoice;
            setColor(COLOR_HEADER);
            cout << "\n====== GAME MENU ======\n";
            setColor(COLOR_DEV);
            cout << "1. Play Rock Paper Scissors\n";
            cout << "2. Play Tic Tac Toe\n";
            cout << "3. Play Race to 100\n";
            cout << "4. Play Number Guessing Game\n";
            cout << "5. Logout\n";
            setColor(COLOR_PROMPT);
            cout << "Select a game: ";
            setColor(COLOR_DEFAULT);
            cin >> gameChoice;

            if (gameChoice >= 1 && gameChoice <= 4) {
                games[gameChoice - 1]->play();
            } else if (gameChoice == 5) {
                loggedIn = false;
                setColor(COLOR_SUCCESS);
                cout << "Logged out.\n";
            } else {
                setColor(COLOR_ERROR);
                cout << "Invalid game choice.\n";
                setColor(COLOR_DEFAULT);
            }
        }

    } while (mainChoice != 5);

    for (auto g : games)
        delete g;

    return 0;
}

void credits() {
    clearScreen();
    setColor(COLOR_HEADER);
    cout << "\n=====================================\n";
    cout << "           CREDITS\n";
    cout << "=====================================\n";
    cout << "   THANK YOU FOR PLAYING OUR GAMES\n";
    cout << "-------------------------------------\n";
    cout << "          DEVELOPERS\n";
    cout << "-------------------------------------\n";
    setColor(COLOR_DEV);
    cout << "  1. Muhammad Bilal -  241914\n";
    cout << "  2. Ali Imran      -  241950\n";
    cout << "  3. Aleena Mushtaq -  241902\n";
    setColor(COLOR_HEADER);
    cout << "-------------------------------------\n";
    cout << " We hope you enjoyed the experience!\n";
    cout << "=====================================\n";
    setColor(COLOR_DEFAULT);
    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}

