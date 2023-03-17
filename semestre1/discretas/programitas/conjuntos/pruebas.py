# import _Ctypes

# import time


# def powerset(seq):
#     '''Returns all the subsets of the list. This is a generator.'''
#     if len(seq) == 0:
#         yield seq
#     if len(seq) == 1:
#         yield seq
#         yield []
#     elif len(seq) > 1:
#         for item in powerset(seq[1:]):
#             yield [seq[0]]+item
#             yield item


# Universo = [-10, -9, -8, -7, -6, -5, -4, -
#             3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# my_powerset = []

# start_time = time.time()
# for element in powerset(Universo):
#     my_powerset.append(element)

# finish_time = time.time()

# print(my_powerset)

# print("--- %s seconds ---" % (finish_time - start_time))

miconjunyo = {1, 2, 4}
conjunto2 = {2, 5, 4}

print(miconjunyo.union(conjunto2))
