#ifndef LOG_UTILS_FANCY_LOG_MAT
#define LOG_UTILS_FANCY_LOG_MAT

#include<iostream>
#include<vector>
#include<string>
#include<armadillo>

namespace fancy_logging {

    void log(std::ostream& stream,
            const std::vector<std::string>& row_labels,
            const std::vector<std::string>& col_labels,
            arma::mat matrix,
            std::string line_prefix = "");

    void log(std::ostream& stream,
            const std::vector<std::string>& row_labels,
            const std::vector<std::string>& col_labels,
            arma::mat matrix,
            unsigned chunk_size,
            std::string line_prefix = "");
    
}

#endif