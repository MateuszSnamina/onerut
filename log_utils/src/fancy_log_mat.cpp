#include<cassert>
#include<iomanip>
#include<algorithm>

#include<esc/esc_manip.hpp>
#include<string_utils/greek_support.hpp>
#include<string_utils/unicode_support.hpp>
#include<log_utils/fancy_visible_size_comparator.hpp>
#include<log_utils/fancy_log_mat.hpp>

namespace fancy_logging {

    const esc::EscData value_esc_data(double value) {
        if (value == 0) {
            return esc::EscDataBuilder() << esc::manip::gray << esc::manip::build_esc_data;
        }
        return esc::EscDataBuilder() << esc::manip::build_esc_data;
    }

    void
    log(std::ostream& stream,
            const std::vector<std::string>& row_labels,
            const std::vector<std::string>& col_labels,
            arma::mat matrix,
            std::string line_prefix) {
        // ---------------------------------------------------------------------
        assert(row_labels.size() == matrix.n_rows);
        assert(col_labels.size() == matrix.n_cols);
        // ---------------------------------------------------------------------
        VisibleLengthComparator<std::string> string_length_cmparator_s(stream);
        const auto comparator_s = [&string_length_cmparator_s](const std::string& lhs, const std::string & rhs) {
            return string_length_cmparator_s.compare(lhs, rhs);
        };
        VisibleLengthComparator<double> string_length_cmparator_d(stream);
        const auto comparator_d = [&string_length_cmparator_d](double lhs, double rhs) {
            return string_length_cmparator_d.compare(lhs, rhs);
        };
        // ---------------------------------------------------------------------        
        const auto longest_row_label = std::max_element(row_labels.begin(), row_labels.end(), comparator_s);
        const auto longest_col_label = std::max_element(col_labels.begin(), col_labels.end(), comparator_s);
        const auto longest_entry = std::max_element(matrix.begin(), matrix.end(), comparator_d);
        const unsigned row_label_visible_length = ToVisibleSize<std::string>(stream).size(*longest_row_label);
        const unsigned col_label_visible_length = ToVisibleSize<std::string>(stream).size(*longest_col_label);
        const unsigned entry_visible_length = ToVisibleSize<double>(stream).size(*longest_entry);
        const unsigned stream_visible_length = static_cast<unsigned> (stream.width(0));
        const unsigned adequate_row_label_visible_length = std::max({row_label_visible_length, stream_visible_length});
        const unsigned adequate_reguler_visible_length = std::max({col_label_visible_length, entry_visible_length, stream_visible_length});
        // ---------------------------------------------------------------------
        const std::u32string horizontal_row_label_bar_segment(adequate_row_label_visible_length, U'─');
        const std::u32string horizontal_regular_bar_segment(adequate_reguler_visible_length, U'─');
        // ---------------------------------------------------------------------
        stream << line_prefix;
        stream << " ";
        stream << std::setw(adequate_row_label_visible_length) << "";
        stream << "┌";
        for (unsigned j = 0; j < matrix.n_cols; ++j) {
            stream << string_utils::unicode_to_utf8(horizontal_regular_bar_segment);
            stream << (j != matrix.n_cols - 1 ? "┬" : "┐");
        }
        stream << std::endl;
        // ---------------------------------------------------------------------
        stream << line_prefix;
        stream << " ";
        stream << std::setw(adequate_row_label_visible_length) << "";
        stream << "│";
        for (unsigned j = 0; j < matrix.n_cols; ++j) {
            stream << std::setw(adequate_reguler_visible_length) << string_utils::StreamToGreek(col_labels[j]);
            stream << "│";
        }
        stream << std::endl;
        // ---------------------------------------------------------------------
        stream << line_prefix;
        stream << "┌";
        stream << string_utils::unicode_to_utf8(horizontal_row_label_bar_segment);
        stream << "┼";
        for (unsigned j = 0; j < matrix.n_cols; ++j) {
            stream << string_utils::unicode_to_utf8(horizontal_regular_bar_segment);
            stream << (j != matrix.n_cols - 1 ? "┼" : "┤");
        }
        stream << std::endl;
        // ---------------------------------------------------------------------
        for (unsigned i = 0; i < matrix.n_rows; ++i) {
            stream << line_prefix;
            stream << "│";
            stream << std::setw(adequate_row_label_visible_length) << string_utils::StreamToGreek(row_labels[i]);
            stream << "│";
            for (unsigned j = 0; j < matrix.n_cols; ++j) {
                const auto esc_data = value_esc_data(matrix(i, j));
                stream << esc_data << std::setw(adequate_reguler_visible_length) << matrix(i, j) << esc::manip::reset;
                stream << "│";
            }
            stream << std::endl;
        }
        // ---------------------------------------------------------------------
        stream << line_prefix;
        stream << "└";
        stream << string_utils::unicode_to_utf8(horizontal_row_label_bar_segment);
        stream << "┴";
        for (unsigned j = 0; j < matrix.n_cols; ++j) {
            stream << string_utils::unicode_to_utf8(horizontal_regular_bar_segment);
            stream << (j != matrix.n_cols - 1 ? "┴" : "┘");
        }
        stream << std::endl;
        // ---------------------------------------------------------------------
    }

}
