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

#version 330

const int num_lights = 8;
const vec3 c = vec3(1.0f, 0.1f, 0.0f);
const float shininess = 128.0f;

struct light_attributes
{
  bool active;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  vec3 position;
};

uniform light_attributes lights[8];

in vec3 vertex_normal;
in vec3 vertex_pos_cam;

out vec4 final_color;

void main()
{
  vec3 normal = normalize(vertex_normal);
  final_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

  for (int i = 0; i < num_lights; ++i)
  {
    // skip if inactive
    if (!lights[i].active)
      continue;

    vec3 light_vector = normalize(lights[i].position - vertex_pos_cam);
    float n_dot_l = dot(normal, light_vector);
    vec3 reflection = normalize(2 * normal * n_dot_l - light_vector);

    n_dot_l = max(n_dot_l, 0.0f);

    // ambient
    vec3 ambient = lights[i].ambient;

    // diffuse
    vec3 diffuse = lights[i].diffuse * n_dot_l;

    // specular
    float r_dot_v = 0.0f;
    if (n_dot_l > 0.0f)
      r_dot_v = max(dot(reflection, normalize(-vertex_pos_cam)), 0.0f);

    vec3 specular = lights[i].specular * pow(r_dot_v, shininess);

    float dist = length(lights[i].position - vertex_pos_cam);
    float att = min(1.0f / (c.x + c.y * dist + c.z * (dist * dist)), 1.0f);

    final_color += vec4(att * (ambient + diffuse + specular), 1.0f);
  }
}
