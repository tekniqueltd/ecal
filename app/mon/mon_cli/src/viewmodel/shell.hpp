#include <string>
#include <vector>

#include <ftxui/component/component.hpp>

class ShellViewModel
{
public:
  int tab_selected = 0;
  std::vector<std::string> tab_names {"Hosts", "Processes", "Topics", "Services"};
  ftxui::Component temp_content = ftxui::Renderer([] { return ftxui::text("WORK IN PROGRESS"); });
  std::vector<ftxui::Component> tab_content;

  ShellViewModel(ftxui::Component topic_view) : tab_content{temp_content, topic_view, temp_content, temp_content} {}
};
