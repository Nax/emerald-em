#include <libemerald/Context.h>

Context::Context(Config& cfg)
: cfg{cfg}
, rom{*this}
{
}
