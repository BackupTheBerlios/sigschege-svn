
# $Id: $

import commands
import posix

def show(tdiagram):
  fname = "/tmp/sigschege_tmp.png"
  tdiagram.exportPic(fname, "png")
  commands.getoutput("display " + fname)
  posix.unlink(fname)


