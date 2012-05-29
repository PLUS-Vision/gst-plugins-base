/* GStreamer
 * Copyright (C) <2003> David A. Schleef <ds@schleef.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __VIDEO_TEST_SRC_H__
#define __VIDEO_TEST_SRC_H__

#include <glib.h>

enum {
  VTS_YUV,
  VTS_RGB,
  VTS_GRAY,
  VTS_BAYER
};

enum {
  VTS_BAYER_BGGR,
  VTS_BAYER_RGGB,
  VTS_BAYER_GRBG,
  VTS_BAYER_GBRG
};

struct vts_color_struct {
  guint8 Y, U, V, A;
  guint8 R, G, B;
  guint16 gray;
};


typedef struct paintinfo_struct paintinfo;
struct paintinfo_struct
{
  int size;                     /* size of a frame */
  int width;
  int height;
  const struct vts_color_struct *colors;
  const struct vts_color_struct *color;
  /*  const struct vts_color_struct *color; */
  void (*paint_hline) (paintinfo * p, int x, int y, int w);
  void (*paint_tmpline) (paintinfo * p, int x, int w);
  void (*convert_tmpline) (paintinfo * p, GstVideoFrame *frame, int y);
  int x_offset;

  int bayer_x_invert;
  int bayer_y_invert;

  guint8 *tmpline;
  guint8 *tmpline2;
  guint8 *tmpline_u8;
  guint16 *tmpline_u16;

  struct vts_color_struct foreground_color;
  struct vts_color_struct background_color;
};
#define PAINT_INFO_INIT {0, }

struct format_list_struct
{
  int type;
  const char *format;
  const char *name;
  void (*paint_setup) (paintinfo * p, GstVideoFrame *frame);
  void (*convert_hline) (paintinfo * p, GstVideoFrame *frame, int y);
};

struct format_list_struct *
        paintrect_find_format           (const gchar *find_format);
struct format_list_struct *
        paintrect_find_name             (const char *name);
struct format_list_struct *
        paintinfo_find_by_structure     (const GstStructure *structure);
GstStructure *
        paint_get_structure             (struct format_list_struct *format);

int     gst_video_test_src_get_size     (GstVideoTestSrc * v, int w, int h);
void    gst_video_test_src_smpte        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_smpte75      (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_snow         (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_black        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_white        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_red          (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_green        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_blue         (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_solid        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_blink        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_checkers1    (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_checkers2    (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_checkers4    (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_checkers8    (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_circular     (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_zoneplate    (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_gamut        (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_chromazoneplate (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_ball         (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_smpte100     (GstVideoTestSrc * v, GstVideoFrame *frame);
void    gst_video_test_src_bar          (GstVideoTestSrc * v, GstVideoFrame *frame);

extern struct format_list_struct format_list[];
extern int n_formats;

#endif
