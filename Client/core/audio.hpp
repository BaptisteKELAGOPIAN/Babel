#include "C:\msys64\mingw64\include\opus\opus.h"
#include <portaudio.h>
#include <iostream>
#include <vector>

class Audio {
    
public:
    int const CHANNEL = 2;
    int const SIZEBUFF = 480;
    int const SAMPLE = 48000;
    int const SEC = 5;
    int opusErr;
    PaStream* stream;
    OpusEncoder* enc;
    std::string s;
    int paErr;

    std::vector<unsigned short> captured;
    std::vector<unsigned char> encoded;

    opus_int32 enc_bytes;
    OpusDecoder* dec = opus_decoder_create(SAMPLE, CHANNEL, &opusErr);
    
    Audio();
    ~Audio();

    int DecodeAndPlay(std::vector<unsigned char> const& encoded);
    std::vector<unsigned char> EnregistreAndEncode(std::vector<unsigned char>);

    int boucle() {
        int framesProcessed = 0;
        std::vector <unsigned char> encoded(SIZEBUFF * CHANNEL);
        while (framesProcessed < SAMPLE * SEC)
        {
            encoded = EnregistreAndEncode(encoded);
            DecodeAndPlay(encoded);
            framesProcessed += SIZEBUFF;
        }
        return 0;
    }
};