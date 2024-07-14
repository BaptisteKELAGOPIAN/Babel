#include "audio.hpp"

Audio::Audio() : captured(SIZEBUFF * CHANNEL){
    enc = opus_encoder_create(SAMPLE, CHANNEL, OPUS_APPLICATION_AUDIO, &opusErr);
    Pa_Initialize();
    stream = nullptr;
    
    Pa_OpenDefaultStream(&stream, CHANNEL, CHANNEL, paInt16, SAMPLE, SIZEBUFF, nullptr, nullptr);
    Pa_StartStream(stream);
}

Audio::~Audio() {
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    opus_encoder_destroy(enc);
    opus_decoder_destroy(dec);
}

int Audio::DecodeAndPlay(std::vector<unsigned char> const& encoded) {
    std::vector<unsigned short> decoded(SIZEBUFF * CHANNEL);
    opus_int32 dec_bytes;
    if ((dec_bytes = opus_decode(dec, encoded.data(), enc_bytes,
        reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0)
    {
        std::cout << "opus_decode failed: " << dec_bytes << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    if ((paErr = Pa_WriteStream(stream, decoded.data(), SIZEBUFF)) != paNoError)
    {
        std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }
    return 0;
}

std::vector<unsigned char> Audio::EnregistreAndEncode(std::vector<unsigned char> encoded) {
    if ((paErr = Pa_ReadStream(stream, captured.data(), SIZEBUFF)) != paNoError)
    {
        std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
    }

    if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const*>(
        captured.data()), 480, encoded.data(), 480)) < 0)
    {
        std::cout << "opus_encode failed: " << enc_bytes << "\n";
        std::getline(std::cin, s);
    }
    return encoded;
}