/*
 * Copyright (c) 2016 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * This space intentionally left blank.
 *
 * All of the #defines have been moved to BUILD.gn. The libsrtp headers
 * equate "building as a library" with HAS_CONFIG_H, so we need to leave that
 * defined and this file needs to be here.
 */


#define HAVE_STDLIB_H     1
#define HAVE_STRING_H     1
#define HAVE_STDINT_H     1
#define HAVE_INTTYPES_H   1
#define HAVE_INT16_T      1
#define HAVE_INT32_T      1
#define HAVE_INT8_T       1
#define HAVE_UINT16_T     1
#define HAVE_UINT32_T     1
#define HAVE_UINT64_T     1
#define HAVE_UINT8_T      1

#define HAVE_WINSOCK2_H   1

#define PACKAGE_STRING "libsrtp"
#define PACKAGE_VERSION "2.0.0"
