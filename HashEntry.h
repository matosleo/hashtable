//
//  HashEntry.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#ifndef HashEntry_h
#define HashEntry_h

template <typename K, typename V>
class HashEntry {
    
private:
    K key;
    V value;
    
public:
    HashEntry()
    {
    }
    
    HashEntry(K key, V value):
    key(key), value(value){}
    
    ~HashEntry()
    {
        
    }
    
    K getKey()
    {
        return this->key;
    }
    void setKey( const K key )
    {
        this->key = key;
    }
    
    V getValue()
    {
        return this->value;
    }
    
    void setValue( const V value )
    {
        this->value = value;
    }
};

#endif /* HashEntry_h */
