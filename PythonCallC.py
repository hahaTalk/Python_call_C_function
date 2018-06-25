import CfuncToPy
import time
import numpy as np

CfuncToPy.Hello()

pylist=[1,2,3]
print "Python : " ,pylist , type(pylist)
clist=CfuncToPy.ShowList(pylist)
print "C return : " ,clist , type(clist)

pystr="abcdefg"
print "Python : " ,pystr , type(pystr)
cstr=CfuncToPy.ShowStr(pystr)
print "C return : " ,cstr,type(cstr)

pynp = np.array([[1.1, 2.2, 3.3],[4.4, 5.5, 6.6]])
print "Python : " ,pynp , type(pynp)
CfuncToPy.ShowNumpy(pynp)
print "C return : " ,pynp,type(pynp)

pyflt1 = 2.4
pyflt2 = 1.2
print "Python : %.2f %.2f" %(pyflt1 , pyflt2),type(pyflt1) 
cf1,cf2,cf3,cf4 = CfuncToPy.Operation(pyflt1,pyflt2)
print "C return : %.2f %.2f %.2f %.2f" %(cf1,cf2,cf3,cf4),type(cf1)

