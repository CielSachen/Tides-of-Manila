#ifndef CCPROG1_WEATHER_H_
#define CCPROG1_WEATHER_H_

#define MAXIMUM_STORM_TURN_DURATION 10

#define DEFAULT_POSTPONED_DEPARTURE_CHANCE 0
#define SIGNAL_THREE_STORM_POSTPONED_DEPARTURE_CHANCE 1
#define SIGNAL_FOUR_STORM_POSTPONED_DEPARTURE_CHANCE 5
#define SIGNAL_FIVE_STORM_POSTPONED_DEPARTURE_CHANCE 10

/**
 * Generates a random boolean based on the provided chance of returning a `true`.
 * @param nTruePercentChance The percentage chance of this function returning `1`.
 * @pre @p nTruePercentChance must have a positive integer value greater than or equal to  `1` and less than or equal to
 * `100`.
 * @returns `1` if `true` or `0` if `false`.
 */
int generateRandomBool(int nTrueChance);

/**
 * Generates a random duration in turns for a storm within the provided minimum and constant maximum turn duration.
 * @param nMinimumTurnDuration The minimum allowed duration in turns.
 * @returns An integer value within the range of `nMinimumTurnDuration` and `10`.
 */
int generateRandomStormTurnDuration(int nMinimumTurnDuration);

/**
 * Sets the wind signal number of the storm to the given new wind signal number and sets its debuffs.
 * @param[in,out] nStormCurrentWindSignalNumber The storm's current wind signal number.
 * @param nStormNewWindSignalNumber The storm's new wind signal number.
 * @param[out] nPostponedDepartureChance The percentage chance of the player being unable to depart their current port.
 */
void setStormStrength(int *nStormCurrentWindSignalNumber, int nStormNewWindSignalNumber,
                      int *nPostponedDepartureChance);

#endif  // CCPROG1_WEATHER_H_
