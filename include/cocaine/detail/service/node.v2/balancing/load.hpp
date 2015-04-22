#pragma once

#include "cocaine/detail/service/node.v2/balancing/base.hpp"

namespace cocaine {

class load_balancer_t:
    public balancer_t
{
    std::uint64_t counter;

public:
    explicit load_balancer_t(std::shared_ptr<overseer_t> overseer);

    slave_info
    on_request(const std::string& event, const std::string& id) override;

    void
    on_slave_spawn(const std::string& uuid) override;

    void
    on_slave_death(const std::string& uuid) override;

    void
    on_queue() override;

    std::uint64_t
    on_channel_started(const std::string& uuid) override;

    void
    on_channel_finished(const std::string& uuid, std::uint64_t channel) override;

private:
    /// Tries to clear the queue by assigning tasks to slaves.
    void
    purge();

    /// Tries to spawn/despawn appropriate number of slaves.
    void
    balance();
};

}
