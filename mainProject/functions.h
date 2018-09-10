#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#endif // FUNCTIONS_H
#include <iostream>
#include <time.h>
#include <vector>

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

};
