#_*_ coding:utf-8_*_
import numpy as np
import matplotlib.pyplot as pyplot

altitude_list = []
time = []

f = open("gbg4.txt", "r")

line_list = f.readlines()
f.close()

line_list = line_list[1:]

for line in line_list:
   words = line.split(",")
   time.append(float(words[0])/1000)
   altitude_list.append(float(words[3]))
  

pyplot.title("Tid och altitud")
pyplot.xlabel("Tid [s]")
pyplot.ylabel(u"Altitud [m.ö.h]")
pyplot.plot(time, altitude_list)
pyplot.show()


