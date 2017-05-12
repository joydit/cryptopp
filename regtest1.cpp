// regtest1.cpp - originally written and placed in the public domain by Wei Dai
//                regtest.cpp split into 3 files due to OOM kills by JW in April 2017

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "cryptlib.h"
#include "factory.h"
#include "bench.h"
#include "cpu.h"

#include "crc.h"
#include "adler32.h"
#include "md2.h"
#include "md5.h"
#include "keccak.h"
#include "sha3.h"
#include "blake2.h"
#include "sha.h"
#include "tiger.h"
#include "ripemd.h"
#include "panama.h"
#include "whrlpool.h"

#include "osrng.h"
#include "drbg.h"
#include "mersenne.h"
#include "rdrand.h"

#include "modes.h"
#include "aes.h"

// Aggressive stack checking with VS2005 SP1 and above.
#if (_MSC_FULL_VER >= 140050727)
# pragma strict_gs_check (on)
#endif

USING_NAMESPACE(CryptoPP)

// Unkeyed ciphers
void RegisterFactories1();
// Shared key ciphers
void RegisterFactories2();
// Public key ciphers
void RegisterFactories3();

void RegisterFactories(Test::TestClass suites)
{
	static bool s_registered = false;
	if (s_registered)
		return;

	if ((suites & Test::Unkeyed) == Test::Unkeyed)
		RegisterFactories1();

	if ((suites & Test::SharedKey) == Test::SharedKey)
		RegisterFactories2();

	if ((suites & Test::PublicKey) == Test::PublicKey)
		RegisterFactories3();

	s_registered = true;
}

// Unkeyed ciphers
void RegisterFactories1()
{
	RegisterDefaultFactoryFor<HashTransformation, CRC32>();
	RegisterDefaultFactoryFor<HashTransformation, CRC32C>();
	RegisterDefaultFactoryFor<HashTransformation, Adler32>();
	RegisterDefaultFactoryFor<HashTransformation, Weak::MD5>();
	RegisterDefaultFactoryFor<HashTransformation, SHA1>();
	RegisterDefaultFactoryFor<HashTransformation, SHA224>();
	RegisterDefaultFactoryFor<HashTransformation, SHA256>();
	RegisterDefaultFactoryFor<HashTransformation, SHA384>();
	RegisterDefaultFactoryFor<HashTransformation, SHA512>();
	RegisterDefaultFactoryFor<HashTransformation, Whirlpool>();
	RegisterDefaultFactoryFor<HashTransformation, Tiger>();
	RegisterDefaultFactoryFor<HashTransformation, RIPEMD160>();
	RegisterDefaultFactoryFor<HashTransformation, RIPEMD320>();
	RegisterDefaultFactoryFor<HashTransformation, RIPEMD128>();
	RegisterDefaultFactoryFor<HashTransformation, RIPEMD256>();
	RegisterDefaultFactoryFor<HashTransformation, Weak::PanamaHash<LittleEndian> >();
	RegisterDefaultFactoryFor<HashTransformation, Weak::PanamaHash<BigEndian> >();
	RegisterDefaultFactoryFor<HashTransformation, Keccak_224>();
	RegisterDefaultFactoryFor<HashTransformation, Keccak_256>();
	RegisterDefaultFactoryFor<HashTransformation, Keccak_384>();
	RegisterDefaultFactoryFor<HashTransformation, Keccak_512>();
	RegisterDefaultFactoryFor<HashTransformation, SHA3_224>();
	RegisterDefaultFactoryFor<HashTransformation, SHA3_256>();
	RegisterDefaultFactoryFor<HashTransformation, SHA3_384>();
	RegisterDefaultFactoryFor<HashTransformation, SHA3_512>();
	RegisterDefaultFactoryFor<HashTransformation, BLAKE2s>();
	RegisterDefaultFactoryFor<HashTransformation, BLAKE2b>();

#ifdef BLOCKING_RNG_AVAILABLE
	RegisterDefaultFactoryFor<RandomNumberGenerator, BlockingRng>();
#endif
#ifdef NONBLOCKING_RNG_AVAILABLE
	RegisterDefaultFactoryFor<RandomNumberGenerator, NonblockingRng>();
#endif
#ifdef OS_RNG_AVAILABLE
	RegisterDefaultFactoryFor<RandomNumberGenerator, AutoSeededRandomPool>();
	RegisterDefaultFactoryFor<RandomNumberGenerator, AutoSeededX917RNG<AES> >();
#endif
	RegisterDefaultFactoryFor<RandomNumberGenerator, MT19937>();
#if (CRYPTOPP_BOOL_X86 || CRYPTOPP_BOOL_X32 || CRYPTOPP_BOOL_X64)
	if (HasRDRAND())
		RegisterDefaultFactoryFor<RandomNumberGenerator, RDRAND>();
	if (HasRDSEED())
		RegisterDefaultFactoryFor<RandomNumberGenerator, RDSEED>();
#endif
	RegisterDefaultFactoryFor<RandomNumberGenerator, OFB_Mode<AES>::Encryption >("AES/OFB RNG");
	RegisterDefaultFactoryFor<NIST_DRBG, Hash_DRBG<SHA1> >("Hash_DRBG(SHA1)");
	RegisterDefaultFactoryFor<NIST_DRBG, Hash_DRBG<SHA256> >("Hash_DRBG(SHA256)");
	RegisterDefaultFactoryFor<NIST_DRBG, HMAC_DRBG<SHA1> >("HMAC_DRBG(SHA1)");
	RegisterDefaultFactoryFor<NIST_DRBG, HMAC_DRBG<SHA256> >("HMAC_DRBG(SHA256)");
}