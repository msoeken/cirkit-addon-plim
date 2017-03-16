/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2016  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file stores_plim.hpp
 *
 * @brief Store definitions
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef STORES_PLIM_HPP
#define STORES_PLIM_HPP

#include <alice/command.hpp>

#include <iostream>

#include <classical/plim/rm3_graph.hpp>
#include <classical/xmg/xmg.hpp>

namespace alice
{

using namespace cirkit;

template<>
struct store_info<rm3_graph>
{
  static constexpr const char* key         = "rm3s";
  static constexpr const char* option      = "rm3";
  static constexpr const char* mnemonic    = "r";
  static constexpr const char* name        = "RM3";
  static constexpr const char* name_plural = "RM3s";
};

template<>
std::string store_entry_to_string<rm3_graph>( const rm3_graph& rm3 );

template<>
void print_store_entry_statistics<rm3_graph>( std::ostream& os, const rm3_graph& rm3 );

template<>
command::log_opt_t log_store_entry_statistics<rm3_graph>( const rm3_graph& rm3 );

template<>
inline bool store_can_convert<xmg_graph, rm3_graph>() { return true; }

template<>
rm3_graph store_convert<xmg_graph, rm3_graph>( const xmg_graph& xmg );

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
