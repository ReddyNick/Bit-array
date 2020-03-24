/** TODO
 * 
 * dynamic memory 
 * 
 */

#include <cassert>

const int DEFAULT_SIZE = 1; 
typedef unsigned int data_type;
typedef unsigned int size_type;
const size_type NBITS = 8 * sizeof(data_type);


class biterator;

class bit_array
{
public:
    bit_array();
    bit_array(size_type sz);
    ~bit_array();

    size_type size() { return _size; };

    void set(size_type idx, bool value);
    bool check(size_type idx);
    
    int firstset(unsigned int idx);
    int firstclear(unsigned int idx);

    int resize(size_type size);

    typedef biterator iterator;
    
    biterator begin();
    biterator end();    

private:
    data_type* _data;
    size_type _size;
    size_type nbyte;

};

class biterator
{
    friend class bit_array;

private:
    
    biterator(bit_array* bitarrptr, size_type current_val):
        bitarr(bitarrptr), 
        current(current_val)
    {};

public:
    biterator(const biterator& iter):
        bitarr(iter.bitarr),
        current(iter.current)
    {};

    bool operator!=(const biterator & other) const;    
    biterator& operator++();

    bool check() const;
    void set(bool val);

private:
    size_type current;
    bit_array* bitarr;
};