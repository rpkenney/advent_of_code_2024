q1 = 0
q2 = 0

def zero(input):
    if input == 'm':
        return 1
    else:
        return 0
    
def one(input):
    if input == 'u':
        return 2
    elif input == 'm':
        return 1
    else:
        return 0
    
def two(input):
    if input == 'l':
        return 3
    elif input == 'm':
        return 1
    else:
        return 0

def three(input):
    if input == '(':
        return 4
    elif input == 'm':
        return 1
    else:
        return 0
    
def four(input):
    global q1
    
    if '0' <= input <= '9':
        q1 = int(input)
        return 5
    q1 = 0    
    if input == 'm':
        return 1
    else:
        return 0

def five(input):
    global q1

    if '0' <= input <= '9':
        q1 *= 10
        q1 += int(input)
        return 5
    elif input == ',':
        return 6
    q1 = 0
    if input == 'm':
        return 1
    else:
        return 0
    
def six(input):
    global q1
    global q2

    if '0' <= input <= '9':
        q2 = int(input)
        return 7
    q1 = 0
    q2 = 0
    if input == 'm':
        return 1
    else:
        return 0
    
def seven(input):
    global q1
    global q2

    if '0' <= input <= '9':
        q2 *= 10
        q2 += int(input)
        return 7
    elif input == ')':
        return 8
    q1 = 0
    q2 = 0
    if input == 'm':
        return 1
    else:
        return 0
    
ACCEPT = 8

try:
    with open('../inputs/day3.txt', 'r') as file:
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

        content = file.read()

        startIdx = 0
        while startIdx != -1:
            endIdx = content.find("don't()", startIdx)
            if endIdx == -1:
                endIdx = len(content) - 1
            for char in content[startIdx:endIdx]:
                state = states[state](char)
                if state == ACCEPT:
                    state = 0
                    sum += q1 * q2

            state = 0

            startIdx = content.find("do()", endIdx)
            
        print(sum)

except FileNotFoundError:
    print("The file was not found.")
