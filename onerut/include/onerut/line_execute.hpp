#ifndef ONERUT_LINES_EXECUTE
#define ONERUT_LINES_EXECUTE

#include<memory>
#include<string>
#include<vector>

#include<onerut_parser_exec/ast_asset.hpp>

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
execute_line(std::shared_ptr<const std::string> line);

std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>>
execute_script_lines(const std::vector<std::shared_ptr<const std::string>>&lines);

#endif