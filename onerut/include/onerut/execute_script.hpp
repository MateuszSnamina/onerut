#ifndef ONERUT_EXECUTE_SCRIPT_HPP
#define ONERUT_EXECUTE_SCRIPT_HPP

#include<string>

void
execute_imperative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines);

void
execute_declarative_script(
        const std::vector<std::shared_ptr<const std::string>>&lines,
        unsigned n_max_iterations);

#endif

