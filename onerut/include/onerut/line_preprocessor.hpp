#ifndef ONERUT_LINE_PREPROCESSOR
#define ONERUT_LINE_PREPROCESSOR

#include<memory>
#include<string>
#include<vector>

#include<onerut_parser_exec/ast_asset.hpp>

std::string
preprocess_line(const std::string& line);

std::vector<std::shared_ptr<const std::string>>
preprocess_line(const std::vector<std::shared_ptr<const std::string>>& lines);


#endif
