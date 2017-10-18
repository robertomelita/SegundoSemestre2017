#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <stdio.h>
#include "audio.h"

ALuint load_a_sound(char *filename)
{
    ALuint buffer, source;
    alutInit(0, NULL);
    alGetError();
    buffer = alutCreateBufferFromFile(filename);
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    return source;
}
