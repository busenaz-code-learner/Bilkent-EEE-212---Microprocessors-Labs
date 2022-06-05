# Prepared by TAs: Ali Necat Karakuloglu and Arda Asci
#from typing import Final, List
from typing import List
# fmt: off
# alphabet: Final = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
# alphabet_size: Final = len(alphabet)
# ASCII_POSITION: Final[int] = 65
alphabet = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
alphabet_size = len(alphabet)
ASCII_POSITION = 65

# fmt: on​
# GENERAL
def text_to_int(text: str) -> List[int]:
    return [ord(char) - ASCII_POSITION for char in text]

def int_to_text(encoded_text: List[int]) -> str:
    return "".join([chr(i + ASCII_POSITION) for i in encoded_text])

# CONSTANT
def constant_shift(text: str, shift: int) -> str:
    text_as_int_list = text_to_int(text)
    encoded_text_as_int_list = [
        (charint + shift) % alphabet_size for charint in text_as_int_list
    ]
    encoded_text = int_to_text(encoded_text_as_int_list)
    return encoded_text

# PROGRESSIVE
def progressive_shift(text: str, initial_shift: int) -> str:
    text_as_int_list = text_to_int(text)
    encoded_text = ""
    for idx, charint in enumerate(text_as_int_list):
        new_charint = (charint + initial_shift + idx) % alphabet_size
        encoded_text += chr(new_charint + ASCII_POSITION)
    return encoded_text

# REGRESSIVE
def regressive_shift(text: str, initial_shift: int) -> str:
    text_as_int_list = text_to_int(text)
    encoded_text = ""
    for idx, charint in enumerate(text_as_int_list):
        new_charint = (charint + initial_shift - idx) % alphabet_size
        encoded_text += chr(new_charint + ASCII_POSITION)
    return encoded_text

# PIVOT
def generate_pivot_alphabet(pivot: int) -> List[str]:
    alphabet_size = len(alphabet)
    new_alphabet = alphabet_size * [""]
    
    for idx, letter in enumerate(alphabet):
        diff = pivot - idx
        new_letter_idx = (pivot + diff) % alphabet_size
        new_alphabet[idx] = alphabet[new_letter_idx]
    return new_alphabet

def pivot_cipher(text: str, pivot: int) -> str:
    new_alphabet = generate_pivot_alphabet(pivot)
    cipher = ""
    for letter in text:
        letter_idx = alphabet.index(letter)
        cipher += new_alphabet[letter_idx]
    return cipher


def constant_shift_decode(text: str, char_idx: int, char: str) -> str:
    text_as_int_list = text_to_int(text)
    encoded_char = text_as_int_list[char_idx]
    for shift_guess in range(alphabet_size):
        guess_chr_int = (shift_guess + encoded_char)%alphabet_size
        guess = chr(guess_chr_int + ASCII_POSITION)
        if char == guess:
            break
    
    return constant_shift(text, shift_guess)



def progressive_shift_decode(text: str, char_idx: int, char: str) -> str:
    text_as_int_list = text_to_int(text)
    encoded_char = text_as_int_list[char_idx]
    for shift_guess in range(alphabet_size):
        guess_chr_int = (shift_guess + encoded_char)%alphabet_size
        guess = chr(guess_chr_int + ASCII_POSITION)
        if char == guess:
            break
        
    return regressive_shift(text, shift_guess+char_idx)



def regressive_shift_decode(text: str, char_idx: int, char: str) -> str:
    text_as_int_list = text_to_int(text)
    encoded_char = text_as_int_list[char_idx]
    for shift_guess in range(alphabet_size):
        guess_chr_int = (shift_guess + encoded_char)%alphabet_size
        guess = chr(guess_chr_int + ASCII_POSITION)
        if char == guess:
            break
        
    return progressive_shift(text, shift_guess-char_idx)


def pivot_decipher(text: str, char_idx: int, char: str) -> str:
    text_as_int_list = text_to_int(text)
    encoded_char = text_as_int_list[char_idx]
    char_int = ord(char)-ASCII_POSITION
    
    pivot_guess = char_int + encoded_char - alphabet_size
    pivot_guess = pivot_guess>>1
    pivot_guess = pivot_guess%alphabet_size
    
    return pivot_cipher(text, pivot_guess)
    


if __name__ == "__main__":
    print("CIPHER")
    print(f"{constant_shift('TESKT', 6)}")
    print(f"{progressive_shift('TEKST', 5)}")
    print(f"{regressive_shift('KTEST', 10)}")
    print(f"{pivot_cipher('CRYPTOLOGY', 15)}")
    
    
    print("DECIPHER")
    print(f"{constant_shift_decode('ZKYQZ', 3, 'K')}")
    print(f"{progressive_shift_decode('YKRAC', 2, 'K')}")
    print(f"{regressive_shift_decode('UCMZZ', 0, 'K')}")
    #teschart, k is the 3rd index
    print(f"{pivot_decipher('LAMLU', 4, 'K')}")
