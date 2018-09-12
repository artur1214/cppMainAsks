#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
class Game{

    public:
        std::vector<int> newNumber(){

            std::vector<int> res;
            srand(time(0));
            std::vector<int> nums;
            for(int i = 0; i< 10; i++){
                nums.push_back(i);
            }
            for(int i = 0; i < 4; i++){
                int pos = rand() % nums.size();
                res.push_back(nums[pos]);
                nums.erase(nums.begin() + pos);
            }
            return res;
        }

        void getMove(){
            int* i = 0;
            std::vector<int> enpNum;
            std::string sEnpNum;
            cin >> sEnpNum;
            for(auto c : sEnpNum){
                enpNum[i] =  c - '0';
                i++;
            }
            delete i;
            checkMove(enpNum);
            return to_res();
        }



    private:
        int cows, bools;
        std::vector<int> generatedNum = newNumber();

        void checkMove(std::vector<int> inputed){

            for(int i=0; i < 4; i++){
                for(int j = 0; j<4; j++){
                    if((generatedNum[i] == inputed[j]) && (i != j)){
                        cows++;
                    }
                    else if((generatedNum[i] == inputed[j]) && (i == j)){
                        bools++;
                    }
                }
            }

        }

        std::string inline toRes(){
            return ""
        }




};
