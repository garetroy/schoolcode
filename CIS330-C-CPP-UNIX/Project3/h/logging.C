#include <logging.h>

using namespace std;

FILE* Logger::logger = fopen("logger", "w");

DataFlowException::DataFlowException(const char *type, const char *error){
	sprintf(msg, "Throwing Exception: (%s): %s", type, error);
	Logger::LogEvent(msg);	
}

void
Logger::LogEvent(const char *event){
	fprintf(logger, "%s\n", event);
}

void
Logger::Finalize(){
	fclose(logger);
}