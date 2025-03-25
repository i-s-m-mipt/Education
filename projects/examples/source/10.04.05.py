import matplotlib.pyplot as plot

####################################################################

def make_plot(string: str, label: str):

    points = [float(coordinate) for coordinate in string.split(',')]

#   ----------------------------------------------------------------

    plot.plot(points[::2], points[1::2], label = label)

    plot.xlabel("strings")
    
    plot.ylabel("collisions")

    plot.grid()
    
    plot.legend()
    
    plot.show()