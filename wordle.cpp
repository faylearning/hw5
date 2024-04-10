#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void wordRec(std::set<std::string>& result, const std::string& in, 
             const std::string& floating, const std::set<std::string>& dict,
             std::string& word, size_t spot, size_t blanks);

// Add prototypes of helper functions here

// class wordleclass{
//     std::string& in;
//     std::string& floating;
//     std::set<std::string>& dict;

//     std::set<std::string> result;

//     void wordRec();
//     bool wordCheck();
// }



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    //recurse once for each spot in the word
    //each recursion checks the spot for every single letter 
    std::set<std::string> result;

    if(in == ""){
        return result;
    }
    // int inLen = in.length();
    // std::string word(inLen, ' '); //word of blanks, size inLen

    std::string word = in;

    //loop through in and if there is a letter, 
    //put the letter in the right spot in the empty word

    // for (int i = 0; i < inLen; i++){
    //     if (in[i] != '-'){
    //         word[i] = in[i];
    //     }
    // }

    //loop through in and calculate the number of empty spaces 
    size_t blanks = 0;
    for (size_t i = 0; i < in.length(); i++){
        if (in[i] == '-'){
            blanks++;
        }
    }

    wordRec(result, in, floating, dict, word, 0, blanks);

    

    return result;

}

// Define any helper functions here


//checks if word is valid according to in, floating, and dict
void wordCheck(std::set<std::string>& result, const std::string& in, string word, 
                                const std::string& floating, const std::set<std::string>& dict){
    
    bool found = true;
    string newW = word;

    // if (word == "bind"){
    //     cout << "breaking" << endl;
    // }
    //loops through newW and if in is a letter at that spot, set spot in new word to blank
    for (size_t i = 0; i < newW.length(); i++){
        if (in[i] != '-'){
            if (in[i] != newW[i]){
                throw std::invalid_argument("word not copied right");
            }
            newW[i] = ' ';
        }
    }


    //loop through floating, if floating char exists in newW, 
    //then set the newW position to blank, and keep found true (avoiding duplicates)
    for (size_t i = 0; i < floating.length(); i++){
        
        char f = floating[i];
        std::size_t pos = newW.find(f);
        if (pos != std::string::npos){
            newW[pos] = ' ';
        }else{
            found = false; 
        }  
    }

    //checking if valid word after making sure the floating letters are in the word 
    if (found != false){
        if (dict.find(word) != dict.end()){
            result.insert(word);
        }
    }

}

//recursion finding combinations 
void wordRec(std::set<std::string>& result, const std::string& in, 
             const std::string& floating, const std::set<std::string>& dict,
             std::string& word, size_t spot, size_t blanks){
    
    if (in[spot] != '-'){ //if the spot in the word is not empty
       if (spot == in.length()-1){ //if spot is last spot of word, check
            wordCheck(result, in, word, floating, dict);
        }else{ //recurse if not last spot
            wordRec(result, in, floating, dict, word, spot+1, blanks);
        }
    }else{
        if(spot < in.length()){ 
            if (blanks <= floating.length()){
                for (size_t i = 0; i < floating.length(); i++){
                    word[spot] = floating[i];

                    if (spot == in.length()-1){
                        wordCheck(result, in, word, floating, dict);
                    }else{
                        wordRec(result, in, floating, dict, word, spot+1, blanks);
                    }

                }
            }else{
                for (char c = 'a'; c <= 'z'; c++){
                    word[spot] = c;

                    if (spot == in.length()-1){
                        wordCheck(result, in, word, floating, dict);
                    }else{
                        wordRec(result, in, floating, dict, word, spot+1, blanks);
                    }
                }
            }
            

            // word[spot] = '-'; dont need
        }
    }
}




