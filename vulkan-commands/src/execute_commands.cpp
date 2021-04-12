#include "check.hpp"
#include "m4c0/vulkan/execute_commands.hpp"

void m4c0::vulkan::cmd::execute_commands::now() const {
  vkCmdExecuteCommands(pointer(), m_cmds.size(), m_cmds.data());
}
