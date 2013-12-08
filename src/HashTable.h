/* 
 * File:   HashTable.h
 * Author: charlie
 *
 * Created on November 19, 2013, 2:26 PM
 */

#include <unordered_map>
#ifndef HASHTABLE_H
#define	HASHTABLE_H

template <class T>
class HashTable : public DataStore<T>
{
public:
    HashTable();
    HashTable(const HashTable& orig);
    virtual ~HashTable();
    
    
private:

};

#endif	/* HASHTABLE_H */

