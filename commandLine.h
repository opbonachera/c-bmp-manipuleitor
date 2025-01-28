#ifndef COMMAND_LINE_INCLUDED
#define COMMAND_LINE_INCLUDED

int processArgument(char* command, short int* parameter, short int* parameters, int* flag);
int processCommandLine(const int argc, char* argv[], short int* parameters, char* imageFiles[], char* filterFile[], int* flag);

#endif // COMMAND_LINE_INCLUDED
