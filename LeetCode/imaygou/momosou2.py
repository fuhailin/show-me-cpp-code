def transform(test):
    res = dict()
    for key in test:
        if '.' not in key:
            res[key] = test[key]
        else:
            keys = key.split('.')
            tmp = res
            for i in range(len(keys)-1):
                try:
                    tmp[keys[i]]
                except:
                    tmp[keys[i]] = dict()
                tmp = tmp[keys[i]]
            tmp[keys[-1]] = test[key]
    return res


test1 = {'A': 1, 'B.A': 2, 'B.B': 3, 'CC.D.E': 4, 'CC.D.F': 5}
test2 = transform(test1)
print(test2)
