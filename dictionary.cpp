#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


#define DICTIONARY "dictionary.txt"

using namespace std;

class Dictionary
{
    private :
        string word;
        string definition;
    public :
        Dictionary()
        {
            word = definition = "NIL";
        }

        Dictionary(string w, string def)
        {
            word = w;
            definition = def;
        }

        ~Dictionary() {}

        string get_word()
        {
            return word;
        }

        string get_definition()
        {
            return definition;
        }

        void set_word(string w)
        {
            word = w;
        }

        void set_definition(string def)
        {
            definition = def;
        }
};


/* Returns the definition of a word if it is found in class */
string search_word(Dictionary *d, string word, int count)
{
    string definition = "";
    for (int i = 0; i < count+1; i++)
    {
        if (word == d[i].get_word())
        {
            definition = d[i].get_definition();
            break;
        }
    }
    return definition;
}


/* A function to print help text */
void help()
{
    cout << setw(80) << "In this record you can save more than 10,000 record with their meanings. Enjoy!" << endl ;
}


/* A function to append new word and definition to the dictionary file */
void write_into_dictionary(Dictionary *d, int i)
{
    ofstream dicFile(DICTIONARY);
    for (int n = 0; n < i; n++)
    {
        if (d[n].get_word() != "NIL")
        {
            dicFile << d[n].get_word() << " " << d[n].get_definition() << '\n';
        }
    }
    dicFile.close();
}


/* A function to read from the dictionary file */
int read_from_dictionaryfile(Dictionary *d)
{
    ifstream dicFile(DICTIONARY);
    string line;
    int i = 0;
    /* If file not found in the same directory */
    if (dicFile == NULL)
    {
        cout << "I could not find a file by the name: " << DICTIONARY << " over here" << endl;
        cout << "You may have to create a blank file named " << DICTIONARY << " in this directory " << endl;
        dicFile.close();
        exit(0);
    }
    /* Read line by line from file */
    while (getline(dicFile, line))
    {
        /* string streams helps to separate strings by space */
        stringstream iss(line);
        string word, definition;
        if (iss >> word >> definition)
        {
            d[i].set_word(word);
            d[i].set_definition(definition);
            ++i;
        }
        else
        {
            break;
        }
    }
    dicFile.close();
    /* Returns the number of lines in the file */
    return i;
}


int main()
{
    string word, definition;
    int choice;
    string dword;
    Dictionary *d = new Dictionary[100000];
    int i = read_from_dictionaryfile(d);
    do
    {
        cout << setw(50) <<"~~~**~~~DICTIONARY~~~**~~~" << endl;
        cout << setw(26) <<"1. Help" << endl;
        cout << setw(29) <<"2. Meaning" << endl;
        cout << setw(32) <<"3. Add a Word" << endl;
        cout << setw(35) <<"4. Delete a word" << endl;
        cout << setw(49) <<"5. Displaying all the elements" << endl;
        cout << setw(26) <<"0. Quit" << endl;
        cout << setw(50) <<"Tip: Use - or _ to write a phrase" << endl;
        cout << setw(39) <<"Enter your choice : ";
        cin >> choice ;

        switch(choice)
        {
            case 1 :
                help();
                break;
            case 2:
                if (i == 0)
                {
                   cout << setw(70) <<"No element exists in the dictionary. Please add a word! " << endl;
                }
                else
                {
                    cout <<"Enter the word that you want to search : ";
                    cin >> dword;
                    if ((definition = search_word(d, dword, i)) != "")
                    {
                        cout << definition << endl;
                    }
                    else
                    {
                        cout <<"Nope! " << dword << " is not here!" << endl;
                    }
                }
                break;
            case 3:
                cout << "Enter word: " << endl;
                cin >> word;
                d[i].set_word(word);
                cout << "Enter definition: " << endl;
                cin >> definition;
                d[i++].set_definition(definition);
                write_into_dictionary(d, i);

                break;
            case 4:
                cout << "Enter word: " << endl;
                cin >> word;
                for (int n = 0; n < i; n++)
                {
                    if (d[n].get_word() == word)
                    {
                        d[n].set_word("NIL");
                        d[n].set_definition("NIL");
                        break;
                    }
                }
                write_into_dictionary(d, i);
                break ;
            case 5:
                for (int n = 0; n < i; n++)
                {
                    if (d[n].get_word() != "NIL")
                    {
                        cout << d[n].get_word() << ':' << d[n].get_definition() << endl;
                    }
                }
                break;
            default:
                cout << setw(50) << "You've entered a wrong option!" << endl;
                break;
        }
    }
    while(choice != 0);
    return 0;
}
