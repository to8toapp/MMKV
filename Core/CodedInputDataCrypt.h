/*
* Tencent is pleased to support the open source community by making
* MMKV available.
*
* Copyright (C) 2020 THL A29 Limited, a Tencent company.
* All rights reserved.
*
* Licensed under the BSD 3-Clause License (the "License"); you may not use
* this file except in compliance with the License. You may obtain a copy of
* the License at
*
*       https://opensource.org/licenses/BSD-3-Clause
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef CodedInputDataCrypt_h
#define CodedInputDataCrypt_h
#ifdef  __cplusplus

#include "MMKVPredef.h"

#include "MMBuffer.h"
#include "KeyValueHolder.h"
#include "aes/AESCrypt.h"
#include <cstdint>
#include <string>

namespace mmkv {

class CodedInputDataCrypt {
    uint8_t *const m_ptr;
    size_t m_size;
    size_t m_position;
    size_t m_decryptPosition;

    AESCrypt &m_decrypter;
    uint8_t *m_decryptBuffer;
    size_t m_decryptBufferSize;
    size_t m_decryptBufferDiscardPosition;
    size_t m_decryptBufferPosition;
    size_t m_decryptBufferDecryptPosition;

    void consumeBytes(size_t length, bool discardPreData = false);
    void skipBytes(size_t length);
    void statusBeforeDecrypt(size_t rollbackSize, AESCryptStatus &status);

    int8_t readRawByte();

    int32_t readRawVarint32(bool discardPreData = false);

    int32_t readRawLittleEndian32();

    int64_t readRawLittleEndian64();

public:
    CodedInputDataCrypt(const void *oData, size_t length, AESCrypt &crypt);

    ~CodedInputDataCrypt();

    bool isAtEnd() { return m_position == m_size; };

    void seek(size_t addedSize);

    bool readBool();

    double readDouble();

    float readFloat();

    int64_t readInt64();

    uint64_t readUInt64();

    int32_t readInt32();

    uint32_t readUInt32();

    int32_t readFixed32();

    MMBuffer readData();
    void readData(KeyValueHolderCrypt &kvHolder);

#ifndef MMKV_APPLE
    std::string readString();
#else
    NSString *readString();
    NSString *readString(KeyValueHolderCrypt &kvHolder);
    NSData *readNSData();
#endif
};

} // namespace mmkv

#endif
#endif /* CodedInputDataCrypt_h */