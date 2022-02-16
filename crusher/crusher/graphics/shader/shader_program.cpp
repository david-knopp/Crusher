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
#include "shader_program.h"
#include "graphics/types/shader_type.h"
#include "graphics/types/object_type.h"
#include "filesystem/file_string.h"

using namespace crusher;

shader_program::shader_program(const std::string& name, const std::string& vert, const std::string& frag)
  : _name(name)
{
  shader_path_list paths(2);
  paths[0] = path(vert);
  paths[1] = path(frag);

  create_program(paths);
}

shader_program::shader_program(const path&)
{
  //! TODO: read shader paths from file
  error("shader_program(const path&) not implemented.");
}

shader_program::~shader_program(void)
{
  glDeleteProgram(*_id);
}

void shader_program::bind(void)
{
  glUseProgram(*_id);
}

void shader_program::unbind(void)
{
  glUseProgram(0);
}

const std::string& shader_program::get_name(void) const
{
  return _name;
}

unsigned shader_program::create_shader(shader_type type, const std::string& shader_path)
{
  unsigned shader = glCreateShader(static_cast<unsigned>(type));
  
  file_string shader_data(shader_path);
  const char* data = shader_data.c_str();

  glShaderSource(shader, 1, &data, nullptr);
  glCompileShader(shader);

  int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		GLchar * err = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, err);

    report("----------------------------\n  glsl compiler error.\n----------------------------\nfilename: '%s'\n\nerror:\n%s", 
           shader_path.c_str(), err);
		fprintf(stderr, "----------------------------\n  glsl compiler error.\n----------------------------\nfilename: '%s'\n\nerror:\n%s", 
            shader_path.c_str(), err);

		delete[] err;
    glDeleteShader(shader);
    shader = 0;
	}

	return shader;
}

bool shader_program::link_shader(void)
{
  glLinkProgram(*_id);

  int status;
  glGetProgramiv(_id, GL_LINK_STATUS, &status);

  if (status == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(*_id, GL_INFO_LOG_LENGTH, &length);

		GLchar * err = new GLchar[length + 1];
		glGetProgramInfoLog(*_id, length, NULL, err);

    report("----------------------------\n  glsl linker error.\n----------------------------\nprogram name: '%s'\n\nerror:\n%s", 
           _name.c_str(), err);
		fprintf(stderr, "----------------------------\n  glsl linker error.\n----------------------------\nprogram name: '%s'\n\nerror:\n%s", 
            _name.c_str(), err);

		delete [] err;
    glDeleteProgram(*_id);
    *_id = 0;

    return false;
	}

  return true;
}

void shader_program::create_program(const shader_path_list& shader_paths)
{
  // create program object
  unsigned program_id = glCreateProgram();
  _id = handle::create_handle(program_id, object_type::SHADER_PROGRAM);
  
  // create and attach shaders
  std::vector<unsigned> shaders(shader_paths.size());
  int i = 0;
  for (const path& shader_path : shader_paths)
  {
    shader_type type = type_from_path(shader_path);
    if (type == shader_type::INVALID)
    {
      shaders[i] = 0;
    }
    else
    {
      shaders[i] = create_shader(type, shader_path.entire_path());
      if (shaders[i] != 0)
        glAttachShader(*_id, shaders[i]);
    }

    ++i;
  }

  // link shaders
  bool linked = link_shader();

  // cleanup shaders
  for (unsigned shader : shaders)
  {
    if (shader != 0)
    {
      if (linked)
        glDetachShader(*_id, shader);
      glDeleteShader(shader);
    }
  }
}

shader_type shader_program::type_from_path(const path& shader_path)
{
  if (shader_path.extension() == "vert")
    return shader_type::VERTEX_SHADER;
  else if (shader_path.extension() == "frag")
    return shader_type::FRAGMENT_SHADER;
  else if (shader_path.extension() == "geom")
    return shader_type::GEOMETRY_SHADER;
  else
  {
    report("glsl shader error.\nshader path:\n'%s'\n\nerror:\ncan't deduce shader type.", 
           shader_path.filename().c_str());
    return shader_type::INVALID;
  }
}
