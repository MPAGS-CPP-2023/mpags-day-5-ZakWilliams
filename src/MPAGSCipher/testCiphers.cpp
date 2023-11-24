//Write a function

//Function takes:
//  cipher                      Cipher& cipher
//  encrypt/decrypt mode        CipherMode mode
//  input text                  std::string& inputText
//  output text                 std::string& outputText

// Use this to test the 3 ciphers

//! Unit Tests for MPAGSCipher Cipher Class
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include "Cipher.hpp"
#include "testCiphers.hpp"

#include <string>
#include <iostream>

bool testCipher( const Cipher& cipher, const CipherMode mode,
                const std::string& inputText, const std::string& expected_outputText ) {
    //Apply cipher for several keys
    std::string received_OutputText = cipher.applyCipher(inputText, mode);

    std::cout << expected_outputText << std::endl;
    std::cout << received_OutputText << std::endl;

    return (received_OutputText == expected_outputText);
}