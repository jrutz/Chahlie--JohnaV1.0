/*
 * File:   DataStore.h
 * Author: charlie
 *
 * Created on November 19, 2013, 2:05 PM
 */

#ifndef DATASTORE_H
#define	DATASTORE_H

template<class T>
class DataStore
{
public:
    DataStore();
    DataStore(const DataStore& orig);
    virtual ~DataStore();
    virtual void insert(T newData) = 0;
private:
};

template <class T>
DataStore<T>::DataStore()
{

}

template <class T>
DataStore<T>::~DataStore()
{

}

#endif	/* DATASTORE_H */

