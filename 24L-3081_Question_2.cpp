#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std;


const int MaxMistakes = 7;

// using vectors because they are easy to handle 
//and ensure safety , memory management , easy cleanup

/**
 * Reads the words from file and store it in a vector string 
 */
vector<string> ReadingWordsFromFile(const string& filename) 
{
    
    vector<string> words;
    // reading from file 
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cout<<"Error: Could not open "<<filename<<endl;
        cout<<"Exiting the program "<<endl;
        exit(1); 
    }

    string word;
    while (getline(file, word)) 
    {
        if (!word.empty()) 
        {
            // if the word i.e the line is not empty then pushing that word in vector
            words.push_back(word);
        }
    }

    file.close();
    return words;
}
/**
 * Fromt he vector string it gets a random word using randomizer to be guessed 
 */
string getRandomWord(const vector<string>& words) 
{
    // if the string of vectors is empty then returning empty word
    if (words.empty())
    {
        return "";
    }

    srand(time(0));
    // getting the index of the random word from the vector array
    int index = rand() % words.size();
    return words[index];
}
/**
 * This function display how much progress the player has made 
 * i.e how many letter has he guessed and how many are wrong and how much attempts left
 */
void displayProgress(const string& guessedWords, int mistakes, const vector<char>& wrongGuesses) 
{
    cout<<endl<<"\t\t""--*-Progess-*--"<<endl;
    cout<<"Correctly guessed : ";
    int length = guessedWords.size();
    for (int i =0 ; i<length; i++) 
    {
        cout<< guessedWords[i]<<" ";
    }

    cout <<endl<< "Remaining Mistakes : " <<MaxMistakes - mistakes << endl;

    length = wrongGuesses.size();

    cout<<"Wrongly guessed : ";
    if (!wrongGuesses.empty()) 
    {
        for (int i =0 ; i<length; i++) 
        {
            cout<<wrongGuesses[i]<<" ";
        }
    }
    cout<<endl;
}
/**
 * This takes input of the letter from the user and checks if its a signle char and is alphanumeric i.e alphabet or a number
 */
char getUserGuess() 
{
    string guess;
    while (true) 
    {
        cout<<"Guess a letter : ";
        getline(cin, guess);
        
        if (guess.length() != 1 || !isalnum(guess[0])) 
        // using isalnum (checks if there is an alphabet or num) so if anyother than the if condition does not works
        {
            cout << "Invalid input Please enter a valid character !! "<<endl;
            continue;
        }
        return tolower(guess[0]);
    }
}
/**
 * After you have entered a guess letter it matches with the word to be guessed and if found 
 * it updates the guessed word array
 */
bool updateProgress(const string& word, string& Guessedwords, char guess) 
{
    bool found = false;
    for (size_t i = 0; i < word.length(); i++) 
    {
        if (tolower(word[i]) == guess && Guessedwords[i] == '_') 
        {
            // if the character matches a character from the given word 
            //then updating the progress string by adding that charac to it

            Guessedwords[i] = word[i];
            found = true;
        }
    }

    return found;
}
/**
 * This function checks if the character the user entered is already entered or not 
 * if already present in the guessed string or wrong guessed then returning true
 * else false
 */
bool isAlreadyGuessed(char guess, const string& guessed, const vector<char>& wronglyGuessed) 
{

    int length = guessed.size();
    char character;
    for (int i =0 ; i<length; i++) 
    {
        character = guessed[i];
        if (tolower(character) == guess)
        {
            return true;
        }
    }
    
    length = wronglyGuessed.size();
    for (int i =0 ; i<length; i++) 
    {
        character = wronglyGuessed[i];
        if (character == guess)
        {
            return true;
        }
    }
    return false;
}
/**
 * This checks if the guessed words string is complete and there is no _ left to be guessed then return true 
 * and if there is letter to be guessed then return false 
 */
bool isWordGuessed(const string& guessedWords) 
{
    int length = guessedWords.length();

    for(int i =0 ; i<length; i++)
    {
        if(guessedWords[i] == '_')
        {
            return false;
        }
    }
    return true;
}
/**
 * This checks if the user has guessed the word and if yes then player won else game over
 */
void showResult(bool won, const string& word)
{
    cout<<endl<<endl;
    if (won)
    {
        cout << "Congratulations! You guessed the word: " << word << endl;
    }

    else
    {
        cout << "Game Over! The correct word was: " << word << endl;
    }
    cout<<endl<<endl;
}
/**
 * This runs a loop till no attempt left i.e all mistakes used and till the word is not guessed 
 * it display how much guessed and all
 * it checks if the number enterd is already guessed then ask user to enter the letter again
 * if the letter is not already used then updates like if correct then update the guessed string else moves to the wrongly guessed string 
 */
void playhangman(const vector<string> word)
{
     string WordtoGuess= getRandomWord(word);
    
    // this creates a string of same size as the word to be guessed and put dashes instead 
    string Guessedwords(WordtoGuess.size(), '_');

    vector<char> wrongGuesses;
    int mistakes = 0;

    while (mistakes < MaxMistakes && !isWordGuessed(Guessedwords)) 
    {
        displayProgress(Guessedwords, mistakes, wrongGuesses);
        char guess = getUserGuess();

        if (isAlreadyGuessed(guess, Guessedwords, wrongGuesses)) 
        {
            cout << "You already guessed '" << guess << "' Try another letter "<<endl;
            continue;
        }

        if (updateProgress(WordtoGuess, Guessedwords, guess))
            cout << "Correct guess!"<<endl;
        else 
        {
            cout << "Wrong guess!"<<endl;
            wrongGuesses.push_back(guess);
            mistakes++;
        }
    }
    showResult(isWordGuessed(Guessedwords), WordtoGuess);
}
int main() 
{
    cout<<"--------------------------------------"<<endl;
    cout<<"                HangMan               "<<endl;
    cout<<"--------------------------------------"<<endl;

    vector<string> words = ReadingWordsFromFile("word.txt");
    playhangman(words);
    return 0;
}
