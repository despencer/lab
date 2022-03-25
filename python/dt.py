#!/usr/bin/python3
import time
from datetime import datetime, timedelta, timezone

dt = datetime.strptime('20180508','%Y%m%d')
dt0 = datetime.strptime('20180507','%Y%m%d')
print(dt)
dt = datetime(dt.year, dt.month, dt.day, tzinfo=timezone.utc)
dt0 = datetime(dt0.year, dt0.month, dt0.day, tzinfo=timezone.utc)
print(dt)

td = timedelta(43228.2476968)
print(td)

dt2 = datetime(1899, 12, 30, tzinfo=timezone.utc) + td
print(dt2)
td2 = dt2-dt
print("{0} {1} {2} {3}".format(td2, td2.days, td2.seconds, td2.total_seconds()))
td20 = dt2-dt0
print("{0} {1} {2} {3}".format(td20, td20.days, td20.seconds, td20.total_seconds()))