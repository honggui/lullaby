/*
Copyright 2017-2019 Google Inc. All Rights Reserved.

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

#ifndef LULLABY_CONTRIB_MUTATOR_STAY_IN_BOX_MUTATOR_SYSTEM_H_
#define LULLABY_CONTRIB_MUTATOR_STAY_IN_BOX_MUTATOR_SYSTEM_H_

#include "lullaby/contrib/mutator/mutator_system.h"
#include "lullaby/generated/stay_in_box_mutator_def_generated.h"

namespace lull {

class StayInBoxMutatorSystem : public System,
                               MutatorSystem::SqtMutatorInterface {
 public:
  explicit StayInBoxMutatorSystem(Registry* registry);
  ~StayInBoxMutatorSystem() override = default;
  void Create(Entity entity, HashValue type, const Def* def) override;

  /// See MutateSystem::SqtMutatorInterface
  void Mutate(Entity entity, HashValue group, int order, Sqt* mutate,
              bool require_valid) override;

 private:
  /// Stay within the bounds of a box.
  struct Mutator {
    MutateSpace space = MutateSpace_Parent;
    Aabb box;
    Aabb stretch;
    // NOTE: order and group are both used to identify a specific mutator on an
    // entity.
    HashValue group = 0;
    int order = 0;
  };

  std::unordered_multimap<Entity, Mutator> mutators_;
};

}  // namespace lull

LULLABY_SETUP_TYPEID(lull::StayInBoxMutatorSystem);

#endif  // LULLABY_CONTRIB_MUTATOR_STAY_IN_BOX_MUTATOR_SYSTEM_H_
