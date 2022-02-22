#pragma once

#include "ecal/ecal_callback.h"
#include "ecal/ecal_process.h"
#include <chrono>

#include <ecal/ecal.h>
#include <ecal/ecal_monitoring.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <map>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4146 4505 4800 4189 4592) // disable proto warnings
#endif
#include "ecal/pb/monitoring.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

using ModelUpdateCallbackT = std::function<void()>;
using HostsT = decltype(std::declval<eCAL::pb::Monitoring>().hosts());
using ProcessesT = decltype(std::declval<eCAL::pb::Monitoring>().processes());
using TopicsT = decltype(std::declval<eCAL::pb::Monitoring>().topics());
using ClientsT = decltype(std::declval<eCAL::pb::Monitoring>().clients());
using ServicesT = decltype(std::declval<eCAL::pb::Monitoring>().services());

class MonitorModel
{
  int update_time_;
  bool is_polling;
  eCAL::pb::Monitoring mon_;
  ModelUpdateCallbackT callback_;

  void Update()
  {
    std::string raw_data;
    eCAL::Monitoring::GetMonitoring(raw_data);
    mon_.ParseFromString(raw_data);
    if(callback_) callback_();
  }

  void PollData()
  {
    eCAL::Process::SleepMS(update_time_);
    while(is_polling)
    {
      Update();
      eCAL::Process::SleepMS(update_time_);
    }
  }

public:
  MonitorModel() : is_polling{true}
  {
    Update();
    std::thread(std::bind(&MonitorModel::PollData, this)).detach();
  }

  HostsT Hosts()
  {
    return mon_.hosts();
  }

  ProcessesT Processes()
  {
    return mon_.processes();
  }

  ClientsT Clients()
  {
    return mon_.clients();
  }

  ServicesT Services()
  {
    return mon_.services();
  }

  TopicsT Topics()
  {
    return mon_.topics();
  }

  void SetModelUpdateCallback(ModelUpdateCallbackT callback)
  {
    callback_ = callback;
  }

  ~MonitorModel()
  {
    is_polling = false;
  }
};
