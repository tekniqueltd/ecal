/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

/**
 * @brief eCALMon Console Application
**/

#include "ecal/ecal_process.h"
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4146 4505 4800 4189 4592) // disable proto warnings
#endif
#include <google/protobuf/message.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "tclap/CmdLine.h"

#include <ecal/msg/protobuf/dynamic_subscriber.h>
#include <ecal/ecal.h>
#include <ecal/msg/string/publisher.h>
#include <ecal/msg/string/subscriber.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4146 4505 4800 4189 4592) // disable proto warnings
#endif
#include "ecal/pb/monitoring.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <ftxui/component/screen_interactive.hpp>

#include "ecal_mon_defs.h"

#include "data/model.hpp"
#include "view/topics.hpp"
#include "view/shell.hpp"

const int _1kB = 1024;
const int _10kB = 10 * _1kB;
const int _1MB = _1kB * _1kB;
const int _10MB = 10 * _1MB;
int pause_val = 500;

// main entry
int main(int argc, char** argv)
{
  auto status = eCAL::Initialize(0, nullptr, nullptr, eCAL::Init::Default | eCAL::Init::Monitoring);
  if (status == -1) std::cout << "Failed to init" << std::endl;
  eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "Running");
  eCAL::Process::SleepMS(1000);

  auto model = MonitorModel();
  auto topic_view = TopicsView(model.Topics());
  auto shell_vm = ShellViewModel(topic_view);

  auto shell = ShellView(shell_vm);

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  screen.Loop(shell);
}
