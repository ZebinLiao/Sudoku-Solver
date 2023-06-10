#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
using std::set;
using std::vector;
using std::sqrt;
using std::ceil;
using std::cout;
using std::endl;

// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable{

    public:
    int size;
    vector<vector<set<int>>> incompleteSolution;

    Sudoku(int sizeIN) : size(sizeIN){
        for (int i = 0; i < sizeIN; i++)
        {
            vector<set<int>> v1;

            for (int j = 0; j < sizeIN; j++) {
                set<int> s;
                for (int k = 1; k < sizeIN+1; k++)
                {
                    s.insert(k);
                }
                v1.push_back(s);
            }
            incompleteSolution.push_back(v1);
        }
    }

    int getSquare(int row, int col)const{
        if(incompleteSolution[row][col].size() > 1){
            return -1;
        }
        else if(incompleteSolution[row][col].size() == 1){
            set<int>::iterator setIt = incompleteSolution[row][col].begin();
            return *setIt;
        }
        else{
            return -1;
        }
    }

bool loopAgain = true;

    bool setSquare(int row, int col, int value){
        bool continueLoop = false;
        loopAgain = true;

        incompleteSolution[row][col].clear();
        incompleteSolution[row][col].insert(value);

        while(loopAgain){
            loopAgain = false;
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    int valueToRemove = getSquare(i, j);
                    if(valueToRemove != -1){
                        continueLoop = removePossibleValues(i, j, valueToRemove);
                        if(!continueLoop){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool removePossibleValues(int rowIN, int colIN, int valueIN){
        //on the same row
        for (int i = 0; i < size; i++){
            if(incompleteSolution[rowIN][i].find(valueIN) != incompleteSolution[rowIN][i].end()){
                if(i == colIN){
                    continue;
                }
                else{
                    loopAgain = true;
                    incompleteSolution[rowIN][i].erase(incompleteSolution[rowIN][i].find(valueIN));
                    if(incompleteSolution[rowIN][i].size() == 0){
                        return false;
                    }
                }
            }
        }
        //on the same column
        for (int i = 0; i < size; i++){
            if(incompleteSolution[i][colIN].find(valueIN) != incompleteSolution[i][colIN].end()){
                if(i == rowIN){
                    continue;
                }
                else{
                    loopAgain = true;
                    incompleteSolution[i][colIN].erase(incompleteSolution[i][colIN].find(valueIN));
                    if(incompleteSolution[i][colIN].size() == 0){
                        return false;
                    }
                }
            }
        }
        //in the same box
        //assumes coorninates starts with 0 not 1
        int boxWidth = (int)sqrt(size);

        float num1 = (float)(rowIN+1)/(float)boxWidth;
        float num2 = (float)(colIN+1)/(float)boxWidth;

        int boxRowStart = (ceil(num1) - 1) * boxWidth;
        int boxColStart = (ceil(num2) - 1) * boxWidth;

        for (int i = boxRowStart; i < (boxRowStart + boxWidth); i++){
            for (int j = boxColStart; j < (boxColStart + boxWidth); j++){
                if(incompleteSolution[i][j].find(valueIN) != incompleteSolution[i][j].end()){
                    if(i ==  rowIN && j == colIN){
                        continue;
                    }
                    else{
                        loopAgain = true;
                        incompleteSolution[i][j].erase(incompleteSolution[i][j].find(valueIN));
                        if(incompleteSolution[i][j].size() == 0){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    virtual bool isSolution()const{
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                int k = getSquare(i, j);
                if(k == -1){
                    return false;
                }
            }
        }
        return true;
    }

    virtual void write(ostream & o)const{
        cout<<"---------------"<<endl;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                int k = getSquare(i, j);
                if(k == -1){
                    cout << " ";
                }
                else{
                    cout << k;
                }
            }
            cout << endl;
        }
    }

    virtual vector<unique_ptr<Searchable>> successors()const{
        //write(cout);
        vector<unique_ptr<Searchable>> possibleSuccessors{};
        //cout<<"lol"<<endl;

        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                int numberOfChoices = incompleteSolution[i][j].size();
                //cout<<"lol"<<endl;
                if(numberOfChoices > 1){
                    set<int>::iterator setIt = incompleteSolution[i][j].begin();
                    for(int l = 0; l < numberOfChoices; l++){
                        //unique_ptr<Sudoku> currentCopy (new Sudoku(size));
                        Sudoku *currentCopy = new Sudoku(size);
                        currentCopy->incompleteSolution = incompleteSolution;
                        //cout<<*setIt<<endl;
                        bool isSuccessor = currentCopy->setSquare(i, j, *setIt);
                        //cout<<isSuccessor<<endl;
                        //currentCopy->write(cout);
                        if(isSuccessor){
                            possibleSuccessors.emplace_back(currentCopy);
                        }
                        else{
                            delete currentCopy;
                        }
                        ++setIt;
                    }
                    return possibleSuccessors;
                }
            }
        }
        return possibleSuccessors;
    }
};


#endif
