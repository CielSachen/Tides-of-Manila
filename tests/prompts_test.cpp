extern "C" {
#include "prompts.h"
}

#include <gtest/gtest.h>

#include <cstdio>

const int kTotalShipCargoAmount = 0;
const int kShipCargoLimit = 1000;
const int kPlayerBalance = 1000;
const int kCargoPrice = 1;
const char kTransactionType = 'B';
const int kShipCargoAmount = 1;
const char kCargoId = 'C';
const char kPortId = 'T';

void verify_file_reopening(FILE* reopened_file) {
  if (reopened_file == NULL) {
    std::cerr << "The file that contains the mocked user inputs could not be opened." << std::endl;

    exit(EXIT_FAILURE);
  }
}

// promptPlayerForMerchantId()
TEST(PromptPlayerForMerchantIdTest, ReturnsGivenInteger) {
  // Mock a user inputting an integer response of 100.
  FILE* mock_inputs_file = freopen("mocks/integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_merchant_id = promptPlayerForMerchantId();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_merchant_id, 100);
}

TEST(PromptPlayerForMerchantIdTest, RetriesWhenIntegerIsNegative) {
  // Mock a user inputting an integer response of -1, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.negative.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_merchant_id = promptPlayerForMerchantId();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_merchant_id, 100);
}

TEST(PromptPlayerForMerchantIdTest, RetriesWhenIntegerIsTooBig) {
  // Mock a user inputting an integer response of 1000, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.big.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_merchant_id = promptPlayerForMerchantId();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_merchant_id, 100);
}

// promptPlayerForInitialBalance()
TEST(PromptPlayerForInitialBalanceTest, ReturnsGivenInteger) {
  // Mock a user inputting an integer response of 100.
  FILE* mock_inputs_file = freopen("mocks/integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_initial_balance = promptPlayerForInitialBalance();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_initial_balance, 100);
}

TEST(PromptPlayerForInitialBalanceTest, ReturnsGivenBigInteger) {
  // Mock a user inputting an integer response of 1000.
  FILE* mock_inputs_file = freopen("mocks/integer.big.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_initial_balance = promptPlayerForInitialBalance();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_initial_balance, 1000);
}

TEST(PromptPlayerForInitialBalanceTest, RetriesWhenIntegerIsNegative) {
  // Mock a user inputting an integer response of -1, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.negative.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_initial_balance = promptPlayerForInitialBalance();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_initial_balance, 100);
}

// promptPlayerForProfitTarget()
TEST(PromptPlayerForPlayerProfitTargetTest, ReturnsGivenInteger) {
  // Mock a user inputting an integer response of 100.
  FILE* mock_inputs_file = freopen("mocks/integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_profit_target = promptPlayerForProfitTarget();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_profit_target, 100);
}

TEST(PromptPlayerForPlayerProfitTargetTest, ReturnsGivenBigInteger) {
  // Mock a user inputting an integer response of 1000.
  FILE* mock_inputs_file = freopen("mocks/integer.big.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_profit_target = promptPlayerForProfitTarget();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_profit_target, 1000);
}

TEST(PromptPlayerForPlayerProfitTargetTest, RetriesWhenIntegerIsLessThanTheMinimum) {
  // Mock a user inputting an integer response of 1, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.small.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_profit_target = promptPlayerForProfitTarget();

  fclose(mock_inputs_file);

  EXPECT_EQ(given_profit_target, 100);
}

// promptPlayerForConfirmation
TEST(PromptPlayerForConfirmationTest, ReturnsTrue) {
  // Mock a user inputting a character response of 'Y.'
  FILE* mock_inputs_file = freopen("mocks/bool.true.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_confirmed = promptPlayerForConfirmation();

  fclose(mock_inputs_file);

  EXPECT_EQ(is_confirmed, true);
}

TEST(PromptPlayerForConfirmationTest, ReturnsFalse) {
  // Mock a user inputting a character response of 'N.'
  FILE* mock_inputs_file = freopen("mocks/bool.false.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_confirmed = promptPlayerForConfirmation();

  fclose(mock_inputs_file);

  EXPECT_EQ(is_confirmed, false);
}

TEST(PromptPlayerForConfirmationTest, RetriesWhenResponseIsAnInvalidCharacter) {
  // Mock a user inputting multiple character responses, then 'Y.'
  FILE* mock_inputs_file = freopen("mocks/bool.invalid.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_confirmed = promptPlayerForConfirmation();

  fclose(mock_inputs_file);

  EXPECT_EQ(is_confirmed, true);
}

// promptPlayerForActionId
TEST(PromptPlayerForActionIdTest, ReturnsGivenCharacter) {
  // Mock a user inputting a character response of 'B.'
  FILE* mock_inputs_file = freopen("mocks/action-id.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_action_id = promptPlayerForActionId(kTotalShipCargoAmount, kShipCargoLimit, kPlayerBalance, kCargoPrice,
                                                  kCargoPrice, kCargoPrice, kCargoPrice);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_action_id, 'B');
}

TEST(PromptPlayerForActionIdTest, RetriesWhenResponseIsAnInvalidCharacter) {
  // Mock a user inputting multiple character responses, then 'B.'
  FILE* mock_inputs_file = freopen("mocks/action-id.invalid.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_action_id = promptPlayerForActionId(kTotalShipCargoAmount, kShipCargoLimit, kPlayerBalance, kCargoPrice,
                                                  kCargoPrice, kCargoPrice, kCargoPrice);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_action_id, 'B');
}

TEST(PromptPlayerForActionIdTest, RetriesWhenResponseIsAnInteger) {
  // Mock a user inputting a character response of '1', then 'B.'
  FILE* mock_inputs_file = freopen("mocks/action-id.integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_action_id = promptPlayerForActionId(kTotalShipCargoAmount, kShipCargoLimit, kPlayerBalance, kCargoPrice,
                                                  kCargoPrice, kCargoPrice, kCargoPrice);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_action_id, 'B');
}

// promptPlayerForCargoId
TEST(PromptPlayerForCargoIdTest, ReturnsGivenCharacter) {
  // Mock a user inputting a character response of 'C.'
  FILE* mock_inputs_file = freopen("mocks/cargo-id.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_cargo_id =
    promptPlayerForCargoId(kTransactionType, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
                           kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_cargo_id, 'C');
}

TEST(PromptPlayerForCargoIdTest, RetriesWhenResponseIsAnInvalidCharacter) {
  // Mock a user inputting multiple character responses, then 'C.'
  FILE* mock_inputs_file = freopen("mocks/cargo-id.invalid.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_cargo_id =
    promptPlayerForCargoId(kTransactionType, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
                           kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_cargo_id, 'C');
}

TEST(PromptPlayerForCargoIdTest, RetriesWhenResponseIsAnInteger) {
  // Mock a user inputting a character response of '1', then 'C.'
  FILE* mock_inputs_file = freopen("mocks/cargo-id.integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_cargo_id =
    promptPlayerForCargoId(kTransactionType, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
                           kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_cargo_id, 'C');
}

// promptPlayerForCargoAmount
TEST(PromptPlayerForCargoAmountTest, ReturnsGivenInteger) {
  // Mock a user inputting an integer response of 100.
  FILE* mock_inputs_file = freopen("mocks/integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_cargo_amount = promptPlayerForCargoAmount(
    kTransactionType, kShipCargoLimit, kCargoId, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
    kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(given_cargo_amount, 100);
}

TEST(PromptPlayerForCargoAmountTest, ReturnsGivenBigInteger) {
  // Mock a user inputting an integer response of 1000, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.big.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_cargo_amount = promptPlayerForCargoAmount(
    kTransactionType, kShipCargoLimit, kCargoId, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
    kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(given_cargo_amount, 1000);
}

TEST(PromptPlayerForCargoAmountTest, RetriesWhenIntegerIsNegative) {
  // Mock a user inputting an integer response of -1, then 100.
  FILE* mock_inputs_file = freopen("mocks/integer.negative.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  int given_cargo_amount = promptPlayerForCargoAmount(
    kTransactionType, kShipCargoLimit, kCargoId, kPlayerBalance, kCargoPrice, kCargoPrice, kCargoPrice, kCargoPrice,
    kShipCargoAmount, kShipCargoAmount, kShipCargoAmount, kShipCargoAmount);

  fclose(mock_inputs_file);

  EXPECT_EQ(given_cargo_amount, 100);
}

// promptPlayerForShipUpgrade
TEST(PromptPlayerForShipUpgradeTest, ReturnsTrue) {
  // Mock a user inputting a character response of 'Y.'
  FILE* mock_inputs_file = freopen("mocks/bool.true.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_upgrading = promptPlayerForShipUpgrade(kShipCargoLimit, kPlayerBalance);

  fclose(mock_inputs_file);

  EXPECT_EQ(is_upgrading, true);
}

TEST(PromptPlayerForShipUpgradeTest, ReturnsFalse) {
  // Mock a user inputting a character response of 'N.'
  FILE* mock_inputs_file = freopen("mocks/bool.false.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_upgrading = promptPlayerForShipUpgrade(kShipCargoLimit, kPlayerBalance);

  fclose(mock_inputs_file);

  EXPECT_EQ(is_upgrading, false);
}

TEST(PromptPlayerForShipUpgradeTest, RetriesWhenResponseIsAnInvalidCharacter) {
  // Mock a user inputting multiple character responses, then 'Y.'
  FILE* mock_inputs_file = freopen("mocks/bool.invalid.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  bool is_upgrading = promptPlayerForShipUpgrade(kShipCargoLimit, kPlayerBalance);

  fclose(mock_inputs_file);

  EXPECT_EQ(is_upgrading, true);
}

// promptPlayerForPortId
TEST(PromptPlayerForPortIdTest, ReturnsGivenCharacter) {
  // Mock a user inputting a character response of 'M.'
  FILE* mock_inputs_file = freopen("mocks/port-id.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_port_id = promptPlayerForPortId(kPortId);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_port_id, 'M');
}

TEST(PromptPlayerForPortIdTest, RetriesWhenResponseIsAnInvalidCharacter) {
  // Mock a user inputting multiple character responses, then 'M.'
  FILE* mock_inputs_file = freopen("mocks/port-id.invalid.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_port_id = promptPlayerForPortId(kPortId);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_port_id, 'M');
}

TEST(PromptPlayerForPortIdTest, RetriesWhenResponseIsAnInteger) {
  // Mock a user inputting a character response of '1', then 'M.'
  FILE* mock_inputs_file = freopen("mocks/port-id.integer.txt", "r", stdin);

  verify_file_reopening(mock_inputs_file);

  char chosen_port_id = promptPlayerForPortId(kPortId);

  fclose(mock_inputs_file);

  EXPECT_EQ(chosen_port_id, 'M');
}
