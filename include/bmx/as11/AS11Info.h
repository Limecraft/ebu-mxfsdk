/*
 * Copyright (C) 2012, British Broadcasting Corporation
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

#ifndef __BMX_AS11_INFO_H__
#define __BMX_AS11_INFO_H__


#include <bmx/BMXTypes.h>
#include <bmx/as11/AS11CoreFramework.h>
#include <bmx/as11/UKDPPFramework.h>
#include <bmx/as11/AS11SegmentationFramework.h>


namespace bmx
{


class AS11Info
{
public:
    static void RegisterExtensions(mxfpp::DataModel *data_model);

public:
    AS11Info();
    ~AS11Info();

    bool Read(mxfpp::HeaderMetadata *header_metadata);

private:
    void Reset();

    void GetStaticFrameworks(std::vector<mxfpp::GenericTrack*> &tracks);
    void GetSegmentation(std::vector<mxfpp::GenericTrack*> &tracks);

public:
    AS11CoreFramework *core;
    UKDPPFramework *ukdpp;
    std::vector<mxfpp::StructuralComponent*> segmentation;
    Rational segmentation_rate;
};


};



#endif

