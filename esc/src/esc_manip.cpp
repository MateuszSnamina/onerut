#include<cassert>

#include<esc/esc_manip.hpp>

namespace esc {
    //--------------------------------------------------------------------------

    std::string to_string(Color color) {
        switch (color) {
            case Color::Gray: return "Color::Gray (code 0)";
            case Color::Red: return "Color::Red (code 1)";
            case Color::Green: return "Color::Green (code 2)";
            case Color::Yellow: return "Color::Yellow (code 3)";
            case Color::Blue: return "Color::Blue (code 4)";
            case Color::Magenta: return "Color::Magenta (code 5)";
            case Color::Cyan: return "Color::Cyan (code 6)";
            case Color::White: return "Color::White (code 7)";
            case Color::Auto: return "Color::Auto (code 9)";
            default: return "InvalidColor (code" + std::to_string(static_cast<int> (color)) + ")";
        }
        assert(false);
        return "internal error";
    }
    //--------------------------------------------------------------------------

    EscDataBuilder::EscDataBuilder(const EscData& esc_data) :
    esc_data(esc_data) {
    }

    //--------------------------------------------------------------------------

    SinkBuilder::SinkBuilder(std::ostream& stream, const EscData& esc_data) :
    stream(stream),
    esc_data(esc_data) {
    }

    //--------------------------------------------------------------------------    

    EscStreamRaii::EscStreamRaii(std::ostream& stream, const EscData& esc_data) :
    stream(stream),
    esc_data(esc_data),
    _is_session_holder(false) {
    }

    EscStreamRaii::EscStreamRaii(EscStreamRaii&& raii) :
    stream(raii.stream),
    esc_data(raii.esc_data),
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

    std::string EscStreamRaii::compile() {
        // fg_color -- preparations:
        const int fg_color_value = 30 + static_cast<int> (esc_data.fg_color);
        assert(30 <= fg_color_value);
        assert(fg_color_value <= 39);
        assert(fg_color_value != 38);
        const std::string fg_color_str = std::to_string(fg_color_value);
        // bg_color -- preparations:
        const int bg_color_value = 40 + static_cast<int> (esc_data.bg_color);
        assert(40 <= bg_color_value);
        assert(bg_color_value <= 49);
        assert(bg_color_value != 48);
        const std::string bg_color_str = std::to_string(bg_color_value);
        // result:
        std::string result = fg_color_str + ";" + bg_color_str;
        if (esc_data.bold) result += ";1";
        if (esc_data.italic) result += ";3";
        if (esc_data.underline) result += ";4";
        return "\033[" + result + "m";
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

    bool EscStreamRaii::is_session_holder() const {
        return _is_session_holder;
    }

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR CLASSES  --------------------------------
    //--------------------------------------------------------------------------

    void EscFgColorManip::apply(EscData& d) const {
        d.fg_color = color;
    }

    void EscBgColorManip::apply(EscData& d) const {
        d.bg_color = color;
    }

    void EscBoldManip::apply(EscData& d) const {
        d.bold = value;
    }

    void EscItalicManip::apply(EscData& d) const {
        d.italic = value;
    }

    void EscUnderlineManip::apply(EscData& d) const {
        d.underline = value;
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

        const BuildEscDataManip build_esc_data;
        const EscResetManip reset;

    }

}


