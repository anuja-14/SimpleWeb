from bs4 import BeautifulSoup , Tag
import sys
from Tkinter import *
import tkHyperlink
import subprocess

import os

class BrowserWindow:

    

    def __init__(self):
        self.root = Tk()
        self.root.geometry('%sx%s+0+0'% self.root.maxsize() )
        self.textFrame = Frame(self.root)
        self.entryLabel = Label(self.textFrame)
        self.entryLabel["text"] = "Enter the URL"
        self.entryLabel.pack(side = LEFT)

        self.entryWidget = Entry(self.textFrame)
        self.entryWidget["width"] = 50
        self.entryWidget.pack(side=LEFT)
        self.textFrame.pack()
        self.button = Button(self.root, text="Submit", command=self.displayText)
        self.button.pack()


        # TODO : Root menu has to be defined here using some kind of function
        # TODO : Functionality to add tabs whenever new page is opened
        self.w = Text ( self.root , bg="white" , wrap = WORD )
        self.w.grid()
        self.w.pack(side = LEFT , fill = BOTH , expand = YES )
        self.root.title('SiMple Web')
        self.count = 0

    def displayText(self):
        """ Display the Entry text value. """


        if self.entryWidget.get().strip() == "":
            tkMessageBox.showerror("Tkinter Entry Widget", "Enter URL")
        else:
            URL = self.entryWidget.get().strip();
            os.system("./client 7000 localhost " + URL);
            numlines = self.w.index('end - 1 line').split(' . ')[0]
            self.w.delete(1.0 , numlines )
            self.openPage("output.html")




    def openPage (self , file):
        input = open(file , 'r')
        
        doc = input.readlines()
        soup = BeautifulSoup(''.join(doc))
        soup.prettify()
        print soup
        self.root.title = soup.page_title.contents[0]
        tag = soup.page_body
        self.parseDisplay( tag , tag.attrs )

    def parseDisplay ( self , tag , style ):
        #print "-------------------- PARSE DISPLAY LOG ----------------------"
        #print tag
        #print style
        #print "---------------------Parse display log end -------------------"
        for child in tag.children:
            if isinstance( child , Tag ):
                if child.name == 'link' :
                    self.writecontent( child['display'] , child['markref'] , 0 )
                elif child.name == 'image':
                    self.writecontent( child['markref'] , style , -1 )
                elif child.attrs:
                    self.parseDisplay(child , child.attrs)
                else:
                    self.parseDisplay(child , style)
            else:
                self.count = self.count+1
                self.writecontent(child , style , self.count)

    def writecontent(self , msg , style , tagCreationCount ):
        self.w['state']='normal'
        print "-----------------------TKINTER LOG------------------------"
        print msg
        print style
        print "------------------------Tkinter Log Done -----------------"
        if tagCreationCount == 0:
            hyperlink = tkHyperlink.HyperlinkManager(self.w)
            self.w.insert('end' , msg , hyperlink.add(lambda: self.reallinkClick(style)))
            return
        elif tagCreationCount == -1:
           print "Image found. Displaying !!"
           img = PhotoImage ( file = 'Sachin_Ramesh_Tendulkar.gif' )
           self.w.image_create ( 'end' , image = img )
           print "Image created"
           return
        if style:
            try:
                ucolor = style['color']
            except KeyError:
                ucolor = "purple" 
            self.w.tag_configure( tagCreationCount , foreground = ucolor )
            self.w.insert('end' , msg , ( tagCreationCount ) )
        else:
            self.w.insert('end' , msg , ( 'default' ) ) 
            self.w['state']='disabled'


    def linkClick(event):
        print "Link Clicked"

    def start(self):
        self.root.mainloop()

if __name__=="__main__":

    window = BrowserWindow()
    home_page = "markemfiles/index.markem"
  

    window.openPage(home_page)
    window.start()



