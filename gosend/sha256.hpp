//
// Created by Jaken on 2017/12/25.
//
#include <string>
#include <cryptopp/eccrypto.h>
#include <cryptopp/hex.h>
#include <iostream>
#ifndef BLOCKCHAINDEMO_ASH256_HPP
#define BLOCKCHAINDEMO_ASH256_HPP
std::string sha256(std::string & data)
{
    CryptoPP::SHA256 hash;

    std::string digest;

    CryptoPP::StringSource s(data, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

    return digest;


}


#endif //BLOCKCHAINDEMO_ASH256_HPP
