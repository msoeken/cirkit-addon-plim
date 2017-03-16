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

#include "stores_plim.hpp"

#include <classical/plim/rm3_conversion.hpp>

namespace alice
{

using namespace cirkit;

template<>
std::string store_entry_to_string<rm3_graph>( const rm3_graph& rm3 )
{
  return boost::str( boost::format( "[i] i/o = %d/%d nodes = %d" ) % rm3.num_inputs() % rm3.num_outputs() % rm3.num_gates() );
}

template<>
void print_store_entry_statistics<rm3_graph>( std::ostream& os, const rm3_graph& rm3 )
{
  rm3.print_statistics( os );
}

template<>
command::log_opt_t log_store_entry_statistics<rm3_graph>( const rm3_graph& rm3 )
{
  return command::log_opt_t({
      {"inputs", rm3.num_inputs()},
      {"outputs", rm3.num_outputs()},
      {"size", rm3.num_gates()}
    });
}

template<>
rm3_graph store_convert<xmg_graph, rm3_graph>( const xmg_graph& xmg )
{
  return rm3_from_xmg( xmg );
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
