# Script de alto consumo de CPU
import time
import math

while True:
    for _ in range(1000000):
        list = [math.sqrt(i) for i in range(1000)]
    time.sleep(0.1)
