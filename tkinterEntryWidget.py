# File name: tkinterEntryWidget.py
# Author: S.Prasanna

from Tkinter import *
import tkMessageBox

def displayText():
    """ Display the Entry text value. """

    global entryWidget

    if entryWidget.get().strip() == "":
        tkMessageBox.showerror("Tkinter Entry Widget", "Enter a text value")
    else:
        tkMessageBox.showinfo("Tkinter Entry Widget", "Text value =" + entryWidget.get().strip()) 

if __name__ == "__main__":

    root = Tk()
    
    root.title("Tkinter Entry Widget")
    root["padx"] = 40
    root["pady"] = 20       

    # Create a text frame to hold the text Label and the Entry widget
    textFrame = Frame(root)
    
    #Create a Label in textFrame
    entryLabel = Label(textFrame)
    entryLabel["text"] = "Enter the text:"
    entryLabel.pack(side=LEFT)

    # Create an Entry Widget in textFrame
    entryWidget = Entry(textFrame)
    entryWidget["width"] = 50
    entryWidget.pack(side=LEFT)

    textFrame.pack()

    button = Button(root, text="Submit", command=displayText)
    button.pack() 
    
    root.mainloop()
