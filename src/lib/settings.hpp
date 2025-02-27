// Copyright © 2024 Giorgio Audrito. All Rights Reserved.

/**
 * @file settings.hpp
 * @brief Definition of default values for settings macros.
 */

#ifndef FCPP_SETTINGS_H_
#define FCPP_SETTINGS_H_

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>


//! @brief Identifier for low-end, resource constrained systems.
#define FCPP_SYSTEM_EMBEDDED 11
//! @brief Identifier for high-end, general purpose systems.
#define FCPP_SYSTEM_GENERAL  22

#ifndef FCPP_SYSTEM
//! @brief Setting defining the system: @ref FCPP_SYSTEM_EMBEDDED or @ref FCPP_SYSTEM_GENERAL (default).
#define FCPP_SYSTEM FCPP_SYSTEM_GENERAL
#endif


//! @brief Identifier for logical cloud systems, not simulating a physical world.
#define FCPP_ENVIRONMENT_LOGICAL   111
//! @brief Identifier for physically deployed systems.
#define FCPP_ENVIRONMENT_PHYSICAL  222
//! @brief Identifier for simulations of deployed systems.
#define FCPP_ENVIRONMENT_SIMULATED 333


#ifndef FCPP_ENVIRONMENT
//! @brief Setting defining the overall environment: @ref FCPP_ENVIRONMENT_LOGICAL, @ref FCPP_ENVIRONMENT_PHYSICAL or @ref FCPP_ENVIRONMENT_SIMULATED (default).
#define FCPP_ENVIRONMENT FCPP_ENVIRONMENT_SIMULATED
#endif


//! @brief Identifier for systems operating stand-alone, without user or network interactions.
#define FCPP_CONFIGURATION_STANDALONE 1111
//! @brief Identifier for systems depending on user or network interaction.
#define FCPP_CONFIGURATION_DEPENDENT  2222

#ifndef FCPP_CONFIGURATION
//! @brief Setting defining the overall environment: @ref FCPP_CONFIGURATION_STANDALONE (default) or @ref FCPP_CONFIGURATION_DEPENDENT.
#define FCPP_CONFIGURATION FCPP_CONFIGURATION_STANDALONE
#endif


#if   FCPP_SYSTEM == FCPP_SYSTEM_GENERAL
    #ifndef FCPP_REAL_TYPE
    //! @brief Setting defining the type to be used for real numbers (double for general systems, float for embedded systems).
    #define FCPP_REAL_TYPE double
    #endif
    #ifndef FCPP_TRACE
    //! @brief Setting defining the size of trace hashes (64 for general systems, 16 for embedded systems).
    #define FCPP_TRACE 64
    #endif
    #ifndef FCPP_DEVICE
    //! @brief Setting defining the size of device identifiers (32 for general systems, 16 for embedded systems).
    #define FCPP_DEVICE 32
    #endif
    #ifndef FCPP_HOPS
    //! @brief Setting defining the size of hop counts (16 for general systems, 8 for embedded systems).
    #define FCPP_HOPS 16
    #endif
#elif FCPP_SYSTEM == FCPP_SYSTEM_EMBEDDED
    #ifndef FCPP_REAL_TYPE
    //! @brief Setting defining the type to be used for real numbers (double for general systems, float for embedded systems).
    #define FCPP_REAL_TYPE float
    #endif
    #ifndef FCPP_TRACE
    //! @brief Setting defining the size of trace hashes (64 for general systems, 16 for embedded systems).
    #define FCPP_TRACE 16
    #endif
    #ifndef FCPP_DEVICE
    //! @brief Setting defining the size of device identifiers (32 for general systems, 16 for embedded systems).
    #define FCPP_DEVICE 16
    #endif
    #ifndef FCPP_HOPS
    //! @brief Setting defining the size of hop counts (16 for general systems, 8 for embedded systems).
    #define FCPP_HOPS 8
    #endif
#else
    static_assert(false, "invalid value for FCPP_SYSTEM");
#endif


