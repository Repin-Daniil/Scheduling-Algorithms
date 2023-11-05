#pragma once

#include <string_view>
#include <unordered_map>

using namespace std::literals;

struct EnglishLabels {
  EnglishLabels() = delete;

  constexpr static std::string_view ADD_PROCESS = "Add process"sv;
  constexpr static std::string_view RESET = "Reset Job Queue"sv;
  constexpr static std::string_view MIDDLE_TIMEOUT = "Middle timeout "sv;
  constexpr static std::string_view MIDDLE_RUNTIME = "Middle runtime "sv;
};

struct ApplicationConstants {
  ApplicationConstants() = delete;

  constexpr static std::string_view FCFS_TITLE = "Lab 1: FCFS"sv;

  constexpr static std::string_view PATH_TO_FONT = "res/TimesNewRomanRegular.ttf"sv;

  // Window
  const static unsigned int WIDTH = 1600u;
  const static unsigned int HEIGHT = 900u;

  // Process cell
  const static unsigned int MARGIN_LEFT = 45u;
  const static unsigned int MARGIN_TOP = 10u;
  const static unsigned int CELL_SIZE = 25u;
};

enum Algorithm { FCFS, RR, SJF, PSJF, RR_SJF };

const std::unordered_map<Algorithm, std::string_view> algo_to_title{
    {FCFS, ApplicationConstants::FCFS_TITLE}
};