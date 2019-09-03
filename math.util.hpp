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
 * \brief Usefull stuff for math::base
 * \copyright GNU GPLv3
 * \date Sep 2017
 * \version 1.0
 */

#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace math {

namespace util {

/*!
 * This using declarate char type
 */
using char_type = typename std::istream::char_type;

/*!
 * This using declarate value type
 * \param first number
 * \param second Is number interpreted from -(a) to +(-a)?
 */
using value_type = std::pair<double, bool>;

/*!
 * This using declarate unary function type
 */
using binary_func = value_type::first_type (*)(value_type::first_type,
                                               value_type::first_type);

/*!
 * This using declarate unary function type
 */
using unary_func = value_type::first_type (*)(value_type::first_type);

/*!
 * This map keep values of constants
 */
static std::map<std::string, value_type::first_type> tableOfConsts = {
    std::make_pair(
        "nan",
        std::nan("")),
    std::make_pair(
        "inf",
        INFINITY),
    std::make_pair(
        "e",
        2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274274663919320030599218174135966290435729003342952605956307381323286279434907632338298807531952510190115738341879307021540891499348841675092447614606680822648001684774118537423454424371075390777449920695517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416928368190255151086574637721112523897844250569536967707854499699679468644549059879316368892300987931277361782154249992295763514822082698951936680331825288693984964651058209392398294887933203625094431173012381970684161403970198376793206832823764648042953118023287825098194558153017567173613320698112509961818815930416903515988885193458072738667385894228792284998920868058257492796104841984443634632449684875602336248270419786232090021609902353043699418491463140934317381436405462531520961836908887070167683964243781405927145635490613031072085103837505101157477041718986106873969655212671546889570350354),
    std::make_pair(
        "pi",
        3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989)};

/*!
 * This map keep unary functions
 */
static std::map<std::string, unary_func> tableOfUnaryFunc = {
    // trigonometric functions
    std::make_pair("cos", static_cast<unary_func>(std::cos)),
    std::make_pair("sin", static_cast<unary_func>(std::sin)),
    std::make_pair("tan", static_cast<unary_func>(std::tan)),
    std::make_pair("acos", static_cast<unary_func>(std::acos)),
    std::make_pair("asin", static_cast<unary_func>(std::asin)),
    std::make_pair("atan", static_cast<unary_func>(std::atan)),

    // hyperbolic functions
    std::make_pair("cosh", static_cast<unary_func>(std::cosh)),
    std::make_pair("sinh", static_cast<unary_func>(std::sinh)),
    std::make_pair("tanh", static_cast<unary_func>(std::tanh)),
    std::make_pair("acosh", static_cast<unary_func>(std::acosh)),
    std::make_pair("asinh", static_cast<unary_func>(std::asinh)),
    std::make_pair("atanh", static_cast<unary_func>(std::atanh)),

    // expotential and logarithmic functions
    std::make_pair("exp", static_cast<unary_func>(std::exp)),
    std::make_pair("log", static_cast<unary_func>(std::log)),
    std::make_pair("log10", static_cast<unary_func>(std::log10)),
    std::make_pair("exp2", static_cast<unary_func>(std::exp2)),
    std::make_pair("expm1", static_cast<unary_func>(std::expm1)),
    std::make_pair("log1p", static_cast<unary_func>(std::log1p)),
    std::make_pair("log2", static_cast<unary_func>(std::log2)),
    std::make_pair("logb", static_cast<unary_func>(std::logb)),

    // power functions
    std::make_pair("sqrt", static_cast<unary_func>(std::sqrt)),
    std::make_pair("cbrt", static_cast<unary_func>(std::cbrt)),

    // error and gamma functions
    std::make_pair("erf", static_cast<unary_func>(std::erf)),
    std::make_pair("erfc", static_cast<unary_func>(std::erfc)),
    std::make_pair("tgamma", static_cast<unary_func>(std::tgamma)),
    std::make_pair("lgamma", static_cast<unary_func>(std::lgamma)),

    // rounding and remainder functions
    std::make_pair("ceil", static_cast<unary_func>(std::ceil)),
    std::make_pair("floor", static_cast<unary_func>(std::floor)),
    std::make_pair("trunc", static_cast<unary_func>(std::trunc)),
    std::make_pair("round", static_cast<unary_func>(std::round)),
    std::make_pair("rint", static_cast<unary_func>(std::rint)),
    std::make_pair("nearbyint", static_cast<unary_func>(std::nearbyint)),

    // other functions
    std::make_pair("fabs", static_cast<unary_func>(std::fabs)),
    std::make_pair("abs", static_cast<unary_func>(std::abs))

};

static std::map<std::string, binary_func> tableOfBinaryFunc = {

  // power functions
    std::make_pair("pow", static_cast<binary_func>(std::pow)),
    std::make_pair("hypot", static_cast<binary_func>(std::hypot)),

  // rounding and remainder functions
    std::make_pair("fmod", static_cast<binary_func>(std::fmod)),
    std::make_pair("remainder", static_cast<binary_func>(std::remainder)),

};

/*!
 * This function start of calculate
 * \param is input stream
 * \return result
 * \throw error::IncorrectSymbol
 */
math::util::value_type Calculate(std::istream& is = std::cin);

/*!
 * This function get symbol of math operation ( +,-,/,* etc.)
 * \param is input stream
 * \return symbol of math operation
 */
std::istream::char_type GetSymbol(std::istream& is = std::cin);

/*!
 * This function get value
 * \param is input stream
 * \return value
 * \throw error::IncorrectLval
 */
math::util::value_type GetVal(std::istream& is = std::cin);

/*!
 * This function peek symbol of math operation ( +,-,/,* etc.)
 * \param is input stream
 * \return symbol of math operation
 * \throw error::IncorrectSymbol
 */
std::istream::char_type PeekSymbol(std::istream& is = std::cin);

}  // namespace util

}  // namespace math

#endif  // MATH_UTIL_HPP
