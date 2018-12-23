item_file = open("item.txt")
status_number = int(item_file.readline())
item_list = []
for i in range(status_number):
    status_order, item_number = (int(x) for x in item_file.readline().strip().split(' '))
    item_dict = dict()
    for j in range(item_number):
        production = item_file.readline().strip()
        item_dict[production] = item_file.readline().strip()
    item_file.readline()
    item_list.append(item_dict)
print(item_list)