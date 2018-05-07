#include "timestamp.hpp"
#include <QTime>

QString timestamp() { return QTime::currentTime().toString(Qt::ISODate); }
