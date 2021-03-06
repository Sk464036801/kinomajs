/*
 *     Copyright (C) 2010-2015 Marvell International Ltd.
 *     Copyright (C) 2002-2010 Kinoma, Inc.
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */
#ifndef __KINOMAAVCDECODE__
#define __KINOMAAVCDECODE__

#ifdef __cplusplus
extern "C" {
#endif

#include "Fsk.h"
#include "FskBitmap.h"
#include "FskUtilities.h"
#include "FskImage.h"

FskErr avcDecodeCanHandle(UInt32 format, const char *mime, const char *extension, Boolean *canHandle);
FskErr avcDecodeNew(FskImageDecompress deco, UInt32 format, const char *mime, const char *extension);
FskErr avcDecodeDispose(void *stateIn, FskImageDecompress deco);
FskErr avcDecodeDecompressFrame(void *stateIn, FskImageDecompress deco, const void *data, UInt32 dataSize, FskInt64 *decodeTime, UInt32 *compositionTimeOffset, FskInt64 *compositionTime, UInt32 frameType);
FskErr avcDecodeGetMetaData(void *stateIn, FskImageDecompress deco, UInt32 metadata, UInt32 index, FskMediaPropertyValue value, UInt32 *flags);


FskErr parse_header( unsigned char *data, int size, int *left, int *right, int *top, int *bottom );
FskErr parse_header2( unsigned char *data, int size, int *weighted_pred_flag );

extern FskMediaPropertyEntryRecord avcDecodeProperties[];

#ifdef __cplusplus
}
#endif

#endif
