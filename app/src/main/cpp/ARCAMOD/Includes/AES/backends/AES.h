#pragma once

// Written by BydzNesia :)

#include "plusaes.hpp"
#include "base64.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <unistd.h>

namespace AES {
    struct iMode {
        int RAND = 0;
        int SECOND = 1;
        int MAIN   = 2;
    } Mode;

    /*
     * Uses to Store Data
     */
    struct iData {
        const std::vector<unsigned char> AES_MAIN_KEY = {
            0x34, 0x73, 0x51, 0x66, 0x72, 0x36, 0x37, 0x38,
            0x38, 0x34, 0x42, 0x54, 0x43, 0x50, 0x34, 0x71,
            0x63, 0x32, 0x4D, 0x32, 0x31, 0x38, 0x31, 0x45,
            0x5A, 0x30, 0x76, 0x58, 0x74, 0x31, 0x54, 0x39
        };
        const unsigned char AES_MAIN_IV[16] = {
            0x32, 0x34, 0x37, 0x49, 0x4e, 0x30, 0x32, 0x4b,
            0x36, 0x4b, 0x37, 0x6a, 0x69, 0x5a, 0x4c, 0x45
        };

        const std::vector<unsigned char> AES_SECOND_KEY = {
            0x38, 0x44, 0x6B, 0x34, 0x61, 0x76, 0x66, 0x68,
            0x39, 0x39, 0x36, 0x4F, 0x30, 0x31, 0x42, 0x4F,
            0x44, 0x6D, 0x50, 0x31, 0x69, 0x63, 0x67, 0x39,
            0x58, 0x33, 0x6F, 0x34, 0x37, 0x78, 0x32, 0x36
        };
        const unsigned char AES_SECOND_IV[16] = {
            0x77, 0x7a, 0x72, 0x79, 0x54, 0x69, 0x55, 0x34,
            0x7a, 0x38, 0x47, 0x39, 0x43, 0x59, 0x37, 0x54
        };
    };

    static iData Data;

