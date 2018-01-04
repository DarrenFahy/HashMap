//Darren Fahy
//dsf34
//Spell Checker Hashing Assignment

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <functional>
#include "hashMap.h"

using namespace std;

int countFiles(int argc, const char * argv[]);
void hashDictionary(int argc, const char * argv[]);
int table(double entries);

int main(int argc, const char * argv[])
{
    
    
    
    
    
    /* File name and path of log file here!!!! */
    string logPath = "/Users/Darren/Desktop/logOutput.txt";
    
    
    
    ofstream os;
    ifstream dictFile;
    ifstream personalFile;
    ifstream txtFile;
    string dictionary_file_path;
    string personal_dict;
    string fileToCheck;
    string line;
    string command;
    string myWord;
    bool personal = false;
    int lineNum = 0;
    int misspelled = 0;
    int tableSize;
    int wordsChecked = 0;
    double lambda;
    
    double dictionaryEntries = countFiles( argc, argv);
    tableSize = table(dictionaryEntries);
    HashTable<string> myHash(tableSize);
    
    if (argc < 3)
    {
        cout << "Not enough command line arguments";
    }
    else
    {
        dictionary_file_path = argv[1];
        fileToCheck = argv[2];
        
        if (argc == 4)
        {
            personal_dict = argv[3];
            personal = true;
        }
        
        try
        {
            dictFile.open(dictionary_file_path.c_str());
            
            while (!dictFile.eof())
            {
                getline(dictFile, line);
                stringstream ss(line);
                myWord = line.substr(0, line.find("/", 0));
                myHash.Insert(myWord);
            }//end while
            dictFile.close();
            
        
            //read personal file
            if (personal == true)
            {
                personalFile.open(personal_dict.c_str());
                
                while (!personalFile.eof())
                {
                    getline(personalFile, line);
                    stringstream ss(line);
                    myWord = line.substr(0, line.find("/", 0));
                    myHash.Insert(myWord);
                    
                }//end while
                personalFile.close();
                
            }//end if personal == true
            
            
            //read file to check
            txtFile.open(fileToCheck.c_str());
            
            while (!txtFile.eof())
            {
                string word;
                lineNum++;
                getline(txtFile, line);
                stringstream ss(line);
                
                while (ss >> myWord)
                {
                    wordsChecked++;
                    if ( myHash.Search(myWord) == -1)
                    {
                        misspelled++;
                        cout << "Misspelled word: '" << myWord << "' on line: " << lineNum << endl;
                        os.open(logPath, ios_base::app);
                        os <<"Misspelled word: '" << myWord << "' on line: " << lineNum << endl;
                        os.close();
                    
                    }
                    //cout << myWord << endl;
                }//end while
                
            }//end other while
            txtFile.close();
            
            
            
            //Output to screen
            lambda = dictionaryEntries/101267;
            cout << wordsChecked << " words checked" << endl;
            cout << misspelled << " misspelled words" << endl;
            cout << myHash.collisions << " collisions while hashing" << endl;
            cout << "Average chain length is: " << myHash.chainLen() << endl;
            cout << "Size of the table is: " << 101267 << endl;
            cout << "Lambda is: " << lambda << endl;
            
            //Output to file
            os.open(logPath, ios_base::app);
            os <<lineNum << " words checked" << endl;
            os << misspelled << " misspelled words" << endl;
            os << myHash.collisions << " collisions while hashing" << endl;
            os << "Average chain length is: " << myHash.chainLen() << endl;
            os << "Size of the table is: " << 101267 << endl;
            os << "Lambda is: " << lambda << endl;
            os.close();


        }
        catch (...)
        {
            cout << "Error reading dictionary and text files..." << endl;
        }
        
        
    }//end else
    
    return 0;
}



int countFiles(int argc, const char * argv[])
{
    ifstream dictFile;
    ifstream personalFile;
    ifstream txtFile;
    string dictionary_file_path;
    string personal_dict;
    string fileToCheck;
    string line;
    string command;
    string myWord;
    bool personal = false;
    int entries = 0;
    
    
    if (argc < 3)
    {
        cout << "Not enough command line arguments";
    }
    else
    {
        dictionary_file_path = argv[1];
        fileToCheck = argv[2];
        
        if (argc == 4)
        {
            personal_dict = argv[3];
            cout << "User supplied personal dictionary" << endl;
            personal = true;
        }
        
        try
        {
            //First, count number of entries in dictionary and personal dictionary
            
            dictFile.open(dictionary_file_path.c_str());
            while (!dictFile.eof())
            {
                getline(dictFile, line);
                stringstream ss(line);
                entries++;
            }//end while
            dictFile.close();
            
            if (personal == true)
            {
                personalFile.open(personal_dict.c_str());
                while (!personalFile.eof())
                {
                    getline(personalFile, line);
                    stringstream ss(line);
                    entries++;
                }//end while
                personalFile.close();
            }
            cout << "Number of entries is: " << entries << endl;
            
        }
        catch (...)
        {
            cout << "Error while counting entries..." << endl;
        }
        
    }//end else
    
    return entries;
}

int table(double entries)
{
    int primes[11] = { 83, 499, 5741, 12097, 38783, 54601, 75689, 103451, 144931, 211063, 514903};
    int tableSize = 0;
    int i =0;
    cout << primes[8] << endl;
    cout << 2*entries << endl;
    while (i < 12)
    {
        if ( 2*entries < primes[i])
        {
            tableSize = primes[i];
            i=12;
        }
        else
            i++;
    }
    
    return tableSize;

}











