#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <iostream>
#include <time.h>
#include <vector>
#include <map>
class Game{

    public:

    Game(){
        std::cout << "Cows and bools game by Arthur, look the rules in the google, you have 6 try" << std::endl << std::endl;
        newNumber();
        generatedNum = newNumber();
        for(int i=0; i<6; i++){
            std::cout << getMove()<< std::endl;
        }
    }


    private:
        int cows = 0; int bools = 0;
        std::vector<int> generatedNum;

        std::string checkMove(std::vector<int> inputed){ //получить число
                cows = 0; bools = 0;
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
            return toRes();
        }


        inline std::string toRes(){  //возврат строки
            return "cows = " + std::to_string(cows) + " ; bools = " + std:: to_string(bools);
        }


        std::vector<int> newNumber(){ //генерация числа

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


        std::string getMove(){
            int i = 0;
            std::vector<int> enpNum;
            std::string sEnpNum;
            std::cin >> sEnpNum;
            for(auto c : sEnpNum){
                enpNum.push_back(c - '0');
                i++;
            }

            checkMove(enpNum);
            return toRes();
        }




};
