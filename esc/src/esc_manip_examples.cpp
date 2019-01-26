#include<iostream>
#include<iomanip>
#include<esc/esc_manip.hpp>

int throwing_function() {
    throw std::runtime_error("Ups, an exception!");
    return 5;
}

struct Vec3 {
    double x, y, z;
};

std::ostream& operator<<(std::ostream& s, const Vec3& v) {
    s << "(" << v.x << " " << v.y << " " << v.z << ")";
    return s;
}

int main() {
    using namespace esc::manip;

    std::cout << "Using esc_manip is easy and intuitive:" << std::endl;

    std::cout << ">>> " << "Normal text" << red << italic << " and the red italic texet."
            << " " << underline << "plus underline" << std::endl
            << ">>> " << green << "(numers are good as well, for example nine: " << 9 << " )" << std::endl;


    std::cout << std::endl;
    std::cout << "The first think to note is that you do not need" << std::endl
            << "reset ansi escape codes you eneted in an expression" << std::endl
            << "at the end of the expression." << std::endl
            << "By esc_manip design, all ansi escape settings are reset automatically" << std::endl
            << "(think of it like of a RAII example)." << std::endl;

    std::cout << "It does deal even with throwing functions:" << std::endl;
    try {
        std::cout << ">>> " << red << 1 << 2 << 3 <<
                4 << 5 << throwing_function() << 6 << 7 << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }


    std::cout << std::endl;
    std::cout << "But sometimes you want to end colors and(or) styles earlier." << std::endl
            << "In such a case: use esc::manip::reset namipoluator." << std::endl;

    std::cout << ">>> " << "black," << blue << " blue," << bold << " and bold,"
            << reset << " again auto." << std::endl;

    std::cout << std::endl;
    std::cout << "After you reset, you may start new session one more time:" << std::endl;

    std::cout << ">>> " << "black," << blue << " blue," << bold << " and bold,"
            << reset << " again auto," << blue << " again blue!" << std::endl;

    std::cout << std::endl;
    std::cout << "You may use esc_manip together with your own data types:" << std::endl;
    const Vec3 v1 = {11.0, 12.0, 13.0};
    const Vec3 v2 = {21.0, 22.0, 23.0};
    std::cout << ">>> " << yellow << "yellow  : " << v1 << " + " << v2 << std::endl;
    std::cout << "And combine them with std iomanip:" << std::endl;
    std::cout << ">>> " << magenta << "magenta : " << v1 << " + " << std::fixed << std::setprecision(5) << v2 << std::endl;


    std::cout << std::endl;
    std::cout << "You may capture the setting using auto:" << std::endl;

    const auto gray_chapter_sink = std::cout << gray << underline;
    gray_chapter_sink << ">>> " << "Chapter line 1." << std::endl;
    gray_chapter_sink << ">>> " << "Chapter line 2." << std::endl;
    gray_chapter_sink << ">>> " << "Chapter line 3." << std::endl;
    std::cout << ">>> " << "Normal line" << std::endl;
    gray_chapter_sink << ">>> " << "Next Chapter line 1." << std::endl;
    gray_chapter_sink << ">>> " << "Next Chapter line 2." << std::endl;

    std::cout << std::endl;
    std::cout << "If you need some more control: take look at EscData struct." << std::endl
            << "The struct holds information about background and background colors" << std::endl
            << "as well as bold, italic, underline fags." << std::endl
            << "Instances of EscData may be created using builder-like pattern" << std::endl
            << "and expose a few self-explanatory fields:" << std::endl;    
    const esc::EscData esc_data = esc::EscDataBuilder() << red << bold << build_esc_data;
    std::cout << ">>> " << "fg_color   " << to_string(esc_data.fg_color) << std::endl;
    std::cout << ">>> " << "bg_color   " << to_string(esc_data.bg_color) << std::endl;
    std::cout << ">>> " << "bold:      " << esc_data.bold << std::endl;
    std::cout << ">>> " << "italic:    " << esc_data.italic << std::endl;
    std::cout << ">>> " << "underline: " << esc_data.underline << std::endl;
    std::cout << "One an EscData instance is prepared in advance," << std::endl;
    std::cout << "then may be utilized during many printing sessions" << std::endl;
    std::cout << "(with any number of streams)" << std::endl;
    std::cout << esc_data << "RedBold 1" << std::endl;
    std::cerr << esc_data << "RedBold 2" << std::endl;
    
    std::cout << std::endl;
    std::cout << "That is all by now! In future new features will be added!" << std::endl;

}