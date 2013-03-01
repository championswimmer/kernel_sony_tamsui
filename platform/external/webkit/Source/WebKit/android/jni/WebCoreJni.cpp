/*
 * Copyright 2007, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define LOG_TAG "webcoreglue"

#include "config.h"
#include "WebCoreJni.h"

#include "NotImplemented.h"
#include <JNIUtility.h>
#include <jni.h>
#include <utils/Log.h>

namespace android {

AutoJObject getRealObject(JNIEnv* env, jobject obj)
{
    jobject real = env->NewLocalRef(obj);
    LOG_ASSERT(real, "The real object has been deleted!");
    return AutoJObject(env, real);
}

/**
 * Helper method for checking java exceptions
 * @return true if an exception occurred.
 */
bool checkException(JNIEnv* env)
{
    if (env->ExceptionCheck() != 0)
    {
        LOGE("*** Uncaught exception returned from Java call!\n");
        env->ExceptionDescribe();
        return true;
    }
    return false;
}

// This method is safe to call from the ui thread and the WebCore thread.
WTF::String jstringToWtfString(JNIEnv* env, jstring str)
{
    if (!str || !env)
        return WTF::String();
    const jchar* s = env->GetStringChars(str, NULL);
    if (!s)
        return WTF::String();
    WTF::String ret(s, env->GetStringLength(str));
    env->ReleaseStringChars(str, s);
    checkException(env);
    return ret;
}

jstring wtfStringToJstring(JNIEnv* env, const WTF::String& str, bool validOnZeroLength)
{
    int length = str.length();
    return length || validOnZeroLength ? env->NewString(str.characters(), length) : 0;
}


#if USE(CHROME_NETWORK_STACK)

// Arima Rockyang added 20120703
size_t convertUTFBytes(char* byte, const char* src) {
    bool is_converted = false;
    size_t length = 0;
    
    while (*src != '\0') {
        switch (*src >> 4) {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            // Bit pattern 0xxx. No need for any extra bytes.
            *byte = *src;
            break;
        case 0x08:
        case 0x09:
        case 0x0a:
        case 0x0b:
        case 0x0f:
            /*
             * Bit pattern 10xx or 1111, which are illegal start bytes.
             * Note: 1111 is valid for normal UTF-8, but not the
             * modified UTF-8 used here.
             */
            *byte = 0xc0 | (*src >> 6);
            byte++; length++;
            *byte = 0x80 | (*src & 0x3f);
            is_converted = true;
            break;
        case 0x0c:  // Bit pattern 110x, so there is one additional byte.
        case 0x0d:  // Bit pattern 110x, so there is one additional byte.
            if ( is_converted == false ) {
                if ( (*(src + 1) & 0xc0) == 0x80 ) {
                    *byte = *src;
                    src++; byte++; length++;
                    *byte = *src;
                    break;
                }
            }
                
            *byte = 0xc0 | (*src >> 6);
            byte++; length++;
            *byte = 0x80 | (*src & 0x3f);
            is_converted = true;            
            break;
        case 0x0e:  // Bit pattern 1110, so there are two additional bytes.
            if ( is_converted == false ) {
                if ( (*(src + 1) & 0xc0) == 0x80 && (*(src + 2) & 0xc0) == 0x80 ) {
                    *byte = *src;
                    src++; byte++; length++;
                    *byte = *src;
                    src++; byte++; length++;
                    *byte = *src;
                    break;
                }
            }
                
            *byte = 0xc0 | (*src >> 6);
            byte++; length++;
            *byte = 0x80 | (*src & 0x3f);
            is_converted = true;
            break;
        }
        src++;
        byte++;
        length++;
    }

    return length;
}
// Arima Rockyang added end

string16 jstringToString16(JNIEnv* env, jstring jstr)
{
    if (!jstr || !env)
        return string16();

    const char* s = env->GetStringUTFChars(jstr, 0);
    if (!s)
        return string16();
    string16 str = UTF8ToUTF16(s);
    env->ReleaseStringUTFChars(jstr, s);
    checkException(env);
    return str;
}

std::string jstringToStdString(JNIEnv* env, jstring jstr)
{
    if (!jstr || !env)
        return std::string();

    const char* s = env->GetStringUTFChars(jstr, 0);
    if (!s)
        return std::string();
    std::string str(s);
    env->ReleaseStringUTFChars(jstr, s);
    checkException(env);
    return str;
}

jstring stdStringToJstring(JNIEnv* env, const std::string& str, bool validOnZeroLength)
{
    // Arima Rockyang added 20120703
    size_t bytes_length = str.length() * 2 + 1;
    char *bytes = new char[bytes_length];
    if ( bytes ) {
        size_t new_bytes_length = 0;
        for ( size_t i = 0; i < bytes_length; i++ ) {
            bytes[i] = 0;
        }
        
        new_bytes_length = convertUTFBytes(bytes, str.c_str());

        jstring js = !str.empty() || validOnZeroLength ? env->NewStringUTF(bytes) : 0;
        free(bytes);
        return js;
    }
    // Arima Rockyang added end
    
    return !str.empty() || validOnZeroLength ? env->NewStringUTF(str.c_str()) : 0;
}

#endif

}
