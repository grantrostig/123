/** Copyright (c) Grant Rostig, grantrostig.com 2023. Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
    NOT PRODUCTION QUALITY CODE, just shows learning/teaching example, not real programming, don't copy this style, just playing around
    Reminder of usefull resources:
        https://coliru.stacked-crooked.com/
        https://godbolt.org/
        https://cppinsights.io/
        https://Wandbox.org
        https://cpp.sh/
        https://quick-bench.com/
        https://arnemertz.github.io/online-compilers/
    [[maybe_unused]] int * my_new_var8 = ::new (22,int);
    Language Versions:  clan++ -std=c++2b, g++ -std=c++23 or =gnu++23
    STD Libraries: Gcc: libstdc++; Clang: libc++; Microsoft: msvc/ms stl  // TODO??: how do we link with different libraries than the default using gcc or clang (the exact command line text)?
    g++ -Werror -Weffc++ -Wextra -Wall -Wconversion -Wshadow -Wpedantic -Wold-style-cast -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-override -Wnon-virtual-dtor \
        -Wcast-align -Woverloaded-virtual -Wunused -pedantic -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough \
        -Wuseless-cast -Wsuggest-final-types -Wsuggest-final-methods -Wduplicated-cond -Wduplicated-branches -Wlogical-op -std=gnuc++23 \
        main.cpp <OTHER>.cpp -o <A.OUT>

    SYMBOL    MEANING // for debugging purposes
    TODO:     the principal programmer needs todo.
    TODO?:	  the principal programmer is not sure about something, that should be addressed.
    TODO?:X   the X programmer is not sure about something, that should be addressed.
    TODO??:   is a question for verbal discussion at CppMSG.com meetup meetings.

    Ordering of headers as follows: re:Lakos
    + The prototype/interface header for this implementation (ie, the .h/.hh file that corresponds to this .cpp/.cc file).
    + Other headers from the same project, as needed.
    + Headers from other non-standard, non-system libraries (for example, Qt, Eigen, etc).
    + Headers from other "almost-standard" libraries (for example, Boost)
    + Standard C++ headers (for example, iostream, functional, etc.)
    + Standard C headers (for example, cstdint, dirent.h, etc.)

    define NDEBUG if asserts are NOT to be checked.  Put in *.h file not *.CPP
    #define NDEBUG
    define GR_DEBUG if we/programmer is Debugging.  Put in *.h file not *.CPP
    #define GR_DEBUG
    #ifdef GR_DEBUG
    #endif GR_DEBUG
 */

//#include <counter.hpp>

//#include "global_entities.h"
#include <cmath>
#include <gsl/gsl> // sudo dnf install  guidelines-support-library-devel
//#include <bits/stdc++.h>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <csignal>
#include <iostream>
#include <optional>
#include <source_location>
#include <string>
#include <stacktrace>
#include <vector>

using std::cin; using std::cout; using std::cerr; using std::clog; using std::endl; using std::string;  // using namespace std;
using namespace std::string_literals;
using namespace std::chrono_literals;

static_assert(CHAR_MIN < 0, "char is signed");
//static_assert(CHAR_MIN == 0, "char is unsigned");
#if CHAR_MIN < 0
    #pragma message("char is signed")
#else
    #pragma message("char is unsigned")
#endif
using Ostring       = std::optional<std::string>;
using Ochar         = std::optional<char>;
using Ointegral     = std::optional<long>;
//inline constexpr char           CHAR_NULL{'\o{177}'};        // Value is unset/not-set, similar to how a SQL DB shows an unset field as NULL, which is different than zero length or some magic number.  Here we turn it into a magic number and hope for the best.
inline constexpr char           CHAR_NULL{CHAR_MIN};        // Value is unset/not-set, similar to how a SQL DB shows an unset field as NULL, which is different than zero length or some magic number.  Here we turn it into a magic number and hope for the best.
inline constexpr signed char    SCHAR_NULL{SCHAR_MIN};       // Value is unset/not-set, similar to how a SQL DB shows an unset field as NULL, which is different than zero length or some magic number.  Here we turn it into a magic number and hope for the best.
inline constexpr unsigned char  UCHAR_NULL{UCHAR_MAX};       // Value is unset/not-set, similar to how a SQL DB shows an unset field as NULL, which is different than zero length or some magic number.  Here we turn it into a magic number and hope for the best.
inline constexpr std::string    STRING_NULL{"NULL"};    // Value is unset/not-set, similar to how a SQL DB shows an unset field as NULL, which is different than zero length or some magic number.  Here we turn it into a magic number and hope for the best.

 // Some crude logging that prints source location, where X prints a variable, and R adds \n\r (which is usefull when tty in in RAW or CBREAK mode. Requires C++20.
#define LOGGER_(  msg )  using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<    "["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<           "."    <<endl;cout.flush();cerr.flush();
#define LOGGER_R( msg )  using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<"\r\n["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<           ".\r\n"<<endl;cout.flush();cerr.flush();
#define LOGGERX(  msg, x)using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<    "["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".:{"<<x<<"}."    <<endl;cout.flush();cerr.flush();
#define LOGGERXR( msg, x)using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<"\r\n["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".:{"<<x<<"}.\r\n"<<endl;cout.flush();cerr.flush();

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };


