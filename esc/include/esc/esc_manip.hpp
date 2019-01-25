#ifndef ESC_ESC_MANIP
#define ESC_ESC_MANIP

#include<iostream>
#include<string>
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
    //-------------------  MANIPULATOR TRAITS   --------------------------------
    //--------------------------------------------------------------------------    

    struct ManipTag {
    };

    struct NoManipTag {
    };

    template<typename T>
    struct ManipDispatcher {
        using Tag = NoManipTag;
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

    //--------------------------------------------------------------------------

    class SinkBuilder {
    public:
        explicit SinkBuilder(std::ostream& stream);
        std::ostream& stream;
        SessionEscData session_ansi_data;
    private:
    };

    //--------------------------------------------------------------------------

    class EscStreamRaii {
    public:
        EscStreamRaii(std::ostream& stream, const SessionEscData& session_ansi_data);
        EscStreamRaii(const EscStreamRaii& raii) = delete;
        EscStreamRaii& operator=(EscStreamRaii&& raii) = delete;
        EscStreamRaii& operator=(const EscStreamRaii& raii) = delete;

        ~EscStreamRaii();
        std::string compile();
        void start_session();
        void end_session();
        bool is_session_holder() const;
        std::ostream& stream;
        SessionEscData session_ansi_data;
    private:
        explicit EscStreamRaii(EscStreamRaii&& raii);
        bool _is_session_holder;

        template<typename T>
        typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii>::type
        friend operator<<(const SinkBuilder& stream, const T& manip);
    };

    //--------------------------------------------------------------------------
    //-------------------  MANIPULATOR CLASSES  --------------------------------
    //--------------------------------------------------------------------------

    struct EscFgColorManip {
        Color color;
        void apply(SessionEscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscFgColorManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscBgColorManip {
        Color color;
        void apply(SessionEscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscBgColorManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscBoldManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscBoldManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscItalicManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscItalicManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscUnderlineManip {
        bool value;
        void apply(SessionEscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscUnderlineManip> {
        using Tag = ManipTag;
    };

    // -------------------------------------------------------------------------    

    struct EscResetManip {
    };

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
    //-------------------  STREAM LIKE API  ------------------------------------
    //--------------------------------------------------------------------------

    typedef std::ostream&(*StdManipFunPtrType)(std::ostream&);

    // std::ostream& << SinkBuilder:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder>::type
    operator<<(std::ostream& stream, const T& manip);

    // SinkBuilder&& << T and const SinkBuilder& << T :

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder&&>::type
    operator<<(SinkBuilder&& sink, const T& manip);

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii>::type
    operator<<(const SinkBuilder& sink, const T& x);

    SinkBuilder&&
    operator<<(SinkBuilder&& sink, StdManipFunPtrType std_namip);

    // EscStreamRaii&& << T:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii&&>::type
    operator<<(EscStreamRaii&& raii, const T& x);

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscStreamRaii&&>::type
    operator<<(EscStreamRaii&& raii, const T& manip);
    // Maybe better return SinkBuilder ?

    EscStreamRaii&&
    operator<<(EscStreamRaii&& raii, StdManipFunPtrType std_namip);

    std::ostream&
    operator<<(EscStreamRaii&& raii, const EscResetManip&);

    //--------------------------------------------------------------------------
    //-------------------  STREAM LIKE API -- IMPLEMENTATION  ------------------
    //--------------------------------------------------------------------------

    // std::ostream& << SinkBuilder:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder>::type
    operator<<(std::ostream& stream, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        SinkBuilder sink(stream);
        manip.apply(sink.session_ansi_data);
        return sink; // return a copy        
    }

    // SinkBuilder&& << T and const SinkBuilder& << T :

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder&&>::type
    operator<<(SinkBuilder&& sink, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        manip.apply(sink.session_ansi_data);
        return std::move(sink); // return a reference
    }

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii>::type
    operator<<(const SinkBuilder& sink, const T& x) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value);
        EscStreamRaii raii(sink.stream, sink.session_ansi_data);
        raii.start_session();
        raii.stream << x;
        return EscStreamRaii(std::move(raii)); // retur a copy
    }

    inline
    SinkBuilder &&
    operator<<(SinkBuilder&& sink, StdManipFunPtrType std_namip) {
        sink.stream << std_namip;
        return std::move(sink);
    }

    // EscStreamRaii&& << T:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii&&>::type
    operator<<(EscStreamRaii&& raii, const T& x) {
        if (!raii.is_session_holder())
            raii.start_session();
        raii.stream << x;
        return std::move(raii); // return a reference
    }

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscStreamRaii&&>::type
    operator<<(EscStreamRaii&& raii, const T& manip) {
        if (raii.is_session_holder())
            raii.end_session();
        manip.apply(raii.session_ansi_data);
        return std::move(raii); // return a reference

    }

    inline
    EscStreamRaii &&
    operator<<(EscStreamRaii&& raii, StdManipFunPtrType std_namip) {
        raii.stream << std_namip;
        return std::move(raii); // return a reference
    }

    inline
    std::ostream&
    operator<<(EscStreamRaii&& raii, const EscResetManip&) {
        if (raii.is_session_holder())
            raii.end_session();
        return raii.stream;
    }

    //    //Classical dispatcher implementation:
    //
    //    template<typename T >
    //    EscStreamRaii&&
    //    operator_impl(EscStreamRaii&& raii, const T& manip, ManipTag) {
    //        if (raii.is_session_holder())
    //            raii.end_session();
    //        manip.apply(raii.session_ansi_data);
    //        return std::move(raii);
    //    }
    //
    //    template<typename T >
    //    EscStreamRaii&&
    //    operator_impl(EscStreamRaii&& raii, const T& x, NoManipTag) {
    //        if (!raii.is_session_holder())
    //            raii.start_session();
    //        raii.stream << x;
    //        return std::move(raii);
    //    }
    //
    //    template<typename T >
    //    EscStreamRaii&&
    //    operator<<(EscStreamRaii&& raii, const T& x) {
    //        typename ManipDispatcher<T>::Tag t;
    //        return operator_impl(std::move(raii), x, t);
    //    }


}

#endif