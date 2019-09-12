#include <cctype>
#include <istream>
#include <utility>

#include "error.hpp"
#include "math.base.hpp"
#include "math.func.hpp"
#include "math.util.hpp"

math::util::value_type math::util::Calculate(std::istream &is) {
  util::value_type result = GetVal(is);

  while (
      std::isprint(static_cast<char_type>(util::PeekSymbol(is)), is.getloc())) {
    switch (static_cast<char_type>(util::PeekSymbol(is))) {
    case ',':
    case ')':
      return result;

    case '+':
    case '-':
    case '*':
    case '(':
    case '/':
    case '^':

      result = base::AddingSubtraction(result, is);
      break;

    default:
      throw error::IncorrectSymbol("Incorrect math operation in Calculate");
    }
  }

  return result;
}

math::util::char_type math::util::GetSymbol(std::istream &is) {
  // skip all whitespaces
  while (std::isblank(static_cast<char_type>(is.get()), is.getloc()))
    continue;

  is.unget();
  return math::util::char_type(is.get());
}

math::util::value_type math::util::GetVal(std::istream &is) {
  if (std::isdigit(static_cast<char_type>(util::PeekSymbol(is)), is.getloc())) {
    util::value_type::first_type buf;
    is >> buf;

    return std::make_pair(buf, false);

  } else if (std::isalpha(static_cast<char_type>(util::PeekSymbol(is)),
                          is.getloc())) {
    return std::make_pair(func::ProcessLexeme(is), false);

  } else {
    switch (static_cast<char_type>(util::GetSymbol(is))) {
    case '(':
      is.unget();
      return std::make_pair(base::Brackets(is), false);

    case '+':
      return GetVal(is);

    case '-': {
      util::value_type buf = GetVal(is);

      buf.first = -buf.first;
      buf.second = true; // -a -> +(-a)

      return buf;
    }

    default:
      throw error::IncorrectVal("Incorrect value in GetVal");
    }
  }
}

math::util::char_type math::util::PeekSymbol(std::istream &is) {
  // skip all whitespaces
  while (std::isblank(static_cast<char_type>(is.get()), is.getloc()))
    continue;

  is.unget();
  return math::util::char_type(is.peek());
}
