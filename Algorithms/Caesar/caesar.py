def getChar(alphabet, char, shift):
    index = alphabet.index(char)
    size = len(alphabet)
    
    if index + shift >= size:
        shift -= (size - index)
        index = 0
        
    return alphabet[index + shift]
    


def caesar(string, shift):
    if shift not in range(1, 26, 1):
        return "Incorrect range"

    ALPHABET = [chr(char) for char in range(ord('A'), ord('Z') + 1)]
    alphabet = [chr(char) for char in range(ord('a'), ord('z') + 1)]

    returnValue = ""
    for char in string:
        if char.isnumeric() or char.isspace():
            returnValue += char
        else:
            returnValue += getChar((ALPHABET if char.isupper() else alphabet), char, shift)
        
    return returnValue
    
    
print("Task from PCAP certification")
print(caesar("The die is cast", 25))