#if   FCPP_ENVIRONMENT == FCPP_ENVIRONMENT_LOGICAL
    #ifndef FCPP_EXPORT_NUM
    //! @brief Setting defining whether exports for self and other devices should be separated (2, default for physical systems) or together (1, default for simulated and logical systems).
    #define FCPP_EXPORT_NUM 1
    #endif
    #ifndef FCPP_EXPORT_PTR
    //! @brief Setting defining whether exports should be handled as values (false, default for physical systems) or shared pointers (true, default for simulated and logical systems).
    #define FCPP_EXPORT_PTR true
    #endif
    #ifndef FCPP_ONLINE_DROP
    //! @brief Setting defining whether old messages should be dropped while new ones arrive (true, default for physical systems) or at round start (false, default for simulated and logical systems).
    #define FCPP_ONLINE_DROP false
    #endif
    #ifndef FCPP_PARALLEL
    //! @brief Setting defining whether the computation should be performed with parallel threads.
    #define FCPP_PARALLEL true
    #endif
    #ifndef FCPP_SYNCHRONISED
    //! @brief Setting defining whether many events are expected to happen at the same time.
    #define FCPP_SYNCHRONISED true
    #endif
#elif FCPP_ENVIRONMENT == FCPP_ENVIRONMENT_PHYSICAL
    #ifndef FCPP_EXPORT_NUM
    //! @brief Setting defining whether exports for self and other devices should be separated (2, default for physical systems) or together (1, default for simulated and logical systems).
    #define FCPP_EXPORT_NUM 2
    #endif
    #ifndef FCPP_EXPORT_PTR
    //! @brief Setting defining whether exports should be handled as values (false, default for physical systems) or shared pointers (true, default for simulated and logical systems).
    #define FCPP_EXPORT_PTR false
    #endif
    #ifndef FCPP_ONLINE_DROP
    //! @brief Setting defining whether old messages should be dropped while new ones arrive (true, default for physical systems) or at round start (false, default for simulated and logical systems).
    #define FCPP_ONLINE_DROP true
    #endif
    #ifndef FCPP_PARALLEL
    //! @brief Setting defining whether the computation should be performed with parallel threads.
    #define FCPP_PARALLEL false
    #endif
    #ifndef FCPP_SYNCHRONISED
    //! @brief Setting defining whether many events are expected to happen at the same time.
    #define FCPP_SYNCHRONISED false
    #endif
#elif FCPP_ENVIRONMENT == FCPP_ENVIRONMENT_SIMULATED
    #ifndef FCPP_EXPORT_NUM
    //! @brief Setting defining whether exports for self and other devices should be separated (2, default for physical systems) or together (1, default for simulated and logical systems).
    #define FCPP_EXPORT_NUM 1
    #endif
    #ifndef FCPP_EXPORT_PTR
    //! @brief Setting defining whether exports should be handled as values (false, default for physical systems) or shared pointers (true, default for simulated and logical systems).
    #define FCPP_EXPORT_PTR true
    #endif
    #ifndef FCPP_ONLINE_DROP
    //! @brief Setting defining whether old messages should be dropped while new ones arrive (true, default for physical systems) or at round start (false, default for simulated and logical systems).
    #define FCPP_ONLINE_DROP false
    #endif
    #ifndef FCPP_PARALLEL
    //! @brief Setting defining whether the computation should be performed with parallel threads.
    #define FCPP_PARALLEL false
    #endif
    #ifndef FCPP_SYNCHRONISED
    //! @brief Setting defining whether many events are expected to happen at the same time.
    #define FCPP_SYNCHRONISED false
    #endif
#else
    static_assert(false, "invalid value for FCPP_ENVIRONMENT");
#endif


#ifndef FCPP_REALTIME
    #if FCPP_ENVIRONMENT == FCPP_ENVIRONMENT_PHYSICAL || FCPP_CONFIGURATION == FCPP_CONFIGURATION_DEPENDENT
    //! @brief Factor multiplying real time passing (1 for physical or dependent systems, infinity for others).
    #define FCPP_REALTIME 1
    #else
    //! @brief Factor multiplying real time passing (1 for physical or dependent systems, infinity for others).
    #define FCPP_REALTIME INF
    #endif
#endif


#ifndef FCPP_TIERS
//! @brief Setting defining the maximum number of different tiers of nodes supported.
#define FCPP_TIERS 8
#endif


