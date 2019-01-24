#ifndef ESC_ESC_MANIP
#define ESC_ESC_MANIP

#include<iostream>
#include<type_traits>

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

    struct SessionEscData {
        Color fg_color;
        Color bg_color;
        bool bold;
        bool italic;
        bool underline;
    };

    class EscStreamRaii {
    public:
        explicit EscStreamRaii(std::ostream& s);
        EscStreamRaii(EscStreamRaii& raii);
        ~EscStreamRaii();
        std::string compile();
        void start_session();
        void end_session();
        bool is_session_holder() const;
        std::ostream& stream;
        SessionEscData session_ansi_data;
    private:
        bool _is_session_holder;
    };

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR CLASSES  --------------------------------
    //--------------------------------------------------------------------------

    struct EscFgColorManip {
        Color color;
        void apply(SessionEscData& d) const;
    };

    struct EscBgColorManip {
        Color color;
        void apply(SessionEscData& d) const;
    };

    struct EscBoldManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    struct EscItalicManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    struct EscUnderlineManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    struct EscResetManip {
    };

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR TRAITS   --------------------------------
    //--------------------------------------------------------------------------    

    struct ManipTag {
    };

    struct NoManipTag {
    };

    template<typename T>
    struct ManipDispatcher {
        typedef NoManipTag Tag;
    };

    template<>
    struct ManipDispatcher<EscFgColorManip> {
        typedef ManipTag Tag;
    };

    template<>
    struct ManipDispatcher<EscBgColorManip> {
        typedef ManipTag Tag;
    };

    template<>
    struct ManipDispatcher<EscBoldManip> {
        typedef ManipTag Tag;
    };

    template<>
    struct ManipDispatcher<EscItalicManip> {
        typedef ManipTag Tag;
    };

    template<>
    struct ManipDispatcher<EscUnderlineManip> {
        typedef ManipTag Tag;
    };

    //--------------------------------------------------------------------------
    //-------------------  STREAM LIKE API  ------------------------------------
    //--------------------------------------------------------------------------

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscStreamRaii>::type
    operator<<(std::ostream& stream, const T& manip);

    template<typename T >
    EscStreamRaii&&
    operator<<(EscStreamRaii&& raii, const T& x);

    std::ostream&
    operator<<(EscStreamRaii&& raii, const EscResetManip&);

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
    //-------------------  TEMPLATES IMPLEMENTATION ----------------------------
    //--------------------------------------------------------------------------

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscStreamRaii>::type
    operator<<(std::ostream& stream, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        EscStreamRaii raii(stream);
        manip.apply(raii.session_ansi_data);
        return raii;
    }

    template<typename T >
    EscStreamRaii&&
    operator_impl(EscStreamRaii&& raii, const T& manip, ManipTag) {
        if (raii.is_session_holder())
            raii.end_session();
        manip.apply(raii.session_ansi_data);
        return std::move(raii);
    }

    template<typename T >
    EscStreamRaii&&
    operator_impl(EscStreamRaii&& raii, const T& x, NoManipTag) {
        if (!raii.is_session_holder())
            raii.start_session();
        raii.stream << x;
        return std::move(raii);
    }

    template<typename T >
    EscStreamRaii&&
    operator<<(EscStreamRaii&& raii, const T& x) {
        typename ManipDispatcher<T>::Tag t;
        return operator_impl(std::move(raii), x, t);
    }

}

#endif