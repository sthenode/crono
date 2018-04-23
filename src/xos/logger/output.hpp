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
///   File: output.hpp
///
/// Author: $author$
///   Date: 4/9/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_LOGGER_OUTPUT_HPP
#define _XOS_LOGGER_OUTPUT_HPP

#include "xos/logger/message.hpp"

namespace xos {
namespace logger {

} /// namespace logger
} /// namespace xos

///
/// XOS_COSTREAM_LOG_ PLAIN  / FUNCTION / LOCATION
/// 
#define XOS_COSTREAM_LOG_PLAIN(ostream_, message_) \
{ ::xos::logger::message message; \
  ostream_ << message << message_ << "\n"; }

#define XOS_COSTREAM_LOG_FUNCTION(ostream_, message_) \
{ ::xos::logger::message message; \
  ostream_ << XOS_LOGGER_FUNCTION << ": " << message << message_ << "\n"; }

#define XOS_COSTREAM_LOG_LOCATION(ostream_, message_) \
{ ::xos::logger::location location = XOS_LOGGER_LOCATION; \
  ::xos::logger::message message; \
  ostream_ <<  location.file_name().chars() << "[" <<  location.line_number().chars() << "] " \
  <<  location.function_name().chars() << ": " << message << message_ << "\n"; }

///
/// XOS_STDSTREAM_LOG_ PLAIN  / FUNCTION / LOCATION
/// 
#define XOS_STDSTREAM_LOG_PLAIN(stream_, message_) \
{ ::xos::logger::message message; message << message_; \
  fprintf(stream_, "%s\n", message.chars()); fflush(stream_); }

#define XOS_STDSTREAM_LOG_FUNCTION(stream_, message_) \
{ ::xos::logger::function function = XOS_LOGGER_FUNCTION; \
  ::xos::logger::message message; message << message_; \
  fprintf(stream_, "%s: %s\n", function.chars(), message.chars()); fflush(stream_); }

#define XOS_STDSTREAM_LOG_LOCATION(stream_, message_) \
{ ::xos::logger::location location = XOS_LOGGER_LOCATION; \
  ::xos::logger::message message; message << message_; \
  fprintf(stream_, "%s[%s] %s: %s\n", location.file_name().chars(), \
  location.line_number().chars(), location.function_name().chars(), message.chars()); fflush(stream_); }

///
/// XOS_ CERR / STDERR _LOG_ PLAIN  / FUNCTION / LOCATION
/// 
#define XOS_CERR_LOG_PLAIN(message_) XOS_COSTREAM_LOG_PLAIN(::std::cerr, message_)
#define XOS_CERR_LOG_FUNCTION(message_) XOS_COSTREAM_LOG_FUNCTION(::std::cerr, message_)
#define XOS_CERR_LOG_LOCATION(message_) XOS_COSTREAM_LOG_LOCATION(::std::cerr, message_)
#define XOS_STDERR_LOG_PLAIN(message_) XOS_STDSTREAM_LOG_PLAIN(stderr, message_)
#define XOS_STDERR_LOG_FUNCTION(message_) XOS_STDSTREAM_LOG_FUNCTION(stderr, message_)
#define XOS_STDERR_LOG_LOCATION(message_) XOS_STDSTREAM_LOG_LOCATION(stderr, message_)

#if defined(XOS_CERR_LOGGING)
#define XOS_ERR_LOG_PLAIN XOS_CERR_LOG_PLAIN
#define XOS_ERR_LOG_FUNCTION XOS_CERR_LOG_FUNCTION
#define XOS_ERR_LOG_LOCATIONN XOS_CERR_LOG_LOCATION
#else /// defined(XOS_CERR_LOGGING)
#define XOS_ERR_LOG_PLAIN XOS_STDERR_LOG_PLAIN
#define XOS_ERR_LOG_FUNCTION XOS_STDERR_LOG_FUNCTION
#define XOS_ERR_LOG_LOCATIONN XOS_STDERR_LOG_LOCATION
#endif /// defined(XOS_CERR_LOGGING)

