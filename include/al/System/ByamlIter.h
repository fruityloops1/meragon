#pragma once

#include "al/System/ByamlData.h"
#include "al/System/ByamlHeader.h"

namespace al {

class ByamlIter {
    union {
        const u8* mData = nullptr;
        const ByamlHeader* mHeader;
    };
    const u8* mRootNode = nullptr;

public:
    ByamlIter();
    ByamlIter(const u8* data);
    ByamlIter(const u8* data, const u8* rootNode);

    bool isValid() const;
    bool isTypeHash() const;
    bool isTypeArray() const;
    bool isTypeContainer() const;
    bool isExistKey(const char* key) const;
    int getKeyIndex(const char* key) const;
    bool isInvertOrder() const;
    int getSize() const;
    ByamlIter getIterByIndex(int index) const;
    bool getByamlDataByIndex(al::ByamlData* out, int index) const;
    ByamlIter getIterByKey(const char* key) const;
    bool getByamlDataByKey(al::ByamlData* out, const char* key) const;
    bool getByamlDataByKeyIndex(al::ByamlData* out, int index) const;
    bool getByamlDataAndKeyName(al::ByamlData* out, const char** key, int index) const;
    bool getKeyName(const char** out, int index) const;
    bool tryGetIterByIndex(ByamlIter* out, int index) const;
    bool tryGetIterAndKeyNameByIndex(ByamlIter* out, const char** key, int index) const;
    bool tryGetIterByKey(ByamlIter* out, const char* key) const;
    bool tryGetStringByKey(const char** out, const char* key) const;
    bool tryConvertString(const char** out, const ByamlData* data) const;
    bool tryGetBinaryByKey(const u8** out, int* size, const char* key) const;
    bool tryConvertBinary(const u8** out, int* size, const ByamlData* data) const;
    bool tryGetBoolByKey(bool* out, const char* key) const;
    bool tryConvertBool(bool* out, const ByamlData* data) const;
    bool tryGetIntByKey(int* out, const char* key) const;
    bool tryConvertInt(int* out, const ByamlData* data) const;
    bool tryConvertUInt(unsigned int* out, const ByamlData* data) const;
    bool tryGetFloatByKey(float* out, const char* key) const;
    bool tryConvertFloat(float* out, const ByamlData* data) const;
    bool tryGetInt64ByKey(long* out, const char* key) const;
    bool tryConvertInt64(long* out, const ByamlData* data) const;
    bool tryConvertUInt64(unsigned long* out, const ByamlData* data) const;
    bool tryGetDoubleByKey(double* out, const char* key) const;
    bool tryConvertDouble(double* out, const ByamlData* data) const;
    bool tryGetStringByIndex(const char** out, int index) const;
    bool tryGetBinaryByIndex(const u8** out, int* size, int index) const;
    bool tryGetBoolByIndex(bool* out, int index) const;
    bool tryGetIntByIndex(int* out, int index) const;
    bool tryGetFloatByIndex(float* out, int index) const;
    bool tryGetInt64ByIndex(long* out, int index) const;
    bool tryConvertIter(ByamlIter* iter, const ByamlData* data) const;
    bool isEqualData(const ByamlIter& other) const;

    const ByamlHeader* getHeader() const { return mHeader; }
};

} // namespace al
