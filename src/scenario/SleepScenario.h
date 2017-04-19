/**
 * @file    SleepScenario.h
 * @Author  Paweł Kaźmierzewski <p.kazmierzewski@inteliclinic.com>
 * @date    April, 2017
 * @brief   Brief description
 *
 * Description
 */

#ifndef SLEEPSCENARIO_H
#define SLEEPSCENARIO_H

#include "BaseScenario.h"
#include "MacroScenario.h"

typedef enum{

}WakeUpType;


class SleepScenario: protected MacroScenario {
  public:
    SleepScenario();
    SleepScenario(const ncScenarioInitArgs *args);

    struct {
      unsigned long wakeUpDownCounter;
      WakeUpType wakeUp;
    }wakeUpParameters;

    virtual ncUpdateOutput update(const ncScenarioInput *);
};

#endif /* !SLEEPSCENARIO_H */
