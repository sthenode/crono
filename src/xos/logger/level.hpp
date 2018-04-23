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
///   File: level.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_LEVEL_HPP
#define _XOS_LOGGER_LEVEL_HPP

#include "xos/base/base.hpp"

namespace xos {
namespace logger {

class _EXPORT_CLASS level: virtual public implement_base, public base {
public:
    typedef implement_base implements;
    typedef base extends;

    typedef unsigned enable;
    enum {
        none  = 0,

        fatal = 1,
        error = (fatal << 1),
        warn  = (error << 1),
        info  = (warn << 1),
        debug = (info << 1),
        trace = (debug << 1),

        next  = (trace << 1),
        all   = (next - 1),
        last  = (next >> 1),
        first = (fatal),
        
        message_fatal = (last << 1),
        message_error = (message_fatal << 1),
        message_warn  = (message_error << 1),
        message_info  = (message_warn << 1),
        message_debug = (message_info << 1),
        message_trace = (message_debug << 1),

        message_next  = (message_trace << 1),
        message_all   = (all << next),
        message_last  = (message_next >> 1),
        message_first = (message_fatal),
   
        fatal_message = message_fatal,
        error_message = message_error,
        warn_message = message_warn,
        info_message = message_info,
        debug_message = message_debug,
        trace_message = message_trace
    };

    level(const level& copy): enable_(copy.enable_) {        
    }
    level(enable _enable): enable_(_enable) {
    }
    level(): enable_(none) {
    }

    virtual level& operator = (enable _enable) {
        enable_ = _enable;
        return *this;
    }
    virtual operator enable() const {
        return enable_;
    }

protected:
    enable enable_;
};

class _EXPORT_CLASS levels: virtual public implement_base, public base {
public:
    typedef implement_base implements;
    typedef base extends;

    typedef unsigned enable;
    enum {
        none  = 0,

        fatal = 1,
        error = (((fatal + 1) << 1) - 1),
        warn  = (((error + 1) << 1) - 1),
        info  = (((warn + 1) << 1) - 1),
        debug = (((info + 1) << 1) - 1),
        trace = (((debug + 1) << 1) - 1),

        all = trace,

        message_none  = 0,

        message_fatal = (fatal << trace),
        message_error = (error << trace),
        message_warn  = (warn << trace),
        message_info  = (info << trace),
        message_debug = (debug << trace),
        message_trace = (trace << trace),

        message_all = message_trace
    };

    levels(const levels& copy): enable_(copy.enable_) {        
    }
    levels(enable _enable): enable_(_enable) {
    }
    levels(): enable_(none) {
    }

    virtual levels& operator = (enable _enable) {
        enable_ = _enable;
        return *this;
    }
    virtual operator enable() const {
        return enable_;
    }

protected:
    enable enable_;
};

} /// namespace logger
} /// namespace xos

#define XOS_LOGGING_LEVELS ::xos::logger::level::enable

#define XOS_LOGGING_LEVELS_ALL ::xos::logger::levels::all
#define XOS_LOGGING_LEVELS_NONE ::xos::logger::levels::none
#define XOS_LOGGING_LEVELS_FATAL ::xos::logger::levels::fatal
#define XOS_LOGGING_LEVELS_ERROR ::xos::logger::levels::error
#define XOS_LOGGING_LEVELS_WARN ::xos::logger::levels::warn
#define XOS_LOGGING_LEVELS_INFO ::xos::logger::levels::info
#define XOS_LOGGING_LEVELS_DEBUG ::xos::logger::levels::debug
#define XOS_LOGGING_LEVELS_TRACE ::xos::logger::levels::trace

#define XOS_LOGGING_LEVELS_MESSAGE_ALL ::xos::logger::levels::message_all
#define XOS_LOGGING_LEVELS_MESSAGE_NONE ::xos::logger::levels::message_none
#define XOS_LOGGING_LEVELS_MESSAGE_FATAL ::xos::logger::levels::message_fatal
#define XOS_LOGGING_LEVELS_MESSAGE_ERROR ::xos::logger::levels::message_error
#define XOS_LOGGING_LEVELS_MESSAGE_WARN ::xos::logger::levels::message_warn
#define XOS_LOGGING_LEVELS_MESSAGE_INFO ::xos::logger::levels::message_info
#define XOS_LOGGING_LEVELS_MESSAGE_DEBUG ::xos::logger::levels::message_debug
#define XOS_LOGGING_LEVELS_MESSAGE_TRACE ::xos::logger::levels::message_trace

#define XOS_LOGGING_LEVELS_ALL_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_ALL
#define XOS_LOGGING_LEVELS_NONE_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_NONE
#define XOS_LOGGING_LEVELS_FATAL_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_FATAL
#define XOS_LOGGING_LEVELS_ERROR_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_ERROR
#define XOS_LOGGING_LEVELS_WARN_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_WARN
#define XOS_LOGGING_LEVELS_INFO_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_INFO
#define XOS_LOGGING_LEVELS_DEBUG_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_DEBUG
#define XOS_LOGGING_LEVELS_TRACE_MESSAGE XOS_LOGGING_LEVELS_MESSAGE_TRACE

#if !defined(XOS_LOGGING_LEVELS_DEFAULT)
#if defined(TRACE_BUILD)
#define XOS_LOGGING_LEVELS_DEFAULT XOS_LOGGING_LEVELS_TRACE
#else // defined(TRACE_BUILD)
#if defined(DEBUG_BUILD)
#define XOS_LOGGING_LEVELS_DEFAULT XOS_LOGGING_LEVELS_DEBUG
#else // defined(DEBUG_BUILD)
#define XOS_LOGGING_LEVELS_DEFAULT XOS_LOGGING_LEVELS_ERROR
#endif // defined(DEBUG_BUILD)
#endif // defined(TRACE_BUILD)
#endif // !defined(XOS_LOGGING_LEVELS_DEFAULT)

#if !defined(XOS_DEFAULT_LOGGING_LEVELS)
#define XOS_DEFAULT_LOGGING_LEVELS XOS_LOGGING_LEVELS_DEFAULT
#endif // !defined(XOS_DEFAULT_LOGGING_LEVELS)

#endif /// _XOS_LOGGER_LEVEL_HPP 
        

