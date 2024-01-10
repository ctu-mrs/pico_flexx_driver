/****************************************************************************\
 * Copyright (C) 2015 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <royale/Definitions.hpp>
#include <royale/StreamId.hpp>
#include <royale/Vector.hpp>

namespace royale {
/**
 *  Infrared image with 8Bit mono information for every pixel.
 *  The resulting image will be lens distorted. To remove the distortion
 *  one can use the lens parameters from the camera.
 */
struct IRImage {
    int64_t timestamp; //!< timestamp for the frame
    StreamId streamId; //!< stream which produced the data
    uint16_t width;    //!< width of depth image
    uint16_t height;   //!< height of depth image
    uint8_t *data;     //!< 8Bit mono IR image

    friend void swap(IRImage &first, IRImage &second) {
        using std::swap;

        swap(first.timestamp, second.timestamp);
        swap(first.streamId, second.streamId);
        swap(first.width, second.width);
        swap(first.height, second.height);
        swap(first.data, second.data);
        swap(first.irCopy, second.irCopy);
        swap(first.isCopy, second.isCopy);
    }

    IRImage() : timestamp(0),
                streamId(0u),
                width(0u),
                height(0u),
                data(nullptr),
                isCopy(false) {
    }

    IRImage(const IRImage &dd) {
        this->timestamp = dd.timestamp;
        this->streamId = dd.streamId;
        this->width = dd.width;
        this->height = dd.height;

        const auto numPixels = this->width * this->height;

        if (numPixels && dd.data) {
            this->irCopy.resize(numPixels);
            memcpy(&this->irCopy[0], &dd.data[0], numPixels * sizeof(uint8_t));
            this->data = &this->irCopy[0];
        }

        this->isCopy = true;
    }

    IRImage(IRImage &&other) noexcept
        : IRImage() {
        swap(*this, other);
    }

    IRImage &operator=(IRImage dd) {
        swap(*this, dd);

        return *this;
    }

    uint8_t getIR(size_t idx) const {
        if (this->data) {
            return this->data[idx];
        } else {
            return 0u;
        }
    }
    size_t getNumPoints() const {
        return this->width * this->height;
    }

    bool getIsCopy() const {
        return isCopy;
    }

  private:
    royale::Vector<uint8_t> irCopy;
    bool isCopy;
};

} // namespace royale