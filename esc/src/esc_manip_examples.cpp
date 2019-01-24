#include<iostream>
#include<iomanip>
#include<esc/esc_manip.hpp>

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
            << "(think of it like of a RAII example)" << std::endl;

    std::cout << std::endl;
    std::cout << "But sometimes you want to end colors and(or) styles earlier." << std::endl
            << "In such a case: use esc::manip::reset namipoluator." << std::endl;

    std::cout << ">>> " << "black" << blue << "blue" << bold << " and bold"
            << reset << "again auto auto" << std::endl;

    std::cout << std::endl;
    std::cout << "After you reset, you may start new session one more time:" << std::endl;

    std::cout << ">>> " << "black" << blue << "blue" << bold << " and bold"
            << reset << "again auto auto" << blue << " again black" << std::endl;

    std::cout << std::endl;
    std::cout << "You may use esc_manip together with your own data types:" << std::endl;
    const Vec3 v1 = {11.0, 12.0, 13.0};
    const Vec3 v2 = {21.0, 22.0, 23.0};
    std::cout << ">>> " << yellow << v1 << "+" << v2 << std::endl;
    std::cout << "And combine them with std iomanip:" << std::endl;
    std::cout << ">>> " << magenta << v1 << "+" << std::fixed << std::setprecision(5) << v2 << std::endl;


    std::cout << std::endl;
    std::cout << "You may capture the setting using auto:" << std::endl;
    {
        auto preparer = std::cout << gray << underline;
        std::move(preparer) << ">>> Write to prepared sink." << std::endl;
    }
    std::cout << "But this feature need some improvement." << std::endl;

    std::cout << std::endl;
    std::cout << "That is all by now! In future new features will be added!" << std::endl;

}