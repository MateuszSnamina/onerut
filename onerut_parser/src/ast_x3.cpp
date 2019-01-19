#include<onerut_parser/ast_x3.hpp>

namespace onerut_parser::onerut_ast::x3 {

    struct to_string_visitor {
        typedef std::wstring result_type;
        template<typename T>
        result_type operator()(const T & i) const;
    };

    template<typename T>
    to_string_visitor::result_type to_string_visitor::operator()(const T & i) const {
        return to_wstring(i);
    }

    std::wstring to_wstring(const IdentifierInfo& i) {
        //boost::algorithm::join(other_chars, std::string(""))
        std::wstring result(1, i.first_char);
        for (unsigned idx = 0; idx < i.other_chars.size(); idx++) {
            result += std::wstring(1, i.other_chars[idx]);
        }
        // POPRAWIC IMPLEMENTACJE!!
        return result;
    }

    std::wstring to_wstring(const LitIntInfo& i) {
        return std::to_wstring(i.value);
    }

    std::wstring to_wstring(const LitDoubleInfo& i) {
        return std::to_wstring(i.value);
    }

    std::wstring to_wstring(const FunctionInfo& i) {
        std::wstring result;
        result += to_wstring(i.name);
        result += L"[";
        for (const ExpressionInfo& temp : i.argv) {
            result += to_wstring(temp);
            result += L",";
        }
        result += L"]";
        return result;
    }

    std::wstring to_wstring(const ExpressionInfo& i) {
        return boost::apply_visitor(to_string_visitor(), i);
    }

    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------
    // -------------------------------------------------------------------------

    struct to_string_chart_visitor {
        typedef void result_type;
        to_string_chart_visitor(
                const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
                unsigned deepness,
                std::vector<std::wstring>& chart
                );
        const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions;
        unsigned deepness;
        std::vector<std::wstring>& chart;
        template<typename T>
        result_type operator()(const T & i);
    };

    to_string_chart_visitor::to_string_chart_visitor(
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart
            ) :
    positions(positions),
    deepness(deepness),
    chart(chart) {
    }

    template<typename T>
    to_string_chart_visitor::result_type to_string_chart_visitor::operator()(const T & i) {
        to_wstring_chart(i, positions, deepness, chart);
    }

    // -------------------------------------------------------------------------

    void to_wstring_chart(
            const ExpressionInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart) {
        auto visitor = to_string_chart_visitor(
                positions,
                deepness,
                chart);
        return boost::apply_visitor(visitor, i);
    }

    const wchar_t chart_fill_character = L'0x00002022' ; //L'\x03B1';//L'0x2022';//▒░'; //▓
    
    void to_wstring_chart(
            const IdentifierInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart) {
        while (chart.size() <= deepness) 
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character);
        const unsigned offset = positions.position_of(i).begin() - positions.first();
        std::copy(positions.position_of(i).begin(), positions.position_of(i).end(), chart[deepness].begin() + offset);
    }
    
    void to_wstring_chart(
            const LitIntInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart) {
        while (chart.size() <= deepness) 
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character);
        const unsigned offset = positions.position_of(i).begin() - positions.first();
        std::copy(positions.position_of(i).begin(), positions.position_of(i).end(), chart[deepness].begin() + offset);
    }

    void to_wstring_chart(
            const LitDoubleInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart) {
        while (chart.size() <= deepness) 
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character);
        const unsigned offset = positions.position_of(i).begin() - positions.first();
        std::copy(positions.position_of(i).begin(), positions.position_of(i).end(), chart[deepness].begin() + offset);
    }

    void to_wstring_chart(
            const FunctionInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions,
            unsigned deepness,
            std::vector<std::wstring>& chart) {
        while (chart.size() <= deepness) 
            chart.emplace_back(positions.last() - positions.first(), chart_fill_character);
        const unsigned offset = positions.position_of(i).begin() - positions.first();
        std::copy(positions.position_of(i).begin(), positions.position_of(i).end(), chart[deepness].begin() + offset);
        for (const ExpressionInfo& temp : i.argv) {
            to_wstring_chart(
                    temp,
                    positions,
                    deepness + 1,
                    chart);
        }
    }

    // publiczna funkcja:

    std::vector<std::wstring> to_wstring_chart(
            const ExpressionInfo& i,
            const boost::spirit::x3::position_cache<std::vector < std::wstring::const_iterator >>&positions) {
        std::vector<std::wstring> chart;
        to_string_chart_visitor visitor(
                positions,
                0,
                chart);
        boost::apply_visitor(visitor, i);
        return chart;
    }
}