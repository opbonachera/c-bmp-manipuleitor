#include "utilities.h"
#include "constantes.h"

int checkArgumentType(char* argument, char* separator)
{
    return (int)strstr(argument, separator);
}

char* getArgument(const char* argument, const char* separator)
{

    char* copy = malloc(strlen(argument) + 1);
    if (!copy)
    {
        return NULL;
    }

    strcpy(copy, argument);


    char* pos = strstr(copy, separator);
    if (!pos)
    {
        free(copy);
        return NULL;
    }

    pos += strlen(separator);

    char* equalSymbol = strchr(pos, '=');
    if (equalSymbol)
    {
        *equalSymbol = '\0';
    }


    char* result = strdup(pos);
    free(copy);
    return result;
}

int getParameter(char* parameter)
{
    char* copy = malloc(strlen(parameter) + 1);

    if (!copy)
        return -1;

    strcpy(copy, parameter);

    char* pos = strrchr(copy, '=');

    if (!pos)
        return -1;

    pos++;

    int result = atoi(pos);

    free(copy);

    return result;
}


int processArgument(char* argument, short int* parameter, short int* parameters[], int* flag)
{
    printf("Argument is (%s) Parameter is (%d) flag is (%d) \n", argument, parameter, *flag);
    if (!strcmp(argument, "red-tone"))
    {
        parameters[1] = parameter;
        return *flag | RED_TONE;
    }

    if (!strcmp(argument, "blue-tone"))
    {
        parameters[2] = parameter;
        return *flag | BLUE_TONE;
    }

    if (!strcmp(argument, "green-tone"))
    {
        parameters[3] = parameter;
        return *flag | GREEN_TONE;
    }

    if (!strcmp(argument, "reduce-contrast"))
    {
        parameters[4] = parameter;
        return *flag | REDUCE_CONTRAST;
    }

    if (!strcmp(argument, "increase-contrast"))
    {
        parameters[5] = parameter;
        return *flag | INCREASE_CONTRAST;
    }

    if (!strcmp(argument, "grayscale"))
        return *flag | GRAYSCALE;

    if (!strcmp(argument, "negative"))
        return *flag | NEGATIVE;

    if (!strcmp(argument, "crop"))
    {
        parameters[6] = parameter;
        return *flag | CROP;
    }

    if (!strcmp(argument, "shrink"))
    {
        parameters[7] = parameter;
        return *flag | SHRINK;
    }

    if (!strcmp(argument, "rotate-left"))
        return *flag | ROTATE_LEFT;

    if (!strcmp(argument, "rotate-right"))
        return *flag | ROTATE_RIGHT;

    if (!strcmp(argument, "flip-vertical"))
        return *flag | FLIP_VERTICAL;

    if (!strcmp(argument, "flip-horizontal"))
        return *flag | FLIP_HORIZONTAL;

    if (!strcmp(argument, "concat-vertical"))
        return *flag | CONCAT_VERTICAL;

    if (!strcmp(argument, "concat-horizontal"))
        return *flag | CONCAT_HORIZONTAL;

    if (!strcmp(argument, "pixelate"))
        return *flag | PIXELATE;

    if (!strcmp(argument, "blur"))
        return *flag | BLUR;

    return *flag; // Default return if no match
}
