/*
 * Copyright 2018 The scinit authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CINIT_CONFIGINTERFACE_H
#define CINIT_CONFIGINTERFACE_H

#include <list>
#include <memory>

namespace scinit {
    class ChildProcessInterface;

    class ConfigInterface {
      public:
        ConfigInterface() = default;
        virtual ~ConfigInterface() = default;

        // No copy
        ConfigInterface(const ConfigInterface&) = delete;
        virtual ConfigInterface& operator=(const ConfigInterface&) = delete;

        // Get a list of _all_ processes
        virtual std::list<std::weak_ptr<ChildProcessInterface>> get_processes() const noexcept = 0;
    };
}  // namespace scinit

#endif  // CINIT_CONFIGINTERFACE_H
