#include<iostream>
#include <string>
#include <cctype>
using namespace std;
/**
 * Main function checks if the word is palindrom or not 
 */
bool isPalaindrome(const string & word)
{
    int start = 0;
    int end = word.length()-1;

    while(start < end)
    {
        if(tolower(word[start]) !=tolower(word[end]))
        // using to lower beause user might write the first letter as upper case 
        {
            return false;
        }
        start++;
        end--;
    }
    return true;
}
/**
 * function to get input  from user 
 */
string getInputFromUser()
{
    string input="";
    cout<<"Enter the word or type exit to quit : ";
    getline(cin, input);

    return input;
}
/**
 * Displays if the given word is palindrom or not
 */
void displayOutput(const string &word , bool ispalindrome )
{
    if(ispalindrome)
    {
        cout<<"\t""The word '"<<  word <<"' is a Palindrome "<<endl<<endl;
    }
    else
    {
        cout<<"\t""The word '"<<word<<"' is not a Palindrome "<<endl<<endl;
    }
}
/**
 * Gives instruction for the program 
 */
void intro()
{
    
    cout<<endl<<"         Palindrom checker      "<<endl<<endl;
    cout<<"Instructions : "<<endl;
    cout<<"    1- You can type any word to check if its palindrome or not "<<endl;
    cout<<"    2- If you wan't to quit then  enter 'exit'  "<<endl<<endl;
}
int main()
{
    intro();
    string input="";
    while(true)
    {
        input = getInputFromUser();
        // i have mac that is why i used exit since i can't use conio.h 
        if(input == "exit" || input =="Exit" || input == "exit " || input == "Exit " )
        {
            cout<<"        Exiting the program     "<<endl;
            break;
        }
        bool result = isPalaindrome(input);
        displayOutput(input , result);
    }
    return 0;
}