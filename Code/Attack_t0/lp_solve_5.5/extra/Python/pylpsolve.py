from lpsolve55 import *
#---------------------------------------------------------------
class Fn :
   '''A callable object to encapsulate passing a function name and
   lp handle to the lp_solve driver method'''
   def __init__(self,nm,*args):
      self.nm = nm
      self.args = args

   def __call__(self, *args):
      return lpsolve(self.nm, *(self.args + args))

#---------------------------------------------------------------
class lp :
   '''Encapsulates the lp_solve handle and makes it possible to
   call functions using dot notation'''

   #======
   def __init__(self, rows = 0, cols = 0):
      '''Create a lp object.  One can pass row,col values, or
      the name of an existing lp object, or
      None.  If None is passed, the handle can be set later
      with setHandle().  The encapsulated lp is automatically
      destroyed when this object is deleted.'''
      if isinstance(rows, int) :
         self.handle = lpsolve("make_lp",rows,cols)
      elif isinstance(rows,str) :
         self.handle = str
      else :
         self.handle = None

   #======
   def setHandle(self, h ):
      '''Sets the handle, deleting any old lp if needed'''
      if self.handle is not None :
         lpsolve("delete_lp", self.handle)
      self.handle = h

   #======
   def __getattr__(self,nm) :
      '''Instantiates and returns a callable object which
      encapsulates the appropriate function call with the
      handle as the first argument'''
      return Fn(nm, self.handle)

   #======
   def __del__(self) :
      if self.handle is not None :
         lpsolve( "delete_lp", self.handle )

   #======
   def __str__(self) :
      return str(self.get_lp_name())

   #======
   def __repr__(self) :
      return str(self.get_mat()[0])

def read_lp(filename, verbose = 4, lp_name = ""):
   handle = lpsolve("read_lp", filename, verbose, lp_name)
   wrapper = lp()
   wrapper.setHandle(handle)
   return wrapper
