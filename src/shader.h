#ifndef SHADER_H
#define SHADER_H
#include <string>
class Shader {
    private:
        unsigned int shaderProgram;

        std::string loadShaderFileFromDisk(const std::string &path);
        unsigned int compileShader(int shaderType, std::string shaderSource);
    public:
        Shader(const std::string &vertPath, const std::string &fragPath);
        ~Shader();

        void bind();


        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
};

#endif
