#ifndef ONERUT_PARSER_ASSET_RECEIPT
#define ONERUT_PARSER_ASSET_RECEIPT

#include<iostream>
#include<string>
#include<onerut_parser/asset.hpp>

namespace onerut_parser {

    void print_receipt(std::ostream& stream, const Asset& asset, std::string line_prefix);

}

#endif