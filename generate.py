import random
alph = 'abcdefg, .hijkl,mn,opqrstuvwxyz ,.'
s = ""
n = 10
random.seed(10)
while n != 1_000_000:
    n *= 10
    with open (f'{n}_2.txt', 'w') as f:
        i = 0
        while i < n:
            c = alph[random.randint(0, len(alph) - 1)]
            s += c
            if c == ',':
                s += ' '
                i += 1
            i += 1
            
        print(s, file=f)
        s = ""
        print(n)