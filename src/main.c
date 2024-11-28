/*
 * Tides of Manila: A Merchant's Quest is a turn-based CLI-based game.
 * Copyright (C) 2024  Louis Raphael V. Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 * This is to certify that this project is my own work, based on my personal efforts in studying
 * and applying the concepts learned. I have constructed the functions and their respective
 * algorithms and corresponding code by myself. The program was run, tested, and debugged by
 * my own efforts. I further certify that I have not copied in part or whole or otherwise
 * plagiarized the work of other students and/or persons.
 *
 *                                   Louis Raphael V. Panaligan, DLSU ID# 12413372
 */

/*
 * Description: My Logic Formulation and Introductory Programming (CCPROG1) machine project.
 * Programmed by: Louis Raphael V. Panaligan
 * Last modified: 2024-11-24
 * Version: 1.0.0
 * Acknowledgements:
 *  - https://www.geeksforgeeks.org/generating-random-number-range-c/
 *  - https://www.theurbanpenguin.com/4184-2/
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "console.h"
#include "prompts.h"
#include "text_graphics.h"
#include "trading.h"
#include "weather.h"

#define MAXIMUM_PLAYER_TURNS 31

int main(void) {
  srand(time(NULL));

  printf("\n");

  printf("Tides of Manila: A Merchant's Quest  Copyright (C) 2024  Louis Raphael V. Panaligan\n");
  printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to redistribute it under certain conditions.\n");

  printGameStartScreen();

  int nPlayerMerchantId;
  int nPlayerInitialBalance;
  int nPlayerBalance;
  int nPlayerProfitTarget;

  nPlayerMerchantId = promptPlayerForMerchantId();

  printf("\n");

  nPlayerInitialBalance = promptPlayerForInitialBalance();
  nPlayerBalance = nPlayerInitialBalance;

  printf("\n");

  nPlayerProfitTarget = promptPlayerForProfitTarget();

  int nPlayerTurns = 0;
  int bIsQuitting = 0;
  char cCurrentPortId = 'M';
  int nPlayerProfit = 0;
  int nShipCargoLimit = TIER_ONE_SHIP_CARGO_LIMIT;
  int nShipCoconutCargoAmount = 0;
  int nShipRiceCargoAmount = 0;
  int nShipSilkCargoAmount = 0;
  int nShipGunCargoAmount = 0;
  int nStormTurnDuration = 0;
  int bIsNewStorm;
  int nStormWindSignalNumber;
  int nPostponedDepartureChance = DEFAULT_POSTPONED_DEPARTURE_CHANCE;

  // This loop will keep running a new game day or turn until the player reaches the maximum amount of turns or the user
  // quits.
  while (nPlayerTurns < MAXIMUM_PLAYER_TURNS && !bIsQuitting) {
    int nCoconutMarketPrice;
    int nRiceMarketPrice;
    int nSilkMarketPrice;
    int nGunMarketPrice;

    switch (cCurrentPortId) {
      case 'T': {
        nCoconutMarketPrice = generateRandomPrice(MINIMUM_TONDO_COCONUT_PRICE, MAXIMUM_TONDO_COCONUT_PRICE);
        nRiceMarketPrice = generateRandomPrice(MINIMUM_TONDO_RICE_PRICE, MAXIMUM_TONDO_RICE_PRICE);
        nSilkMarketPrice = generateRandomPrice(MINIMUM_TONDO_SILK_PRICE, MAXIMUM_TONDO_SILK_PRICE);
        nGunMarketPrice = generateRandomPrice(MINIMUM_TONDO_GUN_PRICE, MAXIMUM_TONDO_GUN_PRICE);

        break;
      }
      case 'M': {
        nCoconutMarketPrice = generateRandomPrice(MINIMUM_MANILA_COCONUT_PRICE, MAXIMUM_MANILA_COCONUT_PRICE);
        nRiceMarketPrice = generateRandomPrice(MINIMUM_MANILA_RICE_PRICE, MAXIMUM_MANILA_RICE_PRICE);
        nSilkMarketPrice = generateRandomPrice(MINIMUM_MANILA_SILK_PRICE, MAXIMUM_MANILA_SILK_PRICE);
        nGunMarketPrice = generateRandomPrice(MINIMUM_MANILA_GUN_PRICE, MAXIMUM_MANILA_GUN_PRICE);

        break;
      }
      case 'P': {
        nCoconutMarketPrice = generateRandomPrice(MINIMUM_PANDAKAN_COCONUT_PRICE, MAXIMUM_PANDAKAN_COCONUT_PRICE);
        nRiceMarketPrice = generateRandomPrice(MINIMUM_PANDAKAN_RICE_PRICE, MAXIMUM_PANDAKAN_RICE_PRICE);
        nSilkMarketPrice = generateRandomPrice(MINIMUM_PANDAKAN_SILK_PRICE, MAXIMUM_PANDAKAN_SILK_PRICE);
        nGunMarketPrice = generateRandomPrice(MINIMUM_PANDAKAN_GUN_PRICE, MAXIMUM_PANDAKAN_GUN_PRICE);

        break;
      }
      case 'S': {
        nCoconutMarketPrice = generateRandomPrice(MINIMUM_SAPA_COCONUT_PRICE, MAXIMUM_SAPA_COCONUT_PRICE);
        nRiceMarketPrice = generateRandomPrice(MINIMUM_SAPA_RICE_PRICE, MAXIMUM_SAPA_RICE_PRICE);
        nSilkMarketPrice = generateRandomPrice(MINIMUM_SAPA_SILK_PRICE, MAXIMUM_SAPA_SILK_PRICE);
        nGunMarketPrice = generateRandomPrice(MINIMUM_SAPA_GUN_PRICE, MAXIMUM_SAPA_GUN_PRICE);

        break;
      }
    }

    int bIsNavigating = 0;

    // This loop will keep looping back into the game's main screen until the player navigates (increments the number of
    // turns exhausted) or quits.
    while (!bIsNavigating && !bIsQuitting) {
      nPlayerProfit = ((nPlayerBalance - nPlayerInitialBalance) / (nPlayerInitialBalance * 1.0)) * 100;

      int nShipTotalCargoAmount =
        nShipCoconutCargoAmount + nShipRiceCargoAmount + nShipSilkCargoAmount + nShipGunCargoAmount;

      printMainScreen(nPlayerTurns, cCurrentPortId, nPlayerMerchantId, nPlayerBalance, nPlayerProfit,
                      nPlayerProfitTarget, nShipTotalCargoAmount, nShipCargoLimit, nShipCoconutCargoAmount,
                      nShipRiceCargoAmount, nShipSilkCargoAmount, nShipGunCargoAmount, nCoconutMarketPrice,
                      nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice);

      char cChosenActionId =
        promptPlayerForActionId(nShipTotalCargoAmount, nShipCargoLimit, nPlayerBalance, nCoconutMarketPrice,
                                nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice);

      printf("\n");

      if (cChosenActionId == 'B' || cChosenActionId == 'S') {
        char cChosenCargoId = promptPlayerForCargoId(
          cChosenActionId, nPlayerBalance, nShipCoconutCargoAmount, nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice,
          nShipCoconutCargoAmount, nShipRiceCargoAmount, nShipSilkCargoAmount, nShipGunCargoAmount);

        if (cChosenCargoId != 'X') {
          printf("\n");

          int nCargoAmount = promptPlayerForCargoAmount(
            cChosenActionId, nShipCargoLimit, cChosenCargoId, nPlayerBalance, nCoconutMarketPrice, nRiceMarketPrice,
            nSilkMarketPrice, nGunMarketPrice, nShipCoconutCargoAmount, nShipRiceCargoAmount, nShipSilkCargoAmount,
            nShipGunCargoAmount);

          printf("\n");

          int bIsConfirmed = promptPlayerForConfirmation();

          if (bIsConfirmed) {
            int nCargoPrice;
            int *nShipCargoAmount;

            if (cChosenCargoId == 'C') {
              nCargoPrice = nCoconutMarketPrice;
              nShipCargoAmount = &nShipCoconutCargoAmount;
            } else if (cChosenCargoId == 'R') {
              nCargoPrice = nRiceMarketPrice;
              nShipCargoAmount = &nShipRiceCargoAmount;
            } else if (cChosenCargoId == 'S') {
              nCargoPrice = nSilkMarketPrice;
              nShipCargoAmount = &nShipSilkCargoAmount;
            } else {
              nCargoPrice = nGunMarketPrice;
              nShipCargoAmount = &nShipGunCargoAmount;
            }

            tradeCargo(cChosenActionId, &nPlayerBalance, nCargoPrice, nCargoAmount, nShipCargoAmount);

            printTransactionScreen(cChosenActionId, cChosenCargoId, nCargoAmount, nCargoPrice);

            promptPlayerForContinuation();
          }
        }
      } else if (cChosenActionId == 'U') {
        printShipUpgradeMenu(nShipCargoLimit);

        int bIsUpgrading = promptPlayerForShipUpgrade(nShipCargoLimit, nPlayerBalance);

        if (bIsUpgrading) {
          int nShipUpgradeCost;
          int nShipNewCargoLimit;
          int nShipCargoLimitIncrease;

          if (nShipCargoLimit == TIER_ONE_SHIP_CARGO_LIMIT) {
            nShipUpgradeCost = TIER_TWO_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_TWO_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          } else if (nShipCargoLimit == TIER_TWO_SHIP_CARGO_LIMIT) {
            nShipUpgradeCost = TIER_THREE_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_THREE_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          } else {
            nShipUpgradeCost = TIER_FOUR_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_FOUR_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          }

          upgradeShip(&nPlayerBalance, nShipUpgradeCost, &nShipCargoLimit, nShipNewCargoLimit);

          printShipUpgradeScreen(nShipCargoLimitIncrease, nShipUpgradeCost);

          promptPlayerForContinuation();
        }
      } else if (cChosenActionId == 'N') {
        printNavigationMenu(cCurrentPortId, nPlayerTurns);

        char cChosenPortId = promptPlayerForPortId(cCurrentPortId);

        if (cChosenPortId != 'X') {
          printf("\n");

          int bIsConfirmed = promptPlayerForConfirmation();

          if (bIsConfirmed) {
            int bIsSuccessful = generateRandomBool(100 - nPostponedDepartureChance);

            if (bIsSuccessful) {
              cCurrentPortId = cChosenPortId;

              printNavigationScreen(bIsSuccessful, cCurrentPortId, nPlayerTurns);
            } else {
              printNavigationScreen(bIsSuccessful, cChosenPortId, nPlayerTurns);
            }

            promptPlayerForContinuation();

            nPlayerTurns++;
            bIsNavigating = 1;
          }
        }
      } else {
        bIsQuitting = 1;
      }
    }

    if (!bIsQuitting) {
      if (nStormTurnDuration == -1) {
        nStormTurnDuration = 0;
      } else if (nStormTurnDuration == 0) {
        int bStartStorm = generateRandomBool(50);

        if (bStartStorm) {
          nStormTurnDuration = generateRandomStormTurnDuration(1) + 1;
          bIsNewStorm = 1;
          nStormWindSignalNumber = 1;
        }
      }

      if (nStormTurnDuration > 0) {
        nStormTurnDuration--;

        int nStormOldWindSignalNumber = nStormWindSignalNumber;

        if (nStormTurnDuration == 0) {
          // Provide the player with a 1 day buffer period.
          nStormTurnDuration--;
        } else if (!bIsNewStorm && (nStormWindSignalNumber < 5)) {
          int bAdjustStormStrength = generateRandomBool(50);

          if (bAdjustStormStrength) {
            int nStormNewWindSignalNumber;

            if (nStormWindSignalNumber < 5) {
              nStormNewWindSignalNumber = nStormWindSignalNumber + 1;
            } else {
              nStormNewWindSignalNumber = nStormWindSignalNumber - 1;
            }

            setStormStrength(&nStormWindSignalNumber, nStormNewWindSignalNumber, &nPostponedDepartureChance);
          }
        }

        printWeatherReportScreen(bIsNewStorm, nStormOldWindSignalNumber, nStormWindSignalNumber,
                                 nPostponedDepartureChance, nStormTurnDuration);

        if (bIsNewStorm) bIsNewStorm = 0;

        promptPlayerForContinuation();
      }
    }
  }

  printGameEndScreen(nPlayerProfit, nPlayerProfitTarget, nPlayerBalance, nPlayerInitialBalance, nPlayerTurns);

  return 0;
}
