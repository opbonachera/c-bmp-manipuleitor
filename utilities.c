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

    if(pos)
    {
        pos += strlen(separator);
    }

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

    return truncate(result);
}

int processArgument(char* argument, short int parameter, short int parameters[], short int* flag)
{
    //printf("Argument is (%s) Parameter is (%hd) Flag is (%d)\n", argument, parameter);

    if (!strcmp(argument, "red-tone"))
    {
        parameters[0] = parameter;
        return *flag |= RED_TONE;
    }
    if (!strcmp(argument, "blue-tone"))
    {
        parameters[1] = parameter;
        return *flag |= BLUE_TONE;
    }
    if (!strcmp(argument, "green-tone"))
    {
        parameters[2] = parameter;
        return *flag |=  GREEN_TONE;
    }
    if (!strcmp(argument, "reduce-contrast"))
    {
        parameters[3] = parameter;
        return *flag |=  REDUCE_CONTRAST;
    }
    if (!strcmp(argument, "increase-contrast"))
    {
        parameters[4] = parameter;
        return *flag |=  INCREASE_CONTRAST;
    }
    if (!strcmp(argument, "grayscale"))
        return *flag |=  GRAYSCALE;
    if (!strcmp(argument, "negative"))
        return *flag |=  NEGATIVE;
    if (!strcmp(argument, "crop"))
    {
        parameters[5] = parameter;
        return *flag |=  CROP;
    }
    if (!strcmp(argument, "shrink"))
    {
        parameters[6] = parameter;
        return *flag |=  SHRINK;
    }
    if (!strcmp(argument, "rotate-left"))
        return *flag |=  ROTATE_LEFT;
    if (!strcmp(argument, "rotate-right"))
        return *flag |=  ROTATE_RIGHT;
    if (!strcmp(argument, "flip-vertical"))
        return *flag |=  FLIP_VERTICAL;
    if (!strcmp(argument, "flip-horizontal"))
        return *flag |=  FLIP_HORIZONTAL;
    if (!strcmp(argument, "concat-vertical"))
        return *flag |=  CONCAT_VERTICAL;
    if (!strcmp(argument, "concat-horizontal"))
        return *flag |=  CONCAT_HORIZONTAL;
    if (!strcmp(argument, "pixelate"))
        return *flag |=  PIXELATE;
    if (!strcmp(argument, "blur"))
        return *flag |=  BLUR;

    return *flag;
}

int truncate(int intg)
{
    return intg < 0 ? 0 : intg > 101 ? 100 : intg;
}

char* getNewFilename(const char* firstFile, const char* secondFile, const char* filterName, const char* extension)
{

    size_t size = strlen(firstFile) + strlen(secondFile) + strlen(filterName) + strlen(extension) + 4;


    char* result = malloc(size);
    if (!result)
        return NULL;


    snprintf(result, size, "%s_%s_%s%s", firstFile, secondFile, filterName, extension);

    return result;
}