/** Requires that a type has insertion operator
    Concept definition - used by a template below.
    Some value needs to be incorporated with above text:
///  Concept using Function Explicit instantiations that are required to generate code for linker.
///  TODO??: is the only used if definition is in *.cpp file?
///  https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
///  https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
//template std::ostream & operator<<( std::ostream & , std::vector<std::string> const & );
/// Concept using Function Explicit instantiations that are required to generate code for linker.
//template std::ostream & operator<<( std::ostream & , std::deque<int>          const & );
*/
template <typename Container>
concept Insertable = requires( std::ostream & out ) {
    requires not std::same_as<std::string, Container>;                                    // OR $ std::is_same <std::string, Container>::value OR std::is_same_v<std::string, Container>;
    { out << typename Container::value_type {} } -> std::convertible_to<std::ostream & >; // OR just $ { out << typename Container::value_type {} };
};

/** Prints contents of a container such as a vector of int's.
    Insertable Concept used by Templated Function definition
    Older version is here for the record:
    template<typename T> std::ostream & operator<<(std::ostream & out, std::vector<T> const & v) { // utility f() to print vectors
    if ( not v.empty() ) {
        out<<'['; std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", ")); out<<"\b\b]";
    }
        return out;
    }
*/
template<typename Container>                        //template<insertable Container>        // OR these 2 lines currently being used.
    requires Insertable<Container>
std::ostream &
operator<<( std::ostream & out, Container const & c) {
    if ( not c.empty()) {
        out << "[<";   //out.width(9);  // TODO??: neither work, only space out first element. //out << std::setw(9);  // TODO??: neither work, only space out first element.
        std::copy(c.begin(), c.end(), std::ostream_iterator< typename Container::value_type >( out, ">,<" ));
        out << "\b\b\b>]"; out.width(); out << std::setw(0);
    } else out << "[CONTAINTER IS EMPTY]";
    return out;
}

namespace Detail {  // NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
std::string source_loc();           // forward declaration
extern void stacktrace_register();
void crash_signals_register();

/** gives a source location for printing.  Used for debugging. */
std::string
source_loc() {
    using loc = std::source_location;
    //using ts = std::to_string;  // todo??: why not?  alternative approach?
    std::string result {"\n"s+loc::current().file_name() +":"s +std::to_string(loc::current().line()) +std::to_string(loc::current().column())+"]`"s +loc::current().function_name()+"`."s};
    return result;
}

/** Called as we try to ABORT ) after already getting another signal from the application code.
    OR should we exit() or terminate() and not use this function? */
auto crash_tracer_SIGABRT(int signal_number) -> void {
    //LOGGERX( "We are getting out and that generated another signal, presumably ABRT, we got signal number", signal_number);
    //LOGGERX( "IGNORE THIS ONE, just shown for understanding:", std::stacktrace::current());
    LOGGER_( "This is the very end!");
    return;
}

/** Prints a stack trace of crash location.  Used for debugging. */
auto crash_tracer(int signal_number) -> void {
    cerr << "\n\r:CRASH_ERROR:Got signal number:" << signal_number;
    cerr << "\n\r:./stack_trace::current():" << std::stacktrace::current() <<":END CRASH_ERROR STACK_TRACE."<<endl;

    if ( bool is_want_prompt{true}; is_want_prompt ) {
        std::string reply; cout << "CRASH_ERROR: q for exit(1) or CR to continue:"; cout.flush(); cin.clear();
        getline( cin, reply );
        if ( reply == "q" )
            exit(1);
        else
            return;
    }
    else {
        /* IGNORE using namespace std::chrono_literals;
    std::chrono::duration my_duration = 2s;
    cerr << "Wait time:" << 2s << " + in variable:"<< my_duration <<endl;
    std::this_thread::sleep_for( my_duration ); // sleep(2);  // seconds
    std::this_thread::sleep_for( std::chrono_literals::s::1 ); //todo??: how to do this?
    LOGGER_LOC( my_tracer(): Now- after stacktrace documenting a catastrophic error- we need to abort().);
    */

        //std::signal( SIGABRT, SIG_DFL ); // repair normal signals in preparation for abort() // OR maybe?? $ std::signal( SIGABRT, SIG_IGN );
        std::abort(); // OR alternatively? $ std::exit(42) or teminate, or quick_exit()??
        // *** we never get here
        assert( false && "Doing something after std::abort() is ERROR.\n" );
        return;
    }
}
/** signals that cause "terminate" and sometimes "core dump"  https://en.wikipedia.org/wiki/Signal_(IPC)
   We define here all the signal names listed in POSIX (1003.1-2008);
   as of 1003.1-2013, no additional signals have been added by POSIX.
   We also define here signal names that historically exist in every
   real-world POSIX variant (e.g. SIGWINCH).
   Signals in the 1-15 range are defined with their historical numbers.
   For other signals, we use the BSD numbers.
   There are two unallocated signal numbers in the 1-31 range: 7 and 29.
   Signal number 0 is reserved for use as kill(pid, 0), to test whether
   a process exists without sending it a signal.
 ISO C99 signals.
#define	SIGINT		2	 Interactive attention signal.
#define	SIGILL		4	 Illegal instruction.
#define	SIGABRT		6	 Abnormal termination.
#define	SIGFPE		8	 Erroneous arithmetic operation.
#define	SIGSEGV		11	 Invalid access to storage.
#define	SIGTERM		15	 Termination request.
 Historical signals specified by POSIX.
#define	SIGHUP		1	 Hangup.
#define	SIGQUIT		3	 Quit.
#define	SIGTRAP		5	 Trace/breakpoint trap.
#define	SIGKILL		9	 Killed.
#define	SIGPIPE		13	 Broken pipe.
#define	SIGALRM		14	 Alarm clock.
 Adjustments and additions to the signal number constants for most Linux systems.
#define SIGSTKFLT	16	 Stack fault (obsolete).
#define SIGPWR		30	 Power failure imminent.
 Historical signals specified by POSIX.
#define SIGBUS		 7	 Bus error.
#define SIGSYS		31	 Bad system call.
 New(er) POSIX signals (1003.1-2008, 1003.1-2013).
#define SIGURG		23	 Urgent data is available at a socket.
#define SIGSTOP		19	 Stop, unblockable.
#define SIGTSTP		20	 Keyboard stop.
#define SIGCONT		18	 Continue.
#define SIGCHLD		17	 Child terminated or stopped.
#define SIGTTIN		21	 Background read from control terminal.
#define SIGTTOU		22	 Background write to control terminal.
#define SIGPOLL		29	 Pollable event occurred (System V).
#define SIGXFSZ		25	 File size limit exceeded.
#define SIGXCPU		24	 CPU time limit exceeded.
#define SIGVTALRM	26	 Virtual timer expired.
#define SIGPROF		27	 Profiling timer expired.
#define SIGUSR1		10	 User-defined signal 1.
#define SIGUSR2		12	 User-defined signal 2.
 Nonstandard signals found in all modern POSIX systems
   (including both BSD and Linux).
#define SIGWINCH	28	 Window size change (4.3 BSD, Sun).
 Archaic names for compatibility.
#define SIGIO		SIGPOLL	 I/O now possible (4.2 BSD).
#define SIGIOT		SIGABRT	 IOT instruction, abort() on a PDP-11.
#define SIGCLD		SIGCHLD	 Old System V name
#define __SIGRTMIN	32
#define __SIGRTMAX	64
*/
auto crash_signals_register() -> void {
    std::signal( SIGHUP,  crash_tracer );
    std::signal( SIGINT,  crash_tracer );
    std::signal( SIGQUIT, crash_tracer );
    std::signal( SIGILL,  crash_tracer );
    std::signal( SIGTRAP, crash_tracer );
    std::signal( SIGABRT, crash_tracer_SIGABRT );
    std::signal( SIGSEGV, crash_tracer );
}
} // End Namespace NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
// ++++++++++++++++ EXAMPLEs begin ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace Example1 { // NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN

