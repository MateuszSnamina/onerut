#include<cassert>
#include<algorithm>
#include<sstream>
#include<iomanip>

#include<string_utils/greek_support.hpp>
#include<string_utils/unicode_support.hpp>

#include<onerut_normal_operator/to_mat.hpp>
#include<onerut_normal_operator/to_string.hpp>

namespace fancy_logging {

    // -------------------------------------------------------------------------

    template<typename T>
    struct ToStringSize;

    // -------------------------------------------------------------------------

    template<>
    struct ToStringSize<std::string> {
        ToStringSize(std::ostream& stream);
        unsigned size(const std::string& s) const;
    };

    inline
    ToStringSize<std::string>::ToStringSize(std::ostream&) {
    }

    inline
    unsigned ToStringSize<std::string>::size(const std::string& s) const {
        return string_utils::to_greek_number_of_visible_characters_in_result(s);
    }

    // -------------------------------------------------------------------------

    template<>
    struct ToStringSize<double> {
        ToStringSize(std::ostream& stream);
        unsigned size(double d) const;
        std::ostream& stream;
    };

    inline
    ToStringSize<double>::ToStringSize(std::ostream& stream) :
    stream(stream) {
    }

    inline
    unsigned ToStringSize<double>::size(double d) const {
        std::ostringstream sstream;
        sstream.flags(stream.flags());
        sstream.precision(stream.precision());
        sstream << d;
        return sstream.str().size();
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------    

    template<class T>
    struct StringLengthComparator {
        StringLengthComparator(std::ostream& stream);
        bool compare(const T& lhs, const T& rhs);
        const ToStringSize<T> to_string_size;
    };

    template<class T>
    StringLengthComparator<T>::StringLengthComparator(std::ostream& stream) :
    to_string_size(stream) {
    }

    template<class T>
    bool StringLengthComparator<T>::compare(const T& lhs, const T& rhs) {
        return to_string_size.size(lhs) < to_string_size.size(rhs);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------    

    void
    log(std::ostream& stream,
            const std::vector<std::string>& row_labels,
            const std::vector<std::string>& col_labels,
            arma::mat matrix,
            std::string line_prefix = "") {//TODO remove def value in cpp when go to header
        // ---------------------------------------------------------------------
        assert(row_labels.size() == matrix.n_rows);
        assert(col_labels.size() == matrix.n_cols);
        // ---------------------------------------------------------------------
        StringLengthComparator<std::string> string_length_cmparator_s(stream);
        const auto comparator_s = [&string_length_cmparator_s](const std::string& lhs, const std::string & rhs) {
            return string_length_cmparator_s.compare(lhs, rhs);
        };
        StringLengthComparator<double> string_length_cmparator_d(stream);
        const auto comparator_d = [&string_length_cmparator_d](double lhs, double rhs) {
            return string_length_cmparator_d.compare(lhs, rhs);
        };
        // ---------------------------------------------------------------------        
        const auto longest_row_label = std::max_element(row_labels.begin(), row_labels.end(), comparator_s);
        const auto longest_col_label = std::max_element(col_labels.begin(), col_labels.end(), comparator_s);
        const auto longest_entry = std::max_element(matrix.begin(), matrix.end(), comparator_d);
        const unsigned row_label_visible_length = ToStringSize<std::string>(stream).size(*longest_row_label);
        const unsigned col_label_visible_length = ToStringSize<std::string>(stream).size(*longest_col_label);
        const unsigned entry_visible_length = ToStringSize<double>(stream).size(*longest_entry);
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
                stream << std::setw(adequate_reguler_visible_length) << matrix(i, j);
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
        // ---------------
    }

}


namespace onerut_normal_operator {

    std::string to_string(const AbstractOperator& op) {
        std::ostringstream sstream;
        sstream << std::fixed;
        sstream << std::setprecision(3);
        //sstream << std::setw(30);
        const arma::mat matrix = to_mat(op);
        fancy_logging::log(sstream, op.get_domain()->state_names, op.get_domain()->state_names, matrix, "[receipt] ");
        return sstream.str();
    }

}
