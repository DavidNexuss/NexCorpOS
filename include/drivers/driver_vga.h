#pragma once
#include "drivers/driver.h"
#include "hardware/port.h"
#include "types.h"

class VGADriver : public Driver{

    protected:
        Port8Bit miscPort;
        Port8Bit crtcIndexPort;
        Port8Bit crtcDataPort;
        Port8Bit sequencerIndexPort;
        Port8Bit sequencerDataPort;
        Port8Bit graphicsControllerIndexPort;
        Port8Bit graphicsControllerDataPort;
        Port8Bit attributeControllerIndexPort;
        Port8Bit attributeControllerReadPort;
        Port8Bit attributeControllerWritePort;
        Port8Bit attributeControllerResetPort;

        void WriteRegisters(uint8_t* registers);
        uint8_t* getFrameBufferSegment();
        virtual uint8_t getColorIndex(uint8_t r,uint8_t g,uint8_t b);
        
    public:
        VGADriver();
        virtual ~VGADriver();
        
        virtual bool SupportMode(uint32_t width,uint32_t height,uint32_t depth);
        virtual bool SetMode(uint32_t width,uint32_t height,uint32_t depth);

        virtual void PutPixel(uint32_t x,uint32_t y,uint8_t colorIndex);
        virtual void PutPixel(uint32_t x,uint32_t y,uint8_t r,uint8_t g,uint8_t b);
};