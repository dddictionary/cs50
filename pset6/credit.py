from cs50 import get_int
import math

def main():
    card_num = get_num()
    length = getlength(card_num)
    print_type(card_num, length)

def get_num():
    while True:
        input = get_int("Number: ")
        if input > 0:
            break
    return input

#fast way of getting a length of an int taken from: https://stackoverflow.com/a/28883802/15339613
def getlength(card_num):
    if card_num <= 999999999999997:
        return int(math.log10(card_num)) + 1
    else:
        counter = 15
        while card_num >= 10**counter:
            counter += 1
        return counter

def print_type(card_num, length):
    string_num = str(card_num)
    if valid(card_num,length) == False:
        print("INVALID")
    elif valid(card_num, length) == True:
        if length == 15 and int(string_num[0:2]) in [34, 37]:
            print("AMEX")
        elif length == 16 and int(string_num[0:2]) in [51, 52, 53, 54, 55]:
            print("MASTERCARD")
        elif length in [13,16] and string_num[0] == '4':
            print("VISA")
    else: 
        print("INVALID")
        
def valid(card_num, length):
    totalsum = 0
    sum1 = 0
    sum2 = 0
    
    for i in range(0, length, 2):
        second_to_last = card_num // (10**(i+1))
        second_to_last %= 10
        last = card_num // (10**i)
        last %= 10

        if (second_to_last * 2 > 9):
            firstNum = (second_to_last * 2) // 10
            secondNum = (second_to_last * 2) % 10
            sum1 = sum1 + firstNum + secondNum - (second_to_last * 2)
        
        sum1 = sum1 + (second_to_last * 2)
        sum2  = sum2 + last

    totalsum = sum1 + sum2
    if totalsum % 10 == 0:
        return True
    else:
        return False
    

if __name__ == "__main__":
    main()