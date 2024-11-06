import math

import matplotlib.pyplot as plot

def factorial(x: int) -> str: return str(math.factorial(x))

def make_plot(raw_points: str, label: str):

    points = [float(coordinate) for coordinate in raw_points.split(',')]

    x = points[ ::2]
    y = points[1::2]

    plot.plot(x, y, label = label)

    plot.xlabel("words")
    plot.ylabel("collisions")

    plot.grid()
    plot.legend()
    plot.show()