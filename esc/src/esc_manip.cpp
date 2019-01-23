#include<cassert>
#include<vector>
#include<boost/algorithm/string/join.hpp>

#include<esc/esc_manip.hpp>

namespace esc {

    EscStreamRaii::EscStreamRaii(std::ostream& stream) :
    stream(stream),
    ansi_data({Color::Auto, Color::Auto, false, false, false}),
    _is_session_holder(false) {
    }

    EscStreamRaii::EscStreamRaii(EscStreamRaii& raii) :
    stream(raii.stream),
    ansi_data(raii.ansi_data),
    _is_session_holder(false) {
        if (raii._is_session_holder) {
            _is_session_holder = true;
            raii._is_session_holder = false;
        }
    }

    EscStreamRaii::~EscStreamRaii() {
        if (_is_session_holder)
            end_session();
    }

    void EscStreamRaii::set_fg_color(Color color) {
        ansi_data.fg_color = color;
    }

    void EscStreamRaii::set_bg_color(Color color) {
        ansi_data.bg_color = color;
    }

    void EscStreamRaii::set_bold(bool value) {
        ansi_data.bold = value;
    }

    void EscStreamRaii::set_italic(bool value) {
        ansi_data.italic = value;
    }

    void EscStreamRaii::set_underline(bool value) {
        ansi_data.underline = value;
    }

    std::string EscStreamRaii::compile() {
        std::string result = "\033[";
        const int fg_color_value = 30 + static_cast<int> (ansi_data.fg_color);
        const int bg_color_value = 40 + static_cast<int> (ansi_data.bg_color);
        assert(30 <= fg_color_value);
        assert(fg_color_value <= 39);
        assert(40 <= bg_color_value);
        assert(bg_color_value <= 49);
        const std::string fg_color_str = std::to_string(fg_color_value);
        const std::string bg_color_str = std::to_string(bg_color_value);
        std::vector<std::string> bits{fg_color_str, bg_color_str};
        if (ansi_data.bold) bits.push_back("1");
        if (ansi_data.italic) bits.push_back("3");
        if (ansi_data.underline) bits.push_back("4");
        result += boost::algorithm::join(bits, ";");
        result += "m";
        return result;
    }

    bool EscStreamRaii::is_session_holder() const {
        return _is_session_holder;
    }

    void EscStreamRaii::start_session() {
        assert(!_is_session_holder);
        _is_session_holder = true;
        stream << compile();
    }

    void EscStreamRaii::end_session() {
        assert(_is_session_holder);
        stream << "\033[0m";
        _is_session_holder = false;
    }

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR CLASSES  --------------------------------
    //--------------------------------------------------------------------------

    //EscFgColorManip::EscFgColorManip(Color color) :
    //color(color) {
    // }

    //EscBgColorManip::EscBgColorManip(Color color) :
    //color(color) {
    //}

    //--------------------------------------------------------------------------
    //-------------------  STREAM LIKE API  ------------------------------------
    //--------------------------------------------------------------------------

    EscStreamRaii operator<<(std::ostream& stream, const EscFgColorManip& manip) {
        EscStreamRaii raii(stream);
        raii.set_fg_color(manip.color);
        return raii;
    }

    EscStreamRaii operator<<(std::ostream& stream, const EscBgColorManip& manip) {
        EscStreamRaii raii(stream);
        raii.set_bg_color(manip.color);
        return raii;
    }

    EscStreamRaii operator<<(std::ostream& stream, const EscBoldManip& manip) {
        EscStreamRaii raii(stream);
        raii.set_bold(manip.value);
        return raii;
    }

    EscStreamRaii operator<<(std::ostream& stream, const EscItalicManip& manip) {
        EscStreamRaii raii(stream);
        raii.set_italic(manip.value);
        return raii;

    }

    EscStreamRaii operator<<(std::ostream& stream, const EscUnderlineManip& manip) {
        EscStreamRaii raii(stream);
        raii.set_underline(manip.value);
        return raii;
    }

    EscStreamRaii operator<<(EscStreamRaii raii, const EscFgColorManip& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        raii.set_fg_color(manip.color);
        return raii;
    }

    EscStreamRaii operator<<(EscStreamRaii raii, const EscBgColorManip& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        raii.set_bg_color(manip.color);
        return raii;
    }

    EscStreamRaii operator<<(EscStreamRaii raii, const EscBoldManip& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        raii.set_bold(manip.value);
        return raii;
    }

    EscStreamRaii operator<<(EscStreamRaii raii, const EscItalicManip& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        raii.set_italic(manip.value);
        return raii;
    }

    EscStreamRaii operator<<(EscStreamRaii raii, const EscUnderlineManip& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        raii.set_underline(manip.value);
        return raii;
    }

    std::ostream& operator<<(EscStreamRaii raii, const EscResetManip&) {
        if (raii.is_session_holder())
            raii.end_session();
        return raii.stream;
    }

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATORS  ---------------------------------------
    //--------------------------------------------------------------------------

    namespace manip {

        const EscFgColorManip gray{Color::Gray};
        const EscFgColorManip red{Color::Red};
        const EscFgColorManip green{Color::Green};
        const EscFgColorManip yellow{Color::Yellow};
        const EscFgColorManip blue{Color::Blue};
        const EscFgColorManip magenta{Color::Magenta};
        const EscFgColorManip cyan{Color::Cyan};
        const EscFgColorManip white{Color::White};
        const EscFgColorManip color_default{Color::Auto};

        const EscBgColorManip bg_gray{Color::Gray};
        const EscBgColorManip bg_red{Color::Red};
        const EscBgColorManip bg_green{Color::Green};
        const EscBgColorManip bg_yellow{Color::Yellow};
        const EscBgColorManip bg_blue{Color::Blue};
        const EscBgColorManip bg_magenta{Color::Magenta};
        const EscBgColorManip bg_cyan{Color::Cyan};
        const EscBgColorManip bg_white{Color::White};
        const EscBgColorManip bg_color_default{Color::Auto};

        const EscBoldManip bold{true};
        const EscBoldManip nobold{false};

        const EscItalicManip italic{true};
        const EscItalicManip noitalic{false};

        const EscUnderlineManip underline{true};
        const EscUnderlineManip nounderline{false};

        const EscResetManip reset;

    }
}


