#include <stdio.h>
#include <string.h>
#include <string>
#include <AVIDEO/avideo.hpp>
#include "SDL2/SDL.h"

class Sample
{
public:
    avideo_platform *platform = nullptr;
    avideo_context_ref context;
    avideo_container_ref container;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *playbackTexture = nullptr;
    bool isQuiting = false;

    void printHelp()
    {
        printf("Playback <video>\n");
    }

    void processEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    isQuiting = true;
                break;
            case SDL_QUIT:
                isQuiting = true;
                break;
            }
        }
    }

    int main(int argc, const char *argv[])
    {
        std::string url;

        for (int i = 1; i < argc; ++i)
        {
            if (!strcmp(argv[i], "-h"))
            {
                printHelp();
                return 0;
            }
            else
            {
                url = argv[i];
            }
        }

        if (url.empty())
        {
            printHelp();
            return 0;
        }

        // Get the platform.
        avideo_size platformCount = 0;
        avideoGetPlatforms(0, nullptr, &platformCount);
        if (!platformCount)
        {
            fprintf(stderr, "No avideo platform is available.\n");
            return 1;
        }
        avideoGetPlatforms(1, &platform, nullptr);

        printf("Avideo platform: %s\n", platform->getName());

        // Create the context
        avideo_context_open_info contextOpenInfo = {};
        context = platform->openContext(&contextOpenInfo);
        if (!context)
        {
            fprintf(stderr, "Failed to open the avideo context.\n");
            return 1;
        }

        // Open the stream
        container = context->openContainerWithURL(url.c_str());
        if (!container)
        {
            fprintf(stderr, "Failed to open an avideo stream.\n");
            return 1;
        }

        printf("Opened container with start time: %f duration: %f\n", container->getStartTime(), container->getDuration());

        if (container->hasVideoStream())
        {
            printf("Video stream width: %d height: %d fps: %f frames: %d\n", container->getVideoStreamWidth(), container->getVideoStreamHeight(), container->getVideoStreamFrameRate(), container->getVideoStreamFrameCount());
        }

        if (container->hasAudioStream())
        {
            printf("Audio stream channels: %d sampleRate: %d\n", container->getAudioStreamChannels(), container->getAudioStreamSampleRate());
        }

        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Playback", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        container->seekTime(0.0);

        while (!isQuiting)
        {
            processEvents();
            bool hasGottenFrame = false;
            int textureFrameWidth = -1;
            int textureFrameHeight = -1;
            int videoFrameWidth = container->getVideoFrameWidth();
            int videoFrameHeight = container->getVideoFrameHeight();

            while (avideoContainerFetchAndDecodeNextPacket(container.get()) == AVIDEO_OK && !hasGottenFrame)
            {
                avideo_error videoDecodeError = avideoContainerFetchAndDecodeNextVideoFrame(container.get());
                while(videoDecodeError == AVIDEO_AGAIN)
                {
                    avideoContainerFetchAndDecodeNextPacket(container.get());
                    videoDecodeError = avideoContainerFetchAndDecodeNextVideoFrame(container.get());
                }

                if (videoDecodeError == AVIDEO_OK)
                {                        
                    printf("Frame %d width %d height %d\n", container->getVideoFrameIndex(), container->getVideoFrameWidth(), container->getVideoFrameHeight());
                    videoFrameWidth = container->getVideoFrameWidth();
                    videoFrameHeight = container->getVideoFrameHeight();
                    hasGottenFrame = true;
                }
            }

            // ensure the texture has the correct size.
            if (textureFrameWidth != videoFrameWidth || textureFrameHeight != videoFrameHeight)
            {
                textureFrameWidth = videoFrameWidth;
                textureFrameHeight = videoFrameHeight;

                if (playbackTexture)
                    SDL_DestroyTexture(playbackTexture);

                playbackTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STREAMING, textureFrameWidth, textureFrameHeight);
                SDL_SetTextureBlendMode(playbackTexture, SDL_BLENDMODE_NONE);
            }

            if (playbackTexture)
            {
                if (hasGottenFrame)
                {
                    void *pixels;
                    int pitch;
                    SDL_LockTexture(playbackTexture, nullptr, &pixels, &pitch);
                    container->readSRGB32ConvertedFrame(pitch, pixels);
                    SDL_UnlockTexture(playbackTexture);

                    SDL_RenderCopy(renderer, playbackTexture, nullptr, nullptr);
                    SDL_RenderPresent(renderer);
                }
            }

            SDL_Delay(1000 / 30);
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 0;
    }
};

int main(int argc, const char *argv[])
{
    return Sample().main(argc, argv);
}
