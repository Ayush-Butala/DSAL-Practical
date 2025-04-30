def create_table(size):
    return [[0, ""] for _ in range(size)]  # [name, phone]

# -------- Linear Probing --------
def insert_linear(table):
    name = input("Enter name: ")
    phone = int(input("Enter phone: "))
    index = phone % len(table)

    for i in range(len(table)):
        h = (index + i) % len(table)
        if table[h][0] == 0:
            table[h] = [name, phone]
            print(f"Inserted at {h}")
            return
    print("Table Full (Linear)")

def search_linear(table):
    phone = int(input("Enter phone to search: "))
    index = phone % len(table)

    for i in range(len(table)):
        h = (index + i) % len(table)
        if table[h][1] == phone:
            print(f"Found at {h}: {table[h][0]}, {table[h][1]}")
            return
        if table[h][0] == 0:
            break
    print("Not found (Linear)")

# -------- Double Hashing --------
def insert_double(table):
    name = input("Enter name: ")
    phone = int(input("Enter phone: "))
    h1 = phone % len(table)
    h2 = 7 - (phone % 7)

    for i in range(len(table)):
        h = (h1 + i * h2) % len(table)
        if table[h][0] == 0:
            table[h] = [name, phone]
            print(f"Inserted at {h}")
            return
    print("Table Full (Double Hashing)")

def search_double(table):
    phone = int(input("Enter phone to search: "))
    h1 = phone % len(table)
    h2 = 7 - (phone % 7)

    for i in range(len(table)):
        h = (h1 + i * h2) % len(table)
        if table[h][1] == phone:
            print(f"Found at {h}: {table[h][0]}, {table[h][1]}")
            return
        if table[h][0] == 0:
            break
    print("Not found (Double Hashing)")

# -------- Display --------
def display(table):
    print("\nHash Table:")
    for i, (name, phone) in enumerate(table):
        print(f"{i}: Name={name}, Phone={phone}")

# -------- Main Menu --------
def main():
    size = int(input("Enter table size: "))
    table = create_table(size)

    while True:
        print("\n1. Insert (Linear)\n2. Insert (Double)\n3. Search (Linear)\n4. Search (Double)\n5. Display\n6. Exit")
        ch = int(input("Enter choice: "))
        if ch == 1:
            insert_linear(table)
        elif ch == 2:
            insert_double(table)
        elif ch == 3:
            search_linear(table)
        elif ch == 4:
            search_double(table)
        elif ch == 5:
            display(table)
        elif ch == 6:
            break
        else:
            print("Invalid choice")

main()
