#include "source.h"

void Source::Update()
{
char msg[128];
SetStart();
sprintf(msg, "%s: about to execute at time (starting timer)", SourceName()); Logger::LogEvent(msg);
Execute();
sprintf(msg, "%s: done executing, took: %fs", SourceName(), GetTime()); Logger::LogEvent(msg);
}