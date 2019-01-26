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

    std::string to_string(Color);
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

    struct EscData {
        Color fg_color;
        Color bg_color;
        bool bold;
        bool italic;
        bool underline;
    };

    //--------------------------------------------------------------------------

    class EscDataBuilder {
    public:
        explicit EscDataBuilder(
                const EscData& session_ansi_data = {Color::Auto, Color::Auto, false, false, false});
        EscData esc_data;
    };

    //--------------------------------------------------------------------------

    class SinkBuilder {
    public:
        explicit SinkBuilder(
                std::ostream& stream,
                const EscData& session_ansi_data = {Color::Auto, Color::Auto, false, false, false});
        std::ostream& stream;
        EscData esc_data;
    };

    //--------------------------------------------------------------------------

    class EscStreamRaii {
    public:
        EscStreamRaii(std::ostream& stream, const EscData& session_ansi_data);
        EscStreamRaii(const EscStreamRaii& raii) = delete;
        EscStreamRaii& operator=(EscStreamRaii&& raii) = delete;
        EscStreamRaii& operator=(const EscStreamRaii& raii) = delete;

        ~EscStreamRaii();
        std::string compile();
        void start_session();
        void end_session();
        bool is_session_holder() const;
        std::ostream& stream;
        EscData session_ansi_data;
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
        void apply(EscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscFgColorManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscBgColorManip {
        Color color;
        void apply(EscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscBgColorManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscBoldManip {
        bool value;
        void apply(EscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscBoldManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscItalicManip {
        bool value;
        void apply(EscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscItalicManip> {
        using Tag = ManipTag;
    };

    //--------------------------------------------------------------------------

    struct EscUnderlineManip {
        bool value;
        void apply(EscData& d) const;
    };

    template<>
    struct ManipDispatcher<EscUnderlineManip> {
        using Tag = ManipTag;
    };

    // -------------------------------------------------------------------------    

    struct BuildEscDataManip {
    };

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

        extern const BuildEscDataManip build_esc_data;
        extern const EscResetManip reset;
    }

    //--------------------------------------------------------------------------
    //-------------------  STREAM LIKE API  ------------------------------------
    //--------------------------------------------------------------------------

    typedef std::ostream&(*StdManipFunPtrType)(std::ostream&);

    // -------------------------------------------------------------------------
    // EscDataBuilder&& << T:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscDataBuilder&&>::type
    operator<<(EscDataBuilder&& builder, const T& manip);

    EscData
    operator<<(const EscDataBuilder& builder, const BuildEscDataManip &);

    // -------------------------------------------------------------------------    
    // std::ostream& << T:

    SinkBuilder operator<<(std::ostream& stream, const EscData& data);

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder>::type
    operator<<(std::ostream& stream, const T& manip);

    // -------------------------------------------------------------------------    
    // SinkBuilder&& << T and const SinkBuilder& << T :    

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder&&>::type
    operator<<(SinkBuilder&& builder, const T& manip);

    SinkBuilder&&
    operator<<(SinkBuilder&& builder, StdManipFunPtrType std_namip);

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii>::type
    operator<<(const SinkBuilder& builder, const T& x);

    // -------------------------------------------------------------------------    
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

    // EscDataBuilder&& << T:

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, EscDataBuilder&&>::type
    operator<<(EscDataBuilder&& builder, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        manip.apply(builder.esc_data);
        return std::move(builder);
    }

    inline
    EscData
    operator<<(const EscDataBuilder& builder, const BuildEscDataManip &) {
        return builder.esc_data;
    }

    // -------------------------------------------------------------------------        
    // std::ostream& << T:

    inline
    SinkBuilder operator<<(std::ostream& stream, const EscData& data) {
        SinkBuilder builder(stream, data);
        return builder; // return a copy  
    }

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder>::type
    operator<<(std::ostream& stream, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        SinkBuilder builder(stream);
        manip.apply(builder.esc_data);
        return builder; // return a copy        
    }


    // -------------------------------------------------------------------------    
    // SinkBuilder&& << T and const SinkBuilder& << T :    

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value, SinkBuilder&&>::type
    operator<<(SinkBuilder&& builder, const T& manip) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, ManipTag>::value);
        manip.apply(builder.esc_data);
        return std::move(builder); // return a reference
    }

    inline
    SinkBuilder &&
    operator<<(SinkBuilder&& builder, StdManipFunPtrType std_namip) {
        builder.stream << std_namip;
        return std::move(builder);
    }

    template<typename T>
    typename std::enable_if<std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value, EscStreamRaii>::type
    operator<<(const SinkBuilder& builder, const T& x) {
        static_assert(std::is_same<typename ManipDispatcher<T>::Tag, NoManipTag>::value);
        EscStreamRaii raii(builder.stream, builder.esc_data);
        raii.start_session();
        raii.stream << x;
        return EscStreamRaii(std::move(raii)); // retur a copy
    }

    // -------------------------------------------------------------------------    
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