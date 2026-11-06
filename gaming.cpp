// Hangman Deluxe
// Developed by: Your Name

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int score = 0;
int streak = 0;
vector<string> technology =
{
    "computer",
    "internet",
    "database",
    "network",
    "programming"
};

vector<string> animals =
{
    "elephant",
    "giraffe",
    "kangaroo",
    "zebra",
    "lion"
};

vector<string> countries =
{
    "rwanda",
    "uganda",
    "kenya",
    "canada",
    "japan"
};

void displayTitle()
{
    cout << CYAN;

    cout << R"(

 _    _
| |  | |
| |__| | __ _ _ __   __ _
|  __  |/ _` | '_ \ / _` |
| |  | | (_| | | | | (_| |
|_|  |_|\__,_|_| |_|\__, |
                      __/ |
                     |___/

)";

    cout << RESET;
}

int menu()
{
    int choice;

    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Play Game\n";
    cout << "2. High Scores\n";
    cout << "3. Exit\n";

    cout << "Choose Option: ";
    cin >> choice;

    return choice;
}

int chooseCategory()
{
    int category;

    cout << "\nChoose Category\n";
    cout << "1. Technology\n";
    cout << "2. Animals\n";
    cout << "3. Countries\n";

    cout << "Choice: ";
    cin >> category;

    return category;
}

int chooseDifficulty()
{
    int difficulty;

    cout << "\nChoose Difficulty\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";

    cout << "Choice: ";
    cin >> difficulty;

    return difficulty;
}
int getLives(int difficulty)
{
    if(difficulty == 1)
        return 10;

    if(difficulty == 2)
        return 7;

    return 5;
}

string getRandomWord(int category)
{
    vector<string> words;

    if(category == 1)
        words = technology;

    else if(category == 2)
        words = animals;

    else
        words = countries;

    int index = rand() % words.size();

    return words[index];
}

void drawHangman(int stage)
{
    string hangman[] =
    {
R"(
 +---+
 |   |
     |
     |
     |
=====)",

R"(
 +---+
 |   |
 O   |
     |
     |
=====)",

R"(
 +---+
 |   |
 O   |
 |   |
     |
=====)",

R"(
 +---+
 |   |
 O   |
/|   |
     |
=====)",

R"(
 +---+
 |   |
 O   |
/|\  |
     |
=====)",

R"(
 +---+
 |   |
 O   |
/|\  |
/    |
=====)",

R"(
 +---+
 |   |
 O   |
/|\  |
/ \  |
=====)"
    };

    cout << hangman[stage];
}

void displayWord(string guessed)
{
    cout << "\nWord: ";

    for(char c : guessed)
    {
        cout << c << " ";
    }

    cout << endl;
}

void showLives(int lives)
{
    cout << "\nLives: ";

    for(int i = 0; i < lives; i++)
    {
        cout << "* ";
    }

    cout << endl;
}

void showHint(string secretWord)
{
    cout << "\nHint: ";

    if(secretWord == "computer")
        cout << "Electronic machine";

    else if(secretWord == "elephant")
        cout << "Largest land animal";

    else if(secretWord == "rwanda")
        cout << "Land of a Thousand Hills";

    else
        cout << "No hint available";

    cout << endl;
}

void saveScore(string playerName, int score)
{
    ofstream file("scores.txt", ios::app);

    file << playerName
         << " "
         << score
         << endl;

    file.close();
}

void showScores()
{
    ifstream file("scores.txt");

    string name;
    int score;

    cout << "\n===== HIGH SCORES =====\n";

    while(file >> name >> score)
    {
        cout << name
             << " : "
             << score
             << endl;
    }

    file.close();
}

bool alreadyGuessed(char letter,
                    const vector<char>& guessedLetters)
{
    for(char guessed : guessedLetters)
    {
        if(letter == guessed)
            return true;
    }

    return false;
}

void achievement(int score)
{
    if(score >= 50)
        cout << "\n First Champion!\n";

    if(score >= 100)
        cout << "\n Word Master!\n";

    if(score >= 200)
        cout << "\n Hangman Legend!\n";
}