#if defined(XOS_PLAIN_LOGGING)
#define XOS_ERR_LOG XOS_ERR_LOG_PLAIN
#define XOS_CERR_LOG XOS_CERR_LOG_PLAIN
#define XOS_STDERR_LOG XOS_STDERR_LOG_PLAIN
#else /// defined(XOS_PLAIN_LOGGING)
#if defined(XOS_FUNCTION_LOGGING)
#define XOS_ERR_LOG XOS_ERR_LOG_FUNCTION
#define XOS_CERR_LOG XOS_CERR_LOG_FUNCTION
#define XOS_STDERR_LOG XOS_STDERR_LOG_FUNCTION
#else /// defined(XOS_FUNCTION_LOGGING)
#define XOS_ERR_LOG XOS_ERR_LOG_LOCATION
#define XOS_CERR_LOG XOS_CERR_LOG_LOCATION
#define XOS_STDERR_LOG XOS_STDERR_LOG_LOCATION
#endif /// defined(XOS_FUNCTION_LOGGING)
#endif /// defined(XOS_PLAIN_LOGGING)

///
/// XOS_IF_COSTREAM_LOG_ PLAIN  / FUNCTION / LOCATION
/// 
#define XOS_IF_COSTREAM_LOG_PLAIN(is_logged_, ostream_, message_) \
if ((is_logged_)) XOS_COSTREAM_LOG_PLAIN(ostream_, message_)

#define XOS_IF_COSTREAM_LOG_FUNCTION(is_logged_, ostream_, message_) \
if ((is_logged_)) XOS_COSTREAM_LOG_FUNCTION(ostream_, message_)

#define XOS_IF_COSTREAM_LOG_LOCATION(is_logged_, ostream_, message_) \
if ((is_logged_)) XOS_COSTREAM_LOG_LOCATION(ostream_, message_)

///
/// XOS_IF_STDSTREAM_LOG_ PLAIN  / FUNCTION / LOCATION
/// 
#define XOS_IF_STDSTREAM_LOG_PLAIN(is_logged_, stream_, message_) \
if ((is_logged_)) XOS_STDSTREAM_LOG_PLAIN(stream_, message_)

#define XOS_IF_STDSTREAM_LOG_FUNCTION(is_logged_, stream_, message_) \
if ((is_logged_)) XOS_STDSTREAM_LOG_FUNCTION(stream_, message_)

#define XOS_IF_STDSTREAM_LOG_LOCATION(is_logged_, stream_, message_) \
if ((is_logged_)) XOS_STDSTREAM_LOG_LOCATION(stream_, message_)

///
/// XOS_IF_ CERR / STDERR _LOG_ PLAIN / FUNCTION / LOCATION
/// 
#define XOS_IF_CERR_LOG_PLAIN(is_logged_, message_) XOS_IF_COSTREAM_LOG_PLAIN(is_logged_, ::std::cerr, message_)
#define XOS_IF_CERR_LOG_FUNCTION(is_logged_, message_) XOS_IF_COSTREAM_LOG_FUNCTION(is_logged_, ::std::cerr, message_)
#define XOS_IF_CERR_LOG_LOCATION(is_logged_, message_) XOS_IF_COSTREAM_LOG_LOCATION(is_logged_, ::std::cerr, message_)
#define XOS_IF_STDERR_LOG_PLAIN(is_logged_, message_) XOS_IF_STDSTREAM_LOG_PLAIN(is_logged_, stderr, message_)
#define XOS_IF_STDERR_LOG_FUNCTION(is_logged_, message_) XOS_IF_STDSTREAM_LOG_FUNCTION(is_logged_, stderr, message_)
#define XOS_IF_STDERR_LOG_LOCATION(is_logged_, message_) XOS_IF_STDSTREAM_LOG_LOCATION(is_logged_, stderr, message_)

#if defined(XOS_PLAIN_LOGGING)
#define XOS_IF_CERR_LOG XOS_IF_CERR_LOG_PLAIN
#define XOS_IF_STDERR_LOG XOS_IF_STDERR_LOG_PLAIN
#else /// defined(XOS_PLAIN_LOGGING)
#if defined(XOS_FUNCTION_LOGGING)
#define XOS_IF_CERR_LOG XOS_IF_CERR_LOG_FUNCTION
#define XOS_IF_STDERR_LOG XOS_IF_STDERR_LOG_FUNCTION
#else /// defined(XOS_FUNCTION_LOGGING)
#define XOS_IF_CERR_LOG XOS_IF_CERR_LOG_LOCATION
#define XOS_IF_STDERR_LOG XOS_IF_STDERR_LOG_LOCATION
#endif /// defined(XOS_FUNCTION_LOGGING)
#endif /// defined(XOS_PLAIN_LOGGING)

