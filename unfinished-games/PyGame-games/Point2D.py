
class Point(object):
    def __init__(self, x, y):
            self.x = x
            self.y = y
    def __str__(self, key):
            return "(%s,%s)"%(self.X, self.Y)
    def move(self, dx, dy):
        self.X = self.X + dx
        self.Y = self.Y + dy
    def __iter__(self):
        yield self.x
        yield self.y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)
    def __radd__(self, other):
        return Point(self.x + other.x, self.y + other.y)