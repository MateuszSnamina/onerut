#ifndef ESC_ESC_MANIP
#define ESC_ESC_MANIP

#include<cassert>//////
#include<iostream>
#include<string>

namespace esc::ansi_codes {

    extern const std::string ColorGray;
    extern const std::string ColorRed;
    extern const std::string ColorGreen;
    extern const std::string ColorYellow;
    extern const std::string ColorBlue;
    extern const std::string ColorMagenta;
    extern const std::string ColorCyan;
    extern const std::string ColorWhite;

    extern const std::string BgColorGray;
    extern const std::string BgColorRed;
    extern const std::string BgColorGreen;
    extern const std::string BgColorYellow;
    extern const std::string BgColorBlue;
    extern const std::string BgColorMagenta;
    extern const std::string BgColorCyan;
    extern const std::string BgColorWhite;

    extern const std::string ColorEnd;
}

enum class Color {
    Gray = 0,
    Red = 1,
    Green = 2,
    Yellow = 3,
    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7,
    Auto = 9 // o reset colors to their defaults, use ESC[39;49m --> Wiki.
};


//-------------------------------------------------------

class EscStreamRaii {
public:
    explicit EscStreamRaii(std::ostream& s);
    EscStreamRaii(EscStreamRaii& raii);
    ~EscStreamRaii();
    void set_fg_color(Color color);
    void set_bg_color(Color color);
    std::string compile();
    void start_session();
    void end_session();
    bool is_in_session() const;
    std::ostream& s;
private:
    Color fg_color;
    Color bg_color;
    bool in_session;
};

EscStreamRaii::EscStreamRaii(std::ostream& s) :
s(s),
fg_color(Color::Auto),
bg_color(Color::Auto),
in_session(false) {
}

EscStreamRaii::EscStreamRaii(EscStreamRaii& raii) :
s(raii.s),
fg_color(raii.fg_color),
bg_color(raii.bg_color) {
    if (raii.in_session) {
        in_session = true;
        raii.in_session = false;
    }
}

EscStreamRaii::~EscStreamRaii() {
    if (in_session)
        end_session();
}

void EscStreamRaii::set_fg_color(Color color) {
    fg_color = color;
}

void EscStreamRaii::set_bg_color(Color color) {
    bg_color = color;
}

std::string EscStreamRaii::compile() {
    std::string result = "\033[";
    //std::string result = "(BEGIN)\033[";
    const int value_fg_color = 30 + static_cast<int> (fg_color);
    const int value_bg_color = 40 + static_cast<int> (bg_color);
    //std::cout << value_fg_color << value_bg_color;
    assert(30 <= value_fg_color);
    assert(value_fg_color <= 39);
    assert(40 <= value_bg_color);
    assert(value_bg_color <= 49);
    // use join(values,';') in the future...        
    result += std::to_string(value_fg_color);
    result += ";";
    result += std::to_string(value_bg_color);
    result += "m";
    return result;
}

bool EscStreamRaii::is_in_session() const {
    return in_session;
}

void EscStreamRaii::start_session() {
    assert(!in_session);
    in_session = true;
    s << compile();
}

void EscStreamRaii::end_session() {
    assert(in_session);
    s << "\033[0m";
    //s << "(END)\033[0m";
    in_session = false;
}

//-------------------------------------------------------

class EscManipFgColor {
public:
    EscManipFgColor(Color color);
    Color color;
};

EscManipFgColor::EscManipFgColor(Color color) :
color(color) {
}

class EscManipBgColor {
public:
    EscManipBgColor(Color color);
    Color color;
};

EscManipBgColor::EscManipBgColor(Color color) :
color(color) {
}

class EscKillerManip {
};

EscManipFgColor gray(Color::Gray);
EscManipFgColor red(Color::Red);
EscManipFgColor green(Color::Green);
EscManipFgColor yellow(Color::Yellow);
EscManipFgColor blue(Color::Blue);
EscManipFgColor magenta(Color::Magenta);
EscManipFgColor cyan(Color::Cyan);
EscManipFgColor white(Color::White);
EscManipFgColor color_default(Color::Auto);

EscManipBgColor bg_gray(Color::Gray);
EscManipBgColor bg_red(Color::Red);
EscManipBgColor bg_green(Color::Green);
EscManipBgColor bg_yellow(Color::Yellow);
EscManipBgColor bg_blue(Color::Blue);
EscManipBgColor bg_magenta(Color::Magenta);
EscManipBgColor bg_cyan(Color::Cyan);
EscManipBgColor bg_white(Color::White);
EscManipBgColor bg_color_default(Color::Auto);

EscKillerManip esc_end;

EscStreamRaii operator<<(std::ostream& s, EscManipFgColor manip) {
    EscStreamRaii raii(s);
    raii.set_fg_color(manip.color);
    return raii;
}

EscStreamRaii operator<<(EscStreamRaii raii, EscManipFgColor manip) {
    if (raii.is_in_session())
        raii.end_session();
    raii.set_fg_color(manip.color);
    return raii;
}

EscStreamRaii operator<<(std::ostream& s, EscManipBgColor manip) {
    EscStreamRaii raii(s);
    raii.set_bg_color(manip.color);
    return raii;
}

EscStreamRaii operator<<(EscStreamRaii raii, EscManipBgColor manip) {
    if (raii.is_in_session())
        raii.end_session();
    raii.set_bg_color(manip.color);
    return raii;
}

std::ostream& operator<<(EscStreamRaii raii, EscKillerManip) {
    if (raii.is_in_session())
        raii.end_session();
    return raii.s;
}

template<typename T >
EscStreamRaii operator<<(EscStreamRaii raii, T x) {
    if (!raii.is_in_session())
        raii.start_session();
    raii.s << x;
    return raii;
}

//----------------------------------------------------------




#endif