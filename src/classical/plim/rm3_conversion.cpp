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

#include "rm3_conversion.hpp"

#include <core/utils/range_utils.hpp>

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

rm3_graph rm3_from_xmg( const xmg_graph& xmg )
{
  rm3_graph rm3( xmg.inputs().size() );

  std::vector<rm3_node> node_to_node( xmg.size() );

  /* constant */
  node_to_node[0u] = 0u;

  for ( const auto& pi : index( xmg.inputs() ) )
  {
    node_to_node[pi.value.first] = pi.index + 2u;
  }

  /* nodes */
  for ( const auto& n : xmg.topological_nodes() )
  {
    /* only real gates */
    if ( xmg.is_input( n ) ) continue;

    /* no XOR for now */
    assert( xmg.is_maj( n ) );

    /* get all children information */
    const auto children = xmg.children( n );
    const auto& xx = children[0u].node;
    const auto& yy = children[1u].node;
    const auto& zz = children[2u].node;
    const auto cx = children[0u].complemented;
    const auto cy = children[1u].complemented;
    const auto cz = children[2u].complemented;
    const auto& x = node_to_node[xx];
    const auto& y = node_to_node[yy];
    const auto& z = node_to_node[zz];

    rm3_node rn{};

    /* AND/OR */
    if ( xx == 0u )
    {
      if ( !cy && !cz )
      {
	rn = rm3.create_rm3( y, cx ? 0 : 1, z );
      }
      else if ( !cy && cz )
      {
	rn = rm3.create_rm3( cx ? 1 : 0, z, y );
      }
      else if ( cy && !cz )
      {
	rn = rm3.create_rm3( cx ? 1 : 0, y, z );
      }
      else if ( cy && cz )
      {
	rn = rm3.create_not( rm3.create_rm3( y, cx ? 1 : 0, z ) );
      }
    }
    /* MAJ */
    else
    {
      if ( cx )
      {
	assert( !cy && !cz );
	rn = rm3.create_rm3( y, x, z );
      }
      else if ( cy )
      {
	assert( !cx && !cz );
	rn = rm3.create_rm3( x, y, z );
      }
      else if ( cz )
      {
	assert( !cx && !cy );
	rn = rm3.create_rm3( x, z, y );
      }
      else
      {
	rn = rm3.create_rm3( x, rm3.create_not( y ), z );
      }
    }

    node_to_node[n] = rn;
  }

  /* outputs */
  for ( const auto& po : xmg.outputs() )
  {
    const auto x = node_to_node[po.first.node];
    rm3.create_po( po.first.complemented ? rm3.create_not( x ) : x, po.second );
  }

  return rm3;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
