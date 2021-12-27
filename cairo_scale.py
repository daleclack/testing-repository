#!/usr/bin/python3

import cairo
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


def draw(da, ctx):
    global surface
    
    ctx.scale(scale, scale)
    ctx.set_source_surface(surface)
    ctx.get_source().set_filter(cairo.FILTER_NEAREST)
    ctx.paint()
    
    da.set_size_request(surface.get_width() * scale, surface.get_height() * scale)
    
def clicked(btn):
    global scale
    scale *= 1.5
    da = btn.get_parent().get_children()[1].get_child().get_child()
    da.queue_draw()


def main():
    global scale
    scale = 1
    
    global surface
    surface = cairo.ImageSurface.create_from_png("../Xe-Project/Gift.png")
    
    win = Gtk.Window()
    win.connect('destroy', lambda w: Gtk.main_quit())
    win.set_default_size(500, 500)
    
    box = Gtk.Box()
    win.add(box)
    
    btn = Gtk.Button()
    btn.set_label("Scale")
    box.add(btn)
    btn.connect('clicked', clicked)
    
    scrolled_win = Gtk.ScrolledWindow()
    box.add(scrolled_win)

    drawingarea = Gtk.DrawingArea()
    drawingarea.set_vexpand(True)
    drawingarea.set_hexpand(True)
    scrolled_win.add(drawingarea)
    drawingarea.connect('draw', draw)
    

    win.show_all()
    Gtk.main()


if __name__ == '__main__':
    main()