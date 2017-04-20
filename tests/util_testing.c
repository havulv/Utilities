

#include <stdlib.h>
#include <stdint.h>
#include "utils.h"



int main(void) {
    char *header = "Testing_Utilities_Header";
    uint8_t hsize = 24;
    char *data = "This is some data";
    uint8_t dsize = 17;

    /* Check that hex_dump and pointer dump are correct
     * for packed values */
    char *packed = malloc(1 + 1 + hsize + dsize); 
    packed[0] = (char) hsize;
    for (int i = 0; i < hsize; i++) {
        packed[i+1] = header[i];
    }
    packed[hsize+1] = (char) dsize;
    for (int j = 0; j < dsize; j++) {
        packed[hsize+2+j] = data[j];
    }
    hex_dump(packed, 2 + hsize + dsize);
    puts("");
    pointer_dump(packed, 2 + hsize + dsize);

    /* Create a bad value for checking on hex_check
     * Should give two reds on the bad packed stuff */

    unsigned char *bad_packed = malloc(2 + hsize + dsize);
    for (int k = 0; k < (2 + hsize + dsize); k++) {
        bad_packed[k] = packed[k];
    }
    bad_packed[hsize] = (unsigned char) 0x30;
    bad_packed[dsize+2] = (unsigned char) 0x7e;
    bad_packed[9] = (unsigned char) 0x29;
    puts("");
    int test = hex_check(packed, bad_packed, 2 + hsize + dsize);
    puts("");
    if (!test) {
        puts("Failed");
    } else {
        puts("Passed");
    }
    free(bad_packed);
    free(packed);
}

