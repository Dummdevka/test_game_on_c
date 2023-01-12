#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../headers/shader.h"

char *read_file(const char * filename);

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {
    //Create vertex
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    char *VertexShaderCode;
    //Create fragment
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    char *FragmentShaderCode;

    VertexShaderCode = read_file(vertex_file_path);
    FragmentShaderCode = read_file(fragment_file_path);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    //Compile vertex
    printf("Compiling shader: %s\n", vertex_file_path);
    const char * VertexSourcePointer = VertexShaderCode;
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    //Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ) {
       char VertexShaderErrorMessage[InfoLogLength+1]; 
       glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
       printf("%s\n", VertexShaderErrorMessage);
    }

    //Compile Shader
    printf("Compiling shader: %s\n", fragment_file_path);
    const char * FragmentSourcePointer = FragmentShaderCode;
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    //Check Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ) {
       char FragmentShaderErrorMessage[InfoLogLength+1]; 
       glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
       printf("%s\n", FragmentShaderErrorMessage);
    }
    else {
        printf("Shader compiled\n");
    }

    //Link the program
    printf("Linking program");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    //Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0) {
        char ProgramErrorMessage[InfoLogLength+1];
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", ProgramErrorMessage);
    }
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    free(VertexShaderCode);
    free(FragmentShaderCode);

    return ProgramID;
}

char * read_file(const char * filename) {
    FILE * fp;
    int chunk = 10; // this will extend (memory allocation size)
    char * buffer = realloc(NULL, sizeof(*buffer)*chunk); // to hold the contents
    int current; // to hold current symbol 

    int position = 0; // position of the cursor in buffer
    //Open file
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("The file doesn't exist");
        exit(-1);
    }
    //Read file
    do {
        current = getc(fp);
        if(current == EOF) break;
        buffer[position++] = current;
        //Extend buffer size
        if(position == chunk) {
            buffer = realloc(buffer, sizeof(*buffer)*(chunk+= 16));
        }
    } while(current != EOF);
    //Return pointer to the start of file
    buffer[position] = '\0';
    return buffer;
}
