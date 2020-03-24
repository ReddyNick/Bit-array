#include <bitarray.h>
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <strings.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <exception>

/**
 * написать обертку под malloc, который выдаёт иногда ошибки ok
 * 
 * firstset() с произвольного места ok
 */

data_type* mynew(int sz)
{
#ifdef _DEBUG
    std::srand(time(0));
    int x = std::rand() % 4;
    if (x == 0){
        throw std::bad_alloc();
    }
    else
#endif
    return new data_type[sz]{};
}

bit_array::bit_array():
    _data(mynew(DEFAULT_SIZE)),
    _size(DEFAULT_SIZE * NBITS),
    nbyte(DEFAULT_SIZE)
{}

bit_array::bit_array(size_type sz):
    _data(mynew(sz)),
    _size(sz * NBITS),
    nbyte(sz)
{}

bit_array::~bit_array()
{
    if (_data != nullptr)
        delete[] _data;

    _data = nullptr;
    _size = nbyte = -1;
}

void bit_array::set(size_type idx, bool value)
{
    assert(idx < _size);

    data_type x = 1 << (idx % NBITS);

    if (value)
        _data[idx / NBITS] |= x;
    else
        _data[idx / NBITS] &= ~x;
}

bool bit_array::check(size_type idx)
{
    assert(idx < _size);

    data_type x = 1 << (idx % NBITS);
    
    if (_data[idx / NBITS] & x)
        return 1;
    else 
        return 0;
}

int bit_array::firstset(unsigned int place)
{
    assert(place < _size);

    //first byte to search
    size_type byteplace = place / NBITS;
    size_type shift = place % NBITS;

    //prepare the first byte
    data_type start_byte = _data[byteplace];
    start_byte &= (0xFFFFFFFF >> shift) << shift; 

    //check the first byte
    size_type idx = ffs(start_byte);
    if (idx)
        return idx - 1 + byteplace * NBITS;

    //if not found search further
    idx = byteplace + 1;
    while (idx < nbyte && !(_data[idx]))
        idx++;    
    
    if (idx == nbyte)
        return -1;                                          
    else
    {     
        return ffs(_data[idx]) - 1 + idx * NBITS;        
    }
}

int bit_array::firstclear(unsigned int place)
{
    assert(place < _size);
    
    //first byte to search
    size_type byteplace = place / NBITS;
    size_type shift = place % NBITS;

    //prepare the first byte
    data_type start_byte = _data[byteplace];
    start_byte |= (0xFFFFFFFF << shift) >> shift; 

    //check the first byte
    size_type idx = ffs(~start_byte);
    if (idx)
        return idx - 1 + byteplace * NBITS;

    //if not found search further
    idx = byteplace + 1;
    while (idx < nbyte && !(~_data[idx]))
        idx++;    
    
    if (idx == nbyte)
        return -1;                                          
    else
    {     
        return ffs(~_data[idx]) - 1 + idx * NBITS;        
    }
} 

int bit_array::resize(size_type size)
{
    data_type* newptr = new data_type[size]{};
    size_type idx = 0;

    if (size == 0){
        delete[] _data;
        _data = nullptr;
        _size = nbyte = 0;
        return 0;
    }

    while (idx < nbyte && idx < size){
        newptr[idx] = _data[idx];
        idx++;
    }

    _size = size * NBITS;
    nbyte = size;

    data_type* delete_ptr = _data;
    _data = newptr;
    delete[] delete_ptr;

    return 0;
}

biterator bit_array::begin()
{
    biterator newiter(this, 0);
    return newiter;
}

biterator bit_array::end()
{
    biterator newiter(this, _size);
    return newiter;
}

void biterator::set(bool val)
{
    return bitarr->set(current, val);
}

bool biterator::check() const
{
    return bitarr->check(current);
}

biterator& biterator::operator++()
{
    current++;
    return *this;
}

bool biterator::operator!=(const biterator& other) const
{
    if (this->bitarr == other.bitarr)
        return this->current != other.current;
    else
        return true;
}  