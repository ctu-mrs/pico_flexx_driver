/****************************************************************************\
* Copyright (C) 2019 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <royale/DepthImage.hpp>
#include <royale/IRImage.hpp>

namespace royale {
/**
 *  This represents combination of both depth and IR image.
 *  Provides depth, confidence and IR 8Bit mono information for every pixel.
 *
 *  Exception Note: For use-cases with UR larger than 8.191 m no confidence
 *  information is available.
 *
 *  As the DepthImage only contains z but no x and y information the resulting
 *  image as well as the IR image will have lens distortion.
 */
struct DepthIRImage {
    int64_t timestamp;  //!< timestamp for the frame
    StreamId streamId;  //!< stream which produced the data
    uint16_t width;     //!< width of depth image
    uint16_t height;    //!< height of depth image
    uint16_t *dpData;   //!< depth and confidence for the pixel
    uint8_t *irData;    //!< 8Bit mono IR image
    bool hasConfidence; //!< to check presence of confidence information

    friend void swap(DepthIRImage &first, DepthIRImage &second) {
        using std::swap;

        swap(first.timestamp, second.timestamp);
        swap(first.streamId, second.streamId);
        swap(first.width, second.width);
        swap(first.height, second.height);
        swap(first.dpData, second.dpData);
        swap(first.irData, second.irData);
        swap(first.hasConfidence, second.hasConfidence);
        swap(first.irCopy, second.irCopy);
        swap(first.depthCopy, second.depthCopy);
        swap(first.isCopy, second.isCopy);
    }

    DepthIRImage() : timestamp(0),
                     streamId(0u),
                     width(0u),
                     height(0u),
                     dpData(nullptr),
                     irData(nullptr),
                     hasConfidence(false),
                     isCopy(false) {
    }

    DepthIRImage(const DepthIRImage &dd) {
        this->timestamp = dd.timestamp;
        this->streamId = dd.streamId;
        this->width = dd.width;
        this->height = dd.height;
        this->hasConfidence = dd.hasConfidence;
        const auto numPixels = this->width * this->height;

        if (numPixels && dd.dpData && dd.irData) {
            this->irCopy.resize(numPixels);
            memcpy(&this->irCopy[0], &dd.irData[0], numPixels * sizeof(uint8_t));
            this->irData = &this->irCopy[0];

            this->depthCopy.resize(numPixels);
            memcpy(&this->depthCopy[0], &dd.dpData[0], numPixels * sizeof(uint16_t));
            this->dpData = &this->depthCopy[0];
        }

        this->isCopy = true;
    }

    DepthIRImage(DepthIRImage &&other) noexcept
        : DepthIRImage() {
        swap(*this, other);
    }

    DepthIRImage &operator=(DepthIRImage dd) {
        swap(*this, dd);

        return *this;
    }

    uint8_t getIR(size_t idx) const {
        if (this->irData) {
            return this->irData[idx];
        } else {
            return 0u;
        }
    }

    uint16_t getDepth(size_t idx) const {
        if (this->dpData) {
            return this->dpData[idx];
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
    royale::Vector<uint16_t> depthCopy;
    bool isCopy;
};
} // namespace royale
