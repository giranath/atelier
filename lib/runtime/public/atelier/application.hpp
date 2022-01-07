#ifndef ATELIER_RUNTIME_APPLICATION_HPP
#define ATELIER_RUNTIME_APPLICATION_HPP

#include "runtime_export.hpp"
#include "scene_tree.hpp"
#include "frame_duration.hpp"
#include <memory>
#include <chrono>

namespace at
{

struct gpu_device;

/**
 * Signature of an application factory function
 */
using application_factory = std::unique_ptr<class application>(*)();

/**
 * Base class every application must implement
 */
class ATELIER_RUNTIME_EXPORT application
{
public:
    enum class states : uint8_t
    {
        uninitialized,
        initializing,
        executing,
        terminating,
        terminated
    };

private:
    std::unique_ptr<gpu_device> gpu_;
    scene_tree scene_;
    states current_state_;
    std::chrono::steady_clock::time_point last_frame_tp_;
    frame_duration render_accumulated_duration_;

public:
    friend int launch_application(int argc, char* argv[], application_factory factory);

    application();
    ~application();

    application(application&& other) noexcept;
    application& operator=(application&& other) noexcept;

    void request_termination();

protected:
    virtual void on_initializing();
    virtual void on_initialized();

    virtual void on_terminating();
    virtual void on_terminated();

    virtual void pump_host_events();

    /**
     * Present the current frame to the player
     */
    virtual void present_frame_to_player();

    /**
     * Make an instance of the GPU device compatible with this application
     * @return The GPU device to create from this application
     * @note This function is guaranteed to be called a single time
     */
    virtual std::unique_ptr<gpu_device> make_gpu_device() = 0;

    /**
     * Change the root of the main scene
     * @param scene The scene to update
     */
    virtual void setup_scene_root(scene_tree& scene);

private:
    void initialize();
    int wait();
    void process_next_frame();
    void tick(frame_duration dt);
    void render();
    void terminate();
};


/**
 * Launch the application
 * @param argc The number of arguments passed to the application
 * @param argv The list of arguments passed to the application
 * @param factory A factory function to instantiate an application
 * @return the exit code of the application
 */
ATELIER_RUNTIME_EXPORT int launch_application(int argc, char* argv[], application_factory factory);

}

#endif
