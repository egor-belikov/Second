#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#define MINSIZE 100
#define p 23 //множитель для хеш-функции. взято какое-то простое число для лучшего распределения
using namespace std;


class HashTable
{
private:
	unsigned int size;//количество цепочек
	unsigned int count;//количество всех строк
	unsigned int hashfunction(const string& s)//хеш-функция
    {
        unsigned int sum = 0, pow = 1;
        for (int i = 0; i < s.size(); i++)
        {
            sum += int(s[i]) * pow;
            pow *= p;
        }
        return sum % size;
    };
    bool findhash(unsigned int hash, const string& s)
    {
        for (int i = 0; i < table[hash].size(); i++)
            if (table[hash][i] == s)
                return true;
        return false;
    };
    void realloc()//реаллокация
    {
        if (count < 4 * size)
            return;
        vector<vector<string> > newtable;
        size *= 4;
        newtable.resize(size);
        for (int i = 0; i < size / 4; i++)
            for (int j = 0; j < table[i].size(); j++)
                newtable[hashfunction(table[i][j])].push_back(table[i][j]);
        table = newtable;
    };
    
public:
    vector<vector<string> > table;//вектор из цепочек
    HashTable()
    {
        size = MINSIZE;
        count = 0;
        table.resize(size);
    };
    void add(const string& s)//добавить строку
    {
        unsigned int hash = hashfunction(s);
        if(!find(s))
        {
            table[hash].push_back(s);
            count++;
        }
        realloc();
    };
    bool find(const string& s)//найти строку
    {
        return findhash(hashfunction(s), s);
    };
    
	void erase(const string& s)//удалить строку
	{
        unsigned int hash = hashfunction(s);
        int i;
        for (i = 0; (i < table[hash].size()) && (table[hash][i] != s); i++);
        if (i < table[hash].size())
            table[hash].erase(table[hash].begin() + i);
	}
};

class HashTableIterator
{
private:
    long int i, j;
    vector<string>::iterator it;
public:
    HashTable& table;
    HashTableIterator(HashTable& hashtable)
    :table(hashtable)
    {
        j = 0;
        for (i = 0; ((i < table.table.size()) && (table.table[i].size() == 0)); i++);
        if (i == table.table.size())
            throw logic_error("no elements");
        it = table.table[i].begin();
    }
    
    void operator++()
    {
        if (j < table.table[i].size() - 1)
        {
            it++;
            j++;
        }
        else
        {
            for (; ((i < table.table.size()) && (table.table[i].size() == 0)); i++);
            if (i == table.table.size())
                throw logic_error("no elements when ++");
            j = 0;
            it = table.table[i].begin();
        }
    };
    void operator--()
    {
        if (j > 0)
        {
            it--;
            j--;
        }
        else
        {
            for (; ((i >= 0) && (table.table[i].size() == 0)); i--);
            if (i == 0)
                throw logic_error("no elements when --");
            j = table.table[i].size() - 1;
            it = table.table[i].end() - 1;
        }
    };
    
    string operator*()
	{
		return *it;
	}
    
    string operator->()
	{
		return *it;
	}
    
    bool operator==(HashTableIterator other)
    {
        return (table.table == other.table.table && i == other.i && j == other.j);
    }
    
    bool operator!=(HashTableIterator other)
    {
        return !(*this == other);
    }
};

int main()
{
}
