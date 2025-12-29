#pragma once

#include <cstdint>
#include <string>

namespace kallisto {

/**
 * SipHash-2-4 implementation for secure hashing.
 * 
 * SipHash is designed to be efficient even for short inputs and resistant
 * to hash flooding attacks (DoS) when used with a secret key.
 */
class SipHash {
public:
    /**
     * Initializes SipHash with a 128-bit key (seed).
     * @param k0 First 64 bits of the key.
     * @param k1 Second 64 bits of the key.
     */
    SipHash(uint64_t k0, uint64_t k1);

    /**
     * Computes the 64-bit SipHash-2-4 result for the given string.
     * @param input The string to hash.
     * @return 64-bit hash value.
     */
    uint64_t hash(const std::string& input) const;

    /**
     * Helper to get hash with custom key.
     */
    static uint64_t hash(const std::string& input, uint64_t k0, uint64_t k1);

private:
    uint64_t k0, k1;

    // SipRound logic
    static inline uint64_t rotl(uint64_t x, int b) {
        return (x << b) | (x >> (64 - b));
    }

    static inline void sipround(uint64_t& v0, uint64_t& v1, uint64_t& v2, uint64_t& v3) {
        v0 += v1; v1 = rotl(v1, 13); v1 ^= v0; v0 = rotl(v0, 32);
        v2 += v3; v3 = rotl(v3, 16); v3 ^= v2;
        v0 += v3; v3 = rotl(v3, 21); v3 ^= v0;
        v2 += v1; v1 = rotl(v1, 17); v1 ^= v2; v2 = rotl(v2, 32);
    }
};

} // namespace kallisto
