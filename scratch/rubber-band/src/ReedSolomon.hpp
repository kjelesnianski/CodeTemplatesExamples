#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

/* Forward declare reed_solomon_base*/
namespace ezpwd {
class reed_solomon_base;
}

namespace ReedSolomonFEC {
/* Create enums for different supports configurations*/
enum class RSConfigurationBPS {
    _8BitsPerSymbol,
    #if USE_RS_ABOVE_8
    _10BitsPerSymbol,
    _12BitsPerSymbol
    #endif
};

enum class RSConfigurationErrorRate {
    BadSymbolRate10,
    BadSymbolRate20,
    BadSymbolRate30
};

class ReedSolomon{
    std::unique_ptr<ezpwd::reed_solomon_base> rs;
public:
    ReedSolomon(RSConfigurationBPS bits_per_symbol, RSConfigurationErrorRate error_rate);
    ~ReedSolomon();

    /**
     * @brief Encode data, and append parity to data
     * 
     * @return int
     */
    int encode(std::string&);

    /**
     * @brief Encode data, and append parity to data
     * 
     * @return int
     */
    int encode(std::vector<uint8_t>&);

    /**
     * @brief Encode data, and append parity to data
     * 
     * @return int
     */
    int encode(std::vector<uint16_t>&);

    /**
     * @brief Decode data, with bit flip error correction
     * 
     * @return int Number of symbols corrected
     */
    int decode(std::string&);

    /**
     * @brief Decode data, with bit flip error correction
     * 
     * @return int Number of symbols corrected
     */
    int decode(std::vector<uint8_t>&);

    /**
     * @brief Decode data, with bit flip error correction
     * 
     * @return int Number of symbols corrected
     */
    int decode(std::vector<uint16_t>&);

    /**
     * @brief Get the size of the ReedSolomon payload
     * 
     * @return size_t 
     */
    size_t load();

    /**
     * @brief Get the number of error symbols appended to the end of a block of data
     * 
     * @return size_t 
     */
    size_t nroots();
};
}