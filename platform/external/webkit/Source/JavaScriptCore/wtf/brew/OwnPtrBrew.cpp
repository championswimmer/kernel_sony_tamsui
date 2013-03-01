/*
 * Copyright (C) 2010 Company 100 Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "OwnPtr.h"

#include <AEEBitmap.h>
#include <AEEFile.h>
#include <AEEIMemGroup.h>
#include <AEEIMemSpace.h>
#include <AEENet.h>
#include <AEESSL.h>
#include <AEEStdLib.h>

namespace WTF {

void deleteOwnedPtr(IFileMgr* ptr)
{
    if (ptr)
        IFILEMGR_Release(ptr);
}

void deleteOwnedPtr(IFile* ptr)
{
    if (ptr)
        IFILE_Release(ptr);
}

void deleteOwnedPtr(IBitmap* ptr)
{
    if (ptr)
        IBitmap_Release(ptr);
}

void deleteOwnedPtr(ISSL* ptr)
{
    if (ptr)
        ISSL_Release(ptr);
}

void deleteOwnedPtr(IMemGroup* ptr)
{
    if (ptr)
        IMemGroup_Release(ptr);
}

void deleteOwnedPtr(IMemSpace* ptr)
{
    if (ptr)
        IMemSpace_Release(ptr);
}

void deleteOwnedPtr(ISocket* ptr)
{
    if (ptr)
        ISOCKET_Release(ptr);
}

}
