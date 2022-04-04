/**
 * \file ciphers.cpp
 *
 * Ebben a fájlban kell megvalósítania az CaesarCipher, MyCipher, CipherQueue osztályok metódusait.
 * 
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include "memtrace.h"
#include "ciphers.h"
CaesarCipher::CaesarCipher(int shift){
    if(shift > 0) this->shift = shift % 26;
    else this->shift = 26 + shift % 26;
}

std::string CaesarCipher::encode(const std::string& msg){
    std::string dst;
    for(size_t i = 0; i < msg.size(); ++i){ 
        if((msg[i] > 'z' || msg[i] < 'a') && msg[i] != ' ') throw("GIS2YB");
        dst.push_back(msg[i] == ' ' ? ' ' : msg[i] + shift <= 'z' ? msg[i] + shift : shift - 'z' + msg[i] + 'a'- 1);
    }

    return dst;
}

std::string CaesarCipher::decode(const std::string& msg){
    std::string dst;
    for(size_t i = 0; i < msg.size(); ++i){
        if((msg[i] > 'z' || msg[i] < 'a') && msg[i] != ' ') throw("GIS2YB");
        dst.push_back(msg[i] == ' ' ? ' ' : msg[i] - shift >= 'a' ? msg[i] - shift : 'z' - shift + msg[i] - 'a' + 1);
    }

    return dst;
}

Cipher* CaesarCipher::clone() const{
    CaesarCipher* dst = new CaesarCipher(this->shift);
    return dst;
}

std::string MyCipher::encode(const std::string& msg){
    std::string dst;
    int val;
    for(size_t i = 0; i < msg.size(); ++i){
        if((msg[i] > 'z' || msg[i] < 'a') && msg[i] != ' ') throw("GIS2YB");
        val = msg[i] + offset + i + key[i % key.size()] - 'a';  
        
        if(msg[i] == ' ') dst.push_back(' ');
        else
            if(val < 'a'){
                dst.push_back(offset + i - 'z' + msg[i] + key[i % key.size()]);
            }else if(val > ('z' + 26)){
                dst.push_back((offset + i + key[i % key.size()]) % 'z' + '`' - ('z' - msg[i]) - 1);
            }else if(val > 'z'){
                dst.push_back(offset + i + key[i % key.size()] - ('z' - msg[i]) - 1);
            } else dst.push_back(val);
    }

    return dst;
}

std::string MyCipher::decode(const std::string& msg){   
    std::string dst;
    int val;
    for(size_t i = 0; i < msg.size(); ++i){
        if((msg[i] > 'z' || msg[i] < 'a') && msg[i] != ' ') throw("GIS2YB");
        val = msg[i] - offset - i - key[i % key.size()] + 'a';
        if(val < 'a'){
            dst.push_back(msg[i] == ' ' ? ' ' : 'z' - (i + offset - (msg[i] - 'a')) - (key[i % key.size()] - 'a') + 1);
        }else if(val > 'z'){
            dst.push_back(msg[i] == ' ' ? ' ' : 'a' + offset - 'z' - msg[i] - i + key[i % key.size()] - 'a');
        }else dst.push_back(msg[i] == ' ' ? ' ' : val);
    }

    return dst;
}

Cipher* MyCipher::clone() const{
    MyCipher* dst = new MyCipher(this->key, this->offset);
    return dst;
}

void CipherQueue::add(Cipher* item){
    Cipher** dst = new Cipher*[len + 1];
    for(size_t i = 0; i < len; ++i){
        dst[i] = this->CipherArr[i]->clone();
        delete this->CipherArr[i];
    }
    delete[] this->CipherArr;
    dst[len] = item;
    this->CipherArr = new Cipher*[len + 1];
    this->len++;

    for(size_t i = 0; i < len; ++i){
        this->CipherArr[i] = dst[i];
    }
}

std::string CipherQueue::encode(const std::string& msg){}
std::string CipherQueue::decode(const std::string& msg){}
Cipher* CipherQueue::clone() const{}
CipherQueue::~CipherQueue(){}