constexpr uint_least8_t      US_ASCII_NUM_BITS{7};  // 2^7 == 128 values, zero origin

const std::vector            PASS_PHRASE_NUM_WORDSX{12, 15, 18, 21, 24}; //TODO??: why not?: constexpr
constexpr std::array<int, 5> PASS_PHRASE_NUM_WORDS{ 12, 15, 18, 21, 24 }; // Enlish words only 1st 4 chars count.
constexpr uint_least16_t     PRIVATE_KEY_NUM_BITS{ 256 };
constexpr uint_least8_t      PRIVATE_KEY_NUM_BYTES{ (PRIVATE_KEY_NUM_BITS / 8) + (PRIVATE_KEY_NUM_BITS % 8 == 0 ? 0 : 1) };  // ie 32
constexpr uint_least8_t      COMPRESSED_PUBLIC_KEY_NUM_BYTES{
    33
}; // They only store the x coordinate and a prefix (0x02 or 0x03) indicating whether the y coordinate is even or odd. This is
   // possible because the elliptic curve math allows calculating the y coordinate from the x one. Uncompressed public key:  These
   // older keys are  65 bytes long. They contain both the x and y coordinates (each 256-bit integers) required to identify a point on
   // an elliptic curve for cryptographic operations.  A constant prefix (0x04) precedes this data.
