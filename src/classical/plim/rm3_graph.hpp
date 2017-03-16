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
 * @file rm3_graph.hpp
 *
 * @brief A dedicated data-structure for RM3 graphs
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef RM3_GRAPH_HPP
#define RM3_GRAPH_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <core/utils/hash_utils.hpp>

namespace cirkit
{

using rm3_node = unsigned;

class rm3_graph
{
public:
  rm3_graph( unsigned num_vars = 0u );

  void create_po( const rm3_node& n, const std::string& name = std::string() );
  rm3_node create_rm3( const rm3_node& x, const rm3_node& y, const rm3_node& z );
  rm3_node create_not( const rm3_node& x );

  unsigned num_gates() const;
  unsigned num_inputs() const;
  unsigned num_outputs() const;

  void print_statistics( std::ostream& os ) const;

private:
  unsigned num_vars = 0u;

  std::vector<unsigned> nodes;
  std::vector<std::string> inputs;
  std::vector<std::pair<unsigned, std::string>> outputs;

  using rm3_graph_hash_key_t = std::tuple<rm3_node, rm3_node, rm3_node>;
  std::unordered_map<rm3_graph_hash_key_t, rm3_node, hash<rm3_graph_hash_key_t>> strash;
};

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
