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
 * \brief This file collect possible exceptions
 * \copyright GNU GPLv3
 * \date Sep 2017
 * \version 1.0
 */

#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>

/*!
 * Namespace of errors
 * \namespace
 */
namespace error {

/*!
 * Exception of incorrect constant
 * \class
 */
class IncorrectConst : public std::exception {
public:
  /*!
   * IncorrectConst constructor
   * \param what what is wrong exactly
   * \return
   */
  IncorrectConst(const char *what) : _what(what) {}

  /*!
   * What is wrong exactly
   * \return String of what is wrong
   */
  virtual const char *what() const noexcept override { return _what; }

private:
  const char *_what;
};

/*!
 * Exception of incorrect function
 * \class
 */
class IncorrectFunc : public std::exception {
public:
  /*!
   * IncorrectFunc constructor
   * \param what what is wrong exactly
   * \return
   */
  IncorrectFunc(const char *what) : _what(what) {}

  /*!
   * What is wrong exactly
   * \return String of what is wrong
   */
  virtual const char *what() const noexcept override { return _what; }

private:
  const char *_what;
};

/*!
 * Exception of incorrect math operation symbol
 * \class
 */
class IncorrectSymbol : public std::exception {
public:
  /*!
   * IncorrectSymbol constructor
   * \param what what is wrong exactly
   * \return
   */
  IncorrectSymbol(const char *what) : _what(what) {}

  /*!
   * What is wrong exactly
   * \return String of what is wrong
   */
  virtual const char *what() const noexcept override { return _what; }

private:
  const char *_what;
};

/*!
 * Exception of incorrect values
 * \class
 */
class IncorrectVal : public std::exception {
public:
  /*!
   * IncorrectVal constructor
   * \param what what is wrong exactly
   * \return
   */
  IncorrectVal(const char *what) : _what(what) {}

  /*!
   * What is wrong exactly
   * \return String of what is wrong
   */
  virtual const char *what() const noexcept override { return _what; }

private:
  const char *_what;
};

} // namespace error

#endif // ERROR_HPP