///
/// XOS_ CERR / STDERR _LOG_ TRACE / DEBUG / ERROR
/// 
#if defined(TRACE_BUILD)
#define XOS_CERR_LOG_TRACE(message_) XOS_CERR_LOG(message_)
#define XOS_STDERR_LOG_TRACE(message_) XOS_STDERR_LOG(message_)
#define XOS_CERR_LOG_PLAIN_TRACE(message_) XOS_CERR_LOG_PLAIN(message_)
#define XOS_STDERR_LOG_PLAIN_TRACE(message_) XOS_STDERR_LOG_PLAIN(message_)
#define XOS_CERR_LOG_FUNCTION_TRACE(message_) XOS_CERR_LOG_FUNCTION(message_)
#define XOS_STDERR_LOG_FUNCTION_TRACE(message_) XOS_STDERR_LOG_FUNCTION(message_)
#define XOS_CERR_LOG_LOCATION_TRACE(message_) XOS_CERR_LOG_LOCATION(message_)
#define XOS_STDERR_LOG_LOCATION_TRACE(message_) XOS_STDERR_LOG_LOCATION(message_)
#else /// defined(TRACE_BUILD)
#define XOS_CERR_LOG_TRACE(message_)
#define XOS_STDERR_LOG_TRACE(message_)
#define XOS_CERR_LOG_PLAIN_TRACE(message_)
#define XOS_STDERR_LOG_PLAIN_TRACE(message_)
#define XOS_CERR_LOG_FUNCTION_TRACE(message_)
#define XOS_STDERR_LOG_FUNCTION_TRACE(message_)
#define XOS_CERR_LOG_LOCATION_TRACE(message_)
#define XOS_STDERR_LOG_LOCATION_TRACE(message_)
#endif /// defined(TRACE_BUILD)

#if defined(DEBUG_BUILD)
#define XOS_CERR_LOG_DEBUG(message_) XOS_CERR_LOG(message_)
#define XOS_STDERR_LOG_DEBUG(message_) XOS_STDERR_LOG(message_)
#define XOS_CERR_LOG_PLAIN_DEBUG(message_) XOS_CERR_LOG_PLAIN(message_)
#define XOS_STDERR_LOG_PLAIN_DEBUG(message_) XOS_STDERR_LOG_PLAIN(message_)
#define XOS_CERR_LOG_FUNCTION_DEBUG(message_) XOS_CERR_LOG_FUNCTION(message_)
#define XOS_STDERR_LOG_FUNCTION_DEBUG(message_) XOS_STDERR_LOG_FUNCTION(message_)
#define XOS_CERR_LOG_LOCATION_DEBUG(message_) XOS_CERR_LOG_LOCATION(message_)
#define XOS_STDERR_LOG_LOCATION_DEBUG(message_) XOS_STDERR_LOG_LOCATION(message_)
#else /// defined(DEBUG_BUILD)
#define XOS_CERR_LOG_DEBUG(message_)
#define XOS_STDERR_LOG_DEBUG(message_)
#define XOS_CERR_LOG_PLAIN_DEBUG(message_)
#define XOS_STDERR_LOG_PLAIN_DEBUG(message_)
#define XOS_CERR_LOG_FUNCTION_DEBUG(message_)
#define XOS_STDERR_LOG_FUNCTION_DEBUG(message_)
#define XOS_CERR_LOG_LOCATION_DEBUG(message_)
#define XOS_STDERR_LOG_LOCATION_DEBUG(message_)
#endif /// defined(DEBUG_BUILD)

#define XOS_CERR_LOG_ERROR(message_) XOS_CERR_LOG(message_)
#define XOS_STDERR_LOG_ERROR(message_) XOS_STDERR_LOG(message_)
#define XOS_CERR_LOG_PLAIN_ERROR(message_) XOS_CERR_LOG_PLAIN(message_)
#define XOS_STDERR_LOG_PLAIN_ERROR(message_) XOS_STDERR_LOG_PLAIN(message_)
#define XOS_CERR_LOG_FUNCTION_ERROR(message_) XOS_CERR_LOG_FUNCTION(message_)
#define XOS_STDERR_LOG_FUNCTION_ERROR(message_) XOS_STDERR_LOG_FUNCTION(message_)
#define XOS_CERR_LOG_LOCATION_ERROR(message_) XOS_CERR_LOG_LOCATION(message_)
#define XOS_STDERR_LOG_LOCATION_ERROR(message_) XOS_STDERR_LOG_LOCATION(message_)

