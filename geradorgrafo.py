from random import randint, uniform


print(50)

for x in range(50):
    a = randint(1,20)
    b = randint(1,20)
    cost = uniform(3,30)
    print(a, b, "{:.2f}".format(cost))