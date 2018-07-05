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

#ifndef CINIT_CHILDPROCESS_H
#define CINIT_CHILDPROCESS_H

#include <string>
#include <list>
#include <map>
#include "gtest/gtest_prod.h"
#include "ProcessHandlerInterface.h"
#include "ChildProcessInterface.h"

namespace scinit {
    class ProcessLifecycleTests;

    // See base class for documentation
    class ChildProcess : public ChildProcessInterface {
    public:
        ChildProcess(const std::string&, const std::string &, const std::list<std::string> &, const std::string &,
                     const std::list<std::string> &, unsigned int, unsigned int, unsigned int,
                     std::shared_ptr<ProcessHandlerInterface>, const std::list<std::string> &,
                     const std::list<std::string> &);

        ChildProcess(const ChildProcess&) = delete;
        virtual ChildProcess& operator=(const ChildProcess&) = delete;

        void do_fork(std::map<int, int>&) noexcept(false) override;
        void register_with_epoll(int, std::map<int, int>&) noexcept(false) override;
        std::string get_name() const noexcept override;
        unsigned int get_id() const noexcept override;
        bool can_start_now() const noexcept override;
        void notify_of_state(std::map<unsigned int, std::weak_ptr<ChildProcessInterface>>) noexcept override;
        void propagate_dependencies(std::list<std::weak_ptr<ChildProcessInterface>>) noexcept override;
        void should_wait_for(int, ProcessState) noexcept override;
        void handle_process_event(ProcessHandlerInterface::ProcessEvent event, int data) noexcept override;
        ProcessState get_state() const noexcept override ;

    private:
        std::string path, name;
        std::list<std::string> args, capabilities, before, after;
        std::list<std::pair<unsigned int, ChildProcessInterface::ProcessState>> conditions;
        unsigned int uid, gid, graph_id;
        int stdouterr[2], primaryPid;
        ProcessType type;
        ProcessState state;
        std::shared_ptr<ProcessHandlerInterface> handler;

        void handle_caps();

        FRIEND_TEST(ConfigParserTests, SmokeTestConfig);
        FRIEND_TEST(ConfigParserTests, SimpleConfDTest);
        FRIEND_TEST(ConfigParserTests, ConfigWithDeps);
        FRIEND_TEST(ProcessLifecycleTests, SingleProcessLifecycle);
        FRIEND_TEST(ProcessLifecycleTests, TwoDependantProcessesLifecycle);
        friend class ProcessLifecycleTests;
    };
}

#endif //CINIT_CHILDPROCESS_H
