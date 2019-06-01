#include "SoundLocator.h"

NullAudio SoundLocator::nullService_;
Audio* SoundLocator::service_;
bool SoundLocator::active = false;
