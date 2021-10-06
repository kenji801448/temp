a = []

#fetch input
first_line = input().split()
n = int(first_line[0])
m = int(first_line[1])
for i in range(n):
    for element in input().split():
        a.append(int(element))

#movement
move = 0

#right, down, left, up
x = [0, 1, 0, -1]
y = [1, 0, -1, 0]

#u upward boundary
#d downward boundary
#l leftward boundary
#r rightward boundary
u = 0
d = n-1
l = 0
r = m-1

#i for row
#j for column
i = 0
j = 0

while u <= d and l <= r:
    #echo
    print(a[row*m+col], end=' ')

    #move forward
    row += x[move]
    col += y[move]

    #check if out of boundary
    if col > r or row > d or col < l or row < u:
        #shrink boundary
        if col > r:
            u += 1
        elif row > d:
            r -= 1
        elif col < l:
            d -= 1
        else:
            l += 1

        #undo
        row -= x[move]
        col -= y[move]

        #turn
        move = (move + 1) % 4

        #move forward again
        row += x[move]
        col += y[move]
