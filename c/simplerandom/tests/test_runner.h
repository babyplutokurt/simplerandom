
#define __STDC_CONSTANT_MACROS
#include "simplerandom-c.h"

#include <time.h>

#define CXXTEST_HAVE_EH
#include <cxxtest/TestSuite.h>
#include <iostream>
#include <limits>

class SimpleRandomWrapper
{
public:
    // Non-standard API
    virtual size_t num_seeds() = 0;
    virtual void discard(uintmax_t n) = 0;
    virtual void mix(uint32_t * p_mix_array, size_t n) = 0;

    // Standard C++ random API
    typedef uint32_t result_type;
    virtual uint32_t operator()() = 0;
    virtual uint32_t min() const
    {
        return 0;
    }
    virtual uint32_t max() const
    {
        return std::numeric_limits<uint32_t>::max();
    }
};

class SimpleRandomWrapperCong : public SimpleRandomWrapper
{
private:
    SimpleRandomCong_t  rng;
public:
    SimpleRandomWrapperCong(uint32_t seed=0) { simplerandom_cong_seed(&rng, seed); }
    SimpleRandomWrapperCong(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_cong_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 1; }

    uint32_t operator()() { return simplerandom_cong_next(&rng); }
    void discard(uintmax_t n) { simplerandom_cong_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_cong_mix(&rng, p_mix_array, n); }
};

typedef SimpleRandomWrapperCong SimpleRandomSeeder;

class SimpleRandomWrapperSHR3 : public SimpleRandomWrapper
{
private:
    SimpleRandomSHR3_t  rng;
public:
    SimpleRandomWrapperSHR3(uint32_t seed=0) { simplerandom_shr3_seed(&rng, seed); }
    SimpleRandomWrapperSHR3(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_shr3_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 1; }

    uint32_t operator()() { return simplerandom_shr3_next(&rng); }
    void discard(uintmax_t n) { simplerandom_shr3_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_shr3_mix(&rng, p_mix_array, n); }
    uint32_t min() const
    {
        // SHR3 is exceptional in that it doesn't ever return 0.
        return 1;
    }
};

class SimpleRandomWrapperMWC1 : public SimpleRandomWrapper
{
private:
    SimpleRandomMWC1_t  rng;
public:
    SimpleRandomWrapperMWC1(uint32_t seed1=0, uint32_t seed2=0) { simplerandom_mwc1_seed(&rng, seed1, seed2); }
    SimpleRandomWrapperMWC1(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_mwc1_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 2; }

    uint32_t operator()() { return simplerandom_mwc1_next(&rng); }
    void discard(uintmax_t n) { simplerandom_mwc1_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_mwc1_mix(&rng, p_mix_array, n); }
};

class SimpleRandomWrapperMWC2 : public SimpleRandomWrapper
{
private:
    SimpleRandomMWC2_t  rng;
public:
    SimpleRandomWrapperMWC2(uint32_t seed1=0, uint32_t seed2=0) { simplerandom_mwc2_seed(&rng, seed1, seed2); }
    SimpleRandomWrapperMWC2(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_mwc2_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 2; }

    uint32_t operator()() { return simplerandom_mwc2_next(&rng); }
    void discard(uintmax_t n) { simplerandom_mwc2_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_mwc2_mix(&rng, p_mix_array, n); }
};

class SimpleRandomWrapperKISS : public SimpleRandomWrapper
{
private:
    SimpleRandomKISS_t  rng;
public:
    SimpleRandomWrapperKISS(uint32_t seed1, uint32_t seed2, uint32_t seed3, uint32_t seed4)
    {
        simplerandom_kiss_seed(&rng, seed1, seed2, seed3, seed4);
    }
    SimpleRandomWrapperKISS(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_kiss_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 4; }

    uint32_t operator()() { return simplerandom_kiss_next(&rng); }
    void discard(uintmax_t n) { simplerandom_kiss_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_kiss_mix(&rng, p_mix_array, n); }
};

#ifdef UINT64_C

