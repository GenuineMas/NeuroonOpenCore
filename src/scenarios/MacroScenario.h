/**
 * @file    MacroScenario.h
 * @Author  Paweł Kaźmierzewski <p.kazmierzewski@inteliclinic.com>
 * @date    April, 2017
 * @brief   Brief description
 *
 * Description
 */

#ifndef MACROSCENARIO_H
#define MACROSCENARIO_H

#include "IMicroScenario.h"
#include "Scenario.h"
#include "ScenarioTrigger.h"

#include <algorithm>

using ScePrioPair = std::pair<IMicroScenario *, int>;
using MacroScenarioTrigger = ScenarioTrigger<const ncScenarioInput *>;

class MacroScenario : public Scenario {
public:
  MacroScenario(const ncScenarioInitArgs *) {}
  virtual ~MacroScenario() {}

  virtual ncUpdateOutput update(const ncScenarioInput *inp);

private:
  struct Chronological {
    bool operator()(const ScePrioPair &lhs, const ScePrioPair &rhs) {
      return lhs.second > rhs.second;
    }
  };


  ncUnixTimestamp _current_moment = 0;
  IMicroScenario *_recently_used_scenario = nullptr;
  std::vector<ScePrioPair> _scenario_queue;
  std::vector<std::shared_ptr<MacroScenarioTrigger>> _triggers_refresh_list = {};

  ScePrioPair
  getHighestPriorityScenario(std::vector<ScePrioPair> scenarios) const;

protected:
  virtual ncUnixTimestamp currentMoment() const { return _current_moment; }

  void
  addTriggersToRefreshList(std::vector<std::shared_ptr<MacroScenarioTrigger>> ts) {
    for (auto t : ts) {
      _triggers_refresh_list.push_back(t);
    }
  }

  void addScenarioWithPriority(IMicroScenario *sc, int priority) {
    _scenario_queue.push_back(std::make_pair(sc, priority));
    std::make_heap(_scenario_queue.begin(), _scenario_queue.end(),
                   Chronological());
  }

  IMicroScenario *lastActiveScenario() const { return _recently_used_scenario; }

  std::shared_ptr<MacroScenarioTrigger>
  moveToShared(ScenarioTrigger<const ncScenarioInput *> *t) const {
    return std::shared_ptr<ScenarioTrigger<const ncScenarioInput *>>(std::move(t));
  }
};

#endif /* !MACROSCENARIO_H */
