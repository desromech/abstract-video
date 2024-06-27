#include <stdio.h>
#include <string.h>
#include <string>
#include <AVIDEO/avideo.hpp>

class Sample
{
public:
    avideo_platform *platform = nullptr;
    avideo_context_ref context;
    avideo_stream_ref stream;

    void printHelp()
    {
        printf("DumpFrames <video>\n");
    }

    int main(int argc, const char *argv[])
    {
        std::string url;

        for(int i = 1; i < argc; ++i)
        {
            if(!strcmp(argv[i], "-h"))
            {
                printHelp();
                return 0;
            }
            else
            {
                url = argv[i];
            }
        }

        if(url.empty())
        {
            printHelp();
            return 0;
        }

        // Get the platform.
        avideo_size platformCount = 0;
        avideoGetPlatforms(0, nullptr, &platformCount);
        if(!platformCount)
        {
            fprintf(stderr, "No avideo platform is available.\n");
            return 1;
        }
        avideoGetPlatforms(1, &platform, nullptr);

        printf("Avideo platform: %s\n", platform->getName());

        // Create the context
        avideo_context_open_info contextOpenInfo = {};
        context = platform->openContext(&contextOpenInfo);
        if(!context)
        {
            fprintf(stderr, "Failed to open the avideo context.\n");
            return 1;
        }
        
        // Open the stream
        stream = context->openStreamWithURL(url.c_str());
        if(!stream)
        {
            fprintf(stderr, "Failed to open an avideo stream.\n");
            return 1;
        }

        return 0;
    }
};

int main(int argc, const char *argv[])
{
    return Sample().main(argc, argv);
}
