def create_set():
    return []

def add(s, value):
    if value not in s:
        s.append(value)

def remove(s, value):
    if value in s:
        s.remove(value)

def contains(s, value):
    return value in s

def length(s):
    count = 0
    for _ in s:
        count += 1
    return count

def size(s):
    return length(s)

def iterator(s):
    i = 0
    result = []
    while i < length(s): 
        result.append(s[i])
        i += 1
    return result

def union(set1, set2):
    result = set1[:]
    for item in set2:
        if item not in result:
            result.append(item)
    return result

def intersection(set1, set2):
    result = []
    for item in set1:
        if item in set2:
            result.append(item)
    return result

def difference(set1, set2):
    result = []
    for item in set1:
        if item not in set2:
            result.append(item)
    return result

def is_subset(set1, set2):
    for item in set1:
        if item not in set2:
            return False
    return True

def display_menu():
    print("\nMenu:")
    print("1. Add element to set")
    print("2. Remove element from set")
    print("3. Check if element is in set")
    print("4. Size of set")
    print("5. Union of two sets")
    print("6. Intersection of two sets")
    print("7. Difference of two sets")
    print("8. Check if set is subset of another set")
    print("9. Display set")
    print("10. Exit")

def menu_driven():
    s1 = create_set()
    s2 = create_set()

    while True:
        display_menu()
        choice = input("Enter your choice (1-10): ")

        if choice == '1':  
            set_choice = input("Choose set (1 for s1, 2 for s2): ")
            value = int(input("Enter value to add: "))
            if set_choice == '1':
                add(s1, value)
            elif set_choice == '2':
                add(s2, value)
            else:
                print("Invalid set choice!")
        
        elif choice == '2': 
            set_choice = input("Choose set (1 for s1, 2 for s2): ")
            value = int(input("Enter value to remove: "))
            if set_choice == '1':
                remove(s1, value)
            elif set_choice == '2':
                remove(s2, value)
            else:
                print("Invalid set choice!")
        
        elif choice == '3':  
            set_choice = input("Choose set (1 for s1, 2 for s2): ")
            value = int(input("Enter value to check: "))
            if set_choice == '1':
                print("Contains:", contains(s1, value))
            elif set_choice == '2':
                print("Contains:", contains(s2, value))
            else:
                print("Invalid set choice!")
        
        elif choice == '4':  
            set_choice = input("Choose set (1 for s1, 2 for s2): ")
            if set_choice == '1':
                print("Size of s1:", size(s1))
            elif set_choice == '2':
                print("Size of s2:", size(s2))
            else:
                print("Invalid set choice!")
        
        elif choice == '5':  
            print("Union of s1 and s2:", union(s1, s2))
        
        elif choice == '6':  
            print("Intersection of s1 and s2:", intersection(s1, s2))
        
        elif choice == '7':  
            print("Difference (s1 - s2):", difference(s1, s2))
        
        elif choice == '8':  
            print("Is s1 a subset of s2?", is_subset(s1, s2))
        
        elif choice == '9':  
            print("s1:", s1)
            print("s2:", s2)
        
        elif choice == '10': 
            print("Exiting program.")
            break
        
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    menu_driven()