    static const char alphanumerics[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    /*
     * Desc : A Function to Create Random String
     * Return Type : std::string
     */
    static std::string CreateRandomString(const int len = 32) {
        //unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        //unsigned seed = reinterpret_cast<unsigned int>(time(0));
        std::srand(time(0));

        std::string tmp;
        tmp.reserve(len);
        for (int i = 0; i < len; ++i) {
            tmp += alphanumerics[rand() % (sizeof(alphanumerics) - 1)];
        }

        return tmp;
    }

    /*
     * Desc : A Function to Create Random String
     * Return Type : const char *
     */
    static const char *CreateRandomCString(const int len = 32) {
        //unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        //unsigned seed = reinterpret_cast<unsigned int>(time(0));
        std::srand(time(0));

        std::string tmp;
        tmp.reserve(len);
        for (int i = 0; i < len; ++i) {
            tmp += alphanumerics[rand() % (sizeof(alphanumerics) - 1)];
        }

        return tmp.c_str();
    }

    /*
     * Convert/Encode std::string to hex std::string
     * Return Type : std::string
     */
    static std::string StringToHex(const std::string& input) {
        std::ostringstream hexStringStream;
        hexStringStream << std::hex << std::setfill('0');

        for (unsigned char c : input) {
            hexStringStream << std::setw(2) << static_cast<int>(c);
        }

        return hexStringStream.str();
    }

    /*
     * Convert/Decode hex std::string to std::string
     * Return Type : std::string
     */
    std::string HexToString(const std::string& hexString) {
        std::string decodedString;

        for (size_t i = 0; i < hexString.length(); i += 2) {
            std::string byteString = hexString.substr(i, 2);
            char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
            decodedString += byte;
        }

        return decodedString;
    }

    /*
     * 
     */
    static std::vector<std::string> SplitKeyIV(const std::string data) {
        std::vector<std::string> tmp;

        std::istringstream iss(data);
        std::string tmp0;

        while (std::getline(iss, tmp0, ':')) {
            tmp.push_back(tmp0);
        }

        return tmp;
    }

    /*
     * MAIN AES Encode with Default / MAIN KEY and IV
     * return : std::string
     */
    static std::string DefaultEncrypt(const std::string data, const std::vector<unsigned char> PASS_KEY, const unsigned char (* PASS_IV)[16]) {
        const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(data.size());
        std::vector<unsigned char> encrypted(encrypted_size);
        plusaes::encrypt_cbc((unsigned char*) data.data(), data.size(), &PASS_KEY[0], PASS_KEY.size(), PASS_IV, &encrypted[0], encrypted.size(), true);
        std::string result(encrypted.begin(), encrypted.end());
        result = Base64::Encode(result);
        return StringToHex(result);
    }

    /*
     * MAIN AES Decode with Default / MAIN KEY and IV
     * return : std::string
     */
    static std::string DefaultDecrypt(const std::string data, const std::vector<unsigned char> PASS_KEY, const unsigned char (* PASS_IV)[16]) {
        unsigned long padded_size = 0;
        std::string decode_hex = HexToString(data);
        std::string decode_64;
        Base64::Decode(decode_hex, decode_64);
        std::vector<unsigned char> decrypted((unsigned long) decode_64.length());
        plusaes::Error decGo = plusaes::decrypt_cbc((unsigned char*) decode_64.data(), decode_64.size(), &PASS_KEY[0], PASS_KEY.size(), PASS_IV, &decrypted[0], decrypted.size(), &padded_size);
        std::string result(decrypted.begin(), decrypted.end() - padded_size);

        return result;
    }

    /*
     * Random-Encode AES
     * return : std::string, DATA:KEY:IV
     */
    static std::string RandomEncrypt(const std::string data) {
        std::string random_key = CreateRandomString(32);
        std::string random_iv  = CreateRandomString(16);

        while (random_key.length() != 32 && random_iv.length() != 16) {
            random_key = CreateRandomString(32);
            random_iv  = CreateRandomString(16);
        }

        const std::vector<unsigned char> MY_RAND_KEY(random_key.begin(), random_key.end());
        unsigned char MY_RAND_IV[16];

        std::copy(random_iv.begin(), random_iv.end(), MY_RAND_IV);

        const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(data.size());
        std::vector<unsigned char> encrypted(encrypted_size);
        plusaes::encrypt_cbc((unsigned char*) data.data(), data.size(), &MY_RAND_KEY[0], MY_RAND_KEY.size(), &MY_RAND_IV, &encrypted[0], encrypted.size(), true);
        std::string sEncrypted(encrypted.begin(), encrypted.end());
        std::string result;
        result += StringToHex(sEncrypted);
        result += OBF(":");
        result += StringToHex(random_key);
        result += OBF(":");
        result += StringToHex(random_iv);

        result = Base64::Encode(result);

        return StringToHex(result);
    }

    /*
     * Random-Decoder AES
     * String format : DATA:KEY:IV
     * return : std::string
     */
    static std::string RandomDecrypt(const std::string data) {
        std::string tmp;
        
        std::string decode_hex = HexToString(data);
        std::string decode_64;
        Base64::Decode(decode_hex, decode_64);

        std::vector<std::string> split_keyiv = SplitKeyIV(decode_64);

        std::string encoded_data_split = split_keyiv[0];
        std::string random_key_split   = split_keyiv[1];
        std::string random_iv_split    = split_keyiv[2];

        std::string encoded_data(encoded_data_split.data());
        std::string encoded_key(random_key_split.data());
        std::string encoded_iv(random_iv_split.data());

        std::string final_data = HexToString(encoded_data);
        std::string random_key = HexToString(encoded_key);
        std::string random_iv  = HexToString(encoded_iv);

        std::vector<unsigned char> MY_RAND_KEY(random_key.begin(), random_key.end());
        unsigned char MY_RAND_IV[16];

        std::copy(random_iv.begin(), random_iv.end(), MY_RAND_IV);

        unsigned long padded_size = 0;
        std::vector<unsigned char> decrypted((unsigned long) final_data.length());
        plusaes::Error decGo = plusaes::decrypt_cbc((unsigned char*) final_data.data(), final_data.size(), &MY_RAND_KEY[0], MY_RAND_KEY.size(), &MY_RAND_IV, &decrypted[0], decrypted.size(), &padded_size);
        std::string result(decrypted.begin(), decrypted.end() - padded_size);

        return result;
    }

    static std::string Encrypt(const std::string data, int mode = 0) {
        if (mode == Mode.MAIN) {
            return DefaultEncrypt(data, Data.AES_MAIN_KEY, &Data.AES_MAIN_IV);
        } else if (mode == Mode.SECOND) {
            return DefaultEncrypt(data, Data.AES_SECOND_KEY, &Data.AES_SECOND_IV);
        }

        return RandomEncrypt(data);
    }

    static std::string Decrypt(const std::string data, int mode = 0) {
        if (mode == Mode.MAIN) {
            return DefaultDecrypt(data, Data.AES_MAIN_KEY, &Data.AES_MAIN_IV);
        } else if (mode == Mode.SECOND) {
            return DefaultDecrypt(data, Data.AES_SECOND_KEY, &Data.AES_SECOND_IV);
        }

        return RandomDecrypt(data);
    }
}