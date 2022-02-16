/*
--------------------------------------------------------------------------------
this file is part of the crusher game engine
Copyright (c) 2014 David Knopp - http://www.davidknopp.net

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--------------------------------------------------------------------------------
*/

#pragma once
#include "filesystem/path.h"
#include "filesystem/file_string.h"
#include "graphics/vertex/vertex.h"

namespace crusher
{

  class obj_loader
  {
    public:
      // public typedefs
      typedef std::vector<vertex> vertex_list;
      typedef std::vector<unsigned> index_list;

      // public methods
      bool load(const path& obj_path);

      const vertex_list& get_vertices(void) const;
      const index_list& get_indices(void) const;

    private:
      // private methods
      void parse_vertex_data(const file_string& fs);
      void read_vertex(const std::string& file_data, unsigned pos);
      void read_face(const std::string& file_data, unsigned pos);
      unsigned get_next_element(const std::string& file_data, unsigned pos);

      void calculate_normals(void);

      // private members
      vertex_list _vertices;
      index_list _indices;

  }; // class obj_loader

} // namespace crusher