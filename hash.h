#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        int strPos = k.size() -1;
        int wPos =4;

        while(strPos >= 0 && wPos >= 0){
          unsigned long long value =0;
          unsigned long long multiplier = 1;

          for(int i =0; i <6 && strPos >=0; i++){
            value += letterDigitToNumber(k[strPos]) * multiplier;
            multiplier *=36;
            strPos--;
          }

          w[wPos] = value;
          wPos--;
        }

        unsigned long long hashVal = 0;
        for(int i=0; i<5; i++)
        {
          hashVal += w[i] * rValues[i];
        }

        return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'a' && letter <='z')
        {
          return letter -'a';
        }

        if(letter >= 'A' && letter <='Z')
        {
          return letter -'A';
        }

        return 26 + (letter - '0');
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
