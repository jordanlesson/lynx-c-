#include <iostream>
#include <string>

class binascii
{
    public:
    static std::string b2a_hex( const std::string& input );
    static std::string hexlify( const std::string& input );
    static std::string a2b_hex( const std::string& input );
    static std::string unhexlify( const std::string& input );
};

std::string binascii::b2a_hex( const std::string& input )
{
    const static std::string HexCodes = "0123456789ABCDEF";
    std::string HexString;
    for ( int i = 0; i < input.length(); ++i )
    {
        unsigned char BinValue = input[i];
        // High half
        HexString += HexCodes[( BinValue >> 4 ) & 0x0F];
        HexString += HexCodes[BinValue & 0x0F];
    }
    return HexString;
}

std::string binascii::hexlify( const std::string& input )
{
    return b2a_hex( input );
}

std::string binascii::a2b_hex( const std::string& input )
{
    const static std::string HexCodes = "0123456789ABCDEF";
    std::string BinString;
        for ( int i = 0; i < input.length() - 1; i += 2 )
        {
        BinString += ( input[i] >= 'A' ? input[i] - 'A' + 10 : input[i] -
        '0' ) * 16 +
        ( input[i + 1] >= 'A' ? input[i + 1] - 'A' + 10 : input[i + 1] -
        '0' );
        }
    return BinString;
}

std::string binascii::unhexlify( const std::string& input )
{
    return a2b_hex( input );
}