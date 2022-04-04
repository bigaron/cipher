/**
 * \file ciphers.h
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef CipherS_H
#define CipherS_H

#include <string>
#include <vector>
#include "memtrace.h"

/**
 * Az ős osztály interfésze
 */ 
class Cipher {
public:
    /**
     * Titkosítja a kapott stringet
     * @param   message titkosítandó üzenet
     * @return  a message szöveg titkosított változata
     */
    virtual std::string encode(const std::string& message) = 0;
    /**
     * Dekódolja a kapott stringet
     * @param   ciphertext titkosított üzenet
     * @return  a megfejtett nyílt szöveg
     */
    virtual std::string decode(const std::string& ciphertext) = 0;
    /**
     * Létrehoz egy másolatot dinamikusan
     * @return  a létrehozott objektumra mutató pointer
     */
    virtual Cipher* clone() const = 0;
    /**
     * Alap destruktor
     */ 
    virtual ~Cipher() { };
};

//Osztályok, amiket meg kell csinálni a leírások és az osztálydiagram alapján
class CaesarCipher:public Cipher {
private:
    int shift;
public:
    CaesarCipher(int shift);
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    Cipher* clone() const;
};

class MyCipher:public Cipher {
private:
    std::string key;
    int offset;
public:
    MyCipher(std::string key): key(key), offset(0) {}
    MyCipher(std::string key, int offset): key(key), offset(offset) {}
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    Cipher* clone() const;
};

class CipherQueue:public Cipher {
    Cipher** CipherArr;
    size_t len; 
public:
    CipherQueue():CipherArr(new Cipher*[1]), len(0){}
    void add(Cipher*);
    std::string encode(const std::string&);
    std::string decode(const std::string&);
    Cipher* clone() const;
    ~CipherQueue();
};

#endif