constexpr std::array<std::string, 2048> WORDS{  // 2^10 words
    "abandon",  "ability",  "able",     "about",    "above",    "absent",   "absorb",   "abstract", "absurd",   "abuse",
    "access",   "accident", "account",  "accuse",   "achieve",  "acid",     "acoustic", "acquire",  "across",   "act",
    "action",   "actor",    "actress",  "actual",   "adapt",    "add",      "addict",   "address",  "adjust",   "admit",
    "adult",    "advance",  "advice",   "aerobic",  "affair",   "afford",   "afraid",   "again",    "age",      "agent",
    "agree",    "ahead",    "aim",      "air",      "airport",  "aisle",    "alarm",    "album",    "alcohol",  "alert",
    "alien",    "all",      "alley",    "allow",    "almost",   "alone",    "alpha",    "already",  "also",     "alter",
    "always",   "amateur",  "amazing",  "among",    "amount",   "amused",   "analyst",  "anchor",   "ancient",  "anger",
    "angle",    "angry",    "animal",   "ankle",    "announce", "annual",   "another",  "answer",   "antenna",  "antique",
    "anxiety",  "any",      "apart",    "apology",  "appear",   "apple",    "approve",  "april",    "arch",     "arctic",
    "area",     "arena",    "argue",    "arm",      "armed",    "armor",    "army",     "around",   "arrange",  "arrest",
    "arrive",   "arrow",    "art",      "artefact", "artist",   "artwork",  "ask",      "aspect",   "assault",  "asset",
    "assist",   "assume",   "asthma",   "athlete",  "atom",     "attack",   "attend",   "attitude", "attract",  "auction",
    "audit",    "august",   "aunt",     "author",   "auto",     "autumn",   "average",  "avocado",  "avoid",    "awake",
    "aware",    "away",     "awesome",  "awful",    "awkward",  "axis",     "baby",     "bachelor", "bacon",    "badge",
    "bag",      "balance",  "balcony",  "ball",     "bamboo",   "banana",   "banner",   "bar",      "barely",   "bargain",
    "barrel",   "base",     "basic",    "basket",   "battle",   "beach",    "bean",     "beauty",   "because",  "become",
    "beef",     "before",   "begin",    "behave",   "behind",   "believe",  "below",    "belt",     "bench",    "benefit",
    "best",     "betray",   "better",   "between",  "beyond",   "bicycle",  "bid",      "bike",     "bind",     "biology",
    "bird",     "birth",    "bitter",   "black",    "blade",    "blame",    "blanket",  "blast",    "bleak",    "bless",
    "blind",    "blood",    "blossom",  "blouse",   "blue",     "blur",     "blush",    "board",    "boat",     "body",
    "boil",     "bomb",     "bone",     "bonus",    "book",     "boost",    "border",   "boring",   "borrow",   "boss",
    "bottom",   "bounce",   "box",      "boy",      "bracket",  "brain",    "brand",    "brass",    "brave",    "bread",
    "breeze",   "brick",    "bridge",   "brief",    "bright",   "bring",    "brisk",    "broccoli", "broken",   "bronze",
    "broom",    "brother",  "brown",    "brush",    "bubble",   "buddy",    "budget",   "buffalo",  "build",    "bulb",
    "bulk",     "bullet",   "bundle",   "bunker",   "burden",   "burger",   "burst",    "bus",      "business", "busy",
    "butter",   "buyer",    "buzz",     "cabbage",  "cabin",    "cable",    "cactus",   "cage",     "cake",     "call",
    "calm",     "camera",   "camp",     "can",      "canal",    "cancel",   "candy",    "cannon",   "canoe",    "canvas",
    "canyon",   "capable",  "capital",  "captain",  "car",      "carbon",   "card",     "cargo",    "carpet",   "carry",
    "cart",     "case",     "cash",     "casino",   "castle",   "casual",   "cat",      "catalog",  "catch",    "category",
    "cattle",   "caught",   "cause",    "caution",  "cave",     "ceiling",  "celery",   "cement",   "census",   "century",
    "cereal",   "certain",  "chair",    "chalk",    "champion", "change",   "chaos",    "chapter",  "charge",   "chase",
    "chat",     "cheap",    "check",    "cheese",   "chef",     "cherry",   "chest",    "chicken",  "chief",    "child",
    "chimney",  "choice",   "choose",   "chronic",  "chuckle",  "chunk",    "churn",    "cigar",    "cinnamon", "circle",
    "citizen",  "city",     "civil",    "claim",    "clap",     "clarify",  "claw",     "clay",     "clean",    "clerk",
    "clever",   "click",    "client",   "cliff",    "climb",    "clinic",   "clip",     "clock",    "clog",     "close",
    "cloth",    "cloud",    "clown",    "club",     "clump",    "cluster",  "clutch",   "coach",    "coast",    "coconut",
    "code",     "coffee",   "coil",     "coin",     "collect",  "color",    "column",   "combine",  "come",     "comfort",
    "comic",    "common",   "company",  "concert",  "conduct",  "confirm",  "congress", "connect",  "consider", "control",
    "convince", "cook",     "cool",     "copper",   "copy",     "coral",    "core",     "corn",     "correct",  "cost",
    "cotton",   "couch",    "country",  "couple",   "course",   "cousin",   "cover",    "coyote",   "crack",    "cradle",
    "craft",    "cram",     "crane",    "crash",    "crater",   "crawl",    "crazy",    "cream",    "credit",   "creek",
    "crew",     "cricket",  "crime",    "crisp",    "critic",   "crop",     "cross",    "crouch",   "crowd",    "crucial",
    "cruel",    "cruise",   "crumble",  "crunch",   "crush",    "cry",      "crystal",  "cube",     "culture",  "cup",
    "cupboard", "curious",  "current",  "curtain",  "curve",    "cushion",  "custom",   "cute",     "cycle",    "dad",
    "damage",   "damp",     "dance",    "danger",   "daring",   "dash",     "daughter", "dawn",     "day",      "deal",
    "debate",   "debris",   "decade",   "december", "decide",   "decline",  "decorate", "decrease", "deer",     "defense",
    "define",   "defy",     "degree",   "delay",    "deliver",  "demand",   "demise",   "denial",   "dentist",  "deny",
    "depart",   "depend",   "deposit",  "depth",    "deputy",   "derive",   "describe", "desert",   "design",   "desk",
    "despair",  "destroy",  "detail",   "detect",   "develop",  "device",   "devote",   "diagram",  "dial",     "diamond",
    "diary",    "dice",     "diesel",   "diet",     "differ",   "digital",  "dignity",  "dilemma",  "dinner",   "dinosaur",
    "direct",   "dirt",     "disagree", "discover", "disease",  "dish",     "dismiss",  "disorder", "display",  "distance",
    "divert",   "divide",   "divorce",  "dizzy",    "doctor",   "document", "dog",      "doll",     "dolphin",  "domain",
    "donate",   "donkey",   "donor",    "door",     "dose",     "double",   "dove",     "draft",    "dragon",   "drama",
    "drastic",  "draw",     "dream",    "dress",    "drift",    "drill",    "drink",    "drip",     "drive",    "drop",
    "drum",     "dry",      "duck",     "dumb",     "dune",     "during",   "dust",     "dutch",    "duty",     "dwarf",
    "dynamic",  "eager",    "eagle",    "early",    "earn",     "earth",    "easily",   "east",     "easy",     "echo",
    "ecology",  "economy",  "edge",     "edit",     "educate",  "effort",   "egg",      "eight",    "either",   "elbow",
    "elder",    "electric", "elegant",  "element",  "elephant", "elevator", "elite",    "else",     "embark",   "embody",
    "embrace",  "emerge",   "emotion",  "employ",   "empower",  "empty",    "enable",   "enact",    "end",      "endless",
    "endorse",  "enemy",    "energy",   "enforce",  "engage",   "engine",   "enhance",  "enjoy",    "enlist",   "enough",
    "enrich",   "enroll",   "ensure",   "enter",    "entire",   "entry",    "envelope", "episode",  "equal",    "equip",
    "era",      "erase",    "erode",    "erosion",  "error",    "erupt",    "escape",   "essay",    "essence",  "estate",
    "eternal",  "ethics",   "evidence", "evil",     "evoke",    "evolve",   "exact",    "example",  "excess",   "exchange",
    "excite",   "exclude",  "excuse",   "execute",  "exercise", "exhaust",  "exhibit",  "exile",    "exist",    "exit",
    "exotic",   "expand",   "expect",   "expire",   "explain",  "expose",   "express",  "extend",   "extra",    "eye",
    "eyebrow",  "fabric",   "face",     "faculty",  "fade",     "faint",    "faith",    "fall",     "false",    "fame",
    "family",   "famous",   "fan",      "fancy",    "fantasy",  "farm",     "fashion",  "fat",      "fatal",    "father",
    "fatigue",  "fault",    "favorite", "feature",  "february", "federal",  "fee",      "feed",     "feel",     "female",
    "fence",    "festival", "fetch",    "fever",    "few",      "fiber",    "fiction",  "field",    "figure",   "file",
    "film",     "filter",   "final",    "find",     "fine",     "finger",   "finish",   "fire",     "firm",     "first",
    "fiscal",   "fish",     "fit",      "fitness",  "fix",      "flag",     "flame",    "flash",    "flat",     "flavor",
    "flee",     "flight",   "flip",     "float",    "flock",    "floor",    "flower",   "fluid",    "flush",    "fly",
    "foam",     "focus",    "fog",      "foil",     "fold",     "follow",   "food",     "foot",     "force",    "forest",
    "forget",   "fork",     "fortune",  "forum",    "forward",  "fossil",   "foster",   "found",    "fox",      "fragile",
    "frame",    "frequent", "fresh",    "friend",   "fringe",   "frog",     "front",    "frost",    "frown",    "frozen",
    "fruit",    "fuel",     "fun",      "funny",    "furnace",  "fury",     "future",   "gadget",   "gain",     "galaxy",
    "gallery",  "game",     "gap",      "garage",   "garbage",  "garden",   "garlic",   "garment",  "gas",      "gasp",
    "gate",     "gather",   "gauge",    "gaze",     "general",  "genius",   "genre",    "gentle",   "genuine",  "gesture",
    "ghost",    "giant",    "gift",     "giggle",   "ginger",   "giraffe",  "girl",     "give",     "glad",     "glance",
    "glare",    "glass",    "glide",    "glimpse",  "globe",    "gloom",    "glory",    "glove",    "glow",     "glue",
    "goat",     "goddess",  "gold",     "good",     "goose",    "gorilla",  "gospel",   "gossip",   "govern",   "gown",
    "grab",     "grace",    "grain",    "grant",    "grape",    "grass",    "gravity",  "great",    "green",    "grid",
    "grief",    "grit",     "grocery",  "group",    "grow",     "grunt",    "guard",    "guess",    "guide",    "guilt",
    "guitar",   "gun",      "gym",      "habit",    "hair",     "half",     "hammer",   "hamster",  "hand",     "happy",
    "harbor",   "hard",     "harsh",    "harvest",  "hat",      "have",     "hawk",     "hazard",   "head",     "health",
    "heart",    "heavy",    "hedgehog", "height",   "hello",    "helmet",   "help",     "hen",      "hero",     "hidden",
    "high",     "hill",     "hint",     "hip",      "hire",     "history",  "hobby",    "hockey",   "hold",     "hole",
    "holiday",  "hollow",   "home",     "honey",    "hood",     "hope",     "horn",     "horror",   "horse",    "hospital",
    "host",     "hotel",    "hour",     "hover",    "hub",      "huge",     "human",    "humble",   "humor",    "hundred",
    "hungry",   "hunt",     "hurdle",   "hurry",    "hurt",     "husband",  "hybrid",   "ice",      "icon",     "idea",
    "identify", "idle",     "ignore",   "ill",      "illegal",  "illness",  "image",    "imitate",  "immense",  "immune",
    "impact",   "impose",   "improve",  "impulse",  "inch",     "include",  "income",   "increase", "index",    "indicate",
    "indoor",   "industry", "infant",   "inflict",  "inform",   "inhale",   "inherit",  "initial",  "inject",   "injury",
    "inmate",   "inner",    "innocent", "input",    "inquiry",  "insane",   "insect",   "inside",   "inspire",  "install",
    "intact",   "interest", "into",     "invest",   "invite",   "involve",  "iron",     "island",   "isolate",  "issue",
    "item",     "ivory",    "jacket",   "jaguar",   "jar",      "jazz",     "jealous",  "jeans",    "jelly",    "jewel",
    "job",      "join",     "joke",     "journey",  "joy",      "judge",    "juice",    "jump",     "jungle",   "junior",
    "junk",     "just",     "kangaroo", "keen",     "keep",     "ketchup",  "key",      "kick",     "kid",      "kidney",
    "kind",     "kingdom",  "kiss",     "kit",      "kitchen",  "kite",     "kitten",   "kiwi",     "knee",     "knife",
    "knock",    "know",     "lab",      "label",    "labor",    "ladder",   "lady",     "lake",     "lamp",     "language",
    "laptop",   "large",    "later",    "latin",    "laugh",    "laundry",  "lava",     "law",      "lawn",     "lawsuit",
    "layer",    "lazy",     "leader",   "leaf",     "learn",    "leave",    "lecture",  "left",     "leg",      "legal",
    "legend",   "leisure",  "lemon",    "lend",     "length",   "lens",     "leopard",  "lesson",   "letter",   "level",
    "liar",     "liberty",  "library",  "license",  "life",     "lift",     "light",    "like",     "limb",     "limit",
    "link",     "lion",     "liquid",   "list",     "little",   "live",     "lizard",   "load",     "loan",     "lobster",
    "local",    "lock",     "logic",    "lonely",   "long",     "loop",     "lottery",  "loud",     "lounge",   "love",
    "loyal",    "lucky",    "luggage",  "lumber",   "lunar",    "lunch",    "luxury",   "lyrics",   "machine",  "mad",
    "magic",    "magnet",   "maid",     "mail",     "main",     "major",    "make",     "mammal",   "man",      "manage",
    "mandate",  "mango",    "mansion",  "manual",   "maple",    "marble",   "march",    "margin",   "marine",   "market",
    "marriage", "mask",     "mass",     "master",   "match",    "material", "math",     "matrix",   "matter",   "maximum",
    "maze",     "meadow",   "mean",     "measure",  "meat",     "mechanic", "medal",    "media",    "melody",   "melt",
    "member",   "memory",   "mention",  "menu",     "mercy",    "merge",    "merit",    "merry",    "mesh",     "message",
    "metal",    "method",   "middle",   "midnight", "milk",     "million",  "mimic",    "mind",     "minimum",  "minor",
    "minute",   "miracle",  "mirror",   "misery",   "miss",     "mistake",  "mix",      "mixed",    "mixture",  "mobile",
    "model",    "modify",   "mom",      "moment",   "monitor",  "monkey",   "monster",  "month",    "moon",     "moral",
    "more",     "morning",  "mosquito", "mother",   "motion",   "motor",    "mountain", "mouse",    "move",     "movie",
    "much",     "muffin",   "mule",     "multiply", "muscle",   "museum",   "mushroom", "music",    "must",     "mutual",
    "myself",   "mystery",  "myth",     "naive",    "name",     "napkin",   "narrow",   "nasty",    "nation",   "nature",
    "near",     "neck",     "need",     "negative", "neglect",  "neither",  "nephew",   "nerve",    "nest",     "net",
    "network",  "neutral",  "never",    "news",     "next",     "nice",     "night",    "noble",    "noise",    "nominee",
    "noodle",   "normal",   "north",    "nose",     "notable",  "note",     "nothing",  "notice",   "novel",    "now",
    "nuclear",  "number",   "nurse",    "nut",      "oak",      "obey",     "object",   "oblige",   "obscure",  "observe",
    "obtain",   "obvious",  "occur",    "ocean",    "october",  "odor",     "off",      "offer",    "office",   "often",
    "oil",      "okay",     "old",      "olive",    "olympic",  "omit",     "once",     "one",      "onion",    "online",
    "only",     "open",     "opera",    "opinion",  "oppose",   "option",   "orange",   "orbit",    "orchard",  "order",
    "ordinary", "organ",    "orient",   "original", "orphan",   "ostrich",  "other",    "outdoor",  "outer",    "output",
    "outside",  "oval",     "oven",     "over",     "own",      "owner",    "oxygen",   "oyster",   "ozone",    "pact",
    "paddle",   "page",     "pair",     "palace",   "palm",     "panda",    "panel",    "panic",    "panther",  "paper",
    "parade",   "parent",   "park",     "parrot",   "party",    "pass",     "patch",    "path",     "patient",  "patrol",
    "pattern",  "pause",    "pave",     "payment",  "peace",    "peanut",   "pear",     "peasant",  "pelican",  "pen",
    "penalty",  "pencil",   "people",   "pepper",   "perfect",  "permit",   "person",   "pet",      "phone",    "photo",
    "phrase",   "physical", "piano",    "picnic",   "picture",  "piece",    "pig",      "pigeon",   "pill",     "pilot",
    "pink",     "pioneer",  "pipe",     "pistol",   "pitch",    "pizza",    "place",    "planet",   "plastic",  "plate",
    "play",     "please",   "pledge",   "pluck",    "plug",     "plunge",   "poem",     "poet",     "point",    "polar",
    "pole",     "police",   "pond",     "pony",     "pool",     "popular",  "portion",  "position", "possible", "post",
    "potato",   "pottery",  "poverty",  "powder",   "power",    "practice", "praise",   "predict",  "prefer",   "prepare",
    "present",  "pretty",   "prevent",  "price",    "pride",    "primary",  "print",    "priority", "prison",   "private",
    "prize",    "problem",  "process",  "produce",  "profit",   "program",  "project",  "promote",  "proof",    "property",
    "prosper",  "protect",  "proud",    "provide",  "public",   "pudding",  "pull",     "pulp",     "pulse",    "pumpkin",
    "punch",    "pupil",    "puppy",    "purchase", "purity",   "purpose",  "purse",    "push",     "put",      "puzzle",
    "pyramid",  "quality",  "quantum",  "quarter",  "question", "quick",    "quit",     "quiz",     "quote",    "rabbit",
    "raccoon",  "race",     "rack",     "radar",    "radio",    "rail",     "rain",     "raise",    "rally",    "ramp",
    "ranch",    "random",   "range",    "rapid",    "rare",     "rate",     "rather",   "raven",    "raw",      "razor",
    "ready",    "real",     "reason",   "rebel",    "rebuild",  "recall",   "receive",  "recipe",   "record",   "recycle",
    "reduce",   "reflect",  "reform",   "refuse",   "region",   "regret",   "regular",  "reject",   "relax",    "release",
    "relief",   "rely",     "remain",   "remember", "remind",   "remove",   "render",   "renew",    "rent",     "reopen",
    "repair",   "repeat",   "replace",  "report",   "require",  "rescue",   "resemble", "resist",   "resource", "response",
    "result",   "retire",   "retreat",  "return",   "reunion",  "reveal",   "review",   "reward",   "rhythm",   "rib",
    "ribbon",   "rice",     "rich",     "ride",     "ridge",    "rifle",    "right",    "rigid",    "ring",     "riot",
    "ripple",   "risk",     "ritual",   "rival",    "river",    "road",     "roast",    "robot",    "robust",   "rocket",
    "romance",  "roof",     "rookie",   "room",     "rose",     "rotate",   "rough",    "round",    "route",    "royal",
    "rubber",   "rude",     "rug",      "rule",     "run",      "runway",   "rural",    "sad",      "saddle",   "sadness",
    "safe",     "sail",     "salad",    "salmon",   "salon",    "salt",     "salute",   "same",     "sample",   "sand",
    "satisfy",  "satoshi",  "sauce",    "sausage",  "save",     "say",      "scale",    "scan",     "scare",    "scatter",
    "scene",    "scheme",   "school",   "science",  "scissors", "scorpion", "scout",    "scrap",    "screen",   "script",
    "scrub",    "sea",      "search",   "season",   "seat",     "second",   "secret",   "section",  "security", "seed",
    "seek",     "segment",  "select",   "sell",     "seminar",  "senior",   "sense",    "sentence", "series",   "service",
    "session",  "settle",   "setup",    "seven",    "shadow",   "shaft",    "shallow",  "share",    "shed",     "shell",
    "sheriff",  "shield",   "shift",    "shine",    "ship",     "shiver",   "shock",    "shoe",     "shoot",    "shop",
    "short",    "shoulder", "shove",    "shrimp",   "shrug",    "shuffle",  "shy",      "sibling",  "sick",     "side",
    "siege",    "sight",    "sign",     "silent",   "silk",     "silly",    "silver",   "similar",  "simple",   "since",
    "sing",     "siren",    "sister",   "situate",  "six",      "size",     "skate",    "sketch",   "ski",      "skill",
    "skin",     "skirt",    "skull",    "slab",     "slam",     "sleep",    "slender",  "slice",    "slide",    "slight",
    "slim",     "slogan",   "slot",     "slow",     "slush",    "small",    "smart",    "smile",    "smoke",    "smooth",
    "snack",    "snake",    "snap",     "sniff",    "snow",     "soap",     "soccer",   "social",   "sock",     "soda",
    "soft",     "solar",    "soldier",  "solid",    "solution", "solve",    "someone",  "song",     "soon",     "sorry",
    "sort",     "soul",     "sound",    "soup",     "source",   "south",    "space",    "spare",    "spatial",  "spawn",
    "speak",    "special",  "speed",    "spell",    "spend",    "sphere",   "spice",    "spider",   "spike",    "spin",
    "spirit",   "split",    "spoil",    "sponsor",  "spoon",    "sport",    "spot",     "spray",    "spread",   "spring",
    "spy",      "square",   "squeeze",  "squirrel", "stable",   "stadium",  "staff",    "stage",    "stairs",   "stamp",
    "stand",    "start",    "state",    "stay",     "steak",    "steel",    "stem",     "step",     "stereo",   "stick",
    "still",    "sting",    "stock",    "stomach",  "stone",    "stool",    "story",    "stove",    "strategy", "street",
    "strike",   "strong",   "struggle", "student",  "stuff",    "stumble",  "style",    "subject",  "submit",   "subway",
    "success",  "such",     "sudden",   "suffer",   "sugar",    "suggest",  "suit",     "summer",   "sun",      "sunny",
    "sunset",   "super",    "supply",   "supreme",  "sure",     "surface",  "surge",    "surprise", "surround", "survey",
    "suspect",  "sustain",  "swallow",  "swamp",    "swap",     "swarm",    "swear",    "sweet",    "swift",    "swim",
    "swing",    "switch",   "sword",    "symbol",   "symptom",  "syrup",    "system",   "table",    "tackle",   "tag",
    "tail",     "talent",   "talk",     "tank",     "tape",     "target",   "task",     "taste",    "tattoo",   "taxi",
    "teach",    "team",     "tell",     "ten",      "tenant",   "tennis",   "tent",     "term",     "test",     "text",
    "thank",    "that",     "theme",    "then",     "theory",   "there",    "they",     "thing",    "this",     "thought",
    "three",    "thrive",   "throw",    "thumb",    "thunder",  "ticket",   "tide",     "tiger",    "tilt",     "timber",
    "time",     "tiny",     "tip",      "tired",    "tissue",   "title",    "toast",    "tobacco",  "today",    "toddler",
    "toe",      "together", "toilet",   "token",    "tomato",   "tomorrow", "tone",     "tongue",   "tonight",  "tool",
    "tooth",    "top",      "topic",    "topple",   "torch",    "tornado",  "tortoise", "toss",     "total",    "tourist",
    "toward",   "tower",    "town",     "toy",      "track",    "trade",    "traffic",  "tragic",   "train",    "transfer",
    "trap",     "trash",    "travel",   "tray",     "treat",    "tree",     "trend",    "trial",    "tribe",    "trick",
    "trigger",  "trim",     "trip",     "trophy",   "trouble",  "truck",    "true",     "truly",    "trumpet",  "trust",
    "truth",    "try",      "tube",     "tuition",  "tumble",   "tuna",     "tunnel",   "turkey",   "turn",     "turtle",
    "twelve",   "twenty",   "twice",    "twin",     "twist",    "two",      "type",     "typical",  "ugly",     "umbrella",
    "unable",   "unaware",  "uncle",    "uncover",  "under",    "undo",     "unfair",   "unfold",   "unhappy",  "uniform",
    "unique",   "unit",     "universe", "unknown",  "unlock",   "until",    "unusual",  "unveil",   "update",   "upgrade",
    "uphold",   "upon",     "upper",    "upset",    "urban",    "urge",     "usage",    "use",      "used",     "useful",
    "useless",  "usual",    "utility",  "vacant",   "vacuum",   "vague",    "valid",    "valley",   "valve",    "van",
    "vanish",   "vapor",    "various",  "vast",     "vault",    "vehicle",  "velvet",   "vendor",   "venture",  "venue",
    "verb",     "verify",   "version",  "very",     "vessel",   "veteran",  "viable",   "vibrant",  "vicious",  "victory",
    "video",    "view",     "village",  "vintage",  "violin",   "virtual",  "virus",    "visa",     "visit",    "visual",
    "vital",    "vivid",    "vocal",    "voice",    "void",     "volcano",  "volume",   "vote",     "voyage",   "wage",
    "wagon",    "wait",     "walk",     "wall",     "walnut",   "want",     "warfare",  "warm",     "warrior",  "wash",
    "wasp",     "waste",    "water",    "wave",     "way",      "wealth",   "weapon",   "wear",     "weasel",   "weather",
    "web",      "wedding",  "weekend",  "weird",    "welcome",  "west",     "wet",      "whale",    "what",     "wheat",
    "wheel",    "when",     "where",    "whip",     "whisper",  "wide",     "width",    "wife",     "wild",     "will",
    "win",      "window",   "wine",     "wing",     "wink",     "winner",   "winter",   "wire",     "wisdom",   "wise",
    "wish",     "witness",  "wolf",     "woman",    "wonder",   "wood",     "wool",     "word",     "work",     "world",
    "worry",    "worth",    "wrap",     "wreck",    "wrestle",  "wrist",    "write",    "wrong",    "yard",     "year",
    "yellow",   "you",      "young",    "youth",    "zebra",    "zero",     "zone",     "zoo"
};

