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

#include "rm3_graph.hpp"

#include <boost/format.hpp>

namespace cirkit
{

/******************************************************************************
 * Types                                                                      *
 ******************************************************************************/

/******************************************************************************
 * Private functions                                                          *
 ******************************************************************************/

/******************************************************************************
 * Public functions                                                           *
 ******************************************************************************/

rm3_graph::rm3_graph( unsigned num_vars )
  : num_vars( num_vars )
{
}

void rm3_graph::create_po( const rm3_node& n, const std::string& name )
{
  outputs.emplace_back( n, name );
}

rm3_node rm3_graph::create_rm3( const rm3_node& x, const rm3_node& y, const rm3_node& z )
{
  /* trivial cases */
  if ( x == z ) return x;
  if ( x == y ) return z;
  if ( z == y ) return x;

  /* cached? */
  const auto key = std::make_tuple( std::min( x, z ), y, std::max( x, z ) );
  const auto it = strash.find( key );
  if ( it != strash.end() ) return it->second;

  /* create node */
  const auto v = nodes.size() / 3u + num_vars + 2u;

  nodes.push_back( std::get<0>( key ) );
  nodes.push_back( std::get<1>( key ) );
  nodes.push_back( std::get<2>( key ) );

  /* insert into cache */
  strash.emplace( key, v );

  return v;
}

rm3_node rm3_graph::create_not( const rm3_node& x )
{
  return create_rm3( 0, x, 1 );
}

unsigned rm3_graph::num_gates() const
{
  return nodes.size() / 3u;
}

unsigned rm3_graph::num_inputs() const
{
  return num_vars;
}

unsigned rm3_graph::num_outputs() const
{
  return outputs.size();
}

void rm3_graph::print_statistics( std::ostream& os ) const
{
  os << boost::format( "[i] RM3 graph i/o = %d/%d nodes = %d" ) % num_inputs() % num_outputs() % num_gates() << std::endl;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
