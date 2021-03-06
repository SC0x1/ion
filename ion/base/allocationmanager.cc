/**
Copyright 2016 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include "ion/base/allocationmanager.h"

#include <cstdlib>  // For malloc() and free()

#include "ion/base/staticsafedeclare.h"

namespace ion {
namespace base {

//-----------------------------------------------------------------------------
//
// AllocationManager::MallocAllocator class definition.
//
//-----------------------------------------------------------------------------

class AllocationManager::MallocAllocator : public Allocator {
 public:
  void* Allocate(size_t size) override { return malloc(size); }
  void Deallocate(void* p) override { free(p); }
};

//-----------------------------------------------------------------------------
//
// AllocationManager class functions.
//
//-----------------------------------------------------------------------------

AllocationManager::AllocationManager()
    : default_allocation_lifetime_(kMediumTerm),
      malloc_allocator_(new MallocAllocator) {
  // Install the MallocAllocator by default for all lifetimes.
  default_allocators_[kShortTerm] =
      default_allocators_[kMediumTerm] =
      default_allocators_[kLongTerm] = malloc_allocator_;
}

AllocationManager::~AllocationManager() {
}

AllocationManager* AllocationManager::GetInstance() {
  ION_DECLARE_SAFE_STATIC_POINTER(AllocationManager, manager);
  return manager;
}

}  // namespace base
}  // namespace ion
