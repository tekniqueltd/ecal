#ifndef _OCLEA_PIPELINE_VIDEOFRAME_H
#define _OCLEA_PIPELINE_VIDEOFRAME_H

#include <stdint.h>

namespace oclea {
namespace pipeline {

/**
 * @brief Video frame for raw YUV frame topics
 * 
 * Because protobuf isn't well suited for large messages the contents
 * for raw video frame topics are defined as a simple struct
 */
struct VideoFrame {
    uint16_t width;        //!< Width in pixels
    uint16_t height;       //!< Height in pixels
    uint32_t buffer_size;  //!< Number of bytes in buffer
    uint64_t pts_usecs;    //!< Presentation time stamp, in microseconds
    uint8_t  buffer[1];    //!< Buffer of size buffer_size
};

}
}

#endif // _OCLEA_PIPELINE_VIDEOFRAME_H
