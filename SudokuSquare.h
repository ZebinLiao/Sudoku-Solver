#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

#include <iostream>
using std::endl;
using std::cout;

// Do not add any #include statements to this file

class SudokuSquareSetIterator {
  
    public:
    int current;
    
    unsigned int currentValues;

    SudokuSquareSetIterator(int currentIn, unsigned int valuesIn)
        : current(currentIn), currentValues(valuesIn){        
    }

    const int operator*() const {
        return current;
    }

    // TODO: complete the code for ConstNodeIterator here
    SudokuSquareSetIterator& operator++(){
        
        unsigned int valuesCopy = currentValues;
        valuesCopy = valuesCopy >> current;
        for (int i = 1; i < 20 - current; i++) {
            if(valuesCopy%2 == 1){
                current = current + i;
                return *this;
            }
            else{
                valuesCopy = valuesCopy >> 1;
                 if(current==9){
                     current = current+1;
                    return *this;
                 }
            }
        }
        return *this;
    }

    // void operator--(){
        
    // }

    bool operator==(const SudokuSquareSetIterator & other) const{
        return(current == other.current);
    }

    bool operator!=(const SudokuSquareSetIterator & other) const{
        return(current != other.current);
    }

    // SudokuSquareSetIterator* getCurrent()const{
    //     return current;
    // }
    
};

class SudokuSquareSet {
    // TODO: write your code here
    public:
    unsigned int values;
    int NumberOfValues;

    SudokuSquareSet() : values(0b000000000), NumberOfValues(0){
        // unsigned int valuesCopy = values;
        // for (int i = 1; i < 10; i++)
        // {
        //     if(valuesCopy%2 == 1){
        //         ++NumberOfValues;
        //     }
        //     else{
        //         valuesCopy >> 1;
        //     }
        // }
    }

    int size(){
        return NumberOfValues;
    }

    bool empty(){
        if(NumberOfValues = 0){
            return true;
        }
        return false;
    }

    void clear(){
        values = 0b000000000;
        NumberOfValues = 0;
    }

    bool operator==(const SudokuSquareSet & other) const{
        return(values == other.values);
    }

    bool operator!=(const SudokuSquareSet & other) const{
        return(values != other.values);
    }

    SudokuSquareSetIterator begin(){
        unsigned int valuesCopy = values;
        for (int i = 1; i < 17; i++)
        {
            if(valuesCopy%2 == 1){
                return SudokuSquareSetIterator(i, values);
            }
            else{
                valuesCopy = valuesCopy >> 1;
            }
        }
        return SudokuSquareSetIterator(10, values);
    }

    SudokuSquareSetIterator end(){
        return SudokuSquareSetIterator(10, values);
    }

    SudokuSquareSetIterator insert(int numberIn){
        unsigned int valuesCopy = values;
        values |= 1UL << numberIn-1;
        if(values != valuesCopy){
            ++NumberOfValues;
        }
        return SudokuSquareSetIterator(10, values);
    }

    SudokuSquareSetIterator find(int numberIn){
        unsigned int valuesCopy = values;
        for (int i = 1; i < 10; i++)
        {
            if(valuesCopy%2 == 1 && numberIn == i){
                return SudokuSquareSetIterator(i,values);
            }
            else{
                valuesCopy = valuesCopy >> 1;
            }
        }
        return SudokuSquareSetIterator(10, values);
    }

    void erase(int numberIn){
        // unsigned int valuesCopy = values;
        // for (int i = 1; i < 10; i++)
        // {
        //     if(valuesCopy%2 == 1 && numberIn == i){
        //         cout<<values<<endl;
        //         values &= ~(1UL << i-1);
        //         //++values;
        //         cout<<values<<endl;
        //         --NumberOfValues;
        //         return;
        //     }
        //     else{
        //         valuesCopy >> 1;
        //     }
        // }
        values &= ~(1UL << numberIn-1);
        --NumberOfValues;
    }
    void erase(SudokuSquareSetIterator itr){
        int num = itr.current;
        erase(num);
    }
};





// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
