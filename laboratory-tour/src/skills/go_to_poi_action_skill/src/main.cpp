#include <QCoreApplication>
#include <QScxmlStateMachine>
#include <QDebug>


#include <iostream>
#include "GoToPoiActionSkill.h"

#include <thread>
#include <chrono>



int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  GoToPoiActionSkill stateMachine("GoToPoiAction");
  stateMachine.start(argc, argv);

  int ret=app.exec();
  
  return ret;
  
}

