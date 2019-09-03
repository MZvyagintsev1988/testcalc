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
 * \brief Realization of functions and constants
 * \copyright GNU GPLv3
 * \date Oct 2017
 * \version 1.0
 */

#ifndef MATH_FUNC_HPP
#define MATH_FUNC_HPP

#include <iostream>
#include <vector>

#include "math.util.hpp"

namespace math {

namespace func {

/*!
 * This function get arguments of function
 * \param is input stream
 * \return array of args
 * \throw error::IncorrectVal error::IncorrectSymbol
 */
std::vector<math::util::value_type::first_type> GetArgs(
    std::istream& is = std::cin);

/*!
 * This function process constants
 * \param is input stream
 * \return result
 * \throw error::IncorrectConst
 */
math::util::value_type::first_type ProcessConst(const util::char_type* name);

/*!
 * This function process functions
 * \param is input stream
 * \return result
 * \throw
 */
math::util::value_type::first_type ProcessFunc(const util::char_type* name,
                                               std::istream& is = std::cin);

/*!
 * This function process lexemes
 * \param is input stream
 * \return result
 * \throw
 */
math::util::value_type::first_type ProcessLexeme(std::istream& is = std::cin);

}  // namespace func

}  // namespace math

#endif  // MATH_FUNC_HPP
