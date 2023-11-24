#ifndef MPAGSCIPHER_CIPHERFACTORY_HPP
#define MPAGSCIPHER_CIPHERFACTORY_HPP

#include "Cipher.hpp"
#include <memory>

enum class CipherType { Caesar, Playfair, Vigenere };

namespace CipherFactory {

    std::unique_ptr<Cipher> makeCipher(const CipherType type, //Generation of cipher only takes key when type already speciifed
                                        const std::string key );

}

#endif