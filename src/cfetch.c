#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <qword/memstats.h>

#define BLACK   "\e[40m"      /* Black */
#define RED     "\e[41m"      /* Red */
#define GREEN   "\e[42m"      /* Green */
#define YELLOW  "\e[43m"      /* Yellow */
#define BLUE    "\e[44m"      /* Blue */
#define MAGENTA "\e[45m"      /* Magenta */
#define CYAN    "\e[46m"      /* Cyan */
#define WHITE   "\e[47m"      /* White */

#define BLACK_CHAR   'N'
#define CYAN_CHAR    'y'
#define MAGENTA_CHAR 'c'
#define WHITE_CHAR   'W'

#define CYAN_FG    "\e[36m"
#define MAGENTA_FG "\e[35m"
#define RESET      "\e[0m"

// Logo.
const char* line1 = "                                                 ";
const char* line2 = "                                                 ";
const char* line3 = "                                                 ";
const char* line4 = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyy          ";
const char* line5 = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyN         ";
const char* line6 = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyN         ";
const char* line7 = "         yyyyyNNNNNNNNNNNNNNNNNNNNNNNNNN         ";
const char* line8 = "         yyyyyN                                  ";
const char* line9 = "         yyyyyN                                  ";
const char* lineA = "         yyyyyN                                  ";
const char* lineB = "         yyyyyN                                  ";
const char* lineC = "         yyyyyN                                  ";
const char* lineD = "         yyyyyN                                  ";
const char* lineE = "         yyyyyN                                  ";
const char* lineF = "         yyyyyN                                  ";
const char* lineG = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyy          ";
const char* lineH = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyN         ";
const char* lineI = "         yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyN         ";
const char* lineJ = "          NNNNNNNNNNNNNNNNNNNNNNNNNNNNNN         ";
const char* lineK = "                                                 ";
const char* lineL = "                                                 ";
const char* lineM = "                                                 ";

char username[1024] = {0}; // So we don't use 1 KiB of stack for a username.
char hostname[1024] = {0}; // Ditto.
char dashes[1024]   = {0}; // Ditto.
char cpuname[1024]  = {0}; // Ditto.
struct memstats mem = {0}; // Memory stats.

void img_printf(const char* img, const char* message, ...);
void get_cpu_name(char *str);

void removeStringTrailingNewline(char *str) {
    if (str == NULL)
        return;
    int length = strlen(str);
    if (str[length-1] == '\n')
        str[length-1]  = '\0';
}

int main(void) {
    // User and host.
    strcpy(username, getpwuid(geteuid())->pw_name);
    gethostname(hostname, 1024);

    // OS detection.
    struct utsname buffer;
    uname(&buffer);
    char* os      = buffer.sysname;
    char* machine = buffer.machine;

    // Dashes
    size_t dashes_length = strlen(username) + strlen(hostname) + 1;

    for (size_t i = 0; i != dashes_length; i++)
        strcat(dashes, "-");

    // Terminal.
    char* tty_name = ttyname(STDIN_FILENO);

    // Shell detection.
    char* shell = getpwuid(geteuid())->pw_shell;
    removeStringTrailingNewline(shell);

    // TODO: Resolution based on TTY
    FILE* fp = fopen("/etc/resolution", "r");
    char resolutionx[16]; // resolution width
    char resolutiony[16]; // resolution height
    fgets(resolutionx, 16, fp);
    fgets(resolutiony, 16, fp);

    // Strip newlines
    resolutionx[strcspn(resolutionx, "\n")] = 0;
    resolutiony[strcspn(resolutiony, "\n")] = 0;

    char resolution[64];
    sprintf(resolution, "%sx%s", resolutionx, resolutiony);

    // CPU detection.
    get_cpu_name(cpuname);

    // TODO: GPU detection.
    char* gpu = "Generic VESA-capable device";

    // Memory detection.
    getmemstats(&mem);

    // Print the info and logo.
    img_printf(line1, "");
    img_printf(line2, "");
    img_printf(line3, "");
    img_printf(line4, "%s%s%s@%s%s%s", CYAN_FG, username, RESET, CYAN_FG, hostname, RESET);
    img_printf(line5, "%s", dashes);
    img_printf(line6, "");
    img_printf(line7, "%sOS%s: %s (%s)", CYAN_FG, RESET, os, machine);
    img_printf(line8, "%sTerminal%s: %s", CYAN_FG, RESET, tty_name);
    img_printf(line9, "%sShell%s: %s", CYAN_FG, RESET, shell);
    img_printf(lineA, "%sResolution%s: %s", CYAN_FG, RESET, resolution);
    img_printf(lineB, "%sCPU%s: %s", CYAN_FG, RESET, cpuname);
    img_printf(lineC, "%sGPU%s: %s", CYAN_FG, RESET, gpu);
    img_printf(lineD, "%sMemory%s: %lluMiB/%lluMiB", CYAN_FG, RESET, mem.used / (1024 * 1024), mem.total / (1024 * 1024));
    img_printf(lineE, "");
    img_printf(lineF, "%s   %s   %s   %s   %s   %s   %s   %s   %s", BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, RESET);
    img_printf(lineG, "");
    img_printf(lineH, "");
    img_printf(lineI, "");
    img_printf(lineJ, "");
    img_printf(lineK, "");
    img_printf(lineL, "");
    img_printf(lineM, "");

    return 0;
}

void img_printf(const char* img, const char* message, ...) {
    va_list args;

    va_start(args, message);

    for (size_t i = 0; img[i]; i++) {
        switch (img[i]) {
            case CYAN_CHAR:
                printf("%s %s", CYAN, RESET);
                break;
            case MAGENTA_CHAR:
                printf("%s %s", MAGENTA, RESET);
                break;
            case WHITE_CHAR:
                printf("%s %s", WHITE, RESET);
                break;
            case BLACK_CHAR:
                printf("%s %s", BLACK, RESET);
                break;
            default:
                putchar(img[i]);
        }
    }

    vprintf(message, args);
    putchar('\n');
    va_end(args);
}

void get_cpu_name(char *str) {
    asm volatile (
        "mov eax, 0x80000002;"
        "cpuid;"
        "stosd;"
        "mov eax, ebx;"
        "stosd;"
        "mov eax, ecx;"
        "stosd;"
        "mov eax, edx;"
        "stosd;"
        "mov eax, 0x80000003;"
        "cpuid;"
        "stosd;"
        "mov eax, ebx;"
        "stosd;"
        "mov eax, ecx;"
        "stosd;"
        "mov eax, edx;"
        "stosd;"
        "mov eax, 0x80000004;"
        "cpuid;"
        "stosd;"
        "mov eax, ebx;"
        "stosd;"
        :
        : "D" (str)
        : "rax", "rbx", "rcx", "rdx"
    );
}
