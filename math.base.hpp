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

/*!
 * \file
 * \author Max Z
 * \brief Realize base math
 * \copyright GNU GPLv3
 * \date Sep 2017
 * \version 1.0
 */

#ifndef MATH_BASE_HPP
#define MATH_BASE_HPP

#include <iostream>

#include "math.util.hpp"

namespace math {

namespace base {

/*!
 * This function make adding and subtraction
 * \param lval left value
 * \param &is input stream
 * \return
 * \throw
 */
util::value_type AddingSubtraction(util::value_type lval,
                                   std::istream& is = std::cin);

/*!
 * This function realize brackets
 * \param &is input stream
 * \return
 * \throw error::IncorrectLval error::IncorrectRval
 */
util::value_type::first_type Brackets(std::istream& is = std::cin);

/*!
 * This function make multiplication and division
 * \param lval left value
 * \param &is input stream
 * \return
 * \throw
 */
util::value_type::first_type MultiplicationDivision(
    util::value_type lval, std::istream& is = std::cin);

/*!
 * This function make power
 * \param lval left value
 * \param &is input stream
 * \return
 * \throw
 */
util::value_type::first_type Power(util::value_type lval,
                                   std::istream& is = std::cin);

}  // namespace base

}  // namespace math

#endif  // MATH_BASE_HPP
