// Structure to keep track of different options that can be selected
typedef struct {
    int background;
    int redirect;
    int pipe;
    int splitChar;
    int error;
} Options;

// Prototype functions for handling redirect and piping
extern void redirect(char* input[], char* output);
extern void pipe_output(char* command1[], char* command2[]);
