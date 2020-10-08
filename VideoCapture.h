#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H
#define CLEAR(x) memset(&(x), 0, sizeof(x))
#pragma message("test")

#include <vector>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h> /* getopt_long() */

#include <fcntl.h> /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

namespace low_level
{
    struct buffer
    {
        void *start;
        size_t length;
    };

    class VideoCapture
    {
    public:
        VideoCapture(const char *dev_name, const int height, const int width);
        ~VideoCapture();
        typedef std::vector<unsigned char> frame_type;
        const frame_type &get_buff();
        int read_frame(void);

    private:
        void set_frame_buffer(const void *p, int size);
        void init_video_capture(const char *device_name);
        void clear_video_capture();
        const int WIDTH = 800;
        const int HEIGHT = 600;
        const char *short_options = "d:hmruofc:";

        enum io_method
        {
            IO_METHOD_READ,
            IO_METHOD_MMAP,
            IO_METHOD_USERPTR,
        };

        static const struct option
            long_options[];

        //static const char *dev_name = "/dev/video2";
        io_method io{IO_METHOD_MMAP};
        int fd{-1};
        struct buffer *buffers;
        unsigned int n_buffers;
        int out_buf;
        int force_format;
        int frame_count{70};
        frame_type buff_frame;

        void open_device(const char *dev_name);
        void init_device(const char *dev_name);
        void init_map(const char *dev_name);
        void start_capturing();
        void main_step();
        void stop_capturing();
        void uninit_device();
        void close_device();
        void mainloop(void);

        void errno_exit(const char *s);
        int xioctl(int fh, int request, void *arg);
        void init_read(unsigned int buffer_size);
        void init_mmap(const char *dev_name);
        void init_userp(unsigned int buffer_size, const char *dev_name);
        void usage(FILE *fp, int argc, char **argv);
        void process_image(const void *p, int size);
    };
} // namespace low_level
#endif