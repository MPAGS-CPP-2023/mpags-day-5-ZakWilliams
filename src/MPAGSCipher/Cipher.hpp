#ifndef MPAGSCIPHER_CIPHER_HPP
#define MPAGSCIPHER_CIPHER_HPP

#include <string>

#include "CipherMode.hpp"

class Cipher{
    public:
        //Special features
        Cipher() = default; //Default constructor
        Cipher(const Cipher& rhs) = default; //Copy constructor, default means compiler generated copy constructor used - Allows objects to be created by copying an existing instance
        Cipher(Cipher&& rhs) = default; //Move constructor. This is used to efficiently transfer ownership of resources - Allows objcts to be created by moving an existing instance
        Cipher& operator=(const Cipher& rhs) = default; //Copy assignment operator. Allows objects to be assigned by copying an existing instance of an object
        Cipher& operator=(Cipher&& rhs) = default; //Move assignment operator. Allows objects to be assigned by moving an instance of an object. 
        virtual ~Cipher() = default; //Declares a destructor

        //Only 1 pure virtual member function - applyCipher
        //Do not use setkey() on this - why?
        virtual std::string applyCipher( const std::string& input,
                                        const CipherMode mode ) const = 0;
        
};

#endif