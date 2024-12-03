q1 = 0
q2 = 0

def zero(input):
    if input == b'm':
        return 1
    else:
        return 0
    
def one(input):
    if input == b'u':
        return 2
    elif input == b'm':
        return 1
    else:
        return 0
    
def two(input):
    if input == b'l':
        return 3
    elif input == b'm':
        return 1
    else:
        return 0

def three(input):
    if input == b'(':
        return 4
    elif input == b'm':
        return 1
    else:
        return 0
    
def four(input):
    global q1
    
    if b'0' <= byte <= b'9':
        q1 = int(byte.decode('utf-8'))
        return 5
    q1 = 0    
    if input == b'm':
        return 1
    else:
        return 0

def five(input):
    global q1

    if b'0' <= byte <= b'9':
        q1 *= 10
        q1 += int(byte.decode('utf-8'))
        return 5
    elif input == b',':
        return 6
    q1 = 0
    if input == b'm':
        return 1
    else:
        return 0
    
def six(input):
    global q1
    global q2

    if b'0' <= byte <= b'9':
        q2 = int(byte.decode('utf-8'))
        return 7
    q1 = 0
    q2 = 0
    if input == b'm':
        return 1
    else:
        return 0
    
def seven(input):
    global q1
    global q2

    if b'0' <= byte <= b'9':
        q2 *= 10
        q2 += int(byte.decode('utf-8'))
        return 7
    elif input == b')':
        return 8
    q1 = 0
    q2 = 0
    if input == b'm':
        return 1
    else:
        return 0
    
ACCEPT = 8

try:
    with open('../inputs/day3.txt', 'rb') as file:
        sum = 0

        states = {
            0: zero,
            1: one,
            2: two,
            3: three,
            4: four,
            5: five,
            6: six,
            7: seven
        }

        state = 0
        while byte := file.read(1):
            state = states[state](byte)
            if state == ACCEPT:
                state = 0
                sum += q1 * q2

        print(sum)
            

except FileNotFoundError:
    print("The file was not found.")
