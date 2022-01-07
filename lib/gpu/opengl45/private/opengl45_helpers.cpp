#include "opengl45_helpers.hpp"
#include <cassert>
#include <iostream>

namespace at
{

GLint gl_attribute_count(gpu_vertex_attribute_type type)
{
    switch(type)
    {
        case gpu_vertex_attribute_type::float1:
            return 1;
        case gpu_vertex_attribute_type::float2:
            return 2;
        case gpu_vertex_attribute_type::float3:
            return 3;
        case gpu_vertex_attribute_type::float4:
            return 4;
        case gpu_vertex_attribute_type::int1:
            return 1;
        case gpu_vertex_attribute_type::int2:
            return 2;
        case gpu_vertex_attribute_type::int3:
            return 3;
        case gpu_vertex_attribute_type::int4:
            return 4;
        default:
            return 0;
    }
}

GLenum gl_attribute_type(gpu_vertex_attribute_type type)
{
    switch(type)
    {
        case gpu_vertex_attribute_type::float1:
        case gpu_vertex_attribute_type::float2:
        case gpu_vertex_attribute_type::float3:
        case gpu_vertex_attribute_type::float4:
            return GL_FLOAT;
        case gpu_vertex_attribute_type::int1:
        case gpu_vertex_attribute_type::int2:
        case gpu_vertex_attribute_type::int3:
        case gpu_vertex_attribute_type::int4:
            return GL_INT;
        default:
            return 0;
    }
}

GLuint gl_attribute_size(gpu_vertex_attribute_type type)
{
    switch(type)
    {
        case gpu_vertex_attribute_type::float1:
            return sizeof(float) * 1;
        case gpu_vertex_attribute_type::float2:
            return sizeof(float) * 2;
        case gpu_vertex_attribute_type::float3:
            return sizeof(float) * 3;
        case gpu_vertex_attribute_type::float4:
            return sizeof(float) * 4;
        case gpu_vertex_attribute_type::int1:
            return sizeof(int) * 1;
        case gpu_vertex_attribute_type::int2:
            return sizeof(int) * 2;
        case gpu_vertex_attribute_type::int3:
            return sizeof(int) * 3;
        case gpu_vertex_attribute_type::int4:
            return sizeof(int) * 4;
        default:
            return 0;
    }
}

GLuint make_vertex_array_from_layout(const gpu_vertex_layout& layout, GLuint& out_stride)
{
    GLuint vao = 0;
    glCreateVertexArrays(1, &vao);

    GLuint offset = 0;
    for(GLuint i = 0; i < layout.size(); ++i)
    {
        const gpu_vertex_attribute& attribute = layout[i];

        glEnableVertexArrayAttrib(vao, i);
        glVertexArrayAttribFormat(vao, i, gl_attribute_count(attribute.type), gl_attribute_type(attribute.type), attribute.is_normalized ? GL_TRUE : GL_FALSE, offset);
        glVertexArrayAttribBinding(vao, i, 0);

        offset += gl_attribute_size(attribute.type);
    }

    out_stride = offset;

    return vao;
}

GLenum gl_internal_texture_format(gpu_texture_format format)
{
    switch(format)
    {
        case gpu_texture_format::rgb8:
            return GL_RGB8;
        case gpu_texture_format::rgba8:
            return GL_RGBA8;
    }

    // Should never reach here
    assert(false);

    return 0;
}

GLuint gl_compile_shader(GLenum shader_type, std::string_view source)
{
    GLuint new_shader = glCreateShader(shader_type);

    const char* source_c_str = source.data();

    glShaderSource(new_shader, source.size(), &source_c_str, nullptr);
    glCompileShader(new_shader);

    GLint compilation_status = 0;
    glGetShaderiv(new_shader, GL_COMPILE_STATUS, &compilation_status);

    if(compilation_status == GL_FALSE)
    {
        char info_log_buffer[2048] = {0};

        GLsizei log_length = 0;
        glGetShaderInfoLog(new_shader, 2048, &log_length, info_log_buffer);

        std::cerr << info_log_buffer << std::endl;

        glDeleteShader(new_shader);

        new_shader = 0;
    }

    return new_shader;
}

GLuint gl_link_program(const gpu_pipeline_state_description& state_description)
{
    GLuint new_program = glCreateProgram();

    const GLuint compiled_shaders[] = {
            gl_compile_shader(GL_VERTEX_SHADER, state_description.vertex_stage.shader_source),
            gl_compile_shader(GL_FRAGMENT_SHADER, state_description.fragment_stage.shader_source),
    };

    for(GLuint compiled_shader : compiled_shaders)
    {
        if(compiled_shader != 0)
        {
            glAttachShader(new_program, compiled_shader);
        }
    }

    glLinkProgram(new_program);

    for(GLuint compiled_shader : compiled_shaders)
    {
        if(compiled_shader != 0)
        {
            glDetachShader(new_program, compiled_shader);
        }
    }

    GLint link_status;
    glGetProgramiv(new_program, GL_LINK_STATUS, &link_status);

    if(link_status == GL_FALSE)
    {
        // Release every compiled shaders
        for(GLuint compiled_shader : compiled_shaders)
        {
            if(compiled_shader != 0)
            {
                glDeleteShader(compiled_shader);
            }
        }

        glDeleteProgram(new_program);

        return 0;
    }

    return new_program;
}

}