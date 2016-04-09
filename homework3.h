typedef struct {
    int background;
    int redirect;
    int pipe;
    int splitChar;
} Options;

extern void redirect(char* input[], char* output);
extern void pipe_output(char* command1[], char* command2[]);
