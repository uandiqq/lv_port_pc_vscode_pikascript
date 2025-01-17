import pika_lvgl as lv
import PikaStdLib
mem = PikaStdLib.MemChecker()

class ArcLoader():
    def __init__(self):
        self.a = 270

    def arc_loader_cb(self,tim,arc):
        # print(tim,arc)
        self.a += 5

        arc.set_end_angle(self.a)

        if self.a >= 270 + 360:
            tim._del()
            mem.max()

#
# Create an arc which acts as a loader.
#

# Create an Arc
arc = lv.arc(lv.scr_act())
arc.set_bg_angles(0, 360)
arc.set_angles(270, 270)
arc.center()

# create the loader
arc_loader = ArcLoader()

# Create an `lv_timer` to update the arc.

timer = lv.timer_create_basic()
timer.set_period(20)

def cb(src):
    arc_loader.arc_loader_cb(src,arc)

timer.set_cb(cb)
