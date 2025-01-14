// Copyright 2016 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/SignerKey.h"

#include "crypto/StrKey.h"
#include "xdr/Stellar-types.h"
#include "xdrpp/marshal.h"

#include <sodium/crypto_sign.h>

namespace stellar
{

std::string
KeyFunctions<SignerKey>::getKeyTypeName()
{
    return "signer key";
}

bool
KeyFunctions<SignerKey>::getKeyVersionIsSupported(
    strKey::StrKeyVersionByte keyVersion)
{
    switch (keyVersion)
    {
    case strKey::STRKEY_PUBKEY_DILITHIUM2:
        return true;
    case strKey::STRKEY_PRE_AUTH_TX:
        return true;
    case strKey::STRKEY_HASH_X:
        return true;
    case strKey::STRKEY_SIGNED_PAYLOAD_DILITHIUM2:
        return true;
    default:
        return false;
    }
}

bool
KeyFunctions<SignerKey>::getKeyVersionIsVariableLength(
    strKey::StrKeyVersionByte keyVersion)
{
    switch (keyVersion)
    {
    case strKey::STRKEY_PUBKEY_DILITHIUM2:
        return false;
    case strKey::STRKEY_PRE_AUTH_TX:
        return false;
    case strKey::STRKEY_HASH_X:
        return false;
    case strKey::STRKEY_SIGNED_PAYLOAD_DILITHIUM2:
        return true;
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

typename KeyFunctions<SignerKey>::getKeyTypeEnum::type
KeyFunctions<SignerKey>::toKeyType(strKey::StrKeyVersionByte keyVersion)
{
    switch (keyVersion)
    {
    case strKey::STRKEY_PUBKEY_DILITHIUM2:
        return SignerKeyType::SIGNER_KEY_TYPE_DILITHIUM2;
    case strKey::STRKEY_PRE_AUTH_TX:
        return SignerKeyType::SIGNER_KEY_TYPE_PRE_AUTH_TX;
    case strKey::STRKEY_HASH_X:
        return SignerKeyType::SIGNER_KEY_TYPE_HASH_X;
    case strKey::STRKEY_SIGNED_PAYLOAD_DILITHIUM2:
        return SignerKeyType::SIGNER_KEY_TYPE_DILITHIUM2_SIGNED_PAYLOAD;
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

strKey::StrKeyVersionByte
KeyFunctions<SignerKey>::toKeyVersion(SignerKeyType keyType)
{
    switch (keyType)
    {
    case SignerKeyType::SIGNER_KEY_TYPE_DILITHIUM2:
        return strKey::STRKEY_PUBKEY_DILITHIUM2;
    case SignerKeyType::SIGNER_KEY_TYPE_PRE_AUTH_TX:
        return strKey::STRKEY_PRE_AUTH_TX;
    case SignerKeyType::SIGNER_KEY_TYPE_HASH_X:
        return strKey::STRKEY_HASH_X;
    case SignerKeyType::SIGNER_KEY_TYPE_DILITHIUM2_SIGNED_PAYLOAD:
        return strKey::STRKEY_SIGNED_PAYLOAD_DILITHIUM2;
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

xdr::opaque_array<1312>&
KeyFunctions<SignerKey>::getDilithium2Value(SignerKey& key)
{
    switch (key.type())
    {
    case SIGNER_KEY_TYPE_DILITHIUM2:
        return key.dilithium2();
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

xdr::opaque_array<1312> const&
KeyFunctions<SignerKey>::getDilithium2Value(SignerKey const& key)
{
    switch (key.type())
    {
    case SIGNER_KEY_TYPE_DILITHIUM2:
        return key.dilithium2();
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

std::vector<uint8_t>
KeyFunctions<SignerKey>::getKeyValue(SignerKey const& key)
{
    switch (key.type())
    {
    case SIGNER_KEY_TYPE_DILITHIUM2:
        return xdr::xdr_to_opaque(key.dilithium2());
    case SIGNER_KEY_TYPE_PRE_AUTH_TX:
        return xdr::xdr_to_opaque(key.preAuthTx());
    case SIGNER_KEY_TYPE_HASH_X:
        return xdr::xdr_to_opaque(key.hashX());
    case SIGNER_KEY_TYPE_DILITHIUM2_SIGNED_PAYLOAD:
        return xdr::xdr_to_opaque(key.dilithium2SignedPayload());
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

void
KeyFunctions<SignerKey>::setKeyValue(SignerKey& key,
                                     std::vector<uint8_t> const& data)
{
    switch (key.type())
    {
    case SIGNER_KEY_TYPE_DILITHIUM2:
        xdr::xdr_from_opaque(data, key.dilithium2());
        break;
    case SIGNER_KEY_TYPE_PRE_AUTH_TX:
        xdr::xdr_from_opaque(data, key.preAuthTx());
        break;
    case SIGNER_KEY_TYPE_HASH_X:
        xdr::xdr_from_opaque(data, key.hashX());
        break;
    case SIGNER_KEY_TYPE_DILITHIUM2_SIGNED_PAYLOAD:
        xdr::xdr_from_opaque(data, key.dilithium2SignedPayload());
        break;
    default:
        throw std::invalid_argument("invalid signer key type");
    }
}

}
