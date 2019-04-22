#include<cctype>
#include<algorithm>
#include<iterator>

#include<onerut/line_preprocess.hpp>

std::string
preprocess_line(const std::string& line) {
    auto it = std::find_if(line.cbegin(), line.cend(),
            [](char ch) {
                return ch == '#';
            });
    it = std::find_if(std::make_reverse_iterator(it), line.crend(),
            [](char ch) {
                return !std::isspace(ch);
            }).base();
    return{line.begin(), it};
}

std::vector<std::shared_ptr<const std::string>>
preprocess_line(const std::vector<std::shared_ptr<const std::string>>& lines) {
    // ------------------
    std::vector<std::shared_ptr <const std::string> > result;
    std::transform(cbegin(lines), cend(lines), std::back_inserter(result),
            [](const std::shared_ptr<const std::string> &line) {
                return std::make_shared<std::string>(preprocess_line(*line));
            });
    // ------------------
    std::vector<std::shared_ptr <const std::string> > result_filtered;
    std::copy_if(cbegin(result), cend(result), std::back_inserter(result_filtered),
            [](const std::shared_ptr<const std::string> &line) {
                return !line->empty();
            });
    // ------------------
    return result_filtered;
}