#ifndef FCPP_THREADS
    //! @brief Setting regulating the number of threads to be used.
    #define FCPP_THREADS std::thread::hardware_concurrency()
#endif


#ifndef FCPP_MESSAGE_PUSH
    //! @brief Setting defining whether incoming messages are pushed or pulled.
    #define FCPP_MESSAGE_PUSH true
#endif


#ifndef FCPP_VALUE_PUSH
    //! @brief Setting defining whether new values should be pushed to aggregators or pulled when needed.
    #define FCPP_VALUE_PUSH false
#endif


#ifndef FCPP_WARNING_TRACE
    //! @brief Setting defining whether hash colliding of code points is admissible.
    #define FCPP_WARNING_TRACE false
#endif


#ifndef FCPP_TIME_TYPE
//! @brief Setting defining the type to be used to represent times (default to \ref FCPP_REAL_TYPE).
#define FCPP_TIME_TYPE FCPP_REAL_TYPE
#endif


#ifndef FCPP_TIME_EPSILON
//! @brief Setting defining which time differences are to be considered negligible.
#define FCPP_TIME_EPSILON 0.01f
#endif


#ifndef FCPP_REFRESH_RATE
//! @brief Setting defining the minimum acceptable refresh rate of graphical representations.
#define FCPP_REFRESH_RATE 0.1f
#endif


#ifndef FCPP_ANTIALIAS
//! @brief Setting defining the antialiasing factor (1 to disable).
#define FCPP_ANTIALIAS 4
#endif


#ifndef FCPP_SPHERICITY
//! @brief Setting defining the definition of spheres (1 for icosahedron).
#define FCPP_SPHERICITY 10
#endif


#ifndef FCPP_TAIL_GRANULARITY
//! @brief Setting defining the granularity of snapshot points in tails in FPS.
#define FCPP_TAIL_GRANULARITY 10
#endif


#ifndef FCPP_FIELD_DRAW_LIMIT
//! @brief Setting defining the maximum number of elements displayed for a field.
#define FCPP_FIELD_DRAW_LIMIT 8
#endif


/**
 * @brief Namespace containing all the objects in the FCPP library.
 */
namespace fcpp {
    //! @brief Signed integer type with a minimum given width in bits.
    template <size_t n>
    using intn_t = std::conditional_t<
        n <= 16,
        std::conditional_t<n <= 8,  int8_t,  int16_t>,
        std::conditional_t<n <= 32, int32_t, int64_t>
    >;

    //! @brief Unsigned integer type with a minimum given width in bits.
    template <size_t n>
    using uintn_t = std::conditional_t<
        n <= 16,
        std::conditional_t<n <= 8,  uint8_t,  uint16_t>,
        std::conditional_t<n <= 32, uint32_t, uint64_t>
    >;

    //! @brief Type used for real numbers.
    using real_t = FCPP_REAL_TYPE;

    //! @brief Type used for times.
    using times_t = FCPP_TIME_TYPE;

#ifdef NAN
    #undef NAN
#endif
    //! @brief Minimum time (infinitely in the past).
    constexpr times_t TIME_MIN = std::numeric_limits<times_t>::has_infinity ? -std::numeric_limits<times_t>::infinity() : std::numeric_limits<times_t>::lowest();
    //! @brief Maximum time (infinitely in the future).
    constexpr times_t TIME_MAX = std::numeric_limits<times_t>::has_infinity ? std::numeric_limits<times_t>::infinity() : std::numeric_limits<times_t>::max();
    //! @brief Shorthand to real infinity value.
    constexpr real_t INF = std::numeric_limits<real_t>::infinity();
    //! @brief Shorthand to real not-a-number value.
    constexpr real_t NAN = std::numeric_limits<real_t>::quiet_NaN();

    //! @brief Type for device identifiers (depends on @ref FCPP_DEVICE).
    using device_t = uintn_t<FCPP_DEVICE>;

    //! @brief Type for hop counts (depends on @ref FCPP_HOPS).
    using hops_t = intn_t<FCPP_HOPS>;

    //! @brief Type for tiers (peer types, depends on @ref FCPP_TIERS).
    using tier_t = uintn_t<FCPP_TIERS>;
}


#endif // FCPP_SETTINGS_H_
