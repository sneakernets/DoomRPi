/* $Id: cursor.inc,v 1.1 2005/01/04 13:08:14 pekberg Exp $
*****************************************************************************

   LibGGI DirectX target - Cursors

   Copyright (C) 1999-2000 John Fortin  [fortinj@ibm.net]

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   THE AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

******************************************************************************
*/

static BYTE ANDmaskInvCursor[] = {
	0xff, 0xff, 0xff, 0xff,	// line 1
	0xff, 0xff, 0xff, 0xff,	// line 2
	0xff, 0xff, 0xff, 0xff,	// line 3
	0xff, 0xff, 0xff, 0xff,	// line 4

	0xff, 0xff, 0xff, 0xff,	// line 5
	0xff, 0xff, 0xff, 0xff,	// line 6
	0xff, 0xff, 0xff, 0xff,	// line 7
	0xff, 0xff, 0xff, 0xff,	// line 8

	0xff, 0xff, 0xff, 0xff,	// line 9
	0xff, 0xff, 0xff, 0xff,	// line 10
	0xff, 0xff, 0xff, 0xff,	// line 11
	0xff, 0xff, 0xff, 0xff,	// line 12

	0xff, 0xff, 0xff, 0xff,	// line 13
	0xff, 0xff, 0xff, 0xff,	// line 14
	0xff, 0xff, 0xff, 0xff,	// line 15
	0xff, 0xff, 0xff, 0xff,	// line 16

	0xff, 0xff, 0xff, 0xff,	// line 17
	0xff, 0xff, 0xff, 0xff,	// line 18
	0xff, 0xff, 0xff, 0xff,	// line 19
	0xff, 0xff, 0xff, 0xff,	// line 20

	0xff, 0xff, 0xff, 0xff,	// line 21
	0xff, 0xff, 0xff, 0xff,	// line 22
	0xff, 0xff, 0xff, 0xff,	// line 23
	0xff, 0xff, 0xff, 0xff,	// line 24

	0xff, 0xff, 0xff, 0xff,	// line 25
	0xff, 0xff, 0xff, 0xff,	// line 26
	0xff, 0xff, 0xff, 0xff,	// line 27
	0xff, 0xff, 0xff, 0xff,	// line 28

	0xff, 0xff, 0xff, 0xff,	// line 29
	0xff, 0xff, 0xff, 0xff,	// line 30
	0xff, 0xff, 0xff, 0xff,	// line 31
	0xff, 0xff, 0xff, 0xff	// line 32
};

static BYTE XORmaskInvCursor[] = {
	0x00, 0x00, 0x00, 0x00,	// line 1
	0x00, 0x00, 0x00, 0x00,	// line 2
	0x00, 0x00, 0x00, 0x00,	// line 3
	0x00, 0x00, 0x00, 0x00,	// line 4

	0x00, 0x00, 0x00, 0x00,	// line 5
	0x00, 0x00, 0x00, 0x00,	// line 6
	0x00, 0x00, 0x00, 0x00,	// line 7
	0x00, 0x00, 0x00, 0x00,	// line 8

	0x00, 0x00, 0x00, 0x00,	// line 9
	0x00, 0x00, 0x00, 0x00,	// line 10
	0x00, 0x00, 0x00, 0x00,	// line 11
	0x00, 0x00, 0x00, 0x00,	// line 12

	0x00, 0x00, 0x00, 0x00,	// line 13
	0x00, 0x00, 0x00, 0x00,	// line 14
	0x00, 0x00, 0x00, 0x00,	// line 15
	0x00, 0x00, 0x00, 0x00,	// line 16

	0x00, 0x00, 0x00, 0x00,	// line 17
	0x00, 0x00, 0x00, 0x00,	// line 18
	0x00, 0x00, 0x00, 0x00,	// line 19
	0x00, 0x00, 0x00, 0x00,	// line 20

	0x00, 0x00, 0x00, 0x00,	// line 21
	0x00, 0x00, 0x00, 0x00,	// line 22
	0x00, 0x00, 0x00, 0x00,	// line 23
	0x00, 0x00, 0x00, 0x00,	// line 24

	0x00, 0x00, 0x00, 0x00,	// line 25
	0x00, 0x00, 0x00, 0x00,	// line 26
	0x00, 0x00, 0x00, 0x00,	// line 27
	0x00, 0x00, 0x00, 0x00,	// line 28

	0x00, 0x00, 0x00, 0x00,	// line 29
	0x00, 0x00, 0x00, 0x00,	// line 30
	0x00, 0x00, 0x00, 0x00,	// line 31
	0x00, 0x00, 0x00, 0x00	// line 32
};

