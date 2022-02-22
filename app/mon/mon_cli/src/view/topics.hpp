#pragma once

#include <vector>
#include <string>

#include "data/model.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/table.hpp>
#include "ftxui/component/component.hpp"  // for ComponentBase
#include "ftxui/dom/elements.hpp"  // for operator|, Element, text, bold, border, center, color
#include "ftxui/screen/color.hpp"  // for Color, Color::Red

ftxui::Component TopicsView(const TopicsT& topics)
{
  using namespace ftxui;

  return Renderer([=]{
    std::vector<std::vector<std::string>> table_data;
    table_data.push_back({
      "Id", "Name", "Direction"
    });

    for(auto t: topics)
    {
      auto& row = table_data.emplace_back();
      row.push_back(t.tid());
      row.push_back(t.tname());
      row.push_back(t.direction());
    }

    auto table = Table(table_data);
    //table.SelectAll().Border(LIGHT);
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(LIGHT);
    table.SelectColumn(0).DecorateCells(size(WIDTH, EQUAL, 50));
    table.SelectColumn(1).DecorateCells(size(WIDTH, EQUAL, 50));
    table.SelectColumn(2).DecorateCells(size(WIDTH, EQUAL, 150));

    return table.Render();
  });
}
