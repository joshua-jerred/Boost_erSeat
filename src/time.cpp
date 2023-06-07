#include <BoosterSeat/time.hpp>

std::string BoosterSeat::time::elapsedAsciiClock(
    const BoosterSeat::clck::TimePoint &time_point) {
  int seconds = BoosterSeat::clck::secondsElapsed(time_point);
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;
  minutes %= 60;

  std::string seconds_str = std::to_string(seconds);
  std::string minutes_str = std::to_string(minutes);
  std::string hours_str = std::to_string(hours);

  if (seconds < 10) {
    seconds_str = "0" + seconds_str;
  }
  if (minutes < 10) {
    minutes_str = "0" + minutes_str;
  }
  if (hours < 10) {
    hours_str = "0" + hours_str;
  }

  return hours_str + ":" + minutes_str + ":" + seconds_str;
}

std::string BoosterSeat::time::utcTimeString() {
  auto time = std::time(nullptr);
  auto tm = *std::gmtime(&time);
  std::stringstream ss;
  ss << std::put_time(&tm, "%H:%M:%S");
  return ss.str();
}

std::string BoosterSeat::time::localTimeString() {
  auto time = std::time(nullptr);
  auto tm = *std::localtime(&time);
  std::stringstream ss;
  ss << std::put_time(&tm, "%H:%M:%S");
  return ss.str();
}

std::string BoosterSeat::time::getDateAndTimeStr() {
  auto time = std::time(nullptr);
  auto tm = *std::localtime(&time);
  std::stringstream ss;
  ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}