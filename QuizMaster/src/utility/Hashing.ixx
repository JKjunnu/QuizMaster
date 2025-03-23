export module Hashing;

import <string>;
import <windows.h>;
import <sstream>;
import <iomanip>;

export std::string sha256(const std::string& str) {
    HCRYPTPROV hProv = NULL;
    HCRYPTPROV hHash = NULL;
    BYTE hash[32];
    DWORD hashLen = 32;

    if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        if (CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
            if (CryptHashData(hHash, reinterpret_cast<const BYTE*>(str.c_str()), str.length(), 0)) {
                if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
                    std::stringstream ss;
                    for (DWORD i = 0; i < hashLen; ++i) {
                        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
                    }
                    CryptDestroyHash(hHash);
                    CryptReleaseContext(hProv, 0);
                    return ss.str();
                }
            }
            CryptDestroyHash(hHash);
        }
        CryptReleaseContext(hProv, 0);
    }
    throw std::runtime_error("Error hashing password");
}