///
/// XOS_IF_ CERR / STDERR _LOG_ TRACE / DEBUG/ ERROR
/// 
#if defined(TRACE_BUILD)
#define XOS_IF_CERR_LOG_TRACE(is_logged_, message_) XOS_IF_CERR_LOG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_TRACE(is_logged_, message_) XOS_IF_STDERR_LOG(is_logged_, message_)
#define XOS_IF_CERR_LOG_PLAIN_TRACE(is_logged_, message_) XOS_IF_CERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_STDERR_LOG_PLAIN_TRACE(is_logged_, message_) XOS_IF_STDERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_CERR_LOG_FUNCTION_TRACE(is_logged_, message_) XOS_IF_CERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_FUNCTION_TRACE(is_logged_, message_) XOS_IF_STDERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_CERR_LOG_LOCATION_TRACE(is_logged_, message_) XOS_IF_CERR_LOG_LOCATION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_LOCATION_TRACE(is_logged_, message_) XOS_IF_STDERR_LOG_LOCATION(is_logged_, message_)
#else /// defined(TRACE_BUILD)
#define XOS_IF_CERR_LOG_TRACE(is_logged_, message_)
#define XOS_IF_STDERR_LOG_TRACE(is_logged_, message_)
#define XOS_IF_CERR_LOG_PLAIN_TRACE(is_logged_, message_)
#define XOS_IF_STDERR_LOG_PLAIN_TRACE(is_logged_, message_)
#define XOS_IF_CERR_LOG_FUNCTION_TRACE(is_logged_, message_)
#define XOS_IF_STDERR_LOG_FUNCTION_TRACE(is_logged_, message_)
#define XOS_IF_CERR_LOG_LOCATION_TRACE(is_logged_, message_)
#define XOS_IF_STDERR_LOG_LOCATION_TRACE(is_logged_, message_)
#endif /// defined(TRACE_BUILD)

#if defined(DEBUG_BUILD)
#define XOS_IF_CERR_LOG_DEBUG(is_logged_, message_) XOS_IF_CERR_LOG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_DEBUG(is_logged_, message_) XOS_IF_STDERR_LOG(is_logged_, message_)
#define XOS_IF_CERR_LOG_PLAIN_DEBUG(is_logged_, message_) XOS_IF_CERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_STDERR_LOG_PLAIN_DEBUG(is_logged_, message_) XOS_IF_STDERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_CERR_LOG_FUNCTION_DEBUG(is_logged_, message_) XOS_IF_CERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_FUNCTION_DEBUG(is_logged_, message_) XOS_IF_STDERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_CERR_LOG_LOCATION_DEBUG(is_logged_, message_) XOS_IF_CERR_LOG_LOCATION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_LOCATION_DEBUG(is_logged_, message_) XOS_IF_STDERR_LOG_LOCATION(is_logged_, message_)
#else /// defined(DEBUG_BUILD)
#define XOS_IF_CERR_LOG_DEBUG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_DEBUG(is_logged_, message_)
#define XOS_IF_CERR_LOG_PLAIN_DEBUG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_PLAIN_DEBUG(is_logged_, message_)
#define XOS_IF_CERR_LOG_FUNCTION_DEBUG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_FUNCTION_DEBUG(is_logged_, message_)
#define XOS_IF_CERR_LOG_LOCATION_DEBUG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_LOCATION_DEBUG(is_logged_, message_)
#endif /// defined(DEBUG_BUILD)

#define XOS_IF_CERR_LOG_ERROR(is_logged_, message_) XOS_IF_CERR_LOG(is_logged_, message_)
#define XOS_IF_STDERR_LOG_ERROR(is_logged_, message_) XOS_IF_STDERR_LOG(is_logged_, message_)
#define XOS_IF_CERR_LOG_PLAIN_ERROR(is_logged_, message_) XOS_IF_CERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_STDERR_LOG_PLAIN_ERROR(is_logged_, message_) XOS_IF_STDERR_LOG_PLAIN(is_logged_, message_)
#define XOS_IF_CERR_LOG_FUNCTION_ERROR(is_logged_, message_) XOS_IF_CERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_FUNCTION_ERROR(is_logged_, message_) XOS_IF_STDERR_LOG_FUNCTION(is_logged_, message_)
#define XOS_IF_CERR_LOG_LOCATION_ERROR(is_logged_, message_) XOS_IF_CERR_LOG_LOCATION(is_logged_, message_)
#define XOS_IF_STDERR_LOG_LOCATION_ERROR(is_logged_, message_) XOS_IF_STDERR_LOG_LOCATION(is_logged_, message_)

