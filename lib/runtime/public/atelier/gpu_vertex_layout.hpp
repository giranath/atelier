#ifndef ATELIER_RUNTIME_GPU_VERTEX_LAYOUT_HPP
#define ATELIER_RUNTIME_GPU_VERTEX_LAYOUT_HPP

#include "runtime_export.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace at
{

/**
 * Supported vertex attribute types
 */
enum class gpu_vertex_attribute_type : uint8_t
{
    float1,
    float2,
    float3,
    float4,
    int1,
    int2,
    int3,
    int4
};

/**
 * Represents a single vertex attribute
 */
struct ATELIER_RUNTIME_EXPORT gpu_vertex_attribute
{
    /// The name of this attribute
    std::string name;

    /// The type of the attribute
    gpu_vertex_attribute_type type;

    /// Is this attribute normalized
    bool is_normalized;

    gpu_vertex_attribute() noexcept;
    explicit gpu_vertex_attribute(std::string_view name, gpu_vertex_attribute_type type, bool normalized = false) noexcept;

    [[nodiscard]] bool operator==(const gpu_vertex_attribute& other) const noexcept;
    [[nodiscard]] bool operator!=(const gpu_vertex_attribute& other) const noexcept;
};

/**
 * Represents the memory layout of a vertex
 */
class ATELIER_RUNTIME_EXPORT gpu_vertex_layout
{
    friend class gpu_vertex_layout_builder;

    static constexpr std::size_t max_attribute_count = 8;

    // An array of attributes
    gpu_vertex_attribute attributes_[max_attribute_count];

    // The number of attributes in this layout
    std::size_t attribute_count_;

public:
    gpu_vertex_layout() noexcept;

    [[nodiscard]] bool operator==(const gpu_vertex_layout& other) const noexcept;
    [[nodiscard]] bool operator!=(const gpu_vertex_layout& other) const noexcept;

    /**
     * Returns a single attribute stored in this layout
     * @param index The index of the attribute to retrieve
     * @return the stored attribute
     */
    const gpu_vertex_attribute& operator[](std::size_t index) const noexcept;

    /**
     * Returns a raw point to the container of attributes stored inside this layout
     * @return A raw pointer to the internal attributes stored inside this layout
     */
    [[nodiscard]] const gpu_vertex_attribute* data() const noexcept;

    /**
     * Returns the number of attributes stored inside this layout
     * @return The number of attributes stored inside this layout
     */
    [[nodiscard]] std::size_t size() const noexcept;
};

/**
 * Builder class for a gpu_vertex_layout
 * This helps at making gpu_vertex_layout immutable
 */
class ATELIER_RUNTIME_EXPORT gpu_vertex_layout_builder
{
    std::vector<gpu_vertex_attribute> attributes_;

public:

    /**
     * Make an instance of a builder
     * @return the instance of the builder
     */
    static gpu_vertex_layout_builder make();

    /**
     * Add a new attribute to the layout
     * @param name The name of the attribute
     * @param type The type of the attribute
     * @param normalized A boolean to indicate if the attribute should be normalized or not
     * @return a reference to this builder to allow chain call
     */
    gpu_vertex_layout_builder& add_attribute(std::string_view name, gpu_vertex_attribute_type type, bool normalized = false);

    /**
     * Build an instance of a vertex layout from this builder
     * @return The instance of the vertex layout
     */
    [[nodiscard]] gpu_vertex_layout build();
};

}

#endif