class SimpleRandomWrapperMWC64 : public SimpleRandomWrapper
{
private:
    SimpleRandomMWC64_t  rng;
public:
    SimpleRandomWrapperMWC64(uint32_t seed1=0, uint32_t seed2=0) { simplerandom_mwc64_seed(&rng, seed1, seed2); }
    SimpleRandomWrapperMWC64(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_mwc64_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 2; }

    uint32_t operator()() { return simplerandom_mwc64_next(&rng); }
    void discard(uintmax_t n) { simplerandom_mwc64_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_mwc64_mix(&rng, p_mix_array, n); }
};

class SimpleRandomWrapperKISS2 : public SimpleRandomWrapper
{
private:
    SimpleRandomKISS2_t rng;
public:
    SimpleRandomWrapperKISS2(uint32_t seed1=0, uint32_t seed2=0, uint32_t seed3=0, uint32_t seed4=0)
    {
        simplerandom_kiss2_seed(&rng, seed1, seed2, seed3, seed4);
    }
    SimpleRandomWrapperKISS2(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_kiss2_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 4; }

    uint32_t operator()() { return simplerandom_kiss2_next(&rng); }
    void discard(uintmax_t n) { simplerandom_kiss2_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_kiss2_mix(&rng, p_mix_array, n); }
};

#endif

class SimpleRandomWrapperLFSR113 : public SimpleRandomWrapper
{
private:
    SimpleRandomLFSR113_t  rng;
public:
    SimpleRandomWrapperLFSR113(uint32_t seed1=0, uint32_t seed2=0, uint32_t seed3=0, uint32_t seed4=0)
    {
        simplerandom_lfsr113_seed(&rng, seed1, seed2, seed3, seed4);
    }
    SimpleRandomWrapperLFSR113(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_lfsr113_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 4; }

    uint32_t operator()() { return simplerandom_lfsr113_next(&rng); }
    void discard(uintmax_t n) { simplerandom_lfsr113_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_lfsr113_mix(&rng, p_mix_array, n); }
};

class SimpleRandomWrapperLFSR88 : public SimpleRandomWrapper
{
private:
    SimpleRandomLFSR88_t  rng;
public:
    SimpleRandomWrapperLFSR88(uint32_t seed1=0, uint32_t seed2=0, uint32_t seed3=0)
    {
        simplerandom_lfsr88_seed(&rng, seed1, seed2, seed3);
    }
    SimpleRandomWrapperLFSR88(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        simplerandom_lfsr88_seed_array(&rng, p_seeds, num_seeds, mix_extras);
    }
    size_t num_seeds() { return 3; }

    uint32_t operator()() { return simplerandom_lfsr88_next(&rng); }
    void discard(uintmax_t n) { simplerandom_lfsr88_discard(&rng, n); }
    void mix(uint32_t * p_mix_array, size_t n) { simplerandom_lfsr88_mix(&rng, p_mix_array, n); }
};


