
#ifndef HashTable_h
#define HashTable_h


#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;


template <typename T>
class Node
{
public:
    int key;
    T info;
    Node<T>* next;
    Node(int key, T info);
};

template <typename T>
class HashTable
{
private:
    Node<T> **dictionaryHT;
    int SIZE;
public:
    HashTable(int size);
    HashTable();
    ~HashTable();
    int HashCode(T s);
    void Insert(T k);
    void _Insert(int key, T info);
    int Search(T info);
    bool operator==(const Node<T> &rhsObj) const;
    int collisions;
    double chainLen();
    
    friend int getHash(T s);
    int getHash(string s);
};

template <typename T>
int HashTable<T>::getHash(string s)
{
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = (23 * hash)^(i+1) + s[i];
    
    return abs(hash) % SIZE;
}

//template <typename T>
//int HashTable<T>::getHash(Node<T> s)
//{
//    int hash = 0;
//    hash = getHash(s.info);
//    
//    return hash;
//}



template <typename T>
Node<T>::Node(int key, T info)
{
    this->key = key;
    this->info = info;
    this->next = nullptr;
}


template <typename T>
HashTable<T>::HashTable(int size)
{
    SIZE = size;
    dictionaryHT = new Node<T>*[SIZE];
    for (int i = 0; i < SIZE; i++)
        dictionaryHT[i] = nullptr;
    
    collisions = 0;
    
}

template <typename T>
HashTable<T>::HashTable()
{
    dictionaryHT = new Node<T>*[SIZE];
    for (int i = 0; i < SIZE; i++)
        dictionaryHT[i] = nullptr;
    
}

template <typename T>
HashTable<T>::~HashTable()
{
    for (int i = 0; i < SIZE; ++i)
    {
        Node<T>* current = dictionaryHT[i];
        while (current != nullptr)
        {
            Node<T>* prev = current;
            current = current->next;
            delete prev;
        }
    }
    delete[] dictionaryHT;
}

template <typename T>
void HashTable<T>::Insert(T k)
{
    int key = HashCode(k);
    //cout << "Inserting " << k << " with hash: " << key << endl;
    _Insert(key, k);
}

template <typename T>
void HashTable<T>::_Insert(int key, T info)
{
    int position = key;
    Node<T>* prev = nullptr;
    Node<T>* current = dictionaryHT[position];
    while (current != nullptr)
    {
        collisions++;
        prev = current;
        current = current->next;
    }
    if (current == nullptr)
    {
        current = new Node<T>(key, info);
        if (prev == nullptr)
        {
            dictionaryHT[position] = current;
        }
        else
        {
            prev->next = current;
        }
    }
    else
    {
        current->info = info;
    }
}

template <typename T>
int HashTable<T>::Search(T info)
{
    //check spot where word should be, if null then not there
    //if not null, if strings match then no error
    //if strings don't match then check *next
    //if next is null then the word is not in dictionary
    
    
    bool found = false;
    int position = HashCode(info);
    Node<T>* current = dictionaryHT[position];
    while (current != nullptr)
    {
        if (current->info == info)
        {
            //cout<< "Found: " << current->info <<endl;
            found = true;
        }
        current = current->next;
    }
    if (!found)
    {
        //cout << "Did not find: " << info << endl;
        return -1;
    }
    
    return 0;
}

template <typename T>
int HashTable<T>::HashCode(T s)
{
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = (23 * hash)^(i+1) + s[i];
    
    return abs(hash) % SIZE;
}


template <typename T>
bool HashTable<T>::operator==(const Node<T> &rhsObj) const
{
    bool answer = false;
    
    answer = (this->current.stringcmp == rhsObj.current);
    
    return answer;
    
}

template <typename T>
double HashTable<T>::chainLen()
{
    Node<T>* temp = dictionaryHT[0];
    double chainlen = 0;
    double chainNum=0;
    double average;
    
    for (int i = 0; i < SIZE; i++)
    {
        temp = dictionaryHT[i];
        
        while (temp != nullptr)
        {
            chainNum++;
            
            while (temp->next != nullptr)
            {
                chainlen++;
                temp = temp->next;
            }
            temp = temp->next;
        }
    }
    //cout << "chainlen = " << chainlen << " and chainNum = " << chainNum << endl;
    //cout << "Average chain length is " << chainNum/chainlen << endl;
    average = chainNum/chainlen;
    return average;
}




#endif /* HashTable_h */
