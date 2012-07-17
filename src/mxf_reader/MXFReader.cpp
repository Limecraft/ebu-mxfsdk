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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstring>

#include <bmx/mxf_reader/MXFReader.h>
#include <bmx/MXFUtils.h>
#include <bmx/Utils.h>
#include <bmx/BMXException.h>
#include <bmx/Logging.h>

using namespace std;
using namespace bmx;
using namespace mxfpp;



MXFReader::MXFReader()
{
    mSampleRate = ZERO_RATIONAL;
    mDuration = 0;
    mMaterialStartTimecode = 0;
    mFileSourceStartTimecode = 0;
    mPhysicalSourceStartTimecode = 0;
    mMaterialPackageUID = g_Null_UMID;
}

MXFReader::~MXFReader()
{
    delete mMaterialStartTimecode;
    delete mFileSourceStartTimecode;
    delete mPhysicalSourceStartTimecode;
}

void MXFReader::ClearFrameBuffers(bool del_frames)
{
    size_t i;
    for (i = 0 ; i < GetNumTrackReaders(); i++)
        GetTrackReader(i)->GetFrameBuffer()->Clear(del_frames);
}

Timecode MXFReader::GetMaterialTimecode(int64_t position) const
{
    if (!HaveMaterialTimecode())
        return Timecode(get_rounded_tc_base(mSampleRate), false);

    return CreateTimecode(mMaterialStartTimecode, position);
}

Timecode MXFReader::GetFileSourceTimecode(int64_t position) const
{
    if (!HaveFileSourceTimecode())
        return Timecode(get_rounded_tc_base(mSampleRate), false);

    return CreateTimecode(mFileSourceStartTimecode, position);
}

Timecode MXFReader::GetPhysicalSourceTimecode(int64_t position) const
{
    if (!HavePhysicalSourceTimecode())
        return Timecode(get_rounded_tc_base(mSampleRate), false);

    return CreateTimecode(mPhysicalSourceStartTimecode, position);
}

bool MXFReader::HavePlayoutTimecode() const
{
    return HaveMaterialTimecode() || HaveFileSourceTimecode() || HavePhysicalSourceTimecode();
}

Timecode MXFReader::GetPlayoutTimecode(int64_t position) const
{
    if (HaveMaterialTimecode())
        return GetMaterialTimecode(position);
    else if (HaveFileSourceTimecode())
        return GetFileSourceTimecode(position);
    else if (HavePhysicalSourceTimecode())
        return GetPhysicalSourceTimecode(position);

    return Timecode(get_rounded_tc_base(mSampleRate), false);
}

bool MXFReader::HaveSourceTimecode() const
{
    return HaveFileSourceTimecode() || HavePhysicalSourceTimecode();
}

Timecode MXFReader::GetSourceTimecode(int64_t position) const
{
    if (HaveFileSourceTimecode())
        return GetFileSourceTimecode(position);
    else if (HavePhysicalSourceTimecode())
        return GetPhysicalSourceTimecode(position);

    return Timecode(get_rounded_tc_base(mSampleRate), false);
}

Timecode MXFReader::CreateTimecode(const Timecode *start_timecode, int64_t position) const
{
    int64_t offset = position;
    if (position == CURRENT_POSITION_VALUE)
        offset = GetPosition();

    Timecode timecode(*start_timecode);
    timecode.AddOffset(offset, mSampleRate);

    return timecode;
}

