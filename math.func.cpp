#include "math.func.hpp"
#include "error.hpp"
#include "math.util.hpp"

#include <cctype>
#include <string>

std::vector<math::util::value_type::first_type> math::func::GetArgs(
    std::istream& is) {
  std::vector<util::value_type::first_type> result;
  if (util::GetSymbol(is) == '(') {
    do {
      result.push_back(util::Calculate(is).first);
    } while (util::GetSymbol(is) == ',');

    is.unget();

    if (util::GetSymbol(is) == ')')
      return result;
    else
      throw error::IncorrectSymbol("Incorrect separator in GetArgs");
  } else
    throw error::IncorrectVal("Start GetArgs without '('");
}

math::util::value_type::first_type math::func::ProcessConst(
    const util::char_type* name) {
  auto iterator = util::tableOfConsts.find(name);

  if (iterator != util::tableOfConsts.end())
    return iterator->second;
  else
    throw error::IncorrectConst("Incorrect constant in ProcessConst");
}

math::util::value_type::first_type math::func::ProcessFunc(
    const util::char_type* name, std::istream& is) {
  auto args = func::GetArgs(is);

  switch (args.size()) {
    case 1: {
      auto iterator = util::tableOfUnaryFunc.find(name);

      if (iterator != util::tableOfUnaryFunc.end())
        return iterator->second(args[0]);
      else
        throw error::IncorrectConst("Incorrect name of unary function");
    }

    case 2: {
      auto iterator = util::tableOfBinaryFunc.find(name);

      if (iterator != util::tableOfBinaryFunc.end()) {
        return iterator->second(args[0], args[1]);
      } else
        throw error::IncorrectConst("Incorrect name of binary function");
    }

    default:
      throw error::IncorrectConst("Too much arguments for math function");
  }
}

math::util::value_type::first_type math::func::ProcessLexeme(std::istream& is) {
  char buf;
  std::string name = "";

  while (std::isprint(buf = util::GetSymbol(), is.getloc())) {
    if (std::isalpha(buf, is.getloc()) || std::isdigit(buf, is.getloc()))
      name += buf;

    else if (buf == '(') {
      is.unget();

      return ProcessFunc(name.c_str(), is);
    }

    else {
      is.unget();

      return ProcessConst(name.c_str());
    }
  }

  is.unget();
  return ProcessConst(name.c_str());
}
