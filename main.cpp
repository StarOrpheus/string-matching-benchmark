#include <array>
#include <iostream>
#include <map>
#include <utility>
#include <unordered_map>

#include "benchmark/benchmark.h"

enum class COMMAND {
  PRINT,
  HELLO,
  WORLD,
  FOO,
  BAR,
  BAZ,
  FOOBAR, // note: same prefix
  FOOBAZ,
  TEST,
  ZAZ,

  INVALID
};

constexpr auto TEST_DATA_SIZE = 1024 * 1024;

namespace {

uint32_t nextRandomU32() noexcept {
  static uint32_t State = 17;
  State <<= 13;
  State >>= 17;
  State <<= 5;
  return State;
}

std::vector<std::string> genTestData() noexcept {
  std::array CorrectCommands{"print", "hello",  "world",  "foo",  "bar",
                             "baz",   "foobar", "foobaz", "test", "zaz"};

  std::array InvalidCommands{"asdasd", "foozaz", "foo ", " foo", "bazbaz"};

  std::vector<std::string> Result;

  for (size_t I = 0; I < TEST_DATA_SIZE / 2; ++I) {
    Result.emplace_back(
        CorrectCommands[nextRandomU32() % CorrectCommands.size()]);
  }

  for (size_t I = 0; I < TEST_DATA_SIZE / 2; ++I) {
    Result.emplace_back(
        InvalidCommands[nextRandomU32() % InvalidCommands.size()]);
  }

  return Result;
}

void BM_std_map(benchmark::State &St) {
  std::map<std::string_view, COMMAND> TranslationTable{
      {"print", COMMAND::PRINT},   {"hello", COMMAND::HELLO},
      {"world", COMMAND::WORLD},   {"foo", COMMAND::FOO},
      {"bar", COMMAND::BAR},       {"baz", COMMAND::BAZ},
      {"foobar", COMMAND::FOOBAR}, {"foobaz", COMMAND::FOOBAZ},
      {"test", COMMAND::TEST},     {"zaz", COMMAND::ZAZ}};

  auto TestData = genTestData();

  for (auto _ : St) {
    for (auto &&Line : TestData) {
      auto Iter = TranslationTable.find(Line);
      COMMAND TranslationResult =
          Iter == TranslationTable.end() ? COMMAND::INVALID : Iter->second;
      benchmark::DoNotOptimize(TranslationResult);
    }
  }
}

BENCHMARK(BM_std_map);

void BM_std_unordered_map(benchmark::State &St) {
  std::unordered_map<std::string_view, COMMAND> TranslationTable{
      {"print", COMMAND::PRINT},   {"hello", COMMAND::HELLO},
      {"world", COMMAND::WORLD},   {"foo", COMMAND::FOO},
      {"bar", COMMAND::BAR},       {"baz", COMMAND::BAZ},
      {"foobar", COMMAND::FOOBAR}, {"foobaz", COMMAND::FOOBAZ},
      {"test", COMMAND::TEST},     {"zaz", COMMAND::ZAZ}};

  auto TestData = genTestData();

  for (auto _ : St) {
    for (auto &&Line : TestData) {
      auto Iter = TranslationTable.find(Line);
      COMMAND TranslationResult =
          Iter == TranslationTable.end() ? COMMAND::INVALID : Iter->second;
      benchmark::DoNotOptimize(TranslationResult);
    }
  }
}

BENCHMARK(BM_std_unordered_map);

using namespace std::literals::string_view_literals;

void BM_std_array(benchmark::State &St) {
  constexpr static std::array<std::pair<std::string_view, COMMAND>, 10>
      TranslationTable{{{"print"sv, COMMAND::PRINT},
                        {"hello"sv, COMMAND::HELLO},
                        {"world"sv, COMMAND::WORLD},
                        {"foo"sv, COMMAND::FOO},
                        {"bar"sv, COMMAND::BAR},
                        {"baz"sv, COMMAND::BAZ},
                        {"foobar"sv, COMMAND::FOOBAR},
                        {"foobaz"sv, COMMAND::FOOBAZ},
                        {"test"sv, COMMAND::TEST},
                        {"zaz"sv, COMMAND::ZAZ}}};

  auto TestData = genTestData();

  for (auto _ : St) {
    for (auto &&Line : TestData) {
      auto Iter = std::find_if(TranslationTable.begin(), TranslationTable.end(),
                               [&] (auto&& EntryPair) {
                                 return EntryPair.first == Line;
                               });
      COMMAND TranslationResult =
          Iter == TranslationTable.end() ? COMMAND::INVALID : Iter->second;
      benchmark::DoNotOptimize(TranslationResult);
    }
  }
}

BENCHMARK(BM_std_array);


} // namespace