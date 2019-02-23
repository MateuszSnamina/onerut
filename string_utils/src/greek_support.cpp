#include<cassert>
#include<cctype>
#include<iomanip>
#include<utility>
#include<vector>

#include<string_utils/greek_support.hpp>

namespace {

    struct GreekLatinPair {
        std::string greek;
        std::string latin;
    };

    const std::vector<GreekLatinPair> greek_latin{
        {"α", "alpha"},
        {"β", "beta"},
        {"γ", "gamma"},
        {"Γ", "Gamma"},
        {"δ", "delta"},
        {"Δ", "Delta"},
        {"ε", "epsilon"},
        {"ζ", "zeta"},
        {"η", "eta"},
        {"θ", "theta"},
        {"Θ", "Theta"},
        {"ι", "iota"},
        {"κ", "kappa"},
        {"λ", "lambda"},
        {"Λ", "Lambda"},
        {"μ", "mu"},
        {"ν", "nu"},
        {"ξ", "xi"},
        {"Ξ", "Xi"},
        {"ο", "omicron"},
        {"π", "pi"},
        {"Π", "Pi"},
        {"ρ", "rho"},
        //{"ς", "final_sigma"},
        {"σ", "sigma"},
        {"Σ", "Sigma"},
        {"τ", "tau"},
        {"υ", "upsilon"},
        {"φ", "phi"},
        {"Φ", "Phi"},
        {"χ", "xi"},
        {"ψ", "psi"},
        {"Ψ", "Psi"},
        {"ω", "omega"},
        {"Ω", "Omega"},
        {"⇑", "up"},
        {"⇓", "down"},
        {"⇐", "left"},
        {"⇒", "right"},
        {"⇖", "upLeft"},
        {"⇗", "upRight"},
        {"⇘", "downRight"},
        {"⇙", "downLeft"},
        {"⇕", "upDown"},
        {"⇔", "leftRight"},
        {"⇍", "notLeft"},
        {"⇏", "notRight"},
        {"⇌", "resonance"},
        {"⬆", "up2"},
        {"⬇", "down2"},
        {"⍐", "boxUp"},
        {"⍗", "boxDown"},
        {"⍓", "boxUp2"},
        {"⍌", "boxDown2"}};

    void _to_greek(
            std::string& str,
            const std::string& greek, const std::string& latin) {
        const std::size_t latin_len = latin.size();
        const std::size_t greek_len = greek.size();
        std::size_t pos = 0;
        while ((pos = str.find(latin, pos)) != std::string::npos) {
            const std::size_t pos_after = pos + latin_len;
            const bool before_letter_test = (pos == 0) || !isalpha(str[pos - 1]);
            const bool after_letter_test = (pos_after == str.size()) || !isalpha(str[pos_after]);
            if (before_letter_test && after_letter_test) {
                str.replace(pos, latin_len, greek);
                pos += greek_len;
            } else {
                pos += latin_len;
            }
        }
    }

    int _to_greek_delta_in_number_of_visible_characters(
            std::string_view str_view,
            const std::string& greek, const std::string& latin) {
        int result = 0;
        const std::size_t latin_len = latin.size();
        const std::size_t greek_len = greek.size();
        std::size_t pos = 0;
        while ((pos = str_view.find(latin, pos)) != std::string::npos) {
            const std::size_t pos_after = pos + latin_len;
            const bool before_letter_test = (pos == 0) || !isalpha(str_view[pos - 1]);
            const bool after_letter_test = (pos_after == str_view.size()) || !isalpha(str_view[pos_after]);
            if (before_letter_test && after_letter_test) {
                result += 1 - latin_len;
                pos += greek_len;
            } else {
                pos += latin_len;
            }
        }
        return result;
    }

}

namespace string_utils {

    std::string to_greek(std::string str) {
        for (const auto & greek_latin_pair : greek_latin) {
            const std::string& greek = greek_latin_pair.greek;
            const std::string& latin = greek_latin_pair.latin;
            _to_greek(str, greek, latin);
        }
        return str;
    }

    std::string to_greek(std::string_view str_view) {
        std::string str{str_view};
        return to_greek(str);
    }

    int to_greek_delta_in_number_of_visible_characters(
            std::string_view str_view) {
        int result = 0;
        for (const auto & greek_latin_pair : greek_latin) {
            const std::string& greek = greek_latin_pair.greek;
            const std::string& latin = greek_latin_pair.latin;
            result += _to_greek_delta_in_number_of_visible_characters(str_view, greek, latin);
        }
        return result;
    }

    unsigned to_greek_number_of_visible_characters_in_result(
            std::string_view str_view) {
        const unsigned basic_length = str_view.size();
        const int delta_length = string_utils::to_greek_delta_in_number_of_visible_characters(str_view);
        assert(static_cast<int> (basic_length) + delta_length >= 0);
        const unsigned length = static_cast<unsigned> (static_cast<int> (basic_length) + delta_length);
        return length;
    }

    // ------------------------

    StreamToGreek::StreamToGreek(const std::string_view& not_translated) :
    not_translated(not_translated) {
    }

    std::ostream& operator<<(std::ostream& stream, const StreamToGreek& t) {
        const unsigned visible_length = stream.width(0);
        const std::string translated = string_utils::to_greek(t.not_translated);
        const unsigned number_of_visible_characters = string_utils::to_greek_number_of_visible_characters_in_result(t.not_translated);
        const unsigned number_of_bytes = translated.size();
        assert(number_of_bytes >= number_of_visible_characters);
        const unsigned width_bytes = visible_length + (number_of_bytes - number_of_visible_characters);
        stream << std::setw(width_bytes) << translated;
        return stream;
    }

}
