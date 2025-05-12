#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <array>
#include <ctime>
#include<cstdlib>

typedef std::size_t HASH_INDEX_T;

using ull = unsigned long long; //i dont feel like typing this everytime so ull it is 

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
				std::array<ull,5> w {0,0,0,0,0};
				int group = 4;
				long idx = static_cast<long>(k.size()-1);

				while(idx >=0 && group >=0){
					ull value = 0;
					ull place = 1;

					for(int i =0; i< 6&&idx >=0; ++i,--idx){
						char ch = k[idx];
						if(ch >= 'A' && ch<= 'Z'){
						ch= static_cast<char> (ch - 'A'+'a');
						}

						ull digit = letterDigitToNumber(ch);
						value += digit*place;
						place*= 36ULL;
					}
					w[group] =value;
					--group;
				}

				ull hash = 0ULL;
				for(std::size_t i=0; i<5; ++i){
					hash+=rValues[i]*w[i];
				}
				return static_cast<HASH_INDEX_T>(hash);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(letter >= '0' && letter <= '9'){
					return 26ULL + static_cast<ull>(letter-'0');
				}
    	if(letter >= 'A' && letter<= 'Z'){
				letter =static_cast<char> (letter - 'A'+'a');
			}
			return static_cast<ull>(letter - 'a');
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
