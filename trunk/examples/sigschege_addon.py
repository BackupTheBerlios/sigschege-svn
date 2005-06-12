
import commands
import posix

def show(tdiagram):
  fname = "/tmp/sigschege_tmp.png"
  tdiagram.exportPic(fname, "png")
  commands.getoutput("xv " + fname)
  posix.unlink(fname)


