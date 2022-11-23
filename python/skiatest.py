#!/usr/bin/python3

import skia

surface = skia.Surface(100, 100)
with surface as canvas:
    canvas.clear(skia.ColorYELLOW)
    canvas.drawCircle((50,50), 25, skia.Paint(Color=skia.ColorGREEN))
image = surface.makeImageSnapshot()
image.save('/mnt/mobihome/temp/skia.png', skia.kPNG)