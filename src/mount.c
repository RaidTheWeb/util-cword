#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <util/messages.h>
#include <cword/mount.h>

// Command line parsing.
extern int opterr;

int main(int argc, char *argv[]) {
    // First, parse the command line.
    opterr = 0; // Disable getopt warnings, we will use our own.
    int option = 0;
    char *type = NULL;
    char *device = NULL;
    char *mount_point = NULL;

    while ((option = getopt(argc, argv, "Vht:")) != -1) {
        switch (option) {
            case 'V':
                puts("mount from util-cword");
                exit(0);
                break;
            case 'h':
                puts("Usage:");
                printf("\t%s [options] <device> <destination>\n", argv[0]);
                puts("");
                puts("Options:");
                puts("\t-V\tPrints the version of the program");
                puts("\t-h\tDisplays this help message");
                puts("\t-t\tTarget filesystem type to mount");
                exit(0);
                break;
            case 't':
                type = strdup(optarg);
                break;
            default:
                error("Unknown option");
        }
    }

    // Device and mount point.
    device = argv[optind];
    mount_point = argv[optind + 1];

    // Check values.
    if (!type || !device || !mount_point) {
        error("Invalid program flags! Have you tried '-h'?");
    }

    // Start the actual program.
    if (mount(device, mount_point, type, 0, 0)) {
        error("Couldn't mount device (syscall returned -1)");
    }

    // Free structures.
    free(type);
}