static BYTE ANDmaskDotCursor[] = {
	0xff, 0xff, 0xff, 0xff,	// line 1
	0xff, 0xff, 0xff, 0xff,	// line 2
	0xff, 0xff, 0xff, 0xff,	// line 3
	0xff, 0xff, 0xff, 0xff,	// line 4

	0xff, 0xff, 0xff, 0xff,	// line 5
	0xff, 0xff, 0xff, 0xff,	// line 6
	0xff, 0xff, 0xff, 0xff,	// line 7
	0xff, 0xff, 0xff, 0xff,	// line 8

	0xff, 0xff, 0xff, 0xff,	// line 9
	0xff, 0xff, 0xff, 0xff,	// line 10
	0xff, 0xff, 0xff, 0xff,	// line 11
	0xff, 0xff, 0xff, 0xff,	// line 12

	0xff, 0xff, 0xff, 0xff,	// line 13
	0xff, 0xff, 0xff, 0xff,	// line 14
	0xff, 0xff, 0xff, 0xff,	// line 15
	0xff, 0xfe, 0xff, 0xff,	// line 16

	0xff, 0xfd, 0x7f, 0xff,	// line 17
	0xff, 0xfe, 0xff, 0xff,	// line 18
	0xff, 0xff, 0xff, 0xff,	// line 19
	0xff, 0xff, 0xff, 0xff,	// line 20

	0xff, 0xff, 0xff, 0xff,	// line 21
	0xff, 0xff, 0xff, 0xff,	// line 22
	0xff, 0xff, 0xff, 0xff,	// line 23
	0xff, 0xff, 0xff, 0xff,	// line 24

	0xff, 0xff, 0xff, 0xff,	// line 25
	0xff, 0xff, 0xff, 0xff,	// line 26
	0xff, 0xff, 0xff, 0xff,	// line 27
	0xff, 0xff, 0xff, 0xff,	// line 28

	0xff, 0xff, 0xff, 0xff,	// line 29
	0xff, 0xff, 0xff, 0xff,	// line 30
	0xff, 0xff, 0xff, 0xff,	// line 31
	0xff, 0xff, 0xff, 0xff	// line 32
};

static BYTE XORmaskDotCursor[] = {
	0x00, 0x00, 0x00, 0x00,	// line 1
	0x00, 0x00, 0x00, 0x00,	// line 2
	0x00, 0x00, 0x00, 0x00,	// line 3
	0x00, 0x00, 0x00, 0x00,	// line 4

	0x00, 0x00, 0x00, 0x00,	// line 5
	0x00, 0x00, 0x00, 0x00,	// line 6
	0x00, 0x00, 0x00, 0x00,	// line 7
	0x00, 0x00, 0x00, 0x00,	// line 8

	0x00, 0x00, 0x00, 0x00,	// line 9
	0x00, 0x00, 0x00, 0x00,	// line 10
	0x00, 0x00, 0x00, 0x00,	// line 11
	0x00, 0x00, 0x00, 0x00,	// line 12

	0x00, 0x00, 0x00, 0x00,	// line 13
	0x00, 0x00, 0x00, 0x00,	// line 14
	0x00, 0x00, 0x00, 0x00,	// line 15
	0x00, 0x01, 0x00, 0x00,	// line 16

	0x00, 0x02, 0x80, 0x00,	// line 17
	0x00, 0x01, 0x00, 0x00,	// line 18
	0x00, 0x00, 0x00, 0x00,	// line 19
	0x00, 0x00, 0x00, 0x00,	// line 20

	0x00, 0x00, 0x00, 0x00,	// line 21
	0x00, 0x00, 0x00, 0x00,	// line 22
	0x00, 0x00, 0x00, 0x00,	// line 23
	0x00, 0x00, 0x00, 0x00,	// line 24

	0x00, 0x00, 0x00, 0x00,	// line 25
	0x00, 0x00, 0x00, 0x00,	// line 26
	0x00, 0x00, 0x00, 0x00,	// line 27
	0x00, 0x00, 0x00, 0x00,	// line 28

	0x00, 0x00, 0x00, 0x00,	// line 29
	0x00, 0x00, 0x00, 0x00,	// line 30
	0x00, 0x00, 0x00, 0x00,	// line 31
	0x00, 0x00, 0x00, 0x00	// line 32
};