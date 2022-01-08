#ifndef ATELIER_OPENGL45_HELPERS_HPP
#define ATELIER_OPENGL45_HELPERS_HPP

#include <atelier/gpu_vertex_layout.hpp>
#include <atelier/gpu_texture.hpp>
#include <atelier/gpu_pipeline_state.hpp>
#include <atelier/gpu_device.hpp>
#include <glad/glad.h>

namespace at
{

/**
 * Returns the number of components inside a vertex attribute type
 * @param type The type to extract the number of components from
 * @return the number of components of an attribute type e.g: float3 means that its 3 floats so the function will return 3
 */
GLint gl_attribute_count(gpu_vertex_attribute_type type);

/**
 * Convert an attribute type to its OpenGL equivalent
 * @param type The type to convert into OpenGL format
 * @return the OpenGL equivalent of the attribute type
 */
GLenum gl_attribute_type(gpu_vertex_attribute_type type);

/**
 * Returns the size of an attribute type in bytes for OpenGL
 * @param type The type of the attribute
 * @return the size in bytes of the attribute for OpenGL
 */
GLuint gl_attribute_size(gpu_vertex_attribute_type type);

/**
 * Make an OpenGL vertex array from an atelier vertex layout
 * @param layout The layout to make the vertex array from
 * @param out_stride The stride for this vertex layout
 * @return the new OpenGL vertex array that was created
 */
GLuint make_vertex_array_from_layout(const gpu_vertex_layout& layout, GLuint& out_stride);

/**
 * Convert a texture format to an internal OpenGL texture format
 * @param format The format to convert
 * @return the equivalent OpenGL format
 */
GLenum gl_internal_texture_format(gpu_texture_format format);

/**
 * Compile a shader
 * @param shader_type The OpenGL type of the shader
 * @param source The source code of the shader
 * @return the compiled shader
 */
GLuint gl_compile_shader(GLenum shader_type, std::string_view source);

/**
 * Compile and link a shader program
 * @param state_description The description of the program
 * @return the linked program
 */
GLuint gl_link_program(const gpu_pipeline_state_description& state_description);

GLenum gl_index_type(gpu_index_types type);
GLsizei gl_index_type_size(gpu_index_types index_type);
GLenum gl_draw_topology(gpu_draw_topology topology);

}

#endif
