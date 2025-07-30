#include "ReedSolomon.hpp"
#include "rs_base"
#include <cstdint>
#include <limits>
namespace ReedSolomonFEC {
enum class SupportedBitsPerSymbol {
    _2 = 2,
    _3 = 3,
    _4 = 4,
    _5 = 5,
    _6 = 6,
    _7 = 7,
    _8 = 8,
    _9 = 9,
    _10 = 10,
    _11 = 11,
    _12 = 12,
    _13 = 13,
    _14 = 14,
    _15 = 15,
    _16 = 16
};

template <typename DataType, SupportedBitsPerSymbol BitsPerSymbol, int NumDataSymbols, int Poly> 
using ReedSolomon__ = ezpwd::reed_solomon<
    DataType,
    static_cast<size_t>(BitsPerSymbol),
    ((1ul << static_cast<int>(BitsPerSymbol)) - 1 - NumDataSymbols),
    1,
    1,
    ezpwd::gfpoly<static_cast<size_t>(BitsPerSymbol), Poly>>;

template <SupportedBitsPerSymbol BitsPerSymbol, int NumDataSymbols>
struct ReedSolomon_;

template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_2,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_2,  NumDataSymbols, 0x07>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_3,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_3,  NumDataSymbols, 0x0B>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_4,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_4,  NumDataSymbols, 0x13>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_5,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_5,  NumDataSymbols, 0x25>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_6,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_6,  NumDataSymbols, 0x43>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_7,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_7,  NumDataSymbols, 0x89>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_8,  NumDataSymbols> : public ReedSolomon__<uint8_t, SupportedBitsPerSymbol::_8,  NumDataSymbols, 0x011D>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_9,  NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_9,  NumDataSymbols, 0x0211>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_10, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_10, NumDataSymbols, 0x0409>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_11, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_11, NumDataSymbols, 0x0805>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_12, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_12, NumDataSymbols, 0x1053>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_13, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_13, NumDataSymbols, 0x201B>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_14, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_14, NumDataSymbols, 0x4443>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_15, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_15, NumDataSymbols, 0x8003>{};
template <int NumDataSymbols> struct ReedSolomon_<SupportedBitsPerSymbol::_16, NumDataSymbols> : public ReedSolomon__<uint16_t, SupportedBitsPerSymbol::_16, NumDataSymbols, 0x01110B>{};

template <SupportedBitsPerSymbol BitsPerSymbol> 
std::unique_ptr<ezpwd::reed_solomon_base> create_ReedSolomon(RSConfigurationErrorRate error_rate){
    switch (error_rate){
        /* If 10% of symbols are bad per block */
        case RSConfigurationErrorRate::BadSymbolRate10: {
            return std::unique_ptr<ezpwd::reed_solomon_base>(new ReedSolomon_<
                BitsPerSymbol, 
                static_cast<int>(((1ul << static_cast<int>(BitsPerSymbol)) * 0.8))
                >
            );
        }
        /* If 20% of symbols are bad per block */
        case RSConfigurationErrorRate::BadSymbolRate20:{
            return std::unique_ptr<ezpwd::reed_solomon_base>(new ReedSolomon_<
                BitsPerSymbol, 
                static_cast<int>(((1ul << static_cast<int>(BitsPerSymbol)) * 0.6))
                >
            );
        }
        /* If 30% of symbols are bad per block */
        case RSConfigurationErrorRate::BadSymbolRate30:{
            return std::unique_ptr<ezpwd::reed_solomon_base>(new ReedSolomon_<
                BitsPerSymbol, 
                static_cast<int>(((1ul << static_cast<int>(BitsPerSymbol)) * 0.4))
                >
            );
        }
    }
    __builtin_unreachable();
}

ReedSolomon::ReedSolomon(RSConfigurationBPS bits_per_symbol, RSConfigurationErrorRate error_rate) {
    switch (bits_per_symbol){
        case (RSConfigurationBPS::_8BitsPerSymbol):{
            rs = create_ReedSolomon<SupportedBitsPerSymbol::_8>(error_rate);
            break;
        }
        /* Not working */

        #if USE_RS_ABOVE_8
        case (RSConfigurationBPS::_10BitsPerSymbol):{
            rs = create_ReedSolomon<SupportedBitsPerSymbol::_10>(error_rate);
            break;
        }
        case (RSConfigurationBPS::_12BitsPerSymbol):{
            rs = create_ReedSolomon<SupportedBitsPerSymbol::_12>(error_rate);
            break;
        }
        #endif
    }
}

ReedSolomon::~ReedSolomon(){
    
}

int ReedSolomon::encode(std::string& data){
    return rs->encode(data);
}

int ReedSolomon::encode(std::vector<uint8_t>& data){
    return rs->encode(data);
}

int ReedSolomon::encode(std::vector<uint16_t>& data){
    return rs->encode(data);
}

int ReedSolomon::decode(std::string& data){
    return rs->decode(data);
}

int ReedSolomon::decode(std::vector<uint8_t>& data){
    return rs->decode(data);
}

int ReedSolomon::decode(std::vector<uint16_t>& data){
    return rs->decode(data);
}

size_t ReedSolomon::load(){
    return rs->load();
}

size_t ReedSolomon::nroots(){
    return rs->nroots();
}
}
