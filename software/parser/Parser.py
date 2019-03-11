import filecmp
x = filecmp.cmp('Good.txt', 'Empty.txt')
print(x)

good = open("Good.txt", "r")
good_contents = good.read()
empty = open("Empty.txt", "r")
empty_contents = empty.read()
if good_contents == empty_contents:
    print ("Success")
else:
    print ("Failure")
