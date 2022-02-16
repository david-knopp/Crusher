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

#include "crusher/precompiled.h"
#include "obj_loader.h"
#include "filesystem/file_string.h"

using namespace crusher;

bool obj_loader::load(const path& obj_path)
{
  file_string fs(obj_path);
  
  if (fs.loaded())
  {
    parse_vertex_data(fs);
    calculate_normals();

    return true;
  }

  return false;
}

const obj_loader::vertex_list& obj_loader::get_vertices(void) const
{
  return _vertices;
}

const obj_loader::index_list& obj_loader::get_indices(void) const
{
  return _indices;
}

void obj_loader::parse_vertex_data(const file_string& fs)
{
  // skip any leading white space
  const std::string& data = fs.str();
  unsigned it = data.find_first_not_of("\n\r\0 ");

  while (it != std::string::npos)
  {
    // extract vertex data
    if (data[it] == 'v')
    {
      read_vertex(data, it + 1);
    }
    // extract face data
    else if (data[it] == 'f')
    {
      read_face(data, it + 1);
    }

    // skip to next line
    it = data.find_first_of("\n\r\0 ", it);
    it = data.find_first_not_of("\n\r\0 ", it);
  }
}

void obj_loader::read_vertex(const std::string& file_data, unsigned pos)
{
  vertex v;
  const char* c_data = file_data.c_str();

  // Read vertex positions
  pos = get_next_element(file_data, pos);
  v.pos.x = static_cast<float>(atof(c_data + pos));

  pos = get_next_element(file_data, pos);
  v.pos.y = static_cast<float>(atof(c_data + pos));

  pos = get_next_element(file_data, pos);
  v.pos.z = static_cast<float>(atof(c_data + pos));

  v.norm = vec3::zero;
  v.tex = vec2::zero;

  _vertices.push_back(v);
}

void obj_loader::read_face(const std::string& file_data, unsigned pos)
{
  const char* c_data = file_data.c_str();

  // read face indices
  pos = get_next_element(file_data, pos);
  _indices.push_back(static_cast<unsigned short>(atoi(c_data + pos) - 1));
  
  pos = get_next_element(file_data, pos);
  _indices.push_back(static_cast<unsigned short>(atoi(c_data + pos) - 1));

  pos = get_next_element(file_data, pos);
  _indices.push_back(static_cast<unsigned short>(atoi(c_data + pos) - 1));
}

unsigned obj_loader::get_next_element(const std::string& file_data, unsigned pos)
{
  // skip past current element
  pos = file_data.find_first_of(" ", pos);

  // skip past white space
  return file_data.find_first_not_of(" ", pos);
}

void obj_loader::calculate_normals(void)
{
  const unsigned num_vertices = _vertices.size();
  const unsigned num_indices = _indices.size();
  std::vector<vec3> normal_sums(num_vertices, vec3::zero);

  for (unsigned i = 0; i < num_indices; i += 3)
  {
    const vertex& v0 = _vertices[_indices[i]];
    const vertex& v1 = _vertices[_indices[i + 1]];
    const vertex& v2 = _vertices[_indices[i + 2]];

    // calculate face normal
    vec3 normal = vec3::cross(v1.pos - v0.pos, v2.pos - v1.pos);
    normal.normalize();

    // sum face normal and each vertex's existing normals
    normal_sums[_indices[i]] += normal;
    normal_sums[_indices[i + 1]] += normal;
    normal_sums[_indices[i + 2]] += normal;
  }

  // store averaged normal
  for (unsigned i = 0; i < num_vertices; ++i)
  {
    vertex& v = _vertices[i];
    float length = normal_sums[i].length();
    if (length > 0)
      v.norm = normal_sums[i] / length;
  }
}
