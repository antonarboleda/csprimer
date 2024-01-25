# # Initial benchmarks
# Data loading: 2.447s
# Computation 1.149s

# # After my initial changes
# Data loading: 2.242s
# Computation 0.757s

# # After watching the solution
# Data loading: 0.659s
# Computation 0.030s

import csv
import math
import time

class User(object):
    def __init__(self, age, payments):
        self.age = age
        self.payments = payments


def average_age(ages):
    return sum(ages) / len(ages)


def average_payment_amount(payments):
    return sum(payments) / len(payments)


def stddev_payment_amount(payments, avg_payment_amount):
    squared_diffs = 0
    for amount in payments:
        diff = amount - avg_payment_amount
        squared_diffs += diff * diff
    return math.sqrt(squared_diffs / len(payments))


def load_data():
    ages, payments = [], []
    with open('users.csv') as f:
        for line in csv.reader(f):
            _, _, age, _, _ = line
            ages.append(int(age))
    with open('payments.csv') as f:
        for line in csv.reader(f):
            amount, _, _ = line
            dollars = float(int(amount)) // 100
            cents = float(amount) % 100
            payments.append(dollars + cents / 100)
    return payments, ages


if __name__ == '__main__':
    t = time.perf_counter()
    payments, ages = load_data()
    print(f'Data loading: {time.perf_counter() - t:.3f}s')
    t = time.perf_counter()
    avg_payment_amount = average_payment_amount(payments)
    assert abs(average_age(ages) - 59.626) < 0.01
    assert abs(stddev_payment_amount(payments, avg_payment_amount) - 288684.849) < 0.01
    assert abs(avg_payment_amount - 499850.559) < 0.01
    print(f'Computation {time.perf_counter() - t:.3f}s')