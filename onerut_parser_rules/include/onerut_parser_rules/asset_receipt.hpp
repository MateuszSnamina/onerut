#ifndef ONERUT_PARSER_ASSET_RECEIPT
#define ONERUT_PARSER_ASSET_RECEIPT

#include<iostream>
#include<string>
#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_rules {

    void print_receipt(std::ostream& stream, const onerut_parser_exec::Asset& asset, std::string line_prefix);

}

#endif