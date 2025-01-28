#ifndef COMMAND_LINE_INCLUDED
#define COMMAND_LINE_INCLUDED

int     processArgument(char* argument, short int* parameter, short int* parameterList, unsigned int flag);
int     processCommandLine(const int argc, char* argv[], int* parameters, char* imageFiles[], char* configFiles[], int* flag);

#endif // COMMAND_LINE_INCLUDED
