typedef struct {
    int background;
    int redirect;
    int pipe;
    int splitChar;
} Options;

extern void redirect(char* input[], char* output);

