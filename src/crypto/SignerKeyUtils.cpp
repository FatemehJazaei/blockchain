// Copyright 2016 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/SignerKeyUtils.h"

#include "crypto/SHA.h"
#include "transactions/FeeBumpTransactionFrame.h"
#include "transactions/TransactionFrame.h"

namespace stellar
{

namespace SignerKeyUtils
{

SignerKey
preAuthTxKey(TransactionFrame const& tx)
{
    SignerKey sk;
    sk.type(SIGNER_KEY_TYPE_PRE_AUTH_TX);
    sk.preAuthTx() = tx.getContentsHash();
    return sk;
}

SignerKey
preAuthTxKey(FeeBumpTransactionFrame const& tx)
{
    SignerKey sk;
    sk.type(SIGNER_KEY_TYPE_PRE_AUTH_TX);
    sk.preAuthTx() = tx.getContentsHash();
    return sk;
}

SignerKey
hashXKey(ByteSlice const& bs)
{
    SignerKey sk;
    sk.type(SIGNER_KEY_TYPE_HASH_X);
    sk.hashX() = sha256(bs);
    return sk;
}

SignerKey
dilithium2PayloadKey(xdr::opaque_array<1312> const& dilithium2,
                     xdr::opaque_vec<64> const& payload)
{
    SignerKey sk;
    sk.type(SIGNER_KEY_TYPE_DILITHIUM2_SIGNED_PAYLOAD);
    sk.dilithium2SignedPayload().dilithium2 = dilithium2;
    sk.dilithium2SignedPayload().payload = payload;
    return sk;
}
}
}