#if defined(XOS_CERR_LOGGING)
#define XOS_ERR_LOG_TRACE(message_) XOS_CERR_LOG_TRACE(message_)
#define XOS_ERR_LOG_DEBUG(message_) XOS_CERR_LOG_DEBUG(message_)
#define XOS_ERR_LOG_ERROR(message_) XOS_CERR_LOG_ERROR(message_)
#else /// defined(XOS_CERR_LOGGING)
#define XOS_ERR_LOG_TRACE(message_) XOS_STDERR_LOG_TRACE(message_)
#define XOS_ERR_LOG_DEBUG(message_) XOS_STDERR_LOG_DEBUG(message_)
#define XOS_ERR_LOG_ERROR(message_) XOS_STDERR_LOG_ERROR(message_)
#endif /// defined(XOS_CERR_LOGGING)

///
/// STDERR_LOG_ LOCATION / FUNTION / PLAIN
/// 
#if !defined(STDERR_LOG_LOCATION)
#define STDERR_LOG_LOCATION(__message__) XOS_STDERR_LOG_LOCATION(__message__) 
#endif /// !defined(STDERR_LOG_LOCATION)

#if !defined(STDERR_LOG_FUNCTION)
#define STDERR_LOG_FUNCTION(__message__) XOS_STDERR_LOG_FUNCTION(__message__)
#endif /// !defined(STDERR_LOG_FUNCTION)

#if !defined(STDERR_LOG_PLAIN)
#define STDERR_LOG_PLAIN(__message__) XOS_STDERR_LOG_PLAIN(__message__) 
#endif /// !defined(STDERR_LOG_PLAIN)

///
/// IF_STDERR_LOG_ LOCATION / FUNTION / PLAIN
/// 
#if !defined(IF_STDERR_LOG_LOCATION)
#define IF_STDERR_LOG_LOCATION(is_logged_, message_) XOS_IF_STDERR_LOG_LOCATION(is_logged_, message_) 
#endif /// !defined(IF_STDERR_LOG_LOCATION)

#if !defined(IF_STDERR_LOG_FUNCTION)
#define IF_STDERR_LOG_FUNCTION(is_logged_, message_) XOS_IF_STDERR_LOG_FUNCTION(is_logged_, message_)
#endif /// !defined(IF_STDERR_LOG_FUNCTION)

#if !defined(IF_STDERR_LOG_PLAIN)
#define IF_STDERR_LOG_PLAIN(is_logged_, message_) XOS_IF_STDERR_LOG_PLAIN(is_logged_, message_) 
#endif /// !defined(IF_STDERR_LOG_PLAIN)

///
/// STDERR_LOG
/// 
#if defined(STDERR_PLAIN_LOGGING)
///
/// plain logging
/// 
#define STDERR_LOG STDERR_LOG_PLAIN
#else /// defined(STDERR_PLAIN_LOGGING)
#if defined(STDERR_FUNCTION_LOGGING)
///
/// function logging
/// 
#define STDERR_LOG STDERR_LOG_FUNCTION
#else /// defined(STDERR_FUNCTION_LOGGING)
///
/// location logging
/// 
#define STDERR_LOG STDERR_LOG_LOCATION
#endif /// defined(STDERR_FUNCTION_LOGGING)
#endif /// defined(STDERR_PLAIN_LOGGING)

///
/// IF_STDERR_LOG
/// 
#if defined(STDERR_PLAIN_LOGGING)
///
/// plain logging
/// 
#define IF_STDERR_LOG IF_STDERR_LOG_PLAIN
#else /// defined(STDERR_PLAIN_LOGGING)
#if defined(STDERR_FUNCTION_LOGGING)
///
/// function logging
/// 
#define IF_STDERR_LOG IF_STDERR_LOG_FUNCTION
#else /// defined(STDERR_FUNCTION_LOGGING)
///
/// location logging
/// 
#define IF_STDERR_LOG IF_STDERR_LOG_LOCATION
#endif /// defined(STDERR_FUNCTION_LOGGING)
#endif /// defined(STDERR_PLAIN_LOGGING)

///
/// STDERR_LOG_ TRACE / DEBUG / ERROR
/// 
#if !defined(STDERR_LOG_TRACE)
#if defined(TRACE_BUILD)
#define STDERR_LOG_TRACE(__message__) STDERR_LOG(__message__)
#else /// defined(TRACE_BUILD)
#define STDERR_LOG_TRACE(__message__)
#endif /// defined(TRACE_BUILD)
#endif /// !defined(STDERR_LOG_TRACE)

#if !defined(STDERR_LOG_DEBUG)
#if defined(DEBUG_BUILD)
#define STDERR_LOG_DEBUG(__message__) STDERR_LOG(__message__)
#else /// defined(DEBUG_BUILD)
#define STDERR_LOG_DEBUG(__message__)
#endif /// defined(DEBUG_BUILD)
#endif /// !defined(STDERR_LOG_DEBUG)

#if !defined(STDERR_LOG_ERROR)
#define STDERR_LOG_ERROR(__message__) STDERR_LOG(__message__)
#endif /// !defined(STDERR_LOG_ERROR)

///
/// IF_STDERR_LOG_ TRACE / DEBUG / ERROR
/// 
#if !defined(IF_STDERR_LOG_TRACE)
#if defined(TRACE_BUILD)
#define IF_STDERR_LOG_TRACE(is_logged_, message_) IF_STDERR_LOG(is_logged_, message_)
#else /// defined(TRACE_BUILD)
#define IF_STDERR_LOG_TRACE(is_logged_, message_)
#endif /// defined(TRACE_BUILD)
#endif /// !defined(IF_STDERR_LOG_TRACE)

#if !defined(IF_STDERR_LOG_DEBUG)
#if defined(DEBUG_BUILD)
#define IF_STDERR_LOG_DEBUG(is_logged_, message_) IF_STDERR_LOG(is_logged_, message_)
#else /// defined(DEBUG_BUILD)
#define IF_STDERR_LOG_DEBUG(is_logged_, message_)
#endif /// defined(DEBUG_BUILD)
#endif /// !defined(IF_STDERR_LOG_DEBUG)

#if !defined(IF_STDERR_LOG_ERROR)
#define IF_STDERR_LOG_ERROR(is_logged_, message_) IF_STDERR_LOG(is_logged_, message_)
#endif /// !defined(IF_STDERR_LOG_ERROR)

///
/// ERR_LOG_ TRACE / DEBUG / ERROR
/// 
#if !defined(ERR_LOG_TRACE)
#define ERR_LOG_TRACE(__message__) STDERR_LOG_TRACE(__message__)
#endif /// !defined(ERR_LOG_TRACE)

#if !defined(ERR_LOG_DEBUG)
#define ERR_LOG_DEBUG(__message__) STDERR_LOG_DEBUG(__message__)
#endif /// !defined(ERR_LOG_DEBUG)

#if !defined(ERR_LOG_ERROR)
#define ERR_LOG_ERROR(__message__) STDERR_LOG_ERROR(__message__)
#endif /// !defined(ERR_LOG_ERROR)

///
/// IF_ERR_LOG_ TRACE / DEBUG / ERROR
/// 
#if !defined(IF_ERR_LOG_TRACE)
#define IF_ERR_LOG_TRACE(is_logged_, message_) IF_STDERR_LOG_TRACE(is_logged_, message_)
#endif /// !defined(IF_ERR_LOG_TRACE)

#if !defined(IF_ERR_LOG_DEBUG)
#define IF_ERR_LOG_DEBUG(is_logged_, message_) IF_STDERR_LOG_DEBUG(is_logged_, message_)
#endif /// !defined(IF_ERR_LOG_DEBUG)

#if !defined(IF_ERR_LOG_ERROR)
#define IF_ERR_LOG_ERROR(is_logged_, message_) IF_STDERR_LOG_ERROR(is_logged_, message_)
#endif /// !defined(IF_ERR_LOG_ERROR)

#endif /// _XOS_LOGGER_OUTPUT_HPP 
