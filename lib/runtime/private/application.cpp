#include "application.hpp"
#include "gpu_device.hpp"
#include <cassert>

namespace at
{

application::application()
: gpu_{}
, scene_()
, current_state_{states::uninitialized}
, last_frame_tp_()
, render_accumulated_duration_()
{

}

application::~application()
{
    assert(current_state_ == states::uninitialized || current_state_ == states::terminated);
}

application::application(application&& other) noexcept = default;
application& application::operator=(application&& other) noexcept = default;

void application::request_termination()
{
    assert(current_state_ == states::executing);

    // TODO: Here we can block termination if it is not a good moment
    current_state_ = states::terminating;
}

gpu_device& application::gpu() noexcept
{
    assert(gpu_);

    return *gpu_;
}

void application::on_initializing()
{
    // NO-OP
}

void application::on_initialized()
{
    // NO-OP
}

void application::on_terminating()
{
    // NO-OP
}

void application::on_terminated()
{
    // NO-OP
}

void application::pump_host_events()
{
    // NO-OP
}

void application::present_frame_to_player()
{
    // NO-OP
}

void application::setup_scene_root(scene_tree& scene)
{
    // NO-OP
}

void application::initialize()
{
    assert(current_state_ == states::uninitialized);

    current_state_ = states::initializing;

    on_initializing();

    // Here we make the GPU device associated with this application
    gpu_ = make_gpu_device();

    on_initialized();

    // Now that everything has been initialized
    // The scene root can be updated with its startup content
    setup_scene_root(scene_);

    last_frame_tp_ = std::chrono::steady_clock::now();

    current_state_ = states::executing;
}

int application::wait()
{
    assert(current_state_ == states::executing);

    while(current_state_ == states::executing)
    {
        process_next_frame();
    }

    return 0;
}

void application::process_next_frame()
{
    const auto current_frame_tp = std::chrono::steady_clock::now();
    const frame_duration previous_frame_duration = current_frame_tp - last_frame_tp_;

    render_accumulated_duration_ += previous_frame_duration;

    // Here we get events from the host
    // NOTE: The implementer must convert host events into atelier's event format
    pump_host_events();

    // Tick as fast as possible
    tick(previous_frame_duration);

    // We try to render the game at 60 FPS
    const frame_duration target_framerate{1.0 / 60.0};
    while(render_accumulated_duration_ >= target_framerate)
    {
        render();
        render_accumulated_duration_ -= target_framerate;
    }

    last_frame_tp_ = current_frame_tp;
}

void application::tick(frame_duration dt)
{
    scene_.tick(dt);
}

void application::render()
{
    // TODO: Render current frame to the user
    present_frame_to_player();
}

void application::terminate()
{
    assert(current_state_ == states::terminating);

    on_terminating();

    // Termination code should go here

    scene_.clear();

    on_terminated();

    current_state_ = states::terminated;
}

int launch_application(int argc, char* argv[], application_factory factory)
{
    // Here we instantiate the application
    std::unique_ptr<application> new_application = factory();

    new_application->initialize();

    const int result = new_application->wait();

    new_application->terminate();

    return result;
}

}