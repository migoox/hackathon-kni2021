import datetime

def calcTime(func):
    def wrapper(*args,**kwargs):
        start = datetime.datetime.now()
        func()
        return "czas wynosi " + str((datetime.datetime.now() - start))
    return wrapper