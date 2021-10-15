from tkinter import *
import tkinter.font as tkFont
import requests
from PIL import ImageTk, Image


root =Tk()
root.title("coDoKota")
# root.geometry("350x400")
text = ""


def changeText():
    global text
    response = requests.get("https://catfact.ninja/fact?max_length=50")
    textLabel.config(text=response.json()["fact"])

image = Image.open("cat.png")
resize_image = image.resize((300,350))
img = ImageTk.PhotoImage(resize_image)

label1 = Label(image=img)
label1.image = img

button = Button(root, text="Get info",padx=50, command= changeText, bg="#7db2f0",activebackground="#6aa5eb",highlightthickness = 1, bd=0)
fontStyle = tkFont.Font(family="Lucida Grande", size=10)
textLabel = Label(root, text=text, font=fontStyle)

textLabel.grid(row=1)
button.grid(row=2)
label1.grid(row=3)


root.mainloop()


