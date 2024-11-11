extern "C" {
#include "weather.h"
}

#include <gtest/gtest.h>

const int kStormWindSignalNumber = 4;
const int kIncreasedStormWindSignalNumber = 5;
const int kDecreasedStormWindSignalNumber = 3;
const int kPostponedDepartureChance = SIGNAL_FOUR_STORM_POSTPONED_DEPARTURE_CHANCE;

// generateRandomBool()
TEST(GenerateRandomBoolTest, ReturnsTrue) {
  srand(0);

  bool is_true = generateRandomBool(100);

  EXPECT_EQ(is_true, true);
}

TEST(GenerateRandomBoolTest, ReturnsFalse) {
  srand(0);

  bool is_true = generateRandomBool(0);

  EXPECT_EQ(is_true, false);
}

TEST(GenerateRandomBoolTest, HandlesNegativeTrueChance) {
  srand(0);

  bool is_true = generateRandomBool(-50);

  EXPECT_EQ(is_true, false);
}

// generateRandomStormTurnDuration()
TEST(GenerateRandomStormTurnDurationTest, ReturnsGreaterThanOrEqualToMinimum) {
  srand(0);

  int storm_turn_duration = generateRandomStormTurnDuration(1);

  EXPECT_GE(storm_turn_duration, 1);
}

TEST(GenerateRandomStormTurnDurationTest, ReturnsLessThanOrEqualToMaximum) {
  srand(0);

  int storm_turn_duration = generateRandomStormTurnDuration(1);

  EXPECT_LE(storm_turn_duration, MAXIMUM_STORM_TURN_DURATION);
}

TEST(GenerateRandomStormTurnDurationTest, HandlesNegativeTurnDuration) {
  srand(0);

  int storm_turn_duration = generateRandomStormTurnDuration(-10);

  EXPECT_GE(storm_turn_duration, -10);
  EXPECT_LE(storm_turn_duration, MAXIMUM_STORM_TURN_DURATION);
}

// setStormStrength()
TEST(SetStormStrengthTest, IncreasesWindSignalNumber) {
  int storm_wind_signal_number = kStormWindSignalNumber;
  int postponed_departure_chance = kPostponedDepartureChance;

  setStormStrength(&storm_wind_signal_number, kIncreasedStormWindSignalNumber, &postponed_departure_chance);

  EXPECT_GE(storm_wind_signal_number, kIncreasedStormWindSignalNumber);
}

TEST(SetStormStrengthTest, DecreasesWindSignalNumber) {
  int storm_wind_signal_number = kStormWindSignalNumber;
  int postponed_departure_chance = kPostponedDepartureChance;

  setStormStrength(&storm_wind_signal_number, kDecreasedStormWindSignalNumber, &postponed_departure_chance);

  EXPECT_GE(storm_wind_signal_number, kDecreasedStormWindSignalNumber);
}

TEST(SetStormStrengthTest, IncreasesPostponedDepartureChance) {
  int storm_wind_signal_number = kStormWindSignalNumber;
  int postponed_departure_chance = kPostponedDepartureChance;

  setStormStrength(&storm_wind_signal_number, kIncreasedStormWindSignalNumber, &postponed_departure_chance);

  EXPECT_GE(postponed_departure_chance, SIGNAL_FIVE_STORM_POSTPONED_DEPARTURE_CHANCE);
}

TEST(SetStormStrengthTest, DecreasesPostponedDepartureChance) {
  int storm_wind_signal_number = kStormWindSignalNumber;
  int postponed_departure_chance = kPostponedDepartureChance;

  setStormStrength(&storm_wind_signal_number, kDecreasedStormWindSignalNumber, &postponed_departure_chance);

  EXPECT_GE(postponed_departure_chance, SIGNAL_THREE_STORM_POSTPONED_DEPARTURE_CHANCE);
}
