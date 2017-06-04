// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef XRTL_GFX_ES3_ES3_SHADER_H_
#define XRTL_GFX_ES3_ES3_SHADER_H_

#include <string>

#include "xrtl/base/array_view.h"
#include "xrtl/base/string_view.h"
#include "xrtl/gfx/es3/es3_common.h"
#include "xrtl/gfx/es3/es3_platform_context.h"

namespace xrtl {
namespace gfx {
namespace es3 {

class ES3Shader : public RefObject<ES3Shader> {
 public:
  ES3Shader(ref_ptr<ES3PlatformContext> platform_context,
            std::string entry_point);
  ~ES3Shader();

  const std::string& entry_point() const { return entry_point_; }
  GLenum shader_type() const { return shader_type_; }
  GLuint shader_id() const { return shader_id_; }

  // Shader compilation info log containing warnings and errors that accumulated
  // during compilation.
  const std::string& info_log() const { return info_log_; }

  // Attempts to compile the given GLSL source code into a shader.
  // Returns false if the compilation fails.
  bool CompileSource(GLenum shader_type, ArrayView<const char*> sources);
  bool CompileSource(GLenum shader_type, ArrayView<std::string> sources);
  bool CompileSource(GLenum shader_type, ArrayView<StringView> sources);

  // Attempts to translate a SPIR-V binary into GLSL and compile that.
  // Returns false if the binary cannot be translated or if compilation fails.
  bool CompileSpirVBinary(const uint32_t* data, size_t data_length);

 private:
  ref_ptr<ES3PlatformContext> platform_context_;
  std::string entry_point_;
  GLenum shader_type_ = GL_VERTEX_SHADER;
  GLuint shader_id_ = 0;

  std::string info_log_;
};

}  // namespace es3
}  // namespace gfx
}  // namespace xrtl

#endif  // XRTL_GFX_ES3_ES3_SHADER_H_