void showStatistics(int correct,
                    int wrong)
{
    cout << "\n===== GAME STATS =====\n";

    cout << "Correct Guesses: "
         << correct
         << endl;

    cout << "Wrong Guesses: "
         << wrong
         << endl;

    double accuracy = 0;

    if(correct + wrong > 0)
    {
        accuracy =
        (double)correct /
        (correct + wrong) * 100;
    }

    cout << "Accuracy: "
         << accuracy
         << "%"
         << endl;
}

void playGame()
{
    int category = chooseCategory();

while(category < 1 || category > 3)
{
    cout << "Invalid category. Try again: ";
    cin >> category;
}

    int difficulty = chooseDifficulty();

    while(difficulty < 1 || difficulty > 3)
{
    cout << "Invalid difficulty. Try again: ";
    cin >> difficulty;
}

    string secretWord = getRandomWord(category);
    string guessedWord(secretWord.length(), '_');

    vector<char> guessedLetters;
    vector<char> wrongLetters;

    int lives = getLives(difficulty);
    int totalLives = lives;

    bool hintUsed = false;

    int correctGuesses = 0;
    int wrongGuesses = 0;

    while(lives > 0 && guessedWord != secretWord)
    {
        cout << "\n================================\n";

        int stage = totalLives - lives;

if(stage > 6)
{
    stage = 6;
}

drawHangman(stage);

        displayWord(guessedWord);

        showLives(lives);

        cout << "\nScore: " << score << endl;

        cout << "Wrong letters: ";

        for(char letter : wrongLetters)
        {
            cout << letter << " ";
        }

        cout << endl;

        char guess;

        cout << "\nEnter a letter (H for hint): ";
        cin >> guess;

        guess = tolower(guess);

        if(guess == 'h')
        {
            if(!hintUsed)
            {
                showHint(secretWord);
                hintUsed = true;
            }
            else
            {
                cout << "\nHint already used.\n";
            }

            continue;
        }

        if(!isalpha(guess))
        {
            cout << RED << "\nPlease enter a valid letter.\n" << RESET;
            continue;
        }

        if(alreadyGuessed(guess, guessedLetters))
        {
            cout << YELLOW << "\nYou already guessed that letter.\n" << RESET;
            continue;
        }

        guessedLetters.push_back(guess);

        bool found = false;

        for(size_t i = 0; i < secretWord.length(); i++)
        {
            if(secretWord[i] == guess)
            {
                guessedWord[i] = guess;
                found = true;
            }
        }

        if(found)
        {
            cout << GREEN << "\nCorrect!\n" << RESET;

            score += 10;
            correctGuesses++;
        }
        else
        {
            cout << RED << "\nWrong!\n" << RESET;

            wrongLetters.push_back(guess);
            lives--;
            wrongGuesses++;
        }
    }

    cout << "\n================================\n";

    if(guessedWord == secretWord)
    {
        cout << GREEN;

        cout << "\n CONGRATULATIONS!\n";
        cout << "You guessed the word: "
             << secretWord
             << endl;

        cout << "\nBonus +50 points!\n";

        score += 50;
        streak++;

        achievement(score);

        cout << RESET;
    }
    else
    {
        drawHangman(6);

        cout << RED;

        cout << "\n GAME OVER!\n";
        cout << "Correct word was: "
             << secretWord
             << endl;

        streak = 0;

        cout << RESET;
    }

    showStatistics(correctGuesses, wrongGuesses);

    cout << "\nCurrent Score: "
         << score
         << endl;

    cout << "Win Streak: "
         << streak
         << endl;


}


int main()
{
    srand(time(0));

    string playerName;

    displayTitle();

    cout << "\nEnter your name: ";
    cin >> playerName;

    int choice;

    do
    {
        choice = menu();

        switch(choice)
        {
        case 1:
{
    char again;

    do
    {
        playGame();

        cout << "\nPlay another round? (y/n): ";
        cin >> again;

    } while(tolower(again) == 'y');

    if(score > 0)
{
    saveScore(playerName, score);
}
    break;
}

            case 2:
                showScores();
                break;

            case 3:
                cout << "\nThank you for playing Hangman Deluxe!\n";
                break;

            default:
                cout << "\nInvalid selection.\n";
        }

    } while(choice != 3);

    return 0;
}