template <typename T>  // Gen AI answer
void packBits(const std::vector<T>& data, std::vector<bool>& container) {
    // Check if input data size is a multiple of 4 (number of 6-bit objects per byte)
    if (data.size() % 4 != 0) {
        throw std::invalid_argument("Input data size must be a multiple of 4");
    }

           // Iterate over the input data 4 elements at a time
    for (size_t i = 0; i < data.size(); i += 4) {
        // Extract 6 bits from each data element
        unsigned char byte =
            ((data[i] & 0x3F) << 6) |  // Shift first element by 6 bits
            ((data[i + 1] & 0x3F) << 3) |  // Shift second element by 3 bits
            ((data[i + 2] & 0x3F) << 0);   // No shift for third element

        // Add each bit of the byte to the container
        for (int j = 7; j >= 0; --j) {
            container.push_back((byte >> j) & 1);
        }
    }
}

void shift6BitObjectIntoContainer(std::vector<bool>& container, int start, int object) {  // Gen AI answer
    if (start + 6 > container.size()) {
        throw std::invalid_argument("Not enough space in the container to hold the 6-bit object.");
    }

    for (int i = 0; i < 6; ++i) {
        container[start + i] = (object >> (5 - i)) & 1;
    }
}

void test1 () {                     std::cout<< "START                Example1 test1. ++++++++++++++++++++++++"<<std::endl;
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    struct Counter {
        std::array<uint8_t, 32> words_single_char{ 'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        //  std::rand()/ ((RAND_MAX + 1u) / 256),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W',
                                        // static_cast<uint8_t> ( std::rand()/ ((RAND_MAX + 1u) / 256)),
                                        'W' };
        //  '.' };  // or more words, they will simply be ignored
    };
    Counter counter{};
    cout<< "W: 101 0111.\n"; cout<< "Counter.words_.size():" << counter.words_single_char.size() << ", list:" << counter.words_single_char << endl;

    // construct binary key
    std::bitset<132> chars_bits{};
    for ( size_t i{0}; i < chars_bits.size()/6; ++i) {
        chars_bits <<= 6;

        using bits6_ut = struct { uint8_t bits6_ :6; };
        struct bits6_st { uint8_t bits6_ :6; };
        bits6_ut tempu {static_cast<bits6_ut>(counter.words_single_char.at(i))};
        bits6_st temps {static_cast<bits6_st>(counter.words_single_char.at(i))};

        std::bitset<6>   char_bits6{counter.words_single_char.at(i)};
        std::bitset<132> char_bits132 {char_bits6.to_ulong()};
        std::bitset<132> char_bits132x{counter.words_single_char.at(i)};
        //chars_bits |= char_bits6;  // TODO??: Strange error message with &bits6_ut ?
        chars_bits |= char_bits132;
        //chars_bits |= char_bits132x;
        cout << "counter:" << std::setw(3)<< i << "," << chars_bits << ".\n";
    }
    std::cout<< "END                  Example1 test1. ++++++++++++++++++++++++"<<std::endl;
} } // END namespace NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNcounter.words_.size() << endl;

int main(int argc, char* arv[]) { string my_arv{*arv}; cout << "~~~ argc, argv:"<<argc<<","<<my_arv<<"."<<endl; cin.exceptions( std::istream::failbit); Detail::crash_signals_register();

    Example1::test1 ();

    cout << "###" << endl;
    return EXIT_SUCCESS;
}
