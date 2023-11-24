#include "CipherFactory.hpp"
#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"
//#include "CipherType.hpp"

#include <stdexcept>

std::unique_ptr<Cipher> CipherFactory::makeCipher(const CipherType type,
                                                const std::string key)

                                                //multiple definitions
{
    switch (type){
        case CipherType::Caesar:
            return std::make_unique<CaesarCipher>(key);

        case CipherType::Playfair:
            return std::make_unique<PlayfairCipher>(key);

        case CipherType::Vigenere:
            return std::make_unique<VigenereCipher>(key);

        default:
            //put default here
            throw std::invalid_argument("Invalid cipher type");
    }
}