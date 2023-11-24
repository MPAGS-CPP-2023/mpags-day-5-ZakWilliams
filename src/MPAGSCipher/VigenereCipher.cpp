#include "VigenereCipher.hpp"
#include "Alphabet.hpp"

#include <algorithm>
#include <string>

VigenereCipher::VigenereCipher(const std::string& key)
{
    this->setKey(key);
}

void VigenereCipher::setKey(const std::string& key)
{
    // Store the key
    key_ = key;
    
    // Make sure the key is uppercase
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),::toupper);
    
    // Remove non-alphabet characters - first move to end with remove_end, then chop off end
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),[](char c) { return !std::isalpha(c); }),std::end(key_));
    
    // Check if the key is empty and replace with default if so
    if (key_ == "") {
        key_ = "DEFAULTKEY";
    }
    
    // loop over the key
    std::size_t caesar_key{0};
    for ( const char& letter : key_ ) {
        // Find the letter position in the alphabet
        for (std::size_t i{0}; i < Alphabet::size; ++i) {
            if (letter == Alphabet::alphabet[i]) {
                caesar_key = i;
                // Create a CaesarCipher using this position as a key
                //CaesarCipher letter_cipher{caesar_key};
                // Insert a std::pair of the letter and CaesarCipher into the lookup
                //charLookup_[letter] = letter_cipher;
                charLookup_.emplace(letter, CaesarCipher{caesar_key}); // Works better
            }
        }
    }
}

std::string VigenereCipher::applyCipher(const std::string& inputText,
                                        const CipherMode cipherMode) const /**/
{
    std::string outputChar{""};
    std::string outputText{""}; 
    std::string feedingChar{""};
    // For each letter in input:
    for ( const char& inputChar : inputText ) {
        // Find the corresponding letter in the key, repeating/truncating as required
        std::size_t position = inputText.find(inputChar);
        size_t key_position = position % key_.size();
        char key_letter = key_[key_position]; //finds the letter in the key
        // Find the Caesar cipher from the lookup
        CaesarCipher currentCaesar = charLookup_.at(key_letter); //CaesarCipher object defined as the one associated with key_letter
        // Run the (de)encryption - apply CaesarCipher shift/unshift to the current inputChar, returning outputChar
        feedingChar = "";
        feedingChar += inputChar; //Exists to bypass character/string issues for CaesarCipher object class
        outputChar = currentCaesar.applyCipher(feedingChar, cipherMode);
        // Add the result to the output
        outputText += outputChar;
    }
    
    return outputText;
}