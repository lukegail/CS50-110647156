# This program simulates a cookie jar that can hold a certain capacity of cookies.
# Users can deposit and withdraw cookies.
# https://cs50.harvard.edu/x/2023/problems/6/jar/

# Define the Jar class
class Jar:
    # __init__ is the constructor method in Python. It gets called when a new object is created.
    # Initialize the Jar object with default capacity of 12
    def __init__(self, capacity=12):
        self._capacity = capacity  # Single underscores indicate "protected" variables.
        self._size = 0

    # __str__ returns a string representation of the object for display purposes
    def __str__(self):
        return "🍪" * self.size  # self.size calls the @property getter for size

    # Deposit cookies into the jar
    def deposit(self, n):
        if self._size + n > self._capacity:
            raise ValueError("Cookie jar overflow")  # ValueError is raised when a function receives an inappropriate argument
        self._size += n

    # Withdraw cookies from the jar
    def withdraw(self, n):
        if self._size - n < 0:
            raise ValueError("Not enough 🍪")  # ValueError again for bad argument
        self._size -= n

    # Getter for capacity using @property decorator. Allows us to use jar.capacity to get the value.
    @property
    def capacity(self):
        return self._capacity

    # Setter for capacity. Allows us to use jar.capacity = x to set the value.
    @capacity.setter
    def capacity(self, value):
        if value < 0:
            raise ValueError("Negative Capacity")
        self._capacity = value

    # Getter for size. Allows us to use jar.size to get the value.
    @property
    def size(self):
        return self._size


# Main function to interact with the Jar class
def main():
    jar = Jar()  # Create a new jar object. Calls __init__.

    # Set the jar capacity
    while True:
        try:  # try/except is used to catch and handle exceptions
            new_capacity = int(input("How many 🍪 can your jar hold? "))
            if new_capacity >= 0:
                jar.capacity = new_capacity  # Using the @property setter for capacity
                break
        except ValueError:  # Handle invalid input that can't be converted to int
            pass  # Do nothing and continue

    # Display the jar's capacity
    # print(f"Capacity of cookie jar: {jar.capacity}")  # Using the @property getter for capacity

    # Loop to deposit and withdraw cookies
    while True:
        print("Current 🍪 in jar:", jar, f"({jar.size})")  # jar automatically uses __str__
        print()

        # Deposit cookies
        while True:
            try:
                num_to_deposit = int(input(f"Deposit how many 🍪? (up to {jar.capacity - jar.size}) "))
                if num_to_deposit >= 0 and num_to_deposit <= jar.capacity - jar.size:
                    break
            except ValueError:
                pass
        jar.deposit(num_to_deposit)

        # Withdraw cookies
        while True:
            try:
                num_to_withdraw = int(input(f"Eat how many 🍪? (up to {jar.size}) "))
                if num_to_withdraw >= 0 and num_to_withdraw <= jar.size:
                    break
            except ValueError:
                pass
        jar.withdraw(num_to_withdraw)


# Run the program
if __name__ == "__main__":  # Only run main() when this script is executed directly (not imported as a module)
    main()