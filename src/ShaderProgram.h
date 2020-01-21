#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include "MatrixFactory.h"

#include "GL/glew.h"

namespace ShaderType {
    enum Type{
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };
};

class ShaderProgramException : public std::runtime_error {
    public:
        ShaderProgramException( const std::string & msg ) :
            std::runtime_error(msg) { }
};

class ShaderProgram {
    private:

        GLuint programID;
        
        std::string logString;
        std::unordered_map<std::string,GLint> uniformIDs;

        

    public:
        bool linked;
        ShaderProgram(){
            programID = 0;
            linked = false;
        }

        ~ShaderProgram(){
            if (programID != 0) {
                detach();
                uniformIDs.erase(uniformIDs.begin(),uniformIDs.end());
                
                // Deleting Program
                glUseProgram(0);
                glDeleteProgram (programID);
            }
            //delete[] shaderNames;
        }

        GLint getUniformLocation(const char* name) {
            std::unordered_map<std::string,GLint>::iterator it;
            it = uniformIDs.find(name);
            if(it == uniformIDs.end())
                uniformIDs[name] = glGetUniformLocation(programID,name);

            return uniformIDs[name];
        }

        void compileShaderFromFile(const char* fileName, ShaderType::Type type) /*throw( ShaderProgramException )*/{
                
                if(programID <= 0 ) {
                    programID = glCreateProgram();
                    if(programID == (GLuint)0) {
                        throw ShaderProgramException("Unable to create shader program.");
                    }
                }

                std::ifstream inFile( fileName, std::ios::in );
                if( !inFile ) {
                    std::string message = std::string("Unable to open: ") + fileName;
                    throw ShaderProgramException(message);
                }

                std::stringstream code;
                code << inFile.rdbuf();
                inFile.close();

                std::string source = code.str();
                GLuint shaderID = glCreateShader(type);
                if (shaderID == 0) {
                    throw ShaderProgramException("Unable to create shader");
                }


                const char * c_code = source.c_str();
                glShaderSource(shaderID, 1, &c_code, NULL );

                glCompileShader(shaderID);

                int result;

                glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result );
                if( GL_FALSE == result ) {
                    int length = 0;
                    std::string logString;
                    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length );
                    if( length > 0 ) {
                        char * c_log = new char[length];
                        int written = 0;
                        glGetShaderInfoLog(shaderID, length, &written, c_log);
                        logString = c_log;
                        delete [] c_log;
                    }
                    std::string msg;
                    if( fileName ) {
                        msg = std::string(fileName) + ": shader compilation failed\n";
                    } else {
                        msg = "Shader compilation failed.\n";
                    }
                    msg += logString;

                    throw ShaderProgramException(msg);

                } else {
                    glAttachShader(programID, shaderID);
                }
            }

        void bindAttribLocation(GLuint location, const char* name){
            glBindAttribLocation(programID,location,name);
        }

        void bindFragDataLocation(GLuint location, const char* name){
            glBindFragDataLocation(programID, location,name);
        }

        int getProgramID(){
            return programID;
        }

        void setProgramID(int p){
            programID = p;
        }

        bool isLinked(){
            return linked;
        }

        void detach () {
            if ( programID != 0 ) {
                GLint numShaders = 0;
                glGetProgramiv(programID, GL_ATTACHED_SHADERS, &numShaders);
                GLuint * shaderNames = new GLuint[numShaders];
                glGetAttachedShaders(programID, numShaders, NULL, shaderNames);

                // Deleting Shaders
                for (int i = 0; i < numShaders; i++) {
                    glDetachShader(programID,shaderNames[i]);
                    glDeleteShader(shaderNames[i]);
                }
                delete[] shaderNames;
            }
        }

        void link() /*throw(ShaderProgramException)*/{
            if( linked ) return;
            if( programID <= 0 )
                throw ShaderProgramException("Program has not been compiled.");

            glLinkProgram(programID);

            int status = 0;
            glGetProgramiv( programID, GL_LINK_STATUS, &status);
            if(status == GL_FALSE) {
                int length = 0;
                std::string logString;

                glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length );

                if( length > 0 ) {
                    char * c_log = new char[length];
                    int written = 0;
                    glGetProgramInfoLog(programID, length, &written, c_log);
                    logString = c_log;
                    delete [] c_log;
                }

                throw ShaderProgramException(std::string("Program link failed:\n") + logString);
            } else {
                //uniformLocations.clear();
                linked = true;
            }
        }

        void use() /*throw(ShaderProgramException)*/{
            if(programID <= 0 || (! linked))
                throw ShaderProgramException("Shader has not been linked");
            glUseProgram(programID);
        }


        void setUniform(const char* name, float x, float y, float z, float w){
            GLint uniformID = getUniformLocation(name);
            glUniform4f(uniformID,(GLfloat)x,(GLfloat)y,(GLfloat)z,(GLfloat)w);
        }

        void setUniform(const char* name, float value) {
            GLint uniformID = getUniformLocation(name);
            glUniform1f(uniformID, value);
        }

		void setUniform(const char* name, int value) {
			GLint uniformID = getUniformLocation(name);
			glUniform1i(uniformID, value);
		}


        void setUniform(const char* name, const float* m){
            GLint uniformID = getUniformLocation(name);
            glUniformMatrix4fv(uniformID,1,GL_TRUE,m);
        }

        void setUniform(const char* name, const float* m, GLboolean b) {
            GLint uniformID = getUniformLocation(name);
            glUniformMatrix4fv(uniformID,1, b, m);
        }

        void addUniformBlock(const char* name, GLuint location){
            GLint uboId = glGetUniformBlockIndex(this->programID,name);
            glUniformBlockBinding(this->programID, uboId, location);

        }
};

#endif