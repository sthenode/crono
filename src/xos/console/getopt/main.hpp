///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: main.hpp
///
/// Author: $author$
///   Date: 4/29/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_CONSOLE_GETOPT_MAIN_HPP
#define _XOS_CONSOLE_GETOPT_MAIN_HPP

#include "xos/console/getopt/main_opt.hpp"
#include "xos/io/logger.hpp"

#define XOS_CONSOLE_MAIN_LOGGING_OPT "logging-level"
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED MAIN_OPT_ARGUMENT_REQUIRED
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT 0
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG "{(a)all | (n)none | (f)fatal | (e)error | (w)waring | (i)info | (d)debug | (t)trace}"
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ALL 'a'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_NONE 'n'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_FATAL 'f'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ERROR 'e'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_WARN 'w'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_INFO 'i'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_DEBUG 'd'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_TRACE 't'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL 'F'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR 'E'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN 'W'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO 'I'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG 'D'
#define XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE 'T'
#define XOS_CONSOLE_MAIN_LOGGING_OPTUSE ""
#define XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S "l:"
#define XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C 'l'
#define XOS_CONSOLE_MAIN_LOGGING_OPTION \
   {XOS_CONSOLE_MAIN_LOGGING_OPT, \
    XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C}, \

#define XOS_CONSOLE_MAIN_DEBUG_OPT "debug"
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG_REQUIRED XOS_CONSOLE_MAIN_LOGGING_OPTARG_REQUIRED
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG_RESULT XOS_CONSOLE_MAIN_LOGGING_OPTARG_RESULT
#define XOS_CONSOLE_MAIN_DEBUG_OPTARG XOS_CONSOLE_MAIN_LOGGING_OPTARG
#define XOS_CONSOLE_MAIN_DEBUG_OPTUSE XOS_CONSOLE_MAIN_LOGGING_OPTUSE
#define XOS_CONSOLE_MAIN_DEBUG_OPTVAL_S "d:"
#define XOS_CONSOLE_MAIN_DEBUG_OPTVAL_C 'd'
#define XOS_CONSOLE_MAIN_DEBUG_OPTION \
   {XOS_CONSOLE_MAIN_DEBUG_OPT, \
    XOS_CONSOLE_MAIN_DEBUG_OPTARG_REQUIRED, \
    XOS_CONSOLE_MAIN_DEBUG_OPTARG_RESULT, \
    XOS_CONSOLE_MAIN_DEBUG_OPTVAL_C}, \

#define CRONO_CONSOLE_MAIN_OPTIONS_CHARS \
    XOS_CONSOLE_MAIN_LOGGING_OPTVAL_S \
    XOS_CONSOLE_MAIN_HELP_OPTVAL_S

#define CRONO_CONSOLE_MAIN_OPTIONS_OPTIONS \
    XOS_CONSOLE_MAIN_LOGGING_OPTION \
    XOS_CONSOLE_MAIN_HELP_OPTION

namespace xos {
namespace console {
namespace getopt {

typedef main_opt::implements maint_implements;
typedef main_opt maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template <class TImplements = maint_implements, class TExtends = maint_extends>
class _EXPORT_CLASS maint: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    
    typedef typename implements::file_t file_t;
    typedef typename implements::null_file_t null_file_t;
    enum { null_file = implements::null_file};
    
    typedef typename implements::string_t string_t;
    typedef typename implements::char_t char_t;
    typedef typename implements::end_char_t end_char_t;
    enum { end_char = implements::end_char };

    maint() {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy) {
    }
    
protected:
    virtual int on_logging_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        char c = 0;
        if ((optarg) && (c = optarg[0]) && (!optarg[1])) {
            switch(c) {

            case '7':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ALL:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ALL | XOS_LOGGING_LEVELS_MESSAGE_ALL);
                break;
            case '0':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_NONE:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_NONE | XOS_LOGGING_LEVELS_MESSAGE_NONE);
                break;

            case '1':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_FATAL:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_FATAL | XOS_LOGGING_LEVELS_MESSAGE_FATAL);
                break;
            case '2':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_ERROR:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_ERROR);
                break;
            case '3':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_WARN:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_WARN | XOS_LOGGING_LEVELS_MESSAGE_WARN);
                break;
            case '4':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_INFO:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_INFO | XOS_LOGGING_LEVELS_MESSAGE_INFO);
                break;
            case '5':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_DEBUG:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_DEBUG | XOS_LOGGING_LEVELS_MESSAGE_DEBUG);
                break;
            case '6':
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_TRACE:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_TRACE | XOS_LOGGING_LEVELS_MESSAGE_TRACE);
                break;

            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_FATAL:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_FATAL | XOS_LOGGING_LEVELS_MESSAGE_FATAL);
                break;
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_ERROR:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_ERROR | XOS_LOGGING_LEVELS_MESSAGE_ERROR);
                break;
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_WARN:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_MESSAGE_WARN);
                break;
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_INFO:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_MESSAGE_INFO);
                break;
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_DEBUG:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_MESSAGE_DEBUG);
                break;
            case XOS_CONSOLE_MAIN_LOGGING_OPTARG_C_MESSAGE_TRACE:
                XOS_SET_LOGGING_LEVEL(XOS_LOGGING_LEVELS_MESSAGE_TRACE);
                break;

            default:
                err = this->on_invalid_option_arg
                (optval, optarg, optname, optind, argc, argv, env);
                break;
            }
        }
        return err;
    }
    virtual const char_t* logging_option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        optarg = XOS_CONSOLE_MAIN_LOGGING_OPTARG;
        chars = XOS_CONSOLE_MAIN_LOGGING_OPTUSE;
        return chars;
    }
    virtual int on_debug_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        err = on_logging_option
        (optval, optarg, optname, optind, argc, argv, env);
        return err;
    }
    virtual const char_t* debug_option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        chars = logging_option_usage(optarg, longopt);
        return chars;
    }
    virtual int on_option
    (int optval, const char_t* optarg,
     const char_t* optname, int optind,
     int argc, char_t**argv, char_t**env) {
        int err = 0;
        switch(optval) {
        case XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C:
            err = this->on_logging_option
            (optval, optarg, optname, optind, argc, argv, env);
            break;
        default:
            err = extends::on_option
            (optval, optarg, optname, optind, argc, argv, env);
        }
        return err;
    }
    virtual const char_t* option_usage
    (const char_t*& optarg, const struct option* longopt) {
        const char_t* chars = "";
        switch(longopt->val) {
        case XOS_CONSOLE_MAIN_LOGGING_OPTVAL_C:
            chars = logging_option_usage(optarg, longopt);
            break;
        default:
            chars = extends::option_usage(optarg, longopt);
            break;
        }
        return chars;
    }
    virtual const char_t* options(const struct option*& longopts) {
        static const char_t* chars = CRONO_CONSOLE_MAIN_OPTIONS_CHARS;
        static struct option optstruct[]= {
            CRONO_CONSOLE_MAIN_OPTIONS_OPTIONS
            {0, 0, 0, 0}};
        longopts = optstruct;
        return chars;
    }
};
typedef maint<> main;

} /// namespace getopt
} /// namespace console
} /// namespace xos

#endif /// _XOS_CONSOLE_GETOPT_MAIN_HPP 