class SimplerandomCongTest : public CxxTest::TestSuite
{
protected:
    SimpleRandomWrapper * rng;
public:
    virtual SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperCong(seed_rng());
    }
    virtual SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperCong(2051391225u);
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperCong(p_seeds, num_seeds, mix_extras);
    }
    virtual uint32_t get_million_result() { return 2416584377u; }
    virtual uint32_t get_mix_million_result() { return 2377132217u; }
    void setUp()
    {
        rng = factory((uint32_t)time(NULL));
    }
    void tearDown()
    {
        delete rng;
    }
    void testSeeds()
    {
        SimpleRandomSeeder      seed_rng(0);
        SimpleRandomWrapper *   array_seed_rng;
        SimpleRandomWrapper *   param_seed_rng;
        uint32_t                seeds[1000];

        for (size_t i = 0; i < rng->num_seeds(); i++)
        {
            seeds[i] = seed_rng();
        }
        array_seed_rng = factory(seeds, rng->num_seeds(), false);
        param_seed_rng = factory(0);
        TS_ASSERT_EQUALS((*array_seed_rng)(), (*param_seed_rng)());
        delete array_seed_rng;
        delete param_seed_rng;
    }
    void testMillion()
    {
        SimpleRandomWrapper * million_rng;
        uint32_t result;

        million_rng = factory();
        for (uint32_t i = 0; i < 1000000; i++)
        {
            result = (*million_rng)();
        }
        TS_ASSERT_EQUALS(result, get_million_result());
        delete million_rng;
    }
    void testDiscardMillion()
    {
        SimpleRandomWrapper * discard_rng;
        uint32_t result_discard;

        discard_rng = factory();
        discard_rng->discard(999999);
        result_discard = (*discard_rng)();
        TS_ASSERT_EQUALS(result_discard, get_million_result());
        delete discard_rng;
    }
    void testMixMillion()
    {
        uint32_t zero_seeds[32] = { 0 };
        SimpleRandomWrapper * rng;

        rng = factory(zero_seeds, 32, false);
        for (uint32_t i = 0; i < 1000000u; ++i)
        {
            rng->mix(&i, 1);
        }
        TS_ASSERT_EQUALS((*rng)(), get_mix_million_result());
    }
    void testDiscard()
    {
        SimpleRandomWrapper * discard_rng;
        SimpleRandomWrapper * next_rng;
        uint32_t result_discard;
        uint32_t result_next;

        CxxTest::setAbortTestOnFail(true);
        next_rng = factory();
        for (uint32_t i = 1; i < 10001; i++)
        {
            result_next = (*next_rng)();
            discard_rng = factory();
            discard_rng->discard(i - 1);
            result_discard = (*discard_rng)();
            TS_ASSERT_EQUALS(result_discard, result_next);
            if (result_discard != result_next)
            {
                std::ostringstream out_temp;
                out_temp << "failed at i = " << i;
                TS_TRACE(out_temp.str().c_str());
                break;
            }
            delete discard_rng;
        }
        delete next_rng;
    }
};

class SimplerandomSHR3Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperSHR3(seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperSHR3(3360276411u);
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperSHR3(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 1153302609u; }
    uint32_t get_mix_million_result() { return 2497398786u; }
};

class SimplerandomMWC1Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperMWC1(seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperMWC1(2374144069u, 1046675282u);
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperMWC1(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 904977562u; }
    uint32_t get_mix_million_result() { return 850045851u; }
};

class SimplerandomMWC2Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperMWC2(seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperMWC2();
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperMWC2(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 767834450u; }
    uint32_t get_mix_million_result() { return 2513067739u; }
};

class SimplerandomKISSTest : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperKISS(seed_rng(), seed_rng(), seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperKISS(2247183469, 99545079, 3269400377, 3950144837);
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperKISS(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 2100752872u; }
    uint32_t get_mix_million_result() { return 3522308965u; }
};

#ifdef UINT64_C

class SimplerandomMWC64Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperMWC64(seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperMWC64();
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperMWC64(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 2191957470u; }
    uint32_t get_mix_million_result() { return 3125681944u; }
};

class SimplerandomKISS2Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperKISS2(seed_rng(), seed_rng(), seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperKISS2();
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperKISS2(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 4044786495u; }
    uint32_t get_mix_million_result() { return 73179452u; }
};

#endif

class SimplerandomLFSR113Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperLFSR113(seed_rng(), seed_rng(), seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperLFSR113();
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperLFSR113(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 300959510u; }
    uint32_t get_mix_million_result() { return 1565144389u; }
};

class SimplerandomLFSR88Test : public SimplerandomCongTest
{
public:
    SimpleRandomWrapper * factory(uint32_t single_seed)
    {
        SimpleRandomSeeder  seed_rng;
        return new SimpleRandomWrapperLFSR88(seed_rng(), seed_rng(), seed_rng());
    }
    SimpleRandomWrapper * factory()
    {
        return new SimpleRandomWrapperLFSR88();
    }
    virtual SimpleRandomWrapper * factory(const uint32_t * p_seeds, size_t num_seeds, bool mix_extras=false)
    {
        return new SimpleRandomWrapperLFSR88(p_seeds, num_seeds, mix_extras);
    }
    uint32_t get_million_result() { return 3774296834u; }
    uint32_t get_mix_million_result() { return 284026550u; }
};
