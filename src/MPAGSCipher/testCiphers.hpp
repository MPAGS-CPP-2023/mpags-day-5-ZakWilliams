#ifndef TEST_CIPHERS_HPP
#define TEST_CIPHERS_HPP

#include "Cipher.hpp"
#include <string>

bool testCipher(const Cipher& cipher, const CipherMode mode,
                const std::string& inputText, const std::string& expectedOutputText);

#endif