#ifndef ESC_ESC_MANIP
#define ESC_ESC_MANIP

#include<iostream>

namespace esc {

    //--------------------------------------------------------------------------
    //-------------------- COLORS ENUM  ----------------------------------------
    //--------------------------------------------------------------------------

    enum class Color {
        Gray = 0,
        Red = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4,
        Magenta = 5,
        Cyan = 6,
        White = 7,
        Auto = 9 // "to reset colors to their defaults, use ESC[39;49m" Wikipedia.
    };

    //--------------------------------------------------------------------------
    //-----------  ANSI ESCAPE SESSION CONTROLLER CLASS  -----------------------
    //--------------------------------------------------------------------------    

    class EscStreamRaii {
    public:
        explicit EscStreamRaii(std::ostream& s);
        EscStreamRaii(EscStreamRaii& raii);
        ~EscStreamRaii();
        void set_fg_color(Color color);
        void set_bg_color(Color color);
        void set_bold(bool value);
        void set_italic(bool value);
        void set_underline(bool value);
        std::string compile();
        void start_session();
        void end_session();
        bool is_session_holder() const;
        std::ostream& stream;
    private:

        struct {
            Color fg_color;
            Color bg_color;
            bool bold;
            bool italic;
            bool underline;
        } ansi_data;
        bool _is_session_holder;
    };

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR CLASSES  --------------------------------
    //--------------------------------------------------------------------------

    struct EscFgColorManip {
        Color color;
    };

    struct EscBgColorManip {
        Color color;
    };

    struct EscBoldManip {
        bool value;
    };

    struct EscItalicManip {
        bool value;
    };

    struct EscUnderlineManip {
        bool value;
    };

    struct EscResetManip {
    };

    //--------------------------------------------------------------------------
    //-------------------  STREAM LIKE API  ------------------------------------
    //--------------------------------------------------------------------------

    EscStreamRaii operator<<(std::ostream& stream, const EscFgColorManip& manip);
    EscStreamRaii operator<<(std::ostream& stream, const EscBgColorManip& manip);
    EscStreamRaii operator<<(std::ostream& stream, const EscBoldManip& manip);
    EscStreamRaii operator<<(std::ostream& stream, const EscItalicManip& manip);
    EscStreamRaii operator<<(std::ostream& stream, const EscUnderlineManip& manip);

    EscStreamRaii operator<<(EscStreamRaii raii, const EscFgColorManip& manip);
    EscStreamRaii operator<<(EscStreamRaii raii, const EscBgColorManip& manip);
    EscStreamRaii operator<<(EscStreamRaii raii, const EscBoldManip& manip);
    EscStreamRaii operator<<(EscStreamRaii raii, const EscItalicManip& manip);
    EscStreamRaii operator<<(EscStreamRaii raii, const EscUnderlineManip& manip);

    std::ostream& operator<<(EscStreamRaii raii, const EscResetManip&);

    template<typename T >
    EscStreamRaii operator<<(EscStreamRaii raii, T x);

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATORS  ---------------------------------------
    //--------------------------------------------------------------------------

    namespace manip {

        extern const EscFgColorManip gray;
        extern const EscFgColorManip red;
        extern const EscFgColorManip green;
        extern const EscFgColorManip yellow;
        extern const EscFgColorManip blue;
        extern const EscFgColorManip magenta;
        extern const EscFgColorManip cyan;
        extern const EscFgColorManip white;
        extern const EscFgColorManip color_default;

        extern const EscBgColorManip bg_gray;
        extern const EscBgColorManip bg_red;
        extern const EscBgColorManip bg_green;
        extern const EscBgColorManip bg_yellow;
        extern const EscBgColorManip bg_blue;
        extern const EscBgColorManip bg_magenta;
        extern const EscBgColorManip bg_cyan;
        extern const EscBgColorManip bg_white;
        extern const EscBgColorManip bg_color_default;

        extern const EscBoldManip bold;
        extern const EscBoldManip nobold;

        extern const EscItalicManip italic;
        extern const EscItalicManip noitalic;

        extern const EscUnderlineManip underline;
        extern const EscUnderlineManip nounderline;

        extern const EscResetManip reset;
    }
    //--------------------------------------------------------------------------
    //-------------------  TEMPLATE IMPLEMENTATION -----------------------------
    //--------------------------------------------------------------------------

    template<typename T >
    EscStreamRaii operator<<(EscStreamRaii raii, T x) {
        if (!raii.is_session_holder())
            raii.start_session();
        raii.stream << x;
        return raii;
    }


}

#endif