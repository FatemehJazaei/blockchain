#pragma once

// Copyright 2016 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/KeyUtils.h"

namespace stellar
{

struct SignerKey;

template <> struct KeyFunctions<SignerKey>
{
    struct getKeyTypeEnum
    {
        using type = SignerKeyType;
    };

    static std::string getKeyTypeName();
    static bool getKeyVersionIsSupported(strKey::StrKeyVersionByte keyVersion);
    static bool
    getKeyVersionIsVariableLength(strKey::StrKeyVersionByte keyVersion);
    static SignerKeyType toKeyType(strKey::StrKeyVersionByte keyVersion);
    static strKey::StrKeyVersionByte toKeyVersion(SignerKeyType keyType);
    static xdr::opaque_array<1312>& getDilithium2Value(SignerKey& key);
    static xdr::opaque_array<1312> const&
    getDilithium2Value(SignerKey const& key);

    static std::vector<uint8_t> getKeyValue(SignerKey const& key);
    static void setKeyValue(SignerKey& key, std::vector<uint8_t> const& data);
};
}
