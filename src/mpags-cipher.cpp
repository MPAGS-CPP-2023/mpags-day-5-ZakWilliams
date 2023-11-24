#include "CaesarCipher.hpp"
#include "CipherMode.hpp"
#include "CipherType.hpp"
#include "PlayfairCipher.hpp"
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"
#include "VigenereCipher.hpp"
#include "testCiphers.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    ProgramSettings settings{false, false, "", "", {}, {}, CipherMode::Encrypt};

    // Process command line arguments
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, settings)};

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (settings.helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>] [-c <cipher>] [-k <key>] [--encrypt/--decrypt]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  -c CIPHER        Specify the cipher to be used to perform the encryption/decryption\n"
            << "                   CIPHER can be caesar or playfair - caesar is the default\n\n"
            << "  -k KEY           Specify the cipher KEY\n"
            << "                   A null key, i.e. no encryption, is used if not supplied\n\n"
            << "  --encrypt        Will use the cipher to encrypt the input text (default behaviour)\n\n"
            << "  --decrypt        Will use the cipher to decrypt the input text\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (settings.versionRequested) {
        std::cout << "0.4.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!settings.inputFile.empty()) {
        // Open the file and check that we can read from it
        std::ifstream inputStream{settings.inputFile};
        if (!inputStream.good()) {
            std::cerr << "[error] failed to create istream on file '"
                      << settings.inputFile << "'" << std::endl;
            return 1;
        }

        // Loop over each character from the file
        while (inputStream >> inputChar) {
            inputText += transformChar(inputChar);
        }

    } else {
        // Loop over each character from user input
        // (until Return then CTRL-D (EOF) pressed)
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    std::string outputText;

    switch (settings.cipherType[0]) {
        case CipherType::Caesar: {
            // Run the Caesar cipher (using the specified key and encrypt/decrypt flag) on the input text
            CaesarCipher cipher{settings.cipherKey[0]};
            outputText = cipher.applyCipher(inputText, settings.cipherMode);
            break;
        }
        case CipherType::Playfair: {
            PlayfairCipher cipher{settings.cipherKey[0]};
            outputText = cipher.applyCipher(inputText, settings.cipherMode);
            break;
        }
        case CipherType::Vigenere: {
            VigenereCipher cipher{settings.cipherKey[0]}; //Initialise as a VigenereCipher type, with key input, settings.cipheeKey[0]
            outputText = cipher.applyCipher(inputText, settings.cipherMode);
            break;
        }
    }

    // Implement tests of dynamic polymorphism
    CaesarCipher cc{1};
    PlayfairCipher pc{"hello"};
    VigenereCipher vc{"HELLOTHERE"}; //Should shift everything by 1 letter, 2 letters

    const bool cc_check{testCipher(cc, CipherMode::Encrypt, "HELLOWORLD", "IFMMPXPSME")};
    const bool pc_check{testCipher(pc, CipherMode::Encrypt, 
                        "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", 
                        "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA")};
    const bool vc_check{testCipher(vc, CipherMode::Encrypt, 
                        "THISISATESTOFTHEVIGENERECIPHERTHISISALONGERPASSAGEOFTEXT", 
                        "ALTDWLHXVWASQEVXCMXIUICPQBWLVVALTDWLHPFRNICAOLZEXIVJEPLM")};

    if (cc_check) {
        std::cout << "CC VERIFIED" << std::endl;
    }
    if (vc_check) {
        std::cout << "VC VERIFIED" << std::endl;
    }
    if (pc_check) {
        std::cout << "PC VERIFIED" << std::endl;
    }


    // Output the encrypted/decrypted text to stdout/file
    if (!settings.outputFile.empty()) {
        // Open the file and check that we can write to it
        std::ofstream outputStream{settings.outputFile};
        if (!outputStream.good()) {
            std::cerr << "[error] failed to create ostream on file '"
                      << settings.outputFile << "'" << std::endl;
            return 1;
        }

        // Print the encrypted/decrypted text to the file
        outputStream << outputText << std::endl;

    } else {
        // Print the encrypted/decrypted text to the screen
        std::cout << outputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}