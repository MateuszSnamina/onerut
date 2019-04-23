#ifndef ONERUT_LINES_PROCESSOR
#define ONERUT_LINES_PROCESSOR

#include<memory>
#include<string>
#include<vector>

#include<onerut_parser_exec/ast_asset.hpp>

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_line(std::shared_ptr<const std::string> line);

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_imperative_line(std::shared_ptr<const std::string> line);

std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>
process_deklarative_line(std::shared_ptr<const std::string> line);

std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>>
process_imperative_lines(const std::vector<std::shared_ptr<const std::string>>&lines);

std::vector<std::shared_ptr<onerut_parser_exec::onerut_ast::asset::AssetNode>>
process_declarative_lines(const std::vector<std::shared_ptr<const std::string>>&lines);

#endif