// Copyright © 2017 Max Z. All rights reserved.
//
// This file is part of Topcalc.
//
// Topcalc is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// Topcalc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Topcalc.  If not, see <http://www.gnu.org/licenses/>.

#include <cctype>
#include <cmath>
#include <istream>

#include "error.hpp"
#include "math.base.hpp"
#include "math.util.hpp"

math::util::value_type math::base::AddingSubtraction(util::value_type lval,
                                                     std::istream &is) {
  switch (static_cast<util::char_type>(util::GetSymbol(is))) {
  case '+':
    return std::make_pair(
        lval.first + AddingSubtraction(util::GetVal(is), is).first, false);

  case '-':
    // realize a-b like a+(-b)
    is.unget();
    return std::make_pair(
        lval.first + AddingSubtraction(util::GetVal(is), is).first, true);

  default:
    is.unget();

    return std::make_pair(MultiplicationDivision(lval, is), false);
  }
}

math::util::value_type::first_type math::base::Brackets(std::istream &is) {
  switch (static_cast<util::char_type>(util::GetSymbol(is))) {
  case '(': {
    auto result = util::Calculate(is).first;

    if (static_cast<util::char_type>(util::GetSymbol(is)) == ')')
      return result;
    else
      throw error::IncorrectVal("Missing ending bracket");
  }

  default:
    throw error::IncorrectVal("Start brackets without '('");
  }
}

math::util::value_type::first_type
math::base::MultiplicationDivision(util::value_type lval, std::istream &is) {
  switch (static_cast<util::char_type>(util::GetSymbol(is))) {
  case '*':
    return lval.first * MultiplicationDivision(util::GetVal(is), is);

  // realize a(b+c) like a*(b+c)
  case '(':
    is.unget();

    return lval.first * MultiplicationDivision(
                            std::make_pair(base::Brackets(is), false), is);

  case '/': {
    // realize a/b*c like a*(1/b)*c
    auto rval = util::GetVal(is);
    rval = std::make_pair(1 / rval.first, rval.second);

    return lval.first * MultiplicationDivision(rval, is);
  }

  default:
    is.unget();

    return Power(lval, is);
  }
}

math::util::value_type::first_type math::base::Power(util::value_type lval,
                                                     std::istream &is) {
  switch (static_cast<util::char_type>(util::GetSymbol(is))) {
  case '^': {
    // Is number interpreted from -(a) to (-a)?
    if (lval.second) {
      // -a = -(a)
      if (lval.first < 0)
        return -std::pow(std::abs(lval.first), Power(util::GetVal(is), is));

      // a = -(-a)
      else
        return -std::pow(-std::abs(lval.first), Power(util::GetVal(is), is));
    }

    else
      return std::pow(lval.first, Power(util::GetVal(is), is));
  }

  default:
    is.unget();

    return lval.first;
  }
}
