def help():
    print("start - to start the car ")
    print("stop - to stop the car ")
    print("quit - to exit ")
start=False
while True:
    instruction=input(">").lower()
    if instruction=="start":
        if start==False:
            print("Car started ready to go...")
            start=True
        else:
            print("Car already started...")
        continue
    elif instruction=="stop":
        if start==True:
            start=False
            print("Car stopped")
        else:
            print("Car already stopped")
        continue
    elif instruction=="help":
        help()
        continue
    elif instruction=="quit":
        print("Thanks for playing!!")
        break
    else:
        print("I dont understand, type help to see instruction...")
        continue