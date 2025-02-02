#pragma once

// Copyright 2016 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "xdr/Stellar-types.h"

namespace stellar
{

class ByteSlice;
class TransactionFrame;
class FeeBumpTransactionFrame;
struct SignerKey;

namespace SignerKeyUtils
{

SignerKey preAuthTxKey(TransactionFrame const& tx);
SignerKey preAuthTxKey(FeeBumpTransactionFrame const& tx);
SignerKey hashXKey(ByteSlice const& bs);
SignerKey dilithium2PayloadKey(xdr::opaque_array<1312> const& dilithium2,
                               xdr::opaque_vec<64> const& payload);
}
}
