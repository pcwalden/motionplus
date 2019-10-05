/*    util.h
 *
 *    This file is part of the Motion application
 *    Copyright (C) 2019  Motion-Project Developers(motion-project.github.io)
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Library General Public
 *    License as published by the Free Software Foundation; either
 *    version 2 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Library General Public License for more details.
 *
 *    You should have received a copy of the GNU Library General Public
 *    License along with this library; if not, write to the
 *    Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 *    Boston, MA  02110-1301, USA.
*/
#ifndef _INCLUDE_UTIL_H_
#define _INCLUDE_UTIL_H_

#if (LIBAVFORMAT_VERSION_MAJOR >= 56)
    #define MY_PIX_FMT_YUV420P   AV_PIX_FMT_YUV420P
    #define MY_PIX_FMT_YUVJ420P  AV_PIX_FMT_YUVJ420P
    #define MyPixelFormat AVPixelFormat
#else  //Old ffmpeg pixel formats
    #define MY_PIX_FMT_YUV420P   PIX_FMT_YUV420P
    #define MY_PIX_FMT_YUVJ420P  PIX_FMT_YUVJ420P
    #define MyPixelFormat PixelFormat
#endif  //Libavformat >= 56

#if (LIBAVFORMAT_VERSION_MAJOR >= 55) || ((LIBAVFORMAT_VERSION_MAJOR == 54) && (LIBAVFORMAT_VERSION_MINOR > 6))
    #define MY_FLAG_READ       AVIO_FLAG_READ
    #define MY_FLAG_WRITE      AVIO_FLAG_WRITE
    #define MY_FLAG_READ_WRITE AVIO_FLAG_READ_WRITE
#else  //Older versions
    #define MY_FLAG_READ       URL_RDONLY
    #define MY_FLAG_WRITE      URL_WRONLY
    #define MY_FLAG_READ_WRITE URL_RDWR
#endif

#if (LIBAVFORMAT_VERSION_MAJOR >= 56)
    #define MY_CODEC_ID_MSMPEG4V2 AV_CODEC_ID_MSMPEG4V2
    #define MY_CODEC_ID_FLV1      AV_CODEC_ID_FLV1
    #define MY_CODEC_ID_FFV1      AV_CODEC_ID_FFV1
    #define MY_CODEC_ID_NONE      AV_CODEC_ID_NONE
    #define MY_CODEC_ID_MPEG2VIDEO AV_CODEC_ID_MPEG2VIDEO
    #define MY_CODEC_ID_H264      AV_CODEC_ID_H264
    #define MY_CODEC_ID_HEVC      AV_CODEC_ID_HEVC
#else
    #define MY_CODEC_ID_MSMPEG4V2 CODEC_ID_MSMPEG4V2
    #define MY_CODEC_ID_FLV1      CODEC_ID_FLV1
    #define MY_CODEC_ID_FFV1      CODEC_ID_FFV1
    #define MY_CODEC_ID_NONE      CODEC_ID_NONE
    #define MY_CODEC_ID_MPEG2VIDEO CODEC_ID_MPEG2VIDEO
    #define MY_CODEC_ID_H264      CODEC_ID_H264
    #define MY_CODEC_ID_HEVC      CODEC_ID_H264
#endif

#if (LIBAVCODEC_VERSION_MAJOR >= 57)
    #define MY_CODEC_FLAG_GLOBAL_HEADER AV_CODEC_FLAG_GLOBAL_HEADER
    #define MY_CODEC_FLAG_QSCALE        AV_CODEC_FLAG_QSCALE
#else
    #define MY_CODEC_FLAG_GLOBAL_HEADER CODEC_FLAG_GLOBAL_HEADER
    #define MY_CODEC_FLAG_QSCALE        CODEC_FLAG_QSCALE
#endif

#ifdef HAVE_GETTEXT
    #include <libintl.h>
    extern int  _nl_msg_cat_cntr;    /* Required for changing the locale dynamically */
#endif

#define _(STRING) mytranslate_text(STRING)

#define SLEEP(seconds, nanoseconds) {              \
                struct timespec ts1;                \
                ts1.tv_sec = (seconds);             \
                ts1.tv_nsec = (nanoseconds);        \
                while (nanosleep(&ts1, &ts1) == -1); \
        }

    void * mymalloc(size_t);
    void * myrealloc(void *, size_t, const char *);
    FILE * myfopen(const char *, const char *);
    int myfclose(FILE *);
    size_t mystrftime(const struct ctx_cam *, char *, size_t, const char *, const struct timespec *, const char *, int);
    int mycreate_path(const char *);

    void mythreadname_set(const char *abbr, int threadnbr, const char *threadname);
    void mythreadname_get(char *threadname);
    int mycheck_passthrough(struct ctx_cam *cam);

    char* mytranslate_text(const char *msgid);
    void mytranslate_init(void);

    int mystrceq(const char* var1, const char* var2);
    int mystrcne(const char* var1, const char* var2);
    int mystreq(const char* var1, const char* var2);
    int mystrne(const char* var1, const char* var2);
    char *mystrdup(const char *);
    char *mystrcpy(char *, const char *);

    AVFrame *myframe_alloc(void);
    void myframe_free(AVFrame *frame);
    void mypacket_unref(AVPacket pkt);
    void myavcodec_close(AVCodecContext *codec_context);
    int myimage_get_buffer_size(enum MyPixelFormat pix_fmt, int width, int height);
    int myimage_copy_to_buffer(AVFrame *frame,uint8_t *buffer_ptr,enum MyPixelFormat pix_fmt,int width,int height,int dest_size);
    int myimage_fill_arrays(AVFrame *frame,uint8_t *buffer_ptr,enum MyPixelFormat pix_fmt,int width,int height);
    int mycopy_packet(AVPacket *dest_pkt, AVPacket *src_pkt);

#endif