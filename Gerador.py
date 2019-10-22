class hanoi():
    def __init__(self, size):
        self.size = size
        self.state_list = []
        self.state = [0 for x in range(size)]

    def canMove(self, disk, tower):
        if self.state[0:disk].__contains__(self.state[disk]):
            return False
        if(self.state[0:disk+1].__contains__(tower)):
            return False
        return True

    def move(self, disk, tower):
        if(self.canMove(disk, tower)):
            self.state_list.append(self.state.copy())
            print(self.state)
            self.state[disk] = tower

    def printState(self):
        print(self.state)

    def findAllStates(self):
        count =  2 
        while(self.state != [2 for x in range(self.size)]):
            for x in range(3):
                self.move(count-x , x)
            

for x in range(3):
    for y in range(3):
        for z in range(3):
            for k in range(3):
                print(f'[{k+1}, {z+1}, {y+1}, {x+1}]')



