# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_Utils', [dirname(__file__)])
        except ImportError:
            import _Utils
            return _Utils
        if fp is not None:
            try:
                _mod = imp.load_module('_Utils', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _Utils = swig_import_helper()
    del swig_import_helper
else:
    import _Utils
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0



def basename(*args):
  return _Utils.basename(*args)
basename = _Utils.basename

def fileExists(*args):
  return _Utils.fileExists(*args)
fileExists = _Utils.fileExists

def pathExists(*args):
  return _Utils.pathExists(*args)
pathExists = _Utils.pathExists

def createPath(*args):
  return _Utils.createPath(*args)
createPath = _Utils.createPath

def removeExtension(*args):
  return _Utils.removeExtension(*args)
removeExtension = _Utils.removeExtension

def bytesToStreambuf(*args):
  return _Utils.bytesToStreambuf(*args)
bytesToStreambuf = _Utils.bytesToStreambuf

def stringToStreambuf(*args):
  return _Utils.stringToStreambuf(*args)
stringToStreambuf = _Utils.stringToStreambuf

def file2ostream(*args):
  return _Utils.file2ostream(*args)
file2ostream = _Utils.file2ostream

def file2istream(*args):
  return _Utils.file2istream(*args)
file2istream = _Utils.file2istream
class StopWatch(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StopWatch, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StopWatch, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _Utils.new_StopWatch(*args)
        try: self.this.append(this)
        except: self.this = this
    def restart(self): return _Utils.StopWatch_restart(self)
    def reset(self): return _Utils.StopWatch_reset(self)
    def isActive(self): return _Utils.StopWatch_isActive(self)
    def elapsed(self): return _Utils.StopWatch_elapsed(self)
    __swig_destroy__ = _Utils.delete_StopWatch
    __del__ = lambda self : None;
StopWatch_swigregister = _Utils.StopWatch_swigregister
StopWatch_swigregister(StopWatch)

class Timer(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Timer, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Timer, name)
    __repr__ = _swig_repr
    def __init__(self, timeoutseconds=0): 
        this = _Utils.new_Timer(timeoutseconds)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Utils.delete_Timer
    __del__ = lambda self : None;
    def setTimeout(self, *args): return _Utils.Timer_setTimeout(self, *args)
    def setCallback(self, *args): return _Utils.Timer_setCallback(self, *args)
    def setSingleShot(self, *args): return _Utils.Timer_setSingleShot(self, *args)
    def start(self): return _Utils.Timer_start(self)
    def stop(self): return _Utils.Timer_stop(self)
    def disable(self): return _Utils.Timer_disable(self)
    def isActive(self): return _Utils.Timer_isActive(self)
Timer_swigregister = _Utils.Timer_swigregister
Timer_swigregister(Timer)

# This file is compatible with both classic and new-style classes.


