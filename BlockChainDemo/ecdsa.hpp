//
// Created by Jaken on 2017/12/22.
//
#include <cryptopp/eccrypto.h>
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>
#include <cryptopp/files.h>
#include <sstream>
#include <unordered_map>

#define SIGNATURE_SIZE 64

#ifndef BLOCKCHAINDEMO_ECDSA_HPP
#define BLOCKCHAINDEMO_ECDSA_HPP
bool generate_privatekey(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey &privateKey){
    CryptoPP::AutoSeededRandomPool prng;
    privateKey.Initialize( prng, CryptoPP::ASN1::secp256k1());
    return privateKey.Validate( prng, 3 );
}

bool make_publickey(const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey &privateKey,
                    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey &publicKey){
    privateKey.MakePublicKey( publicKey);
    CryptoPP::AutoSeededRandomPool prng;
    return publicKey.Validate( prng, 3 );
}

bool sign_message(const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey &privateKey,
                  const std::string & message,std::string & signature){
    CryptoPP::ECDSA<CryptoPP::ECP,CryptoPP::SHA256>::Signer signer( privateKey );
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::StringSource s( message, true /*pump all*/,
                    new CryptoPP::SignerFilter( prng,
                                      signer,
                                      new CryptoPP::StringSink( signature )
                    ) // SignerFilter
    ); // StringSource


    return !signature.empty();
}

bool verify_Message(const CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey &publicKey,
                    std::string & message, std::string & signature){
    CryptoPP::ECDSA<CryptoPP::ECP,CryptoPP::SHA256>::Verifier verifier(publicKey);
    // Result of the verification process
    bool result = false;

    CryptoPP::StringSource ss( signature+message, true /*pump all*/,
                     new CryptoPP::SignatureVerificationFilter(
                             verifier,
                             new CryptoPP::ArraySink( (byte*)&result, sizeof(result) )
                     ) // SignatureVerificationFilter
    );



    return result;
}

void save_publickey(std::string path,CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey & publicKey)
{
    CryptoPP::FileSink fs( path.c_str(), true /*binary*/ );
    publicKey.Save(fs);
}

void save_privatekey(std::string path,CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey & privateKey)
{
    CryptoPP::FileSink fs( path.c_str(), true /*binary*/ );
    privateKey.Save(fs);
}

bool load_publickey(std::string path,CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey & publicKey)
{
    CryptoPP::FileSource fs(path.c_str(),true);
    publicKey.Load(fs);
    CryptoPP::AutoSeededRandomPool prng;
    return publicKey.Validate( prng, 3 );
}

bool load_privatekey(std::string path,CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey & privateKey)
{
    CryptoPP::FileSource fs(path.c_str(),true);
    privateKey.Load(fs);
    CryptoPP::AutoSeededRandomPool prng;
    return privateKey.Validate( prng, 3 );
}


std::string base58_encode(const std::string message)
{

    CryptoPP::Integer num;
    num.Decode((byte*)message.c_str(),message.size());

    std::string alphabet[58] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F",
                           "G","H","J","K","L","M","N","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c",
                           "d","e","f","g","h","i","j","k","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    int base_count = 58; std::string encoded; CryptoPP::Integer div; CryptoPP::Integer mod;
    while (num >= base_count)
    {
        div = num / base_count;   mod = (num - (base_count * div));
        encoded = alphabet[ mod.ConvertToLong() ] + encoded;   num = div;
    }
    encoded = alphabet[ num.ConvertToLong() ] + encoded;
    return encoded;
}

std::string base58_decode(std::string veri){
    CryptoPP::Integer num;
    std::string alphabet[58] = {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F",
                                "G","H","J","K","L","M","N","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c",
                                "d","e","f","g","h","i","j","k","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

    static std::unordered_map<char,int> map;
    static bool rec=false;
    if(!rec)
    for(int i=0;i<58;++i)
    {
        map[*alphabet[i].begin()]=i;
    }

    veri.reserve();
    for(int i=0;i<veri.size();++i)
    {
        num=num*58+map[veri[i]];
    }

    byte output[SIGNATURE_SIZE];
    num.Encode(output,SIGNATURE_SIZE);

    std::string data;

    for(int i=0;i<SIGNATURE_SIZE;++i)
    {
        data.push_back(output[i]);
    }
    return data;
}

#endif //BLOCKCHAINDEMO_ECDSA_HPP
