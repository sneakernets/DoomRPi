/* $Id: mode.c,v 1.6 2004/10/28 21:19:59 cegger Exp $
******************************************************************************

   Display-multi: mode management

   Copyright (C) 1997 Andreas Beck	[becka@ggi-project.org]
   Copyright (C) 1998 Andrew Apted	[andrew@ggi-project.org]
   Copyright (C) 1999 Marcus Sundberg	[marcus@ggi-project.org]

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

#include "config.h"
#include <ggi/internal/ggi-dl.h>

#include <ggi/display/multi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int GGI_multi_setmode(ggi_visual *vis, ggi_mode *tm)
{ 
	ggi_multi_priv *priv = GGIMULTI_PRIV(vis);
	MultiVis *cur;
	int err;

	err = ggiCheckMode(vis, tm);
	if (err) return err;

	GG_SLIST_FOREACH(cur, &priv->vis_list, visuals) {
		err = ggiSetMode(cur->vis, tm);
		if (err != 0) {
			if (cur == GG_SLIST_FIRST(&priv->vis_list))
				return err;
			return GGI_EFATAL;
		}
		if (ggiSetMode(cur->vis, tm) != 0) err = -1;
	}

	/* We hope that the pixelformat is the same on all child visuals */
	memcpy(LIBGGI_PIXFMT(vis),
		ggiGetPixelFormat(GG_SLIST_FIRST(&priv->vis_list)->vis),
		sizeof(ggi_pixelformat));

	memcpy(LIBGGI_MODE(vis), tm, sizeof(ggi_mode));

	return 0;
}


static int try_checkmode(ggi_visual *vis, ggi_mode *tm, int count)
{
	ggi_multi_priv *priv = GGIMULTI_PRIV(vis);
	MultiVis *cur;
	int err;

	count++;
	if (count > 10) {
		/* Can't find any mode useable by all child visuals */
		return GGI_EFATAL;
	}

	GG_SLIST_FOREACH(cur, &priv->vis_list, visuals) {
		err = ggiCheckMode(cur->vis, tm);
		if (err) {
			try_checkmode(vis, tm, count);
			return err;
		}
	}

	return 0;
}


int GGI_multi_checkmode(ggi_visual *vis, ggi_mode *tm)
{
	return try_checkmode(vis, tm, 0);
}


int GGI_multi_getmode(ggi_visual *vis, ggi_mode *tm)
{
	ggi_multi_priv *priv = GGIMULTI_PRIV(vis);

	return ggiGetMode(GG_SLIST_FIRST(&priv->vis_list)->vis, tm);
}


int GGI_multi_setflags(ggi_visual *vis,ggi_flags flags)
{
	ggi_multi_priv *priv = GGIMULTI_PRIV(vis);
	MultiVis *cur;

	int err=0;

	GG_SLIST_FOREACH(cur, &priv->vis_list, visuals) {
		if (ggiSetFlags(cur->vis, flags) != 0) err = -1;
	}

	LIBGGI_FLAGS(vis) = flags;

	LIBGGI_FLAGS(vis) &= GGIFLAG_ASYNC; /* Unkown flags don't take. */

	return err;
}
                

int GGI_multi_flush(ggi_visual *vis, int x, int y, int w, int h, int tryflag)
{
	ggi_multi_priv *priv = GGIMULTI_PRIV(vis);
	MultiVis *cur;
	int err = 0;

	GG_SLIST_FOREACH(cur, &priv->vis_list, visuals) {
		if (_ggiInternFlush(cur->vis, x, y, w, h, tryflag) != 0) {
			err = -1;
		}
	}

	return err;
}


