#include <stdio.h>
#include <stdlib.h>

#include "imagegeneration.h"

int main(int argc, char* argv[])
{

    bmpManipuleitor(argc, argv);

    char* res = getNewFilename("Ornella", "paula", "bonachera", ".bmp");
    printf("result is (%s)\n", res);
    return 0;
}

