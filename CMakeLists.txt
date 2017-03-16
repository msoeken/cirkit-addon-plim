add_cirkit_library(
  NAME cirkit_plim
  AUTO_DIRS src
  USE
    cirkit_classical
  INCLUDE
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
  DEFINE
    PUBLIC ADDON_PLIM
  COMMANDS
    classical/cli/commands/plim_commands.hpp
)
