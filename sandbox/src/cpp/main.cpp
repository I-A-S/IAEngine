// IAEngine: 2D ECS Game Engine.
// Copyright (C) 2026 IAS (ias@iasoft.dev)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iaengine/engine.hpp>

namespace iae
{
  auto main() -> Result<void>
  {
    return {};
  }
} // namespace iae

int main(int argc, char *argv[])
{
  au::auxid::MainThreadGuard _thread_guard;

  const auto res = iae::main();
  if (!res)
  {
    au::auxid::get_thread_logger().error("%s", res.error().c_str());
    return -1;
  }

  return 0;
}