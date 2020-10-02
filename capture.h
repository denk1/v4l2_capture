 #ifndef CAPTURE_H
 #define CAPTURE_H
 #define CLEAR(x) memset(&(x), 0, sizeof(x))
 #pragma message("test")
    enum io_method {
	    IO_METHOD_READ,
	    IO_METHOD_MMAP,
	    IO_METHOD_USERPTR,
    };

    struct buffer {
	    void   *start;
	    size_t  length;
    };

    inline const int WIDTH = 1184;
    inline const int HEIGHT = 656;
    static const char            *dev_name =  "/dev/video0";
    static enum io_method   io = IO_METHOD_MMAP;
    static int              fd = -1;
    static struct buffer          *buffers;
    static unsigned int     n_buffers;
    static int              out_buf;
    static int              force_format;
    static int              frame_count = 70;
    inline unsigned char my_frame[HEIGHT * WIDTH * 2];


void open_device();
void init_device();
void start_capturing();
int read_frame(void);
void main_step();
void stop_capturing();
void uninit_device();
void close_device();
#endif