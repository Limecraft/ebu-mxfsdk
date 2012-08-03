/*
 * Copyright (C) 2010, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __BMX_LOGGING_H__
#define __BMX_LOGGING_H__

#include <cstdarg>

#include <string>



namespace bmx
{


typedef enum
{
    DEBUG_LOG = 0,
    INFO_LOG,
    WARN_LOG,
    ERROR_LOG,
} LogLevel;

typedef void (*log_func)(LogLevel level, const char *format, ...);
typedef void (*vlog_func)(LogLevel level, const char *format, va_list p_arg);
typedef void (*vlog2_func)(LogLevel level, const char *source, const char *format, va_list p_arg);

extern log_func log;
extern vlog_func vlog;
extern vlog2_func vlog2;
extern LogLevel LOG_LEVEL;


bool open_log_file(std::string filename);
void close_log_file();

void flush_log();


void log_debug(const char *format, ...);
void log_info(const char *format, ...);
void log_warn(const char *format, ...);
void log_error(const char *format, ...);

void log_error_nl(const char *format, ...);


void log_debug(const char *format, va_list args);
void log_info(const char *format, va_list args);
void log_warn(const char *format, va_list args);
void log_error(const char *format, va_list args);

void log_error_nl(const char *format, va_list args);

};



#endif
