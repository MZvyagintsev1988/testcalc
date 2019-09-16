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
 * \brief main file
 * \copyright GNU GPLv3
 * \date Sep 2017
 * \version 1.0
 */


#include <cctype>
#include <exception>
#include <iostream>
#include <limits>
#include <locale>

#include "error.hpp"
#include "math.util.hpp"

int test();

int main() {
  test();

  const char *PROMPT = " > "; // prompt to input

  std::cout << PROMPT;
  while (true) {
    try {
      if (std::isprint(char(std::cin.get()), std::locale())) {
        std::cin.unget();

        // check exit words
        std::string buffer;
        std::cin >> buffer;
        if (buffer.find("quit") == 0 || buffer.find("exit") == 0 ||
            buffer.find("quit") == 0 || buffer.find("exit") == 0)
          break;

        // return symbols in cin
        for (int i = int(buffer.size()) - 1; i >= 0; i--)
          std::cin.putback(buffer[std::string::size_type(i)]);

        std::cout << " = " << math::util::Calculate(std::cin).first
                  << std::endl;

        // clean cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), int('\n'));
      } else {
        // clean cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), int('\n'));

        std::cin.clear();
      }

      std::cout << PROMPT;
    } catch (std::exception &exc) {
      std::cerr << "\tError: " << exc.what() << '.' << std::endl;

      // clean cin
      std::cin.unget();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), int('\n'));

      std::cout << PROMPT;
    } catch (...) {
      std::cerr << "Unexpected exception " << std::endl;
      throw;
    }
  }

  return 0;
}
