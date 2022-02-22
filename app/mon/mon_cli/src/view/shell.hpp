
#pragma once

#include <vector>
#include <string>

#include <ftxui/component/component.hpp>

#include "viewmodel/shell.hpp"

ftxui::Component CreateShellTabs(ShellViewModel &vm)
{
  using namespace ftxui;
  auto toggle = Toggle(&vm.tab_names, &vm.tab_selected);
  auto tab_container = Container::Tab(vm.tab_content, &vm.tab_selected);
  auto container = Container::Horizontal({
      toggle,
      tab_container,
  });
  return Renderer(container, [=] {
    return vbox({
              toggle->Render(),
              separator(),
              tab_container->Render(),
            }) | border;
  });
}

ftxui::Component ShellView(ShellViewModel &vm)
{
  return CreateShellTabs(